#ifndef PE_STATE_H
#define PE_STATE_H

#include <gdk/gdk.h>

typedef struct EncryptionState {
   gboolean incoming_encrypted;
   gboolean outgoing_encrypted;
   gboolean has_been_notified;
   gboolean is_capable;
} EncryptionState;

void PE_state_init();
void PE_state_delete();


EncryptionState* PE_get_state(PurpleConversation* conv);
void PE_reset_state(PurpleConversation *conv);
void PE_free_state(PurpleConversation *conv);

void     PE_set_tx_encryption(PurpleConversation* conv, gboolean new_state);
gboolean PE_get_tx_encryption(PurpleConversation *conv);

void     PE_set_capable(PurpleConversation *conv, gboolean cap);

gboolean PE_has_been_notified(PurpleConversation *conv);
void     PE_set_notified(PurpleConversation *conv, gboolean newstate);

void     PE_set_rx_encryption(PurpleConversation *conv, gboolean encrypted);

gboolean  PE_get_default_notified(const PurpleAccount *account, const gchar* name);

/* Ensure that the conversation's state is reflected in the conversation's menu */
void PE_sync_state(PurpleConversation *conv);

#endif
