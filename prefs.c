/*  Pidgin-Encryption Legacy Preferences file interface                   */
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

#include "internal.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <glib.h>
#if GLIB_CHECK_VERSION(2,6,0)
#	include <glib/gstdio.h>
#else
#	define g_freopen freopen
#	define g_fopen fopen
#	define g_rmdir rmdir
#	define g_remove remove
#	define g_unlink unlink
#	define g_lstat lstat
#	define g_stat stat
#	define g_mkdir mkdir
#	define g_rename rename
#	define g_open open
#endif

#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <gtk/gtkplug.h>

#include "prefs.h"
#include "util.h"
#include "prefs.h"
#include "config_ui.h"
#include "keys.h"

#ifdef _WIN32
#include "win32dep.h"
#endif

void PE_prefs_changed_cb(const char* name, PurplePrefType type, gconstpointer val, gpointer data) {
   const char * displayedpath =  purple_prefs_get_string("/plugins/gtk/encrypt/key_path_displayed");
   const char * basepath = purple_prefs_get_string("/plugins/gtk/encrypt/key_path");

   const char * previous_displayedpath = basepath;

   if (basepath && basepath[0] == 0) {
      /* if the basepath is blank, then the previous displayed path was actually the users's Purple dir */
      previous_displayedpath = purple_user_dir();
   }

   /* did the displayedpath get changed? */
   if (basepath && displayedpath && strcmp(displayedpath, previous_displayedpath) != 0) {
      /* yes, so set the underlying basepath pref appropriately */
      if (strcmp(displayedpath, purple_user_dir()) == 0) {
         purple_prefs_set_string("/plugins/gtk/encrypt/key_path", "");
      } else {
         purple_prefs_set_string("/plugins/gtk/encrypt/key_path", displayedpath);
      }
   }

   if (PE_check_base_key_path()) {
      PE_key_rings_init();
      PE_config_update();
   } else {
      purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "pref_changed_cb: %s\n", (char*)val);
      if (g_path_is_absolute(val)) {
         PE_config_show_invalid_keypath();
      } else {
         purple_prefs_set_string("/plugins/gtk/encrypt/key_path", "");
         purple_prefs_set_string("/plugins/gtk/encrypt/key_path_displayed", purple_user_dir());
         PE_config_show_nonabsolute_keypath();
      }
   }
}


/* Old self-kept preferences: only here to convert to new Purple-kept prefs */
static gboolean Prefs_accept_key_unknown = FALSE;
static gboolean Prefs_accept_key_conflict = FALSE;
/*static gboolean Prefs_encrypt_response = TRUE; */
static gboolean Prefs_broadcast_notify = FALSE;
static gboolean Prefs_encrypt_if_notified = TRUE;

const static char key_file[] = "encrypt.prefs";

static gboolean parse_key_val(char* val, gboolean def) {
   if (strcmp(val, "TRUE") == 0) {
      return TRUE;
   }
   if (strcmp(val, "FALSE") == 0) {
      return FALSE;
   }
   return def;
}

void PE_convert_legacy_prefs() {
   char key[51], value[51];
   
   char* filename = g_build_filename(purple_user_dir(), key_file, NULL);

   FILE* fp = g_fopen(filename, "r");

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Checking for old prefs file (%s)...\n", filename);

   if (fp == NULL) {
      g_free(filename);
      return;
   }   
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Converting...\n");

   while (fscanf(fp, "%50s%50s", key, value) != EOF) {
      if (strcmp(key, "AcceptUnknown") == 0) {
         purple_prefs_set_bool("/plugins/gtk/encrypt/accept_unknown_key",
                             parse_key_val(value, Prefs_accept_key_unknown));
      } else if (strcmp(key, "AcceptDuplicate") == 0) {
         purple_prefs_set_bool("/plugins/gtk/encrypt/accept_conflicting_key",
                             parse_key_val(value, Prefs_accept_key_conflict));
      } else if (strcmp(key, "BroadcastNotify") == 0) {
         purple_prefs_set_bool("/plugins/gtk/encrypt/broadcast_notify",
                             parse_key_val(value, Prefs_broadcast_notify));
      } else if (strcmp(key, "EncryptIfNotified") == 0) {
         purple_prefs_set_bool("/plugins/gtk/encrypt/encrypt_if_notified",
                             parse_key_val(value, Prefs_encrypt_if_notified));
      } else {
         purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Bad Preference Key %s\n", value);
      }
   }
   fclose(fp);

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Deleting old prefs\n");
   unlink(filename);

   g_free(filename);
}
