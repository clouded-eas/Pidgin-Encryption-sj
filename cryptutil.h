/*        Misc utility functions for the Pidgin-Encryption plugin         */
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

#ifndef CRYPTUTIL_H
#define CRYPTUTIL_H

#include "debug.h"

#define MSG_HUNK_SIZE 126
#define CRYPT_HUNK_SIZE 256

/* Utility Functions: */

/* Convert a byte array to ascii-encoded character array.                     */
void PE_bytes_to_str(char* str, unsigned char* bytes, int numbytes);

/* Convert a byte array to hex like a5:38:49:...   .                          */
/* returns number of chars in char array.  No null termination!               */
/* int PE_bytes_to_colonstr(unsigned char* hex, unsigned char* bytes, int numbytes); */

/* Convert ascii-encoded bytes in a null terminated char* into a byte array */
unsigned int PE_str_to_bytes(unsigned char* bytes, char* hex);

/* Strip returns from a block encoded string */
GString* PE_strip_returns(GString* s);

/* Zero out a string (use for plaintext before freeing memory) */
void PE_clear_string(char* s);

/* Escape all spaces in name so it can go in a key file */
void PE_escape_name(GString* name);

/* Reverse the previous escaping.  Since it will only get shorter, allow char* */
void PE_unescape_name(char* name);

/* Returns true if the message starts with an HTML link */
gboolean PE_msg_starts_with_link(const char* c);

/* Split a message (hopefully on a space) so we can send it in pieces */
GSList *PE_message_split(char *message, int limit);
#endif
