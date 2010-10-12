#include "internal.h"  // #defines needed for Gaim headers

#include <blist.h>
#include <debug.h>
#include <gtkutils.h>

#include "pe_blist.h"
#include "state.h"
#include "nls.h"

gboolean PE_get_buddy_default_autoencrypt(const PurpleAccount* account, const char* buddyname) {
   PurpleBuddy *buddy;
   gboolean retval;

   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
              "get_buddy_default_autoencrypt for %p:%s\n", account, buddyname);
   
   if (!account) return FALSE;

   buddy = purple_find_buddy((PurpleAccount*)account, buddyname);

   if (buddy) {
      if (!buddy->node.settings) {
         /* Some users have been getting a crash because buddy->node.settings is/was
            null.  I can't replicate the problem on my system...  So we sanity check
            until the bug in Gaim is found/fixed */
         purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption",
                    "Bad buddy settings for %s\n", buddyname);
         return FALSE;
      }

      retval = purple_blist_node_get_bool(&buddy->node, "PE_Auto_Encrypt");
      purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Found buddy:%s:%d\n", buddyname, retval);

      return retval;
   }

   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "No setting found for buddy:%s\n", buddyname);
   return FALSE;
}

static void buddy_autoencrypt_callback(PurpleBuddy* buddy, gpointer data) {
   gboolean setting;

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption",
              "encrypt callback hit (%p) %s\n", buddy, buddy->name);

   setting = purple_blist_node_get_bool(&buddy->node, "PE_Auto_Encrypt");
   purple_blist_node_set_bool(&buddy->node, "PE_Auto_Encrypt", !setting);

   /* could iterate through conversations to set encryption status */
   /* PE_set_tx_encryption(buddy->account, buddy->name, !setting); */
}

void PE_buddy_menu_cb(PurpleBlistNode* node, GList **menu, void* data) {
   PurpleMenuAction *action;
   PurpleBuddy* buddy;
   gboolean setting;

   if (!PURPLE_BLIST_NODE_IS_BUDDY(node)) return;
   /* else upcast to the buddy that we know it is: */
   buddy = (PurpleBuddy*) node;

   setting = purple_blist_node_get_bool(node, "PE_Auto_Encrypt");

   if (setting) {
      action = purple_menu_action_new(_("Turn Auto-Encrypt Off"), /* it is now turned on */ 
                                          PURPLE_CALLBACK(buddy_autoencrypt_callback), buddy->account->gc, 0);
   } else {
      action = purple_menu_action_new(_("Turn Auto-Encrypt On"),  /* it is now turned off */ 
                                          PURPLE_CALLBACK(buddy_autoencrypt_callback), buddy->account->gc, 0);
   }
   *menu = g_list_append(*menu, action);
}
