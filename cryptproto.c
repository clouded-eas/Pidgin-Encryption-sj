/*                    Wrapper for encryption protocols                    */
/*             Copyright (C) 2001-2003 William Tompkins                   */

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

#include <string.h>

#include "cryptproto.h"
#include "keys.h"
#include "cryptutil.h"

/* cryptproto:  an interface to the encryption protocols that we know about. */

GSList*  crypt_proto_list = 0;

/* Find the largest unencrypted message that can fit
   in a given size encrypted msg                                             */
int PE_calc_unencrypted_size(crypt_key* enc_key, crypt_key* sign_key, int size){
   size = (size / 4) * 3; /* for Base 64 */
   /*   size = size / 2;   for binary->ascii encoding */
   size = enc_key->proto->calc_unencrypted_size(enc_key, size);
   size = sign_key->proto->calc_unsigned_size(sign_key, size);
   return size;
}

char* PE_encrypt(char* msg, struct crypt_key* key) {
   unsigned char *encrypted_bin;
   char *out;
   int len;
   
   len = key->proto->encrypt(&encrypted_bin, (unsigned char*)msg, strlen(msg), key);
   out = g_malloc(len*2+1);  /* long enough for even straight hex conversion */
   
   PE_bytes_to_str(out, encrypted_bin, len);

   g_free(encrypted_bin);

   return out;
}

char* PE_decrypt(char* msg, struct crypt_key* key){
   unsigned char *binary;
   unsigned char *decrypted;
   int len = strlen(msg);
   
   binary = g_malloc(len);
   
   len = PE_str_to_bytes(binary, msg);
   
   len = key->proto->decrypt(&decrypted, binary, len, key);
   return (char*)decrypted;
}

void PE_encrypt_signed(char** out, char* msg, struct crypt_key* priv_key,
                       struct crypt_key* pub_key) {
   unsigned char *encrypted_bin, *signed_msg;
   int len;

   len = priv_key->proto->sign(&signed_msg, (unsigned char*)msg, strlen(msg), priv_key, pub_key);
   
   len = pub_key->proto->encrypt(&encrypted_bin, signed_msg, len, pub_key);

   *out = g_malloc(len*2+1);  /* long enough for even straight hex conversion */
   
   PE_bytes_to_str(*out, encrypted_bin, len);

   g_free(encrypted_bin);
   g_free(signed_msg);
}

/* returns length of decrypted/authed message, or <=0 on error                        */
/* on error, authed may contain a message ID                                          */
                    
int PE_decrypt_signed(char** authed, char* msg, struct crypt_key* priv_key,
                      struct crypt_key* pub_key, const char* name) {

   unsigned char *binary, *decrypted;
   int len = strlen(msg);

   *authed = 0;
   binary = g_malloc(len);
   
   len = PE_str_to_bytes(binary, msg);
   
   len = pub_key->proto->decrypt(&decrypted, binary, len, priv_key);

   if (len > 0) {
      len = priv_key->proto->auth((unsigned char**)authed, decrypted, len, pub_key, name);   
      g_free(decrypted);
   }

   g_free(binary);

   return len;
}      

GString* PE_key_to_gstr(struct crypt_key* key) {
   return key->proto->key_to_gstr(key);
}

gchar* PE_make_key_id(struct crypt_key* key) {
   return key->proto->make_key_id(key);
}

GString* PE_make_sendable_key(struct crypt_key* key, const char* name){
   return key->proto->make_sendable_key(key, name);
}

void PE_free_key(struct crypt_key* key) {
   key->proto->free(key);
}
