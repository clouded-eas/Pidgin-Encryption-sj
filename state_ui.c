#include "internal.h"

#include "pidgin-encryption-config.h"

#include <string.h>
#include <gdk/gdk.h>
#include <gtk/gtkplug.h>
#include <gtk/gtkimagemenuitem.h>

#include <gtkplugin.h>
#include <gtkmenutray.h>
#include <debug.h>
#include <gtkimhtml.h>
#include <gtklog.h>

#include "state_ui.h"
#include "state.h"
#include "encrypt.h"
#include "nls.h"

#ifdef _WIN32
#include "win32/win32dep.h"
#endif

/* Icons */
/* #include "icon_out_lock.xpm" */
/* #include "icon_out_unlock.xpm" */
/* #include "icon_out_capable.xpm" */
/* #include "icon_in_lock.xpm" */
/* #include "icon_in_unlock.xpm" */

#define PIXMAP_TX_UNENCRYPTED "Pidgin-Encryption_Out_Unencrypted"
#define PIXMAP_TX_CAPABLE "Pidgin-Encryption_Out_Capable"
#define PIXMAP_TX_ENCRYPTED "Pidgin-Encryption_Out_Encrypted"
#define PIXMAP_RX_UNENCRYPTED "Pidgin-Encryption_In_Unencrypted"
#define PIXMAP_RX_ENCRYPTED "Pidgin-Encryption_In_Encrypted"

static GHashTable * tx_encrypt_menus = 0;
static GHashTable * rx_encrypt_iconlist = 0;
static gchar * smiley_filepath = 0;

struct _TxMenuButtons {
   GtkWidget *unencrypted;  /* each is a iconmenu item with one corresponding submenu item */
   GtkWidget *capable;
   GtkWidget *encrypted;
};
typedef struct _TxMenuButtons TxMenuButtons;


static struct StockIcon{
   const char * name;
   const char * filename;
} const stock_icons [] = {
   { PIXMAP_TX_ENCRYPTED, "icon_out_lock.png" },
   { PIXMAP_TX_UNENCRYPTED, "icon_out_unlock.png" },
   { PIXMAP_TX_CAPABLE, "icon_out_capable.png" },
   { PIXMAP_RX_ENCRYPTED, "icon_in_lock.png" },
   { PIXMAP_RX_UNENCRYPTED, "icon_in_unlock.png" },
};

static TxMenuButtons * get_txbuttons_for_win(PidginWindow *win);
static GtkIMHtmlSmiley * create_smiley_if_absent(GtkIMHtml *imhtml);
static void enable_encrypt_cb(GtkWidget* item, PidginWindow* win);
static void disable_encrypt_cb(GtkWidget* item, PidginWindow* win);
static void remove_txbuttons_cb( GtkWidget *widget, gpointer data );
static void remove_rx_icon_cb( GtkWidget *widget, gpointer data);



static TxMenuButtons * get_txbuttons_for_win(PidginWindow *win) {
   TxMenuButtons *tx_menubuttons;
   GtkWidget *submenuitem, *menuitem;
   GtkWidget *menu;
   GtkWidget *image;

   tx_menubuttons = g_hash_table_lookup(tx_encrypt_menus, win);

   if (!tx_menubuttons) {
      GtkWidget *menubar = win->menu.menubar;
      int newMenuPos = 0; /* Where to insert our 3 new menu items: at current pos of menu tray */

      if (menubar == NULL) {
         return NULL;
      }

      {
         GList * list = gtk_container_get_children(GTK_CONTAINER(menubar));
         GList * iter = list;
         while (iter) {
            if (PIDGIN_IS_MENU_TRAY(iter->data)) {
               iter = 0;
            } else {
               ++newMenuPos;
               iter = iter->next;
            }
         }
         g_list_free(list);
      }

      tx_menubuttons = g_malloc(sizeof(TxMenuButtons));


      /* 'not capable' icon on menu with "Enable Encryption" as sole menu possibility */
      menu = gtk_menu_new();

      submenuitem = gtk_menu_item_new_with_label (_("Enable Encryption"));
      gtk_menu_shell_append(GTK_MENU_SHELL(menu), submenuitem);
      gtk_widget_show(submenuitem);
      g_signal_connect(G_OBJECT(submenuitem), "activate", G_CALLBACK(enable_encrypt_cb), win);

      image = gtk_image_new_from_stock(PIXMAP_TX_UNENCRYPTED, GTK_ICON_SIZE_MENU);
      menuitem = gtk_image_menu_item_new_with_label("");
      gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menuitem), image);
      gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(menuitem), TRUE);

      gtk_menu_shell_insert(GTK_MENU_SHELL(menubar), menuitem, newMenuPos);
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);
      gtk_widget_show(menuitem);

      tx_menubuttons->unencrypted = menuitem;


      /* 'capable' icon on menu with "Enable Encryption" as sole menu possibility */
      menu = gtk_menu_new();

      submenuitem = gtk_menu_item_new_with_label (_("Enable Encryption"));
      gtk_menu_shell_append(GTK_MENU_SHELL(menu), submenuitem);
      gtk_widget_show(submenuitem);
      g_signal_connect(G_OBJECT(submenuitem), "activate", G_CALLBACK(enable_encrypt_cb), win);

      image = gtk_image_new_from_stock(PIXMAP_TX_CAPABLE, GTK_ICON_SIZE_MENU);

      menuitem = gtk_image_menu_item_new_with_label("");
      gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menuitem), image);
      gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(menuitem), TRUE);

      gtk_menu_shell_insert(GTK_MENU_SHELL(menubar), menuitem, newMenuPos);
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);
      gtk_widget_hide(menuitem);

      tx_menubuttons->capable = menuitem;

      /* 'encrypted' icon on menu with "Disable Encryption" as sole menu possibility */
      menu = gtk_menu_new();

      submenuitem = gtk_menu_item_new_with_label (_("Disable Encryption"));
      gtk_menu_shell_append(GTK_MENU_SHELL(menu), submenuitem);
      gtk_widget_show(submenuitem);
      g_signal_connect(G_OBJECT(submenuitem), "activate", G_CALLBACK(disable_encrypt_cb), win);

      image = gtk_image_new_from_stock(PIXMAP_TX_ENCRYPTED, GTK_ICON_SIZE_MENU);

      menuitem = gtk_image_menu_item_new_with_label("");
      gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(menuitem), image);
      gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(menuitem), TRUE);

      gtk_menu_shell_insert(GTK_MENU_SHELL(menubar), menuitem, newMenuPos);
      gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem), menu);
      gtk_widget_hide(menuitem);

      tx_menubuttons->encrypted = menuitem;

      g_hash_table_insert(tx_encrypt_menus, win, tx_menubuttons);

      g_signal_connect (G_OBJECT(win->window), "destroy", G_CALLBACK(remove_txbuttons_cb), win);

      purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                 "Adding menu item to win %p, item %p\n",
                 win, tx_menubuttons);
   }
   return tx_menubuttons;
}

static void remove_txbuttons_cb( GtkWidget *widget, gpointer data ) {
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
              "Got callback for destroyed window %p %p\n", data, widget);
   g_hash_table_remove(tx_encrypt_menus, data);
}

static void remove_rx_icon_cb( GtkWidget *widget, gpointer data ) {
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
              "Got callback for destroyed window %p %p\n", data, widget);
   g_hash_table_remove(rx_encrypt_iconlist, data);
}

void PE_state_ui_init() {
   smiley_filepath = g_build_filename(DATADIR, "pixmaps", "pidgin-encryption", "crypto.png", NULL);

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Smiley Filepath: '%s'\n", smiley_filepath);

   tx_encrypt_menus = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, g_free);

   rx_encrypt_iconlist = g_hash_table_new(g_direct_hash, g_direct_equal);
}

void PE_state_ui_delete() {
   g_hash_table_destroy(tx_encrypt_menus);
   tx_encrypt_menus = NULL;

   g_hash_table_destroy(rx_encrypt_iconlist);
   rx_encrypt_iconlist = NULL;

   g_free(smiley_filepath);
   smiley_filepath = NULL;
}

void PE_set_tx_encryption_icon(PurpleConversation* conv,
                               gboolean do_encrypt, gboolean is_capable) {
   PidginConversation *gtkconv = PIDGIN_CONVERSATION(conv);
   PidginWindow *win;
   TxMenuButtons *buttons;

   /* we now get called based on conversation changes before the gtkconv has */
   /* been set up for the conversation.  If that is going on, just bail until */
   /* things are set up right */

   if (!gtkconv) return;

   win = pidgin_conv_get_window(gtkconv);
   g_return_if_fail(win != NULL);

   /* ensure that the conv we are adding for is actually the active one */
   if (pidgin_conv_window_get_active_gtkconv(win)->active_conv != conv) {
      return;
   }

   buttons = get_txbuttons_for_win(win);
   g_return_if_fail(buttons != NULL);

   if (do_encrypt) {
      gtk_widget_hide(buttons->unencrypted);
      gtk_widget_hide(buttons->capable);
      gtk_widget_show(buttons->encrypted);
   } else if (is_capable) {
      gtk_widget_hide(buttons->unencrypted);
      gtk_widget_show(buttons->capable);
      gtk_widget_hide(buttons->encrypted);
   } else {
      gtk_widget_show(buttons->unencrypted);
      gtk_widget_hide(buttons->capable);
      gtk_widget_hide(buttons->encrypted);
   }
}

void PE_set_rx_encryption_icon(PurpleConversation *conv, gboolean encrypted) {
   PidginConversation *gtkconv = PIDGIN_CONVERSATION(conv);
   PidginWindow *win;

   GtkWidget *tray;
   GtkWidget *rx_encrypted_icon;

   /* we now get called based on conversation changes before the gtkconv has */
   /* been set up for the conversation.  If that is going on, just bail until */
   /* things are set up right */

   if (!gtkconv) return;

   win = pidgin_conv_get_window(gtkconv);
   g_return_if_fail(win != NULL);
   tray = win->menu.tray;

   /* ensure that the conv we are adding for is actually the active one */
   if (pidgin_conv_window_get_active_gtkconv(win)->active_conv != conv) {
      return;
   }


   rx_encrypted_icon = g_hash_table_lookup(rx_encrypt_iconlist, win);

   if (!rx_encrypted_icon) {
      rx_encrypted_icon = gtk_image_new_from_stock(PIXMAP_RX_ENCRYPTED, GTK_ICON_SIZE_MENU);

	  pidgin_menu_tray_append(PIDGIN_MENU_TRAY(tray), rx_encrypted_icon,
                              _("The last message received was encrypted  with the Pidgin-Encryption plugin"));

      g_hash_table_insert(rx_encrypt_iconlist, win, rx_encrypted_icon);
      g_signal_connect (G_OBJECT(win->window), "destroy", G_CALLBACK(remove_rx_icon_cb), win);

   } else {
      purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                 "Using pre-existing menu icon for conv %p, win %p, item %p\n",
                 conv, win, rx_encrypted_icon);
   }

   if (encrypted) {
      gtk_widget_show(rx_encrypted_icon);
   } else {
      gtk_widget_hide(rx_encrypted_icon);
   }
}

/* returns the new Smiley if created, or NULL if it was already there */
static GtkIMHtmlSmiley * create_smiley_if_absent(GtkIMHtml *imhtml) {
   GtkIMHtmlSmiley * smiley;
   const char* category = gtk_imhtml_get_protocol_name(imhtml);

   /* make sure that the category we're about to use to add (based on the protocol name) */
   /* already exists.  If it doesn't, just use the default category so it isn't created. */
   if (category && g_hash_table_lookup(imhtml->smiley_data, category) == NULL) {
      category = NULL;
   }

   smiley = gtk_imhtml_smiley_get(imhtml, category, CRYPTO_SMILEY);

   if (smiley) {
      /* We're not creating it, because it was already there.  Tell the caller that */
      return NULL;
   }

   /* This may leak.  How does it get cleaned up? */
   smiley = g_new0(GtkIMHtmlSmiley, 1);
   smiley->file = smiley_filepath;
   smiley->smile = CRYPTO_SMILEY;
   smiley->loader = NULL;
   smiley->flags  = smiley->flags | GTK_IMHTML_SMILEY_CUSTOM;

   gtk_imhtml_associate_smiley(imhtml, category, smiley);
   return smiley;
}

static void enable_encrypt_cb(GtkWidget* item, PidginWindow* win) {
   PidginConversation *gtkconv;
   PurpleConversation *conv;

   g_return_if_fail(win != NULL);
   gtkconv = pidgin_conv_window_get_active_gtkconv(win);

   g_return_if_fail(gtkconv != NULL);

   conv = gtkconv->active_conv;

   g_return_if_fail(conv != NULL);

   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Enable encryption on conv %p\n", conv);
   PE_set_tx_encryption(conv, TRUE);
}

static void disable_encrypt_cb(GtkWidget* item, PidginWindow* win) {
   PidginConversation *gtkconv;
   PurpleConversation *conv;

   g_return_if_fail(win != NULL);
   gtkconv = pidgin_conv_window_get_active_gtkconv(win);

   g_return_if_fail(gtkconv != NULL);

   conv = gtkconv->active_conv;

   g_return_if_fail(conv != NULL);

   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Disable encryption on conv %p\n", conv);
   PE_set_tx_encryption(conv, FALSE);
}

void PE_add_smiley(PurpleConversation* conv) {
   GtkIMHtmlSmiley * smiley;
   GtkIMHtml * imhtml;

   PidginConversation *gtkconv = PIDGIN_CONVERSATION(conv);

   if (!gtkconv) return;

   create_smiley_if_absent( GTK_IMHTML(gtkconv->entry) );

   imhtml = GTK_IMHTML(gtkconv->imhtml);

   smiley = create_smiley_if_absent(imhtml);

   /* if the smiley was created this time, the value of the new smiley was returned */
   /* given that, we want to iterate through and use the smiley everywhere          */
   if (smiley) {
      GtkTextIter cur_iter, cur_plus_offset_iter;
      gboolean offset_is_ok;
      const char* category = gtk_imhtml_get_protocol_name(imhtml);

      /* Go through the buffer and replace our smiley text with the smiley */
      gtk_text_buffer_get_start_iter(imhtml->text_buffer, &cur_iter);

      cur_plus_offset_iter = cur_iter;
      offset_is_ok = gtk_text_iter_forward_chars(&cur_plus_offset_iter, CRYPTO_SMILEY_LEN);
      while (offset_is_ok) {
         char *buffer_text = gtk_text_buffer_get_text(imhtml->text_buffer, &cur_iter,
                                                      &cur_plus_offset_iter, FALSE);
         if (strcmp(buffer_text, CRYPTO_SMILEY) == 0) {
            gtk_text_buffer_delete(imhtml->text_buffer, &cur_iter, &cur_plus_offset_iter);
            gtk_imhtml_insert_smiley_at_iter(imhtml, category, CRYPTO_SMILEY, &cur_iter);
         } else {
            gtk_text_iter_forward_chars(&cur_iter, 1);
         }
         cur_plus_offset_iter = cur_iter;
         offset_is_ok = gtk_text_iter_forward_chars(&cur_plus_offset_iter, CRYPTO_SMILEY_LEN);
         g_free(buffer_text);
      }
   }
}

void PE_log_displaying_cb(PidginLogViewer *viewer, PurpleLog *log, gpointer data) {
   create_smiley_if_absent( GTK_IMHTML(viewer->imhtml) );
}



void PE_remove_decorations(PurpleConversation *conv) {
   PidginConversation *gtkconv = PIDGIN_CONVERSATION(conv);
   PidginWindow *win;
   TxMenuButtons *tx_menubuttons;
   GtkWidget *rx_encrypted_icon;
   
   if (!gtkconv) return;

   win = pidgin_conv_get_window(gtkconv);
   g_return_if_fail(win != NULL);

   /* Remove the destroy callbacks: */
   g_signal_handlers_disconnect_by_func(G_OBJECT(win->window),
                                        G_CALLBACK(remove_txbuttons_cb), win);

   g_signal_handlers_disconnect_by_func(G_OBJECT(win->window),
                                        G_CALLBACK(remove_rx_icon_cb), win);

   tx_menubuttons = g_hash_table_lookup(tx_encrypt_menus, win);
   if (tx_menubuttons) {
      gtk_widget_destroy(tx_menubuttons->unencrypted);
      gtk_widget_destroy(tx_menubuttons->encrypted);
      gtk_widget_destroy(tx_menubuttons->capable);      
      g_hash_table_remove(tx_encrypt_menus, win);
   }

   rx_encrypted_icon = g_hash_table_lookup(rx_encrypt_iconlist, win);
   if (rx_encrypted_icon) {
      gtk_widget_destroy(rx_encrypted_icon);
      g_hash_table_remove(rx_encrypt_iconlist, win);
   }
}


/* stolen from Pidgin/Gaim's icon factory code: */
void
PE_stock_init(void)
{
	static gboolean stock_initted = FALSE;
	GtkIconFactory *icon_factory;
	size_t i;
	GtkWidget *win;
	
	if (stock_initted)
		return;

	stock_initted = TRUE;

	/* Setup the icon factory. */
	icon_factory = gtk_icon_factory_new();

	gtk_icon_factory_add_default(icon_factory);

	/* Er, yeah, a hack, but it works. :) */
	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_realize(win);

	for (i = 0; i < G_N_ELEMENTS(stock_icons); i++)
	{
		GtkIconSource *source;
		GtkIconSet *iconset;
		gchar *filename;

      filename = g_build_filename(DATADIR, "pixmaps", "pidgin-encryption", stock_icons[i].filename, NULL);

      if (filename == NULL)
         continue;
      
      purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                   "Adding stock from %s\n", filename);

      source = gtk_icon_source_new();
      gtk_icon_source_set_filename(source, filename);
      gtk_icon_source_set_direction_wildcarded(source, TRUE);
      gtk_icon_source_set_size_wildcarded(source, TRUE);
      gtk_icon_source_set_state_wildcarded(source, TRUE);
      
      iconset = gtk_icon_set_new();
      gtk_icon_set_add_source(iconset, source);
      
      gtk_icon_source_free(source);
      g_free(filename);

      purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                   "iconset = %p\n", iconset);

      gtk_icon_factory_add(icon_factory, stock_icons[i].name, iconset);
      
      gtk_icon_set_unref(iconset);
	}

	gtk_widget_destroy(win);
	g_object_unref(G_OBJECT(icon_factory));

}


void PE_pixmap_init() {

   PE_stock_init();

/*    /\* Here we make a "stock" icon factory to make our icons, and inform GTK *\/ */
/*    int i; */
/*    GdkPixbuf *pixbuf; */
/*    GtkIconSet *icon_set; */

/*    static const GtkStockItem items[] = { */
/*       { "Pidgin-Encryption_Encrypted", "_GTK!", (GdkModifierType)0, 0, NULL }, */
/*       { "Pidgin-Encryption_Unencrypted", "_GTK!", (GdkModifierType)0, 0, NULL }, */
/*       { "Pidgin-Encryption_Capable", "_GTK!", (GdkModifierType)0, 0, NULL } */
/*    }; */


/*    GtkIconFactory *factory; */

/*    gtk_stock_add (items, G_N_ELEMENTS (items)); */

/*    factory = gtk_icon_factory_new(); */
/*    gtk_icon_factory_add_default(factory); */

/*    for (i = 0; i < G_N_ELEMENTS(stock_icons); i++) { */
/*       pixbuf = gdk_pixbuf_new_from_xpm_data((const char **)item_names[i].xpm_data); */
/*       icon_set = gtk_icon_set_new_from_pixbuf (pixbuf); */
/*       gtk_icon_factory_add (factory, item_names[i].name, icon_set); */
/*       gtk_icon_set_unref (icon_set); */
/*       g_object_unref (G_OBJECT (pixbuf)); */
/*    } */

/*    g_object_unref(factory); */
}



void PE_error_window(const char* message) {
   GtkWidget *dialog, *label, *okay_button;
   dialog = gtk_dialog_new();
   label = gtk_label_new(message);

   okay_button = gtk_button_new_with_label(_("Ok"));
      gtk_signal_connect_object (GTK_OBJECT (okay_button), "clicked",
                              GTK_SIGNAL_FUNC (gtk_widget_destroy), dialog);
   gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->action_area),
                      okay_button);

   gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox),
                      label);
   gtk_widget_show_all (dialog);

}
