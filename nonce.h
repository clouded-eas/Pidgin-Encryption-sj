/*             Nonces for the Pidgin-Encryption plugin                    */
/*            Copyright (C) 2001-2007 William Tompkins                    */

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

#ifndef NONCE_H
#define NONCE_H

#include "glib.h"

typedef unsigned char Nonce[24];

void PE_nonce_map_init();

void PE_str_to_nonce(Nonce* nonce, char* nonce_str);
gchar* PE_nonce_to_str(Nonce* nonce);

void PE_incr_nonce(Nonce* nonce);

gchar* PE_new_incoming_nonce(const char* name);
int PE_check_incoming_nonce(const char* name, char* nonce_str);

int PE_nonce_str_len();

#endif
