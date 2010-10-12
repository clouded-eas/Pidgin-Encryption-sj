#ifndef PE_BLIST_H
#define PE_BLIST_H

#include <gdk/gdk.h>
#include <gtk/gtkplug.h>

#include <gtkplugin.h>
#include <blist.h>

#include "pidgin-encryption-config.h"

void PE_buddy_menu_cb(PurpleBlistNode* node, GList **menu, void* data);

gboolean PE_get_buddy_default_autoencrypt(const PurpleAccount* account, const char* buddyname);

#endif
