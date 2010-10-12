/*                    Pidgin encryption plugin                            */
/*             Copyright (C) 2001-2007 William Tompkins                   */

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

#define PURPLE_PLUGINS

#include "internal.h"

#include "pidgin-encryption-config.h"

#include <gdk/gdk.h>
#include <gtk/gtkplug.h>

#include <debug.h>
#include <core.h>
#include <gtkutils.h>
#include <gtkplugin.h>
#include <gtkconv.h>
#include <gtkdialogs.h>
#include <gtkprefs.h>
#include <blist.h>
#include <gtkblist.h>
#include <gtkimhtml.h>
#include <gtklog.h>
#include <signals.h>
#include <util.h>
#include <version.h>

#include "cryptproto.h"
#include "cryptutil.h"
#include "state.h"
#include "state_ui.h"
#include "keys.h"
#include "nonce.h"
#include "prefs.h"
#include "config_ui.h"
#include "pe_blist.h"

#include "encrypt.h"
#include "nls.h"

#include <time.h>
#include <sys/types.h>
#ifndef _WIN32
  #include <sys/time.h>
#endif
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#endif

#ifdef _WIN32
#include "win32dep.h"
#endif


/* from Purple's internal.h, but it isn't critical that it is in sync: */
#define PE_BUF_LONG 4096

G_MODULE_IMPORT GSList *purple_accounts;
G_MODULE_IMPORT guint im_options;


#define ENCRYPT_PLUGIN_ID "gtk-obobo-pidgin-encryption"

/* Types */
struct msg_node {
   char who[64];
   time_t time;
   PurpleConnection* gc;
   struct msg_node* next;
   char msg[1];
};
typedef struct msg_node msg_node;


static PurplePlugin *PE_plugin_handle;
static guint PE_pref_callback_id;

/* Outgoing message queue (waiting on a public key to encrypt) */
static msg_node* first_out_msg = 0;
static msg_node* last_out_msg = 0;

/* Incoming message queue (waiting on a public key to verify) */
static msg_node* first_inc_msg = 0;
static msg_node* last_inc_msg = 0;

static int PE_get_msg_size_limit(PurpleAccount*);
static void PE_send_key(PurpleAccount *, const char *name, int, char*);
static crypt_key * PE_get_key(PurpleConnection *, const char *name);
static int decrypt_msg(char **decrypted, char *msg,
                       const char *name, crypt_key *, crypt_key *);
static void PE_store_msg(const char *name, PurpleConnection*, char *,
                         msg_node**, msg_node**);
static void got_encrypted_msg(PurpleConnection *, const char *name, char **);

static void reap_all_sent_messages(PurpleConversation*);
static void reap_old_sent_messages(PurpleConversation*);

/* Function pointers exported to Purple */
static gboolean PE_got_msg_cb(PurpleAccount *, char **, char **, PurpleConversation *conv, int* flags);
static void PE_send_msg_cb(PurpleAccount *, char *, char **, void *);
static void PE_new_conv_cb(PurpleConversation *, void *);
static void PE_del_conv_cb(PurpleConversation *, void *);
static void PE_updated_conv_cb(PurpleConversation *, void *);

/* legacy... we try to use HTML in some of our headers- format is protocol dependent */
static GHashTable *header_table, *footer_table, *notify_table;
static gchar* header_default;  /* the non-HTML default header */

static gchar* header_broken;   /* if a server is stripping HTML and we're using it */
                               /* in our header, we'll see this                    */
static GHashTable *broken_users;  /* keeps track of who is seeing broken HTML */

static char * unrequited_capable_who = 0;  /* if we learn that someone is capable, but don't have */
                                           /* a conv for them yet, we set this to be them         */

/* A field for the LibPurple conversation "data" hashmap to indicate that we want to use non-html */
#define BROKEN_HTML "Encrypt-HTMLBroken"

static void strip_crypto_smiley(char* s) {
   char * pos;
   
   while ( (pos = strstr(s, CRYPTO_SMILEY)) != 0 ) {
      memmove(pos, pos + CRYPTO_SMILEY_LEN, strlen(pos + CRYPTO_SMILEY_LEN)+1);
   }
}

/* Send key to other side.  If msg_id is non-null, we include a request to re-send */
/* a certain message, as well.                                                     */

static void PE_send_key(PurpleAccount *acct, const char *name, int asError, gchar *msg_id) {
   /* load key somehow */
   char *msg;
   GString *key_str;
   crypt_key *pub_key;
   PurpleConversation *conv;
   int conv_breaks_html = 0;

   int header_size, footer_size;
   const gchar* header = g_hash_table_lookup(header_table, purple_account_get_protocol_id(acct));
   const gchar* footer = g_hash_table_lookup(footer_table, purple_account_get_protocol_id(acct));

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "send_key: %s\n", acct->username);
   
   conv = purple_find_conversation_with_account(PURPLE_CONV_TYPE_IM, name, acct);
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "send_key: %s, %p, %s\n", name, conv, acct->username);

   if (g_hash_table_lookup(broken_users, name)) {
      conv_breaks_html = 1;
   }

   if (!header || conv_breaks_html) header = header_default;
   if (!footer || conv_breaks_html) footer = "";

   header_size = strlen(header);
   footer_size = strlen(footer);

   pub_key = PE_find_own_key_by_name(&PE_my_pub_ring, acct->username, acct, conv);
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "send_key2: %s\n", acct->username);
   if (!pub_key) return;

   key_str = PE_make_sendable_key(pub_key, name);
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "send_key3: %s\n", acct->username);

   msg = alloca(header_size + footer_size + key_str->len + 100);
   if (msg == 0) return;
   if (asError) {
      if (msg_id) {
         sprintf(msg, "%s: ErrKey: Prot %s: Len %d:%sResend:%s:%s", header,
                 pub_key->proto->name, (int)key_str->len, key_str->str, msg_id, footer);
      } else {
         sprintf(msg, "%s: ErrKey: Prot %s: Len %d:%s%s", header,
                 pub_key->proto->name, (int)key_str->len, key_str->str, footer);
      }
   } else {
      sprintf(msg, "%s: Key: Prot %s: Len %d:%s%s", header,
              pub_key->proto->name, (int)key_str->len, key_str->str, footer);
   }

   if (strlen(msg) > PE_get_msg_size_limit(acct)) {
      purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Key too big to send in message (%u > %d)\n", 
                   (unsigned)strlen(msg), PE_get_msg_size_limit(acct));
      conv = purple_find_conversation_with_account(PURPLE_CONV_TYPE_IM, name, acct);
      if (conv == NULL) {
         conv = purple_conversation_new(PURPLE_CONV_TYPE_IM, acct, name);
      }
      purple_conversation_write(conv, 0,
                              _("This account key is too large for this protocol. "
                                "Unable to send."),
                              PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));
      return;
   }

   serv_send_im(acct->gc, name, msg, 0);
   g_string_free(key_str, TRUE);
}

static crypt_key *PE_get_key(PurpleConnection *gc, const char *name) {
   crypt_key *bkey;

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "get_key: %s\n", name);
   bkey = PE_find_key_by_name(PE_buddy_ring, name, gc->account);
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "got key: %p\n", bkey);

   if( bkey == 0 ) {
      char* tmpmsg;
      
      int header_size, footer_size;
      const gchar* header = g_hash_table_lookup(header_table, purple_account_get_protocol_id(gc->account));
      const gchar* footer = g_hash_table_lookup(footer_table, purple_account_get_protocol_id(gc->account));
      int conv_breaks_html = 0;

      if (g_hash_table_lookup(broken_users, name)) {
         conv_breaks_html = 1;
      }
      if (g_hash_table_lookup(broken_users, name)) {
         conv_breaks_html = 1;
      }
   
      
      if (!header || conv_breaks_html) header = header_default;
      if (!footer || conv_breaks_html) footer = "";
      
      header_size = strlen(header);
      footer_size = strlen(footer);

      tmpmsg = alloca(header_size + footer_size +
                      sizeof (": Send Key")); // sizeof() gets the trailing null too

      sprintf(tmpmsg, "%s%s%s", header, ": Send Key", footer);

      purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Sending: %s\n", tmpmsg);
      serv_send_im(gc, name, tmpmsg, 0);
      return 0;
   }

   return bkey;
}


static int decrypt_msg(char **decrypted, char *msg, const char *name, 
                       crypt_key *priv_key, crypt_key *pub_key) {
   int realstart = 0;
	unsigned int length;
   int len;
   char* decrypted_no_header = 0;
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "decrypt_msg\n");

   *decrypted = 0;
   if ( (sscanf(msg, ": Len %u:%n", &length, &realstart) < 1) || (realstart == 0)) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Garbled length in decrypt\n");
      return -1;
   }

   msg += realstart;

   if (strlen(msg) < length) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Length doesn't match in decrypt\n");
      return -1;
   }
   msg[length] = 0;
   
   len = PE_decrypt_signed(&decrypted_no_header, msg, priv_key, pub_key, name);

   if (len <= 0 || decrypted_no_header == 0) {
      return -1;
   }
   strip_crypto_smiley(decrypted_no_header);   

   if (purple_prefs_get_bool("/plugins/gtk/encrypt/show_inline_icons")) {
      if (decrypted_no_header[0] == '/') {
         gchar** slashsplit = g_strsplit(decrypted_no_header, " ", 2);
         *decrypted = g_strconcat(slashsplit[0], " ", CRYPTO_SMILEY, " ", slashsplit[1], NULL);
         g_strfreev(slashsplit);
         g_free(decrypted_no_header);
      } else {
         *decrypted = g_strconcat(CRYPTO_SMILEY, " ", decrypted_no_header, NULL);
         g_free(decrypted_no_header);
      }

      return len + CRYPTO_SMILEY_LEN + 1; /* plus 1 from space after smiley */

   } else {
      /* not showing inline icons */
      *decrypted = decrypted_no_header;
      return len;
   }
}


static void PE_store_msg(const char *who, PurpleConnection *gc, char *msg, msg_node** first_node,
               msg_node** last_node) {
   msg_node* newnode;
   

   newnode = g_malloc(sizeof(msg_node) + strlen(msg));
   
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "store_msg: %p : %s\n", newnode, who);

   strncpy(newnode->who, purple_normalize(gc->account, who), sizeof(newnode->who));
   newnode->who[sizeof(newnode->who)-1] = 0;

   newnode->gc = gc;
   newnode->time = time((time_t)NULL);
   strcpy(newnode->msg, msg);
   newnode->next = 0;

   
   if (*first_node == 0) {
      *last_node = newnode;
      *first_node = newnode;
   } else {
      (*last_node)->next = newnode;
      *last_node = newnode;
   }

   for (newnode = *first_node; newnode != *last_node; newnode = newnode->next) {
      purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "   In store stack: %p, %s\n",
                 newnode, newnode->who);
   }
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "   In store stack: %p, %s\n",
              *last_node, (*last_node)->who);
}

void PE_send_stored_msgs(PurpleAccount* acct, const char* who) {
   msg_node* node = first_out_msg;
   msg_node* prev = 0;
   char *tmp_msg;

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "send_stored_msgs\n");

   while (node != 0) {
      purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
                 "Looking for stored msg:%s:%s\n",node->who, who);
      if ((strcmp(node->who, who) == 0) && (node->gc->account == acct)) {
         tmp_msg = g_strdup(node->msg);
         PE_send_msg_cb(node->gc->account, (char*)who, &tmp_msg, 0);
         PE_clear_string(node->msg);
         if (tmp_msg != 0) {
            g_free(tmp_msg);
         }
         if (node == last_out_msg) {
            last_out_msg = prev;
         }
         if (prev != 0) { /* a random one matched */
            prev->next = node->next;
            g_free(node);
            node = prev->next;
         } else {  /* the first one matched */
            first_out_msg = node->next;
            g_free(node);
            node = first_out_msg;
         }
      } else { /* didn't match */
         prev = node;
         node = node->next;
      }
   }
}

void PE_delete_stored_msgs(PurpleAccount* acct, const char* who) {
   msg_node* node = first_out_msg;
   msg_node* prev = 0;

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "delete_stored_msgs\n");

   while (node != 0) {
      purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
                 "Looking for stored msg:%s:%s\n",node->who, who);
      if ((strcmp(node->who, who) == 0) && (node->gc->account == acct)) {
         PE_clear_string(node->msg);
         if (node == last_out_msg) {
            last_out_msg = prev;
         }
         if (prev != 0) { /* a random one matched */
            prev->next = node->next;
            g_free(node);
            node = prev->next;
         } else {  /* the first one matched */
            first_out_msg = node->next;
            g_free(node);
            node = first_out_msg;
         }
      } else { /* didn't match */
         prev = node;
         node = node->next;
      }
   }
}

void PE_show_stored_msgs(PurpleAccount*acct, const char* who) {
   msg_node* node = first_inc_msg;
   msg_node* prev = 0;
   char *tmp_msg;

   PurpleConversation *conv;
   
   while (node != 0) {
      purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "show_stored_msgs:%p:%s:%s:\n", node, node->who, who);
		if (strcmp(node->who, who) == 0) {
         tmp_msg = g_strdup(node->msg);
         got_encrypted_msg(node->gc, who, &tmp_msg);
         if (tmp_msg != 0) {
            purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "showing msg:%s\n", tmp_msg);

            conv = purple_find_conversation_with_account(PURPLE_CONV_TYPE_IM, who, acct);

            // let gtkconv (and others) know that we're about to display a message, so
            // this is their chance to thwart it, or change the window, or...
            purple_signal_emit(purple_conversations_get_handle(), "received-im-msg", acct,
                             who, tmp_msg, conv, PURPLE_MESSAGE_RECV);

            // the conv may have been updated with that signal, so fetch it again
            conv = purple_find_conversation_with_account(PURPLE_CONV_TYPE_IM, who, acct);

            if (!conv) {
               conv = purple_conversation_new(PURPLE_CONV_TYPE_IM, node->gc->account, who);
            }

            purple_conv_im_write(PURPLE_CONV_IM(conv), NULL, tmp_msg,
                               PURPLE_MESSAGE_RECV, time((time_t)NULL));
            
            g_free(tmp_msg);

            /* we might have just created the conversation, and now we're displaying an  */
            /* encrypted message.  So... make sure we've got all the trappings, and then */
            /* set the various indicators                                                */

            PE_updated_conv_cb(conv, 0);
            PE_set_capable(conv, TRUE);
            if (purple_prefs_get_bool("/plugins/gtk/encrypt/encrypt_response")) {
               PE_set_tx_encryption(conv, TRUE);
            }
            PE_set_rx_encryption(conv, TRUE);               

         }
         if (node == last_inc_msg) {
            last_inc_msg = prev;
         }
         if (prev != 0) { /* a random one matched */
            prev->next = node->next;
            g_free(node);
            node = prev->next;
         } else {  /* the first one matched */
            first_inc_msg = node->next;
            g_free(node);
            node = first_inc_msg;
         }
      } else { /* didn't match */
         prev = node;
         node = node->next;
      }
   }
}

static void reap_all_sent_messages(PurpleConversation* conv){

   GQueue *sent_msg_queue = g_hash_table_lookup(conv->data, "sent messages");

   PE_SentMessage *sent_msg_item;

   /* purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "ZZZ Reaping all messages: %p\n", conv); */
   
   while (!g_queue_is_empty(sent_msg_queue)) {
      sent_msg_item = g_queue_pop_tail(sent_msg_queue);
      /* purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "ZZZ Message: %s\n", sent_msg_item->id); */
      g_free(sent_msg_item->id);
      g_free(sent_msg_item->msg);
      g_free(sent_msg_item);
   }
}

static void reap_old_sent_messages(PurpleConversation* conv){
   GQueue *sent_msg_queue = g_hash_table_lookup(conv->data, "sent messages");
   
   PE_SentMessage *sent_msg_item;
   time_t curtime = time(0);
   
   /* purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "ZZZ Reaping old messages: %p\n", conv); */

   while (!g_queue_is_empty(sent_msg_queue)) {
      sent_msg_item = g_queue_peek_tail(sent_msg_queue);
      /* purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "ZZZ Message: %s\n", sent_msg_item->id); */
      if (curtime - sent_msg_item->time > 60) { /* message is over 1 minute old */
         sent_msg_item = g_queue_pop_tail(sent_msg_queue);
         /* purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "ZZZ  Deleted\n"); */
         g_free(sent_msg_item->id);
         g_free(sent_msg_item->msg);
         g_free(sent_msg_item);
      } else {
         /* These were pushed on in order, so if this one is not old, we're done */
         break;
      }
   }
}

static gboolean PE_got_msg_cb(PurpleAccount *acct, char **who, char **message,
                              PurpleConversation *conv, int *flags) {
   char *name;

   gchar *headerpos;    /* Header is allowed to be anywhere in message now */
   gchar *notifypos = 0;
   gchar *caps_header, *caps_message,    /* temps for ascii_strup() versions of each */
         *caps_notify;                   /* since Jabber mucks with case             */

   gchar *boldAsterixPos;                /* position of <b>*</b>-substituted header */
   gchar *debianHeaderPos;               /* position of Debian-specific header */
   gchar *unescaped_message;             /* temps for html_unescaped       */
                                         /* since ICQ will now escape HTML */

   int header_size, footer_size;
   const gchar* header = g_hash_table_lookup(header_table, purple_account_get_protocol_id(acct));
   const gchar* footer = g_hash_table_lookup(footer_table, purple_account_get_protocol_id(acct));
   const gchar* notify = g_hash_table_lookup(notify_table, purple_account_get_protocol_id(acct));

   if (!header) header = header_default;
   if (!footer) footer = "";

   header_size = strlen(header);
   footer_size = strlen(footer);

   /* Since we don't have a periodic callback, we do some housekeeping here */
   purple_conversation_foreach(reap_old_sent_messages);
   
   name = g_strdup(purple_normalize(acct, *who));
   
   if (*message != NULL) {
      /* More header madness: Debian patched the headers to start with
         "--- Encrypted with the ...", to fix the issue that sometimes
         "***" is being replaced with <b>*</b>.  So... replace either that
         we see, to canonicalize the message */

      /* also make message all caps... */
      caps_message = g_ascii_strup(*message, -1);
      caps_header = g_ascii_strup(header, -1);

      boldAsterixPos = strstr(caps_message, "<B>*</B> ENCRYPTED WITH THE GAIM-ENCRYPTION PLUGIN");
      if (boldAsterixPos) {
          memcpy(boldAsterixPos, "     ***", 8);
      }

      debianHeaderPos = strstr(caps_message, "--- ENCRYPTED WITH THE GAIM-ENCRYPTION PLUGIN");

      if (debianHeaderPos) {
          memcpy(debianHeaderPos, "***", 3);
      }

      headerpos = strstr(caps_message, caps_header);
      g_free(caps_header);

      if (headerpos == 0 && notify) {
         caps_notify = g_ascii_strup(notify, -1);
         notifypos = strstr(caps_message, caps_notify);
         g_free(caps_notify);
      } else {
         notifypos = 0;
      }
      if (headerpos != 0) {
         /* adjust to where the header is in the _real_ message, if */
         /* we found it in the caps_message                         */
         headerpos += (*message) - caps_message;
      }

      if (notifypos != 0) {
         /* ditto for the notification header */
         notifypos += (*message) - caps_message;
      }

      g_free(caps_message);

      if (headerpos == 0 && notifypos == 0) {
         unescaped_message = purple_unescape_html(*message);
         /* Check for ICQ-escaped header*/
         headerpos = strstr(unescaped_message, header);
         if (headerpos == 0 && notify) {
            notifypos = strstr(unescaped_message, notify);
         }
         if (headerpos != 0 || notifypos != 0) {
            /* ICQ PRPL escaped our HTML header, but we outsmarted it     */
            /* replace message with unescaped message.                    */
            purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                         "Escaped header: replacing %s with %s\n",
                       *message, unescaped_message);
            g_free(*message);
            *message = unescaped_message;
         } else {
            g_free(unescaped_message);
         }
      }

      if (headerpos == 0 && notifypos == 0) {
         /* check for a header that has had the HTML ripped out. */
         if (strstr(*message, header_broken)) {
            /* mark this name as having broken HTML, so we send appropriately */
            g_hash_table_insert(broken_users, g_strdup(name), (gpointer)TRUE);
            /* send key to other side as an error condition */
            PE_send_key(acct, name, 1, 0);
            (*message)[0] = 0;
            g_free(*message);
            *message = NULL;
            purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                         "Broken HTML header found, asking for key\n");
            
            // Bail early, since we short-circuited the logic below
            g_free(name);
            return FALSE;
         }
      }

      if (headerpos == 0 && header != header_default){
         /* look for a default header, in case other side has decided that html is broken */
         headerpos = strstr(*message, header_default);
         if (headerpos) {
            purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                         "Found default header when expecting proto-specific one\n");
            header_size = strlen(header_default);
            footer_size = 0;

            /* mark this conv as having broken HTML, so we send appropriately */
            g_hash_table_insert(broken_users, g_strdup(name), (gpointer)TRUE);
         }
      }

      /* Whew.  Enough of this header-finding.  */
      
      if (headerpos != 0) {
         PE_set_capable(conv, TRUE);
         if (purple_prefs_get_bool("/plugins/gtk/encrypt/encrypt_response")) {
            PE_set_tx_encryption(conv, TRUE);
         }
         if (strncmp(headerpos + header_size, ": Send Key",
                     sizeof(": Send Key")-1) == 0) {
            PE_send_key(acct, name, 0, 0);
            (*message)[0] = 0;
            g_free(*message);
            *message = NULL;
            purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Sent key per request\n");
         } else if (strncmp(headerpos + header_size, ": Key",
                            sizeof(": Key") - 1) == 0) {
               purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Got key\n");
               PE_received_key(headerpos + header_size + sizeof(": Key") - 1, name, acct,
                               conv, message);
         } else if (strncmp(headerpos + header_size, ": ErrKey",
                            sizeof(": ErrKey") - 1) == 0) {
            purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Got key in response to error\n");
            purple_conversation_write(conv, 0,
                                      _("Last outgoing message not received properly- resetting"),
                                      PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));
            
            PE_received_key(headerpos + header_size + sizeof(": ErrKey") - 1, name, acct,
                            conv, message);
         } else if (strncmp(headerpos + header_size, ": Msg",
                            sizeof(": Msg") - 1) == 0){
            purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                         "Got encrypted message: %u\n", (unsigned)strlen(*message)); 
            purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
                         "Message is:%s:\n", *message);
            memmove(*message, headerpos + header_size + sizeof(": Msg") - 1,
                    strlen(headerpos + header_size + sizeof(": Msg") -1)+1);
            got_encrypted_msg(acct->gc, name, message);
            PE_set_rx_encryption(conv, TRUE);
         } else {
            purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption",
                         "Invalid Pidgin-Encryption packet type\n"); 
         }
      } else if (notifypos != 0) {
         PE_set_rx_encryption(conv, FALSE);
         if (conv) {
            PE_set_capable(conv, TRUE);
            if (purple_prefs_get_bool("/plugins/gtk/encrypt/encrypt_if_notified")) {
               PE_set_tx_encryption(conv, TRUE);
            }
         } else {
            /* remember who this was.  If the next new conversation event is for */
            /* the same guy, we'll set as capable then */
            if (unrequited_capable_who) {
               g_free(unrequited_capable_who);
            }
            unrequited_capable_who = g_strdup(*who);
         }
         /* remove the notification HTML so it doesn't pollute the logs */
         memmove(notifypos, notifypos+strlen(notify),
                 strlen(notifypos+strlen(notify))+1); /* +1 to include null */
         strip_crypto_smiley(*message);
      } else {  /* No encrypt-o-header */
         PE_set_rx_encryption(conv, FALSE);
         purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "No header: %s\n", *message);
         purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                      "Proto '%s', header should be: %s\n", purple_account_get_protocol_id(acct), header);
         strip_crypto_smiley(*message);
      }
   }
   
   g_free(name);

	if (*message) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

static void got_encrypted_msg(PurpleConnection *gc, const char* name, char **message){
   unsigned char send_key_sum[KEY_DIGEST_LENGTH], recv_key_sum[KEY_DIGEST_LENGTH];
   char *tmp_msg=0;
   crypt_key *priv_key, *pub_key;
   int msg_pos = 0;
   PurpleConversation* conv;

   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "got_encrypted_msg\n");

   if ( (sscanf(*message, ": S%10c: R%10c%n", send_key_sum, recv_key_sum, &msg_pos) < 2) ||
        (msg_pos == 0) ) {
      purple_debug(PURPLE_DEBUG_WARNING, "pidgin-encryption", "Garbled msg header\n");
      return;
   }

   priv_key = PE_find_key_by_name(PE_my_priv_ring, gc->account->username, gc->account);
   pub_key = PE_get_key(gc, name);
   
   if (strncmp((char*)priv_key->digest, (char*)recv_key_sum, KEY_DIGEST_LENGTH) != 0) {
      /*  Someone sent us a message, but didn't use our correct public key */
      PE_send_key(gc->account, name, 1, 0);
      purple_debug(PURPLE_DEBUG_WARNING, "pidgin-encryption", 
                 "Digests aren't same: {%*s} and {%*s}\n",
                 KEY_DIGEST_LENGTH, priv_key->digest,
                 KEY_DIGEST_LENGTH, recv_key_sum);
      conv = purple_find_conversation_with_account(PURPLE_CONV_TYPE_IM, name, gc->account);
      if (conv != 0) {
         purple_conversation_write(conv, 0,
                                 _("Received message encrypted with wrong key"),
                                 PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));

      } else {
         purple_debug(PURPLE_DEBUG_WARNING, "pidgin-encryption",
                    "Received msg with wrong key, "
                    "but can't write err msg to conv: %s\n", name);
      }
      g_free(*message);
      *message = NULL;
      return;
   }
   
   if (pub_key && (strncmp((char*)pub_key->digest, (char*)send_key_sum, KEY_DIGEST_LENGTH) != 0)) {
      /* We have a key for this guy, but the digest didn't match.  Store the message */
      /* and ask for a new key */
      PE_del_key_from_ring(PE_buddy_ring, name, gc->account);
      pub_key = PE_get_key(gc, name); /* will be 0 now */
   }
   
   if (pub_key == 0) {
      purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "g_e_m: Storing message on Show stack\n");
      PE_store_msg(name, gc, *message, &first_inc_msg, &last_inc_msg);
      g_free(*message);
      *message = NULL;
      return;
   }
   
   memmove(*message, *message + msg_pos, strlen(*message + msg_pos) + 1);

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "attempting decrypt on '%s'\n", *message);

   if (decrypt_msg(&tmp_msg, *message, name, priv_key, pub_key) < 0) {     
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error in decrypt\n");
      conv = purple_find_conversation_with_account(PURPLE_CONV_TYPE_IM, name, gc->account);
      if (conv != 0) {
         purple_conversation_write(conv, 0,
                                 _("Error in decryption- asking for resend..."),
                                 PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));

      } else {
         purple_debug(PURPLE_DEBUG_WARNING, "pidgin-encryption",
                    "Asking for resend, but can't write err msg to conv: %s\n", name);
      }
      PE_send_key(gc->account, name, 1, tmp_msg);
      g_free(*message);
      if (tmp_msg) g_free(tmp_msg);
      *message = NULL;     
      return;
   }
   
   /* Successful Decryption */

   /* Note- we're feeding purple an arbitrarily formed message, which could
      potentially have lots of nasty control characters and stuff.  But, that
      has been tested, and at present, at least, Purple won't barf on any
      characters that we give it.

      As an aside- Purple does now use g_convert() to convert to UTF-8 from
      other character streams.  If we wanted to be all i18n, we could
      do the same, and even include the encoding type with the message.
      We're not all that, at least not yet.
   */
      
   /* Why the extra space (and the extra buffered copy)?  Well, the  *
    * purple server.c code does this, and having the extra space seems *
    * to prevent at least one possible type of crash.  Pretty scary. */

   g_free(*message);
   *message = g_malloc(MAX(strlen(tmp_msg) + 1, PE_BUF_LONG));
   strcpy(*message, tmp_msg);
   g_free(tmp_msg);

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Msg rcv:'%s'\n", *message);
}

/* Get account-specific message size limit*/

static int PE_get_msg_size_limit(PurpleAccount *acct) {
   const char* protocol_id = purple_account_get_protocol_id(acct);

   if (strcmp(protocol_id, "prpl-yahoo") == 0) {
      return 945;
   } else if (strcmp(protocol_id, "prpl-msn") == 0) {
      return 1500; /* This may be too small... somewhere in the 1500-1600 (+ html on front/back) */
   } else {
      /* Well, ok, this isn't too exciting.  Someday we can actually check  */
      /* to see what the real limits are.  For now, 2500 works for everyone */
      /* but Yahoo.                                                         */
      return 2500;
   }
}      

static void PE_send_msg_cb(PurpleAccount *acct, char *who, char **message, void* data) {
   char *out_msg, *crypt_msg = 0;
   char *dupname = g_strdup(purple_normalize(acct, who));

   int msgsize;
   const char msg_format[] = "%s: Msg:S%.10s:R%.10s: Len %d:%s%s";
   PurpleConversation *conv = purple_find_conversation_with_account(PURPLE_CONV_TYPE_IM, who, acct);
   crypt_key *our_key, *his_key;
   GSList *cur_msg;
   GQueue *sent_msg_queue;
   PE_SentMessage *sent_msg_item;

   int unencrypted_size_limit, msg_size_limit;
   int baggage_size;
   char baggage[PE_BUF_LONG];

   const gchar* header = g_hash_table_lookup(header_table, purple_account_get_protocol_id(acct));
   const gchar* footer = g_hash_table_lookup(footer_table, purple_account_get_protocol_id(acct));
   const gchar* notify = g_hash_table_lookup(notify_table, purple_account_get_protocol_id(acct));

   int conv_breaks_html = 0;
   
   if (g_hash_table_lookup(broken_users, dupname)) {
      conv_breaks_html = 1;
   }
   
   if (!header || conv_breaks_html) header = header_default;
   if (!footer || conv_breaks_html) footer = "";
   
   msg_size_limit = PE_get_msg_size_limit(acct);

   /* who: name that you are sending to */
   /* gc->username: your name           */

   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "send_msg: %s\n", who);

   /* Since we don't have a periodic callback, we do some housekeeping here */
   purple_conversation_foreach(reap_old_sent_messages);

   /* Message might have been eaten by another plugin: */
   if ((message == NULL) || (*message == NULL)) {
      g_free(dupname);
      return;
   }

   if (conv == NULL) {
      conv = purple_conversation_new(PURPLE_CONV_TYPE_IM, acct, who);
   }

   if (PE_get_tx_encryption(conv) == FALSE) {
      if (notify && purple_prefs_get_bool("/plugins/gtk/encrypt/broadcast_notify")
          && !PE_has_been_notified(conv)) {
         PE_set_notified(conv, TRUE);
         if (PE_msg_starts_with_link(*message) == TRUE) {
            /* This is a hack- AOL's client has a bug in the html parsing
               so that adjacent links (like <a href="a"></a><a href="b"></a>)
               get concatenated (into <a href="ab"></a>).  So we insert a
               space if the first thing in the message is a link.
            */
            out_msg = g_strconcat(notify, " ", *message, NULL);
         } else {
            out_msg = g_strconcat(notify, *message, NULL);
         }
         g_free(*message);
         *message = out_msg;
      }
      purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Outgoing Msg::%s::\n", *message);
      g_free(dupname);
      return;
   }

   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "send_msg B: %s, %p, %p, %p\n",
              who, &PE_my_priv_ring, acct, conv);

   our_key = PE_find_own_key_by_name(&PE_my_priv_ring, acct->username, acct, conv);
   
   if (!our_key) {
      *message[0] = 0; /* Nuke message so it doesn't look like it was sent.       */
                      /* find_own_key (above) will have displayed error messages */
		purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "leaving\n");

      g_free(dupname);
      return;
   }

   his_key = PE_get_key(acct->gc, dupname);

   if (his_key == 0) { /* Don't have key for this guy yet */
      /* PE_get_key will have sent the key request, just let user know */

      purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "requesting key\n");
      purple_conversation_write(conv, 0, _("Requesting key..."),
                              PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));

      PE_store_msg(who, acct->gc, *message, &first_out_msg, &last_out_msg);

   } else {  /* We have a key.  Encrypt and send. */
      purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "has key (%s)\n", dupname);
      baggage_size = snprintf(baggage, sizeof(baggage), msg_format, header, our_key->digest,
                             his_key->digest, 10000, "", footer);
      baggage_size = MIN(baggage_size, sizeof(baggage) - 1);
      
      /* Warning:  message_split keeps static copies, so if our */
      /*   caller uses it, we're hosed.  Looks like nobody else */
      /*   uses it now, though.                                 */
      unencrypted_size_limit =
         PE_calc_unencrypted_size(our_key, his_key, msg_size_limit - baggage_size);

      cur_msg = PE_message_split(*message, unencrypted_size_limit);
      while (cur_msg) {
         gchar* disp_msg;
         if (purple_prefs_get_bool("/plugins/gtk/encrypt/show_inline_icons")) {
            /* add our smiley to front of message */
            if (((gchar*)cur_msg->data)[0] == '/') {
               /* doh, starting with a /command, so put the smiley after the /command */
               gchar** slashsplit = g_strsplit(cur_msg->data, " ", 2);
               disp_msg = g_strconcat(slashsplit[0], " ", CRYPTO_SMILEY, " ", slashsplit[1], NULL);
               g_strfreev(slashsplit);
            } else {
               disp_msg = g_strconcat(CRYPTO_SMILEY, " ", cur_msg->data, NULL);
            }
         } else {
            /* no smiley at front of message */
            disp_msg = g_strdup(cur_msg->data);
         }

         purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "im_write: %s\n", dupname);
         
         purple_conv_im_write(PURPLE_CONV_IM(conv), NULL, disp_msg,
                            PURPLE_MESSAGE_SEND, time((time_t)NULL));
         g_free(disp_msg);
         
         /* Add message to stash of sent messages: in case a key or nonce is wrong, we */
         /* can then re-send the message when asked.                                   */
         sent_msg_queue = g_hash_table_lookup(conv->data, "sent messages");
         sent_msg_item = g_malloc(sizeof(PE_SentMessage));
         sent_msg_item->time = time(0);
         sent_msg_item->id = PE_make_key_id(his_key);   /* current nonce value */
         sent_msg_item->msg = g_strdup(cur_msg->data);

         g_queue_push_head(sent_msg_queue, sent_msg_item);

         purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Enc for send: '%s'\n", (char*)cur_msg->data);

         PE_encrypt_signed(&crypt_msg, cur_msg->data, our_key, his_key);
         msgsize = strlen(crypt_msg);

         out_msg = g_malloc(msgsize + baggage_size + 1);
      
         sprintf(out_msg, msg_format, header,
                 our_key->digest, his_key->digest, msgsize, crypt_msg,
                 footer);

         serv_send_im(acct->gc, who, out_msg, 0);

         /* emit the "sent-im-msg" event, which will cause sounds to get played, etc*/
			purple_signal_emit(purple_conversations_get_handle(), "sent-im-msg",
							 acct, purple_conversation_get_name(conv), out_msg);

         purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
                      "send_im: %s: %u\n", who, (unsigned)strlen(out_msg));
         purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
                    "outgoing:%s:\n", out_msg);
         g_free(out_msg);
         g_free(crypt_msg);
         cur_msg = cur_msg->next;
         /* if (purple_prefs_get_bool("/pidgin/conversations/im/hide_on_send")) {
            purple_window_hide(purple_conversation_get_window(conv));
            } */
      }
   }

   *message[0] = 0;
   g_free(dupname);

	return;
}


void PE_resend_msg(PurpleAccount* acct, const char* name, gchar *msg_id) {
   char *out_msg, *crypt_msg = 0, *msg = 0;
   PurpleConversation* conv = purple_find_conversation_with_account(PURPLE_CONV_TYPE_IM, name, acct);
   int msgsize;
   const char msg_format[] = "%s: Msg:S%.10s:R%.10s: Len %d:%s%s";
   crypt_key *our_key, *his_key;

   GQueue *sent_msg_queue;
   PE_SentMessage *sent_msg_item;

   int baggage_size;
   char baggage[PE_BUF_LONG];
   const gchar *header, *footer;
   int conv_breaks_html = 0;

   if (msg_id == 0) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Bad call to resend_msg: %p %p\n", conv, msg_id);
      return;
   }

   if (conv == 0) {
      conv = purple_conversation_new(PURPLE_CONV_TYPE_IM, acct, name);
   }

   header = g_hash_table_lookup(header_table, purple_account_get_protocol_id(acct));
   footer = g_hash_table_lookup(footer_table, purple_account_get_protocol_id(acct));

   if (g_hash_table_lookup(broken_users, name)) {
      conv_breaks_html = 1;
   }
   
   if (!header || conv_breaks_html) header = header_default;
   if (!footer || conv_breaks_html) footer = "";
   
   /*Sometimes callers don't know whether there's a msg to send... */
   if (msg_id == 0 || conv == 0) return;

   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
              "resend_encrypted_msg: %s:%s\n", conv->name, msg_id);

   our_key = PE_find_key_by_name(PE_my_priv_ring, conv->account->username, conv->account);

   his_key = PE_find_key_by_name(PE_buddy_ring, name, conv->account);

   if (his_key == 0) { /* Don't have key for this guy */
      purple_conversation_write(conv, 0,
                              _("No key to resend message.  Message lost."),
                              PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));

   } else {  /* We have a key.  Encrypt and send. */

      sent_msg_queue = g_hash_table_lookup(conv->data, "sent messages");

      /* Root through the queue looking for the right message.  Any that are older than this */
      /* one we will throw out, since they would have already been asked for.                */

      while (!g_queue_is_empty(sent_msg_queue)) {
         sent_msg_item = g_queue_pop_tail(sent_msg_queue);
         purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Examining Message: %s\n",
                    sent_msg_item->id);
         
         if (strcmp(sent_msg_item->id, msg_id) == 0) { /* This is the one to resend */
            msg = sent_msg_item->msg;
            g_free(sent_msg_item->id);
            g_free(sent_msg_item);
            break; 
         }
         /* Not the one to resend: pitch it */
         purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "  Deleted\n");
         g_free(sent_msg_item->id);
         g_free(sent_msg_item->msg);
         g_free(sent_msg_item);
      }
      
      if (msg) {
         baggage_size = snprintf(baggage, sizeof(baggage), msg_format, header, our_key->digest,
                                 his_key->digest, 10000, "", footer);
         baggage_size = MIN(baggage_size, sizeof(baggage) - 1);

         PE_encrypt_signed(&crypt_msg, msg, our_key, his_key);
         msgsize = strlen(crypt_msg);
         out_msg = g_malloc(msgsize + baggage_size + 1);
         
         sprintf(out_msg, msg_format, header,
                 our_key->digest, his_key->digest, msgsize, crypt_msg,
                 footer);
         purple_conversation_write(conv, 0,
                                 "Resending...",
                                 PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));
         serv_send_im(conv->account->gc, name, out_msg, 0);
         
         purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
                      "resend_im: %s: %u\n", name, (unsigned)strlen(out_msg));
         purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
                    "resend outgoing:%s:\n", out_msg);
         g_free(msg);
         g_free(out_msg);
         g_free(crypt_msg);
      } else {
         purple_conversation_write(conv, 0, _("Outgoing message lost."),
                                 PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));
      }
   } 
}



static void PE_new_conv(PurpleConversation *conv) {
   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "New conversation\n");

   if ((conv != NULL) && (purple_conversation_get_type(conv) == PURPLE_CONV_TYPE_IM)) {
      g_hash_table_insert(conv->data, g_strdup("sent messages"), g_queue_new());
      g_hash_table_insert(conv->data, g_strdup("sent_capable"), FALSE);
      PE_add_smiley(conv);
      PE_sync_state(conv);      
      if (unrequited_capable_who) {
         if (strcmp(unrequited_capable_who, purple_conversation_get_name(conv)) == 0) {
            PE_set_capable(conv, TRUE);
            if (purple_prefs_get_bool("/plugins/gtk/encrypt/encrypt_if_notified")) {
               PE_set_tx_encryption(conv, TRUE);
            }
         }
         g_free(unrequited_capable_who);
         unrequited_capable_who = 0;
      }
   } else {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "New conversation IS NULL\n");
   }
}

static void PE_new_conv_cb(PurpleConversation *conv, void* data) {
   PE_new_conv(conv);
}

static void PE_updated_conv_cb(PurpleConversation *conv, void* data) {
   PE_add_smiley(conv);
   PE_sync_state(conv);
}

static void PE_del_conv_cb(PurpleConversation *conv, void* data)
{
   GQueue *sent_msg_queue;

   if ((conv != NULL) && (purple_conversation_get_type(conv) == PURPLE_CONV_TYPE_IM)) {
      purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                 "Got conversation delete event for %s\n", conv->name);
      
      /* Remove cached copies of sent messages */
      reap_all_sent_messages(conv);
      sent_msg_queue = g_hash_table_lookup(conv->data, "sent messages");
      g_queue_free(sent_msg_queue);
      g_hash_table_remove(conv->data, "sent messages");
      
      /* Remove to-be-sent-on-receipt-of-key messages: */
      PE_delete_stored_msgs(conv->account, purple_normalize(conv->account, conv->name));
      
      PE_buddy_ring = PE_del_key_from_ring(PE_buddy_ring,
                                           purple_normalize(conv->account, conv->name), conv->account);
      
      /* Would be good to add prefs for these, but for now, just reset: */
      PE_free_state(conv);
      
      purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                 "Finished conversation delete event for %s\n", conv->name);   
      /* button widgets (hopefully) destroyed on window close            */
      /* hash table entries destroyed on hash table deletion, except     */
      /*   for any dynamically allocated values (keys are ok).           */ 
   }
}  

static void PE_headers_init() {
   header_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
   footer_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
   notify_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);

   g_hash_table_insert(header_table, g_strdup("prpl-toc"),
                       g_strdup("*** Encrypted with the Gaim-Encryption plugin <A HREF=\""));
   g_hash_table_insert(footer_table, g_strdup("prpl-toc"),
                       g_strdup("\"></A>"));
   g_hash_table_insert(notify_table, g_strdup("prpl-toc"),
                       g_strdup("<A HREF=\"Gaim-Encryption Capable\"></A>"));

   g_hash_table_insert(header_table, g_strdup("prpl-oscar"),
                       g_strdup("*** Encrypted with the Gaim-Encryption plugin <A HREF=\""));
   g_hash_table_insert(footer_table, g_strdup("prpl-oscar"),
                       g_strdup("\"></A>"));
   g_hash_table_insert(notify_table, g_strdup("prpl-oscar"),
                       g_strdup("<A HREF=\"Gaim-Encryption Capable\"></A>"));

   g_hash_table_insert(header_table, g_strdup("prpl-aim"),
                       g_strdup("*** Encrypted with the Gaim-Encryption plugin <A HREF=\""));
   g_hash_table_insert(footer_table, g_strdup("prpl-aim"),
                       g_strdup("\"></A>"));
   g_hash_table_insert(notify_table, g_strdup("prpl-aim"),
                       g_strdup("<A HREF=\"Gaim-Encryption Capable\"></A>"));

/* If jabber stops stripping HTML, we can go back to these headers */
/*    g_hash_table_insert(header_table, g_strdup("prpl-jabber"), */
/*                        g_strdup("*** Encrypted with the Gaim-Encryption plugin <A HREF='")); */
/*    g_hash_table_insert(footer_table, g_strdup("prpl-jabber"), */
/*                        g_strdup("'></A>")); */
/*    g_hash_table_insert(notify_table, g_strdup("prpl-jabber"), */
/*                        g_strdup("<A HREF='Gaim-Encryption Capable'> </A>")); */


   g_hash_table_insert(header_table, g_strdup("prpl-jabber"),
                       g_strdup("*** Encrypted with the Gaim-Encryption plugin "));
   g_hash_table_insert(footer_table, g_strdup("prpl-jabber"),
                       g_strdup(" "));
   g_hash_table_insert(notify_table, g_strdup("prpl-jabber"),
                       g_strdup("<A HREF='Gaim-Encryption Capable'> </A>"));

   header_default = g_strdup("*** Encrypted :");

   header_broken = g_strdup("*** Encrypted with the Gaim-Encryption plugin");

   broken_users = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
}

/* #define CRYPT_HEADER "*** Encrypted with the Gaim-Encryption plugin <A HREF=\"" */
/* #define CRYPT_FOOTER "\"></A>" */
/* #define CRYPT_NOTIFY_HEADER "<A HREF=\"Gaim-Encryption Capable\"></A>" */

// Jabber seems to turn our double quotes into single quotes at times, so define
// the same headers, only with single quotes.  Lengths MUST be the same as above
/* #define CRYPT_HEADER_MANGLED "*** Encrypted with the Gaim-Encryption plugin <A HREF='" */
/* #define CRYPT_NOTIFY_HEADER_MANGLED "<A HREF='Gaim-Encryption Capable'></A>" */


static void init_prefs() {
   /* These only add/set a pref if it doesn't currently exist: */

   int default_width;

   if (purple_prefs_get_type("/plugins/gtk/encrypt/accept_unknown_key") == PURPLE_PREF_NONE) {
      /* First time loading the plugin, since we don't have our prefs set yet */

      /* so up the default window width to accomodate new buttons */
      default_width = purple_prefs_get_int(PIDGIN_PREFS_ROOT "/conversations/im/default_width");

      if (default_width == 410) { /* the stock pidgin default width */
         purple_prefs_set_int(PIDGIN_PREFS_ROOT "/conversations/im/default_width", 490);
      }
   }

   purple_prefs_add_none("/plugins/gtk");
   purple_prefs_add_none("/plugins/gtk/encrypt");
   
   purple_prefs_add_bool("/plugins/gtk/encrypt/accept_unknown_key", FALSE);
   purple_prefs_add_bool("/plugins/gtk/encrypt/accept_conflicting_key", FALSE);
   purple_prefs_add_bool("/plugins/gtk/encrypt/encrypt_response", TRUE);
   purple_prefs_add_bool("/plugins/gtk/encrypt/broadcast_notify", FALSE);
   purple_prefs_add_bool("/plugins/gtk/encrypt/encrypt_if_notified", TRUE);

   purple_prefs_add_string("/plugins/gtk/encrypt/key_path", "");
   purple_prefs_add_string("/plugins/gtk/encrypt/key_path_displayed", purple_user_dir());

   PE_pref_callback_id =
      purple_prefs_connect_callback(PE_plugin_handle, "/plugins/gtk/encrypt/key_path_displayed",
                                  PE_prefs_changed_cb, 0);

   PE_convert_legacy_prefs();
}

/* Called by Purple when plugin is first loaded */
static gboolean PE_plugin_load(PurplePlugin *h) {

	void *conv_handle;

#ifdef ENABLE_NLS
   bindtextdomain (ENC_PACKAGE, LOCALEDIR);
   bind_textdomain_codeset (ENC_PACKAGE, "UTF-8");
   setlocale(LC_ALL, "");
#endif

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
              "Compiled with Purple '%d.%d.%d', running with Purple '%s'.\n",
              PURPLE_MAJOR_VERSION, PURPLE_MINOR_VERSION, PURPLE_MICRO_VERSION, purple_core_get_version());

   init_prefs();

   conv_handle = purple_conversations_get_handle();
   
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "plugin_load called\n");
   PE_plugin_handle = h;

   PE_state_init();
   PE_pixmap_init();

   if (!rsa_nss_init()) {
      return FALSE;
   }

   PE_key_rings_init();
   PE_nonce_map_init();
   PE_state_ui_init();
   PE_headers_init();

   purple_signal_connect(conv_handle, "receiving-im-msg", h, 
                       PURPLE_CALLBACK(PE_got_msg_cb), NULL);
   purple_signal_connect(conv_handle, "sending-im-msg", h,
                       PURPLE_CALLBACK(PE_send_msg_cb), NULL);
   purple_signal_connect(conv_handle, "conversation-created", h,
                       PURPLE_CALLBACK(PE_new_conv_cb), NULL);
   purple_signal_connect(conv_handle, "conversation-updated", h,
                       PURPLE_CALLBACK(PE_updated_conv_cb), NULL);
   purple_signal_connect(conv_handle, "deleting-conversation", h, 
                       PURPLE_CALLBACK(PE_del_conv_cb), NULL);
   purple_signal_connect(pidgin_log_get_handle(), "log-displaying", h, 
                       PURPLE_CALLBACK(PE_log_displaying_cb), NULL);
  
   purple_signal_connect(purple_blist_get_handle(), "blist-node-extended-menu", h,
                       PURPLE_CALLBACK(PE_buddy_menu_cb), NULL);


   purple_conversation_foreach(PE_sync_state);

   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "done loading\n");


   return TRUE;
}

/* Called by Purple when plugin is removed */
static gboolean PE_plugin_unload(PurplePlugin *h) {

   purple_signals_disconnect_by_handle(h);

   purple_prefs_disconnect_callback(PE_pref_callback_id);

   PE_config_unload();
   
   purple_conversation_foreach(PE_remove_decorations);

   PE_my_priv_ring = PE_clear_ring(PE_my_priv_ring);
   PE_my_pub_ring = PE_clear_ring(PE_my_pub_ring);
   PE_buddy_ring = PE_clear_ring(PE_buddy_ring);

   PE_state_delete();
   PE_state_ui_delete();
   return TRUE;
}

static PidginPluginUiInfo ui_info =
{
   PE_get_config_frame,
        0, /* page_num (Reserved) */

        /* padding */
        NULL,
        NULL,
        NULL,
        NULL
};

static PurplePluginInfo info =
{
   PURPLE_PLUGIN_MAGIC,                              /**< I'm a plugin!  */
   PURPLE_MAJOR_VERSION,
   PURPLE_MINOR_VERSION,
   PURPLE_PLUGIN_STANDARD,                           /**< type           */
   PIDGIN_PLUGIN_TYPE,                               /**< ui_requirement */
   0,                                                /**< flags          */
   NULL,                                             /**< dependencies   */
   PURPLE_PRIORITY_DEFAULT,                          /**< priority       */

   ENCRYPT_PLUGIN_ID,                                /**< id             */
   0,                                                /**< name           */
   ENC_VERSION,                                      /**< version        */
   0,                                                /**  summary        */
   0,                                                /**  description    */
   0,                                                /**< author         */
   ENC_WEBSITE,                                      /**< homepage       */

   PE_plugin_load,                                   /**< load           */
   PE_plugin_unload,                                 /**< unload         */
   NULL,                                             /**< destroy        */

   &ui_info,                                         /**< ui_info        */
   NULL,                                             /**< extra_info     */
   NULL,                                             /**< prefs_info     */
   NULL,                                              /**< actions        */

   /* padding */
   NULL,
   NULL,
   NULL,
   NULL
};

static void
init_plugin(PurplePlugin *plugin)
{

#ifdef ENABLE_NLS
   bindtextdomain (ENC_PACKAGE, LOCALEDIR);
   bind_textdomain_codeset (ENC_PACKAGE, "UTF-8");
   setlocale(LC_ALL, "");
#endif

   info.name = _("Pidgin-Encryption");
   info.summary = _("Encrypts conversations with RSA encryption.");
   info.description = _("RSA encryption with keys up to 4096 bits,"
                        " using the Mozilla NSS crypto library.\n");
   /* Translators: Feel free to add your name to the author field, with text like  */
   /*   "Bill Tompkins, translation by Phil McGee"                                   */
   info.author = _("Bill Tompkins");

}


PURPLE_INIT_PLUGIN(pidgin_encryption, init_plugin, info);
