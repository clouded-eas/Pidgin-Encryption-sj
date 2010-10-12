#include "internal.h"

#include <string.h>
#include <ctype.h>

#include <gdk/gdk.h>
#include <gtk/gtkplug.h>

#include <gtkplugin.h>

#include <debug.h>
#include <util.h>
#include <conversation.h>

#include "pe_blist.h"
#include "state_ui.h"
#include "state.h"

GHashTable *encryption_state_table; /* name -> EncryptionState */

/* Helper function: */
static void reset_state_struct(const PurpleAccount* account,
                               const gchar* name,
                               EncryptionState* state);

void PE_state_init() {
   encryption_state_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
}

void PE_state_delete() {
   g_hash_table_destroy(encryption_state_table);
}

EncryptionState* PE_get_state(PurpleConversation* conv) {
   if (conv == NULL) return NULL;

   EncryptionState *state = purple_conversation_get_data(conv, "PE_state");

   if (state == NULL) {
      state = g_malloc(sizeof(EncryptionState));
      purple_conversation_set_data(conv, "PE_state", state);

      // should probably change this to use some prefs info rather than our buddy list stuff
      state->outgoing_encrypted =
         PE_get_buddy_default_autoencrypt(purple_conversation_get_account(conv),
                                          purple_conversation_get_name(conv));
      
      if (conv == NULL) {
         return NULL;
      }

      state->has_been_notified =
         PE_get_default_notified(purple_conversation_get_account(conv),
                                 purple_conversation_get_name(conv));
      
      state->incoming_encrypted = FALSE;
      state->is_capable = FALSE;      
   }
   return state;
}

void PE_reset_state(PurpleConversation* conv) {
   EncryptionState *state;

   if (conv == NULL) return;

   state = PE_get_state(conv);

   reset_state_struct(purple_conversation_get_account(conv), purple_conversation_get_name(conv), state);
}

void PE_free_state(PurpleConversation* conv) {
   EncryptionState *state;

   if (conv == NULL) return;

   state = PE_get_state(conv);

   if (state) {
      g_free(state);
   }
}

static void reset_state_struct(const PurpleAccount* account, const gchar* name,
                               EncryptionState* state) {

   state->outgoing_encrypted = PE_get_buddy_default_autoencrypt(account, name);
   state->has_been_notified = PE_get_default_notified(account, name);

   state->incoming_encrypted = FALSE;
   state->is_capable = FALSE;
}

void PE_set_tx_encryption(PurpleConversation* conv, gboolean do_encrypt) {
   EncryptionState *state;

   if (conv == NULL) return;

   state = PE_get_state(conv);

   if (state->outgoing_encrypted != do_encrypt) {
      state->outgoing_encrypted = do_encrypt;
      PE_sync_state(conv);
   }
}

void PE_set_capable(PurpleConversation* conv, gboolean cap) {
   EncryptionState *state;

   if (conv == NULL) return;

   state = PE_get_state(conv);

   if (state->is_capable != cap) {
      state->is_capable = cap;
      if (state->outgoing_encrypted == FALSE) {
         PE_sync_state(conv);
      }
   }
}

void PE_set_rx_encryption(PurpleConversation *conv, gboolean incoming_encrypted) {
   EncryptionState *state;

   if (conv == NULL) return;

   state = PE_get_state(conv);

   if (state->incoming_encrypted != incoming_encrypted) {
      state->incoming_encrypted = incoming_encrypted;
      PE_set_rx_encryption_icon(conv, incoming_encrypted);
   }
}

gboolean PE_get_tx_encryption(PurpleConversation *conv) {
   EncryptionState *state = PE_get_state(conv);

   if (state == NULL) return FALSE;

   return state->outgoing_encrypted;
}

void PE_sync_state(PurpleConversation *conv) {
   EncryptionState *state;

   if (conv == NULL) return;

   state = PE_get_state(conv);
   PE_set_rx_encryption_icon(conv, state->incoming_encrypted);
   PE_set_tx_encryption_icon(conv, state->outgoing_encrypted, state->is_capable);
}

gboolean PE_has_been_notified(PurpleConversation *conv) {
   EncryptionState *state = PE_get_state(conv);

   if (state == NULL) return TRUE;

   return state->has_been_notified;
}

void PE_set_notified(PurpleConversation *conv, gboolean new_state) {
   EncryptionState *state;

   if (conv == NULL) return;

   state = PE_get_state(conv);

   state->has_been_notified = new_state;
}


gboolean PE_get_default_notified(const PurpleAccount *account, const gchar* name) {
   /* Most protocols no longer have a notify message, since they don't do HTML */
   
   /* The only special case here is Oscar/TOC: If the other user's name is all */
   /* digits, then they're ICQ, so we pretend that we already notified them    */

   const char* protocol_id = purple_account_get_protocol_id(account);
   
   if (strcmp(protocol_id, "prpl-toc") == 0 || strcmp(protocol_id, "prpl-oscar") == 0) {
      
      while(*name != 0) {
         if (!isdigit(*name++)) {
            /* not ICQ */
            return FALSE;
         }
      }
      /* Hrm.  must be ICQ */
      return TRUE;
   }

   /* default to notifying next time, if protocol allows it */

   return FALSE;
}

   
