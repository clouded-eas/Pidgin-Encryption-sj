#ifndef PE_STATE_UI_H
#define PE_STATE_UI_H


#include "pidgin-encryption-config.h"

#include <gdk/gdk.h>
#include <gtk/gtkplug.h>

#include "gtkplugin.h"

#include <gtkdialogs.h>
#include <log.h>
#include <gtkconv.h>
#include <gtklog.h>
#include <gtkutils.h>

void PE_state_ui_init();
void PE_state_ui_delete();

void PE_set_rx_encryption_icon(PurpleConversation *c, gboolean encrypted);
void PE_set_tx_encryption_icon(PurpleConversation *c, gboolean do_encrypt, gboolean is_capable);

void PE_pixmap_init();
void PE_error_window(const char* message);

void PE_log_displaying_cb(PidginLogViewer *viewer, PurpleLog *log, gpointer data);

void PE_remove_decorations(PurpleConversation *conv);


void PE_add_smiley(PurpleConversation *conv);

#endif
