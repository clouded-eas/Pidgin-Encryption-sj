/*  Key acceptance UI bits                                                */
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

#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <gtk/gtkplug.h>

#include <debug.h>
#include <prefs.h>
#include <gtkdialogs.h>
#include <sound.h>

#include "encrypt.h"
#include "keys.h"
#include "prefs.h"
#include "keys_ui.h"
#include "nls.h"

#ifdef _WIN32
#include "win32dep.h"
#endif

typedef struct accept_key_ui {
   GtkWidget *window;
   key_ring_data *ring_data;
   gchar* resend_msg_id;
} accept_key_ui;


static void destroy_callback(GtkWidget* widget, gpointer ginstance) {
   accept_key_ui *instance = (accept_key_ui*)ginstance;
   
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "enter destroy_callback\n");

   g_free(instance->resend_msg_id);
   gtk_widget_destroy(instance->window);
   g_free(instance);
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "leaving destroy_callback\n");
}

static void reject_key_callback(GtkWidget* widget, gpointer ginstance) {
   accept_key_ui *instance = (accept_key_ui*)ginstance;
   
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "enter reject_callback\n");
   gtk_widget_destroy(instance->window);
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "leaving reject_callback\n");
}

static void accept_key_callback(GtkWidget* widget, gpointer ginstance) {
   accept_key_ui *instance = (accept_key_ui*)ginstance;

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "enter accept_callback\n");
   PE_buddy_ring = PE_add_key_to_ring(PE_buddy_ring, instance->ring_data);

   PE_send_stored_msgs(instance->ring_data->account, instance->ring_data->name);
   PE_show_stored_msgs(instance->ring_data->account, instance->ring_data->name);
   if (instance->resend_msg_id) {
      PE_resend_msg(instance->ring_data->account, instance->ring_data->name, instance->resend_msg_id);
   }
   instance->ring_data = 0;

   gtk_widget_destroy(instance->window);
   /* reject_key_callback will now be called since we called destroy on the window */

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "exit accept_callback\n");
}

static void save_key_callback(GtkWidget* widget, gpointer ginstance) {
   accept_key_ui *instance = (accept_key_ui*)ginstance;

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "enter save_callback\n");
   PE_add_key_to_file(Buddy_key_file, instance->ring_data);
   accept_key_callback(widget, ginstance);
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "exit save_callback\n");
}


void PE_choose_accept_unknown_key(key_ring_data* newkey, gchar* resend_msg_id, PurpleConversation *conv) {
   GtkWidget *win;
   GtkWidget *vbox, *hbox;
   GtkWidget *button;
   GtkWidget *label;
   char strbuf[4096];
   accept_key_ui *this_instance;
   
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "enter choose_accept_unknown\n");
   /* First look at the prefs...  */   
   if (purple_prefs_get_bool("/plugins/gtk/encrypt/accept_unknown_key")) {
      PE_add_key_to_file(Buddy_key_file, newkey);
      PE_buddy_ring = PE_add_key_to_ring(PE_buddy_ring, newkey);
      PE_send_stored_msgs(newkey->account, newkey->name);
      PE_show_stored_msgs(newkey->account, newkey->name);
      if (resend_msg_id) {
         PE_resend_msg(newkey->account, newkey->name, resend_msg_id);
      }
      return;
   }
   
   /* Need to ask the user... */

   if (conv) {
      purple_sound_play_event(PURPLE_SOUND_RECEIVE, purple_conversation_get_account(conv));
   }

   this_instance = g_malloc(sizeof(accept_key_ui));
   PIDGIN_DIALOG(win);
   this_instance->window = win;
   this_instance->ring_data = newkey;
   this_instance->resend_msg_id = g_strdup(resend_msg_id);

   gtk_window_set_title(GTK_WINDOW(win), _("Pidgin-Encryption Key Received"));
   g_signal_connect(GTK_OBJECT(win), "destroy", 
                    GTK_SIGNAL_FUNC(destroy_callback),
                    (gpointer)this_instance);

   vbox = gtk_vbox_new(0, 2);
   gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
   gtk_container_add(GTK_CONTAINER(win), vbox);
   gtk_widget_show (vbox);

   g_snprintf(strbuf, sizeof(strbuf), _("%s key received for '%s'"),
              newkey->key->proto->name, newkey->name);
   label = gtk_label_new(strbuf);
   gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
   gtk_widget_set_size_request(label, -1, 30);
   gtk_widget_show(label);

   g_snprintf(strbuf, sizeof(strbuf), _("Key Fingerprint:%*s"),
              KEY_FINGERPRINT_LENGTH, newkey->key->fingerprint);
   label = gtk_label_new(strbuf);
   gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
   gtk_widget_set_size_request(label, -1, 30);
   gtk_widget_show(label);

   g_snprintf(strbuf, sizeof(strbuf), _("Do you want to accept this key?"));
   label = gtk_label_new(strbuf);
   gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
   gtk_widget_set_size_request(label, -1, 30);
   gtk_widget_show(label);
   
   hbox = gtk_hbox_new(FALSE, 2);
   gtk_box_pack_end(GTK_BOX(vbox), hbox, 0, 0, 0);
   gtk_widget_show(hbox);

   button = gtk_button_new_with_label(_("No"));
   g_signal_connect(GTK_OBJECT(button), "clicked",
                    GTK_SIGNAL_FUNC(reject_key_callback),
                    (gpointer)this_instance);
   gtk_box_pack_start(GTK_BOX(hbox), button, 0, 0, 0);
   gtk_widget_set_size_request(button, 100, -1);
   gtk_widget_show(button);
   
   button = gtk_button_new_with_label(_("Accept and Save"));
   g_signal_connect(GTK_OBJECT(button), "clicked",
                    GTK_SIGNAL_FUNC(save_key_callback),
                    (gpointer)this_instance);
   gtk_box_pack_end(GTK_BOX(hbox), button, 0, 0, 0);
   gtk_widget_set_size_request(button, 120, -1);
   gtk_widget_show(button);

   button = gtk_button_new_with_label(_("This session only"));
   g_signal_connect(GTK_OBJECT(button), "clicked",
                    GTK_SIGNAL_FUNC(accept_key_callback),
                    (gpointer)this_instance);
   gtk_box_pack_end(GTK_BOX(hbox), button, 0, 0, 0);
   gtk_widget_set_size_request(button, 130, -1);
   gtk_widget_show(button);

   gtk_widget_show(win);

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "exit choose_accept_unknown\n");
}


void PE_choose_accept_conflict_key(key_ring_data* newkey, gchar* resend_msg_id, PurpleConversation *conv) {
   GtkWidget *win;
   GtkWidget *vbox, *hbox;
   GtkWidget *button;
   GtkWidget *label;
   char strbuf[4096];
   accept_key_ui *this_instance;
   
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "enter choose_accept_conflict\n");
   /* First look at the prefs...  */   
   if (purple_prefs_get_bool("/plugins/gtk/encrypt/accept_conflicting_key")) {
      PE_add_key_to_file(Buddy_key_file, newkey);
      PE_buddy_ring = PE_add_key_to_ring(PE_buddy_ring, newkey);
      PE_send_stored_msgs(newkey->account, newkey->name);
      PE_show_stored_msgs(newkey->account, newkey->name);
      if (resend_msg_id) {
         PE_resend_msg(newkey->account, newkey->name, resend_msg_id);
      }
      return;
   }
   
   /* Need to ask the user... */

   if (conv) {
      purple_sound_play_event(PURPLE_SOUND_RECEIVE, purple_conversation_get_account(conv));
   }

   this_instance = g_malloc(sizeof(accept_key_ui));
   PIDGIN_DIALOG(win);
   this_instance->window = win;
   this_instance->ring_data = newkey;
   this_instance->resend_msg_id = g_strdup(resend_msg_id);
   
   gtk_window_set_title(GTK_WINDOW(win), _("CONFLICTING Pidgin-Encryption Key Received"));
   g_signal_connect(GTK_OBJECT(win), "destroy", 
                    GTK_SIGNAL_FUNC(destroy_callback),
                    (gpointer)this_instance);

   vbox = gtk_vbox_new(0, 2);
   gtk_container_set_border_width(GTK_CONTAINER(vbox), 4);
   gtk_container_add(GTK_CONTAINER(win), vbox);
   gtk_widget_show (vbox);

   label = gtk_label_new(_(" ******* WARNING ******* "));
   gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
   gtk_widget_set_size_request(label, -1, 30);
   gtk_widget_show(label);

   g_snprintf(strbuf, sizeof(strbuf), _("CONFLICTING %s key received for '%s'!"),
              newkey->key->proto->name, newkey->name);
   label = gtk_label_new(strbuf);
   gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
   gtk_widget_set_size_request(label, -1, 30);
   gtk_widget_show(label);

   g_snprintf(strbuf, sizeof(strbuf), _("Key Fingerprint:%*s"),
              KEY_FINGERPRINT_LENGTH, newkey->key->fingerprint);
   label = gtk_label_new(strbuf);
   gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
   gtk_widget_set_size_request(label, -1, 30);
   gtk_widget_show(label);

   label = gtk_label_new(_(" ******* WARNING ******* "));
   gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
   gtk_widget_set_size_request(label, -1, 30);
   gtk_widget_show(label);

   label = gtk_label_new(_("This could be a man-in-the-middle attack, or\n"
                           "could be someone impersonating your buddy.\n"
                           "You should check with your buddy to see if they have\n"
                           "generated this new key before trusting it."));
   gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
   //   gtk_widget_set_size_request(label, -1, 30);
   gtk_widget_show(label);

   g_snprintf(strbuf, sizeof(strbuf), _("Do you want to accept this key?"));
   label = gtk_label_new(strbuf);
   gtk_box_pack_start(GTK_BOX(vbox), label, 0, 0, 0);
   gtk_widget_set_size_request(label, -1, 30);
   gtk_widget_show(label);

   hbox = gtk_hbox_new(FALSE, 2);
   gtk_box_pack_end(GTK_BOX(vbox), hbox, 0, 0, 0);
   gtk_widget_show(hbox);

   button = gtk_button_new_with_label(_("No"));
   g_signal_connect(GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(reject_key_callback),
                      (gpointer)this_instance);
   gtk_box_pack_start(GTK_BOX(hbox), button, 0, 0, 0);
   gtk_widget_set_size_request(button, 100, -1);
   gtk_widget_show(button);
   
   button = gtk_button_new_with_label(_("Accept and Save"));
   g_signal_connect(GTK_OBJECT(button), "clicked",
                      GTK_SIGNAL_FUNC(save_key_callback),
                      (gpointer)this_instance);
   gtk_box_pack_end(GTK_BOX(hbox), button, 0, 0, 0);
   gtk_widget_set_size_request(button, 120, -1);
   gtk_widget_show(button);

   button = gtk_button_new_with_label(_("This session only"));
   g_signal_connect(GTK_OBJECT(button), "clicked",
                    GTK_SIGNAL_FUNC(accept_key_callback),
                    (gpointer)this_instance);
   gtk_box_pack_end(GTK_BOX(hbox), button, 0, 0, 0);
   gtk_widget_set_size_request(button, 130, -1);
   gtk_widget_show(button);

   gtk_widget_show(win);

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "enter choose_accept_conflict\n");
}


