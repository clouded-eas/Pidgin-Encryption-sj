/*             Nonces for the Pidgin encryption plugin                      */
/*            Copyright (C) 2001-2003 William Tompkins                    */

/* This plugin is free software, distributed under the GNU General Public */
/* License.                                                               */
/* Please see the file "COPYING" distributed with this source code        */
/* for more details                                                       */
/*                                                                        */
/*                                                                        */
/*    This software is distributed in the hope that it will be useful,    */
/*   but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    */
/*   General Public License for more details.                             */

/*   To compile and use:                                                  */
/*     See INSTALL file.                                                  */

#include "internal.h"

#include <glib.h>

#include "debug.h"

#include "base64.h"
#include "pk11func.h"

#include "nonce.h"


static GHashTable *incoming_nonces;

static const int MaxNonceIncr = 20;

void PE_nonce_map_init() {
   incoming_nonces = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
}

int PE_nonce_str_len() {
   return (sizeof(Nonce) * 4 / 3);
}

void PE_incr_nonce(Nonce* nonce) {
   int i = sizeof(Nonce);
   unsigned char carry = 1;

   while (carry && i > 0) {
      ++((*nonce)[--i]);
      carry = (nonce[i] == 0);
   }
}

gchar* PE_nonce_to_str(Nonce* nonce) {
   char * tmp = BTOA_DataToAscii(*nonce, sizeof(Nonce));
   gchar* out = g_strdup(tmp);

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Built Nonce:%u:%s\n", (unsigned)sizeof(Nonce), tmp);

   PORT_Free(tmp);
   return out;
}

/* Intentionally un-optimized compare: should take constant time no matter */
/* where nonces may differ.                                                */

static int nonce_cmp(Nonce* n1, Nonce* n2) {
   int retval = 0;
   int i;
   for (i = 0; i < sizeof(Nonce); ++i) {
      if ((*n1)[i] != (*n2)[i]) retval = 1;
   }
   
   return retval;
}


void PE_str_to_nonce(Nonce* nonce, char* nonce_str) {
   unsigned int tmp_len;
   unsigned char* tmp_bin;

   tmp_bin = ATOB_AsciiToData(nonce_str, &tmp_len);
   if (tmp_len != sizeof(Nonce)) {
      PORT_Free(tmp_bin);
      memset(nonce, 0, sizeof(Nonce));
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error parsing RSANSS nonce\n");
      return;
   }
   memcpy(nonce, tmp_bin, sizeof(Nonce));
   
   PORT_Free(tmp_bin);
}

gchar* PE_new_incoming_nonce(const char* name) {
   Nonce *nonce = g_malloc(sizeof(Nonce));

   SECStatus rv = PK11_GenerateRandom(*nonce, sizeof(Nonce));
   g_assert(rv == SECSuccess);

   g_hash_table_replace(incoming_nonces, g_strdup(name), nonce);   

   return PE_nonce_to_str(nonce);
}

int PE_check_incoming_nonce(const char* name, char* nonce_str) {
   Nonce new_nonce;
   Nonce* orig_nonce = g_hash_table_lookup(incoming_nonces, name);
   Nonce try_nonce;
   int i;
   
   /* purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Nonce Check start\n"); */

   if (orig_nonce == 0) return 0;

   memcpy(&try_nonce, orig_nonce, sizeof(Nonce));
   
   PE_str_to_nonce(&new_nonce, nonce_str);
   
   for (i = 0; i < MaxNonceIncr; ++i) {
      if (nonce_cmp(&new_nonce, &try_nonce) == 0) {
         memcpy(orig_nonce, &try_nonce, sizeof(Nonce));
         PE_incr_nonce(orig_nonce);
         return 1;
      }
      PE_incr_nonce(&try_nonce);
   }
   
   return 0;
}

