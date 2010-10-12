/*                   Gaim encryption plugin                               */
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

#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <time.h>

#ifndef NO_CONFIG
#include "pidgin-encryption-config.h"
#endif

#include <conversation.h>
#define ENC_WEBSITE "http://pidgin-encrypt.sourceforge.net"

#define CRYPTO_SMILEY "PECRYPT:"
#define CRYPTO_SMILEY_LEN (sizeof(CRYPTO_SMILEY)-1)

typedef struct PE_SentMessage
{
   time_t time;
   gchar* id;
   gchar* msg;
} PE_SentMessage;


void PE_send_stored_msgs(PurpleAccount*, const char *who);
void PE_delete_stored_msgs(PurpleAccount*, const char *who);
void PE_show_stored_msgs(PurpleAccount*, const char* who);
void PE_resend_msg(PurpleAccount*, const char* who, gchar*);

#endif
