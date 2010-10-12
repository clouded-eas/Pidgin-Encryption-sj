/*  Protocol-independent Key structures                                   */
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

#include <debug.h>
#include <util.h>

#include <time.h>
#include <sys/types.h>
#ifndef _WIN32
  #include <sys/time.h>
#endif
#include <string.h>
#include <unistd.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "keys.h"
#include "cryptutil.h"
#include "prefs.h"
#include "encrypt.h"
#include "keys_ui.h"
#include "pe_ui.h"
#include "nls.h"

#ifdef _WIN32
#include "win32dep.h"
#endif

/* List of all the keys we know about */
key_ring *PE_buddy_ring = 0, *PE_saved_buddy_ring = 0, *PE_my_priv_ring = 0, *PE_my_pub_ring = 0;

typedef enum {KEY_MATCH, KEY_NOT_THERE, KEY_CONFLICT} KeyCheckVal;


static KeyCheckVal PE_check_known_key(const char *filename, key_ring_data* key);


crypt_key * PE_find_key_by_name(key_ring *ring, const char *name, PurpleAccount *acct) {
   key_ring *i = PE_find_key_node_by_name(ring, name, acct);
   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "find key by name: %s\n", name);
   return (i == NULL) ? NULL : ((key_ring_data *)i->data)->key;
}

crypt_key * PE_find_own_key_by_name(key_ring **ring, char *name, PurpleAccount *acct, PurpleConversation *conv) {
   crypt_key *key = PE_find_key_by_name(*ring, name, acct);
   if (key) return key;

   /* Can't find the key, but it's ours, so we'll make one */
   purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error!  Can't find own key for %s\n",
              name);
   purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Dumping public keyring:\n");      
   PE_debug_dump_keyring(PE_my_pub_ring);
      
   if (conv != 0) {
      purple_conversation_write(conv, "Encryption Manager",
                              _("Making new key pair..."),
                              PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));
   }
   
   PE_make_private_pair((crypt_proto *)crypt_proto_list->data, name, conv->account, 1024);
   
   key = PE_find_key_by_name(*ring, name, conv->account);
   if (key) return key;

   /* Still no key: something is seriously wrong.  Probably having trouble saving the */
   /* key to the key file, or some such.                                              */

   purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error!  Can't make new key for %s\n",
              name);

   if (conv != 0) {
      purple_conversation_write(conv, "Encryption Manager",
                              _("Error trying to make key."),
                              PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));
   }
   
   return 0;
}

key_ring * PE_find_key_node_by_name(key_ring *ring, const char *name, PurpleAccount* acct) {
   key_ring *i = 0;

   for( i = ring; i != NULL; i = i->next ) {
      if( (strncmp(name, ((key_ring_data *)i->data)->name, sizeof(((key_ring_data*)i->data)->name)) == 0 ) &&
          (acct == ((key_ring_data*)i->data)->account))
         break;
   }

   return (i == NULL) ? NULL : i;
}

void PE_debug_dump_keyring(key_ring * ring) {
   key_ring *i = 0;

   for( i = ring; i != NULL; i = i->next ) {
      purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Key ring::%*s::%p\n",
                   (unsigned)sizeof(((key_ring_data *)i->data)->name),
                   ((key_ring_data *)i->data)->name,
                   ((key_ring_data *)i->data)->account);
   }
}

/* add_key_to_ring will ensure that there is only one key on a ring that matches
   a given name.  So your buddy switches computers (and keys), we will discard
   his old key when he sends us his new one.                                  */

key_ring* PE_add_key_to_ring(key_ring* ring, key_ring_data* key) {
   key_ring* old_key = PE_find_key_node_by_name(ring, key->name, key->account);

   if (old_key != NULL) {
      ring = g_slist_remove_link(ring, old_key);
   }
   ring = g_slist_prepend(ring, key);
   return ring;
}

key_ring* PE_del_key_from_ring(key_ring* ring, const char* name, PurpleAccount* acct) {
   key_ring* old_key = PE_find_key_node_by_name(ring, name, acct);

   if (old_key != NULL) {
      purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Removing key for %s\n", name);
      ring = g_slist_remove_link(ring, old_key);
   }
   return ring;
}

key_ring* PE_clear_ring(key_ring* ring) {
   crypt_key* key;
   key_ring *iter = ring;
   
   while (iter != NULL) {
      key = ((key_ring_data *)(iter->data))->key;
      PE_free_key(key);
      g_free(iter->data);
      iter = iter->next;
   }
   g_slist_free(ring);
   return NULL;
}

void PE_received_key(char *key_msg, char *name, PurpleAccount* acct, PurpleConversation* conv, char** orig_msg) {
   GSList *protoiter;
   crypt_proto* proto=0;
   char* key_len_msg=0;
   unsigned int length;
	int realstart = 0;
   gchar** after_key;
   gchar* resend_msg_id = 0;

   key_ring_data *new_key;
   KeyCheckVal keycheck_return;
   
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "received_key\n");
   
   if (strncmp(key_msg, ": Prot ", sizeof(": Prot ") - 1) != 0) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error in received key\n");
      return;
   }
   key_msg += sizeof(": Prot ") - 1;

   protoiter = crypt_proto_list;
   while (protoiter != 0 && proto == 0) {
      if( (key_len_msg = 
           ((crypt_proto *)protoiter->data)->parseable(key_msg)) != 0 ) {
         proto = ((crypt_proto *) protoiter->data);
      }
      protoiter = protoiter->next;
   }

   if (proto == 0) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Unknown protocol type: %10s\n", key_msg);
      return;
   }

   if ( (sscanf(key_len_msg, ": Len %u:%n", &length, &realstart) < 1) ||
        (realstart == 0) ) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error in key header\n");
      return;
   }

   key_len_msg += realstart;
   if (strlen(key_len_msg) < length) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Length doesn't match in add_key\n");
      return;
   }

   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "After key:%s\n", key_len_msg+length);   
   after_key = g_strsplit(key_len_msg+length, ":", 3);
   if (after_key[0] && (strcmp(after_key[0], "Resend") == 0)) {
      if (after_key[1]) {
         resend_msg_id = g_strdup(after_key[1]);
      }
   }
   g_strfreev(after_key);

   key_len_msg[length] = 0;
   
   /* Make a new node for the linked list */
   new_key = g_malloc(sizeof(key_ring_data));
   new_key->account = acct;
   new_key->key = proto->parse_sent_key(key_len_msg);

   if (new_key->key == 0) {
      g_free(new_key);
      if (resend_msg_id) {
         g_free(resend_msg_id);
      }
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Invalid key received\n");
      return;
   }

   strncpy(new_key->name, name, sizeof(new_key->name));
   
   keycheck_return = PE_check_known_key(Buddy_key_file, new_key);

   /* Now that we've pulled the key out of the original message, we can free it */
   /* so that (maybe) a stored message can be returned in it                    */

   (*orig_msg)[0] = 0;
   g_free(*orig_msg);
   *orig_msg = 0;
   
   switch(keycheck_return) {
   case KEY_NOT_THERE:
      PE_choose_accept_unknown_key(new_key, resend_msg_id, conv);
      break;
   case KEY_MATCH:
      PE_buddy_ring = PE_add_key_to_ring(PE_buddy_ring, new_key);
      PE_send_stored_msgs(new_key->account, new_key->name);
      PE_show_stored_msgs(new_key->account, new_key->name);
      if (resend_msg_id) {
         PE_resend_msg(new_key->account, new_key->name, resend_msg_id);
      }

      break;
   case KEY_CONFLICT:
      if (conv) {
         purple_conversation_write(conv, "Encryption Manager", _("Conflicting Key Received!"),
                                 PURPLE_MESSAGE_SYSTEM, time((time_t)NULL));
      }
      PE_choose_accept_conflict_key(new_key, resend_msg_id, conv);
      break;
   }
   if (resend_msg_id) {
      g_free(resend_msg_id);
      resend_msg_id = 0;
   }
}

static const char * get_base_key_path() {
   const char * basepath = purple_prefs_get_string("/plugins/gtk/encrypt/key_path");
   const char * displayedpath =  purple_prefs_get_string("/plugins/gtk/encrypt/key_path_displayed");

   // migration help: if the base key path is equal to purple_user_dir, blank the pref (ie default)
   if (strcmp(basepath, purple_user_dir()) == 0) {
      purple_prefs_set_string("/plugins/gtk/encrypt/key_path", "");      
      basepath = 0;
   } else {
      // see if the basepath matches purple_user_dir with .purple -> .gaim.  If so, migrate it
      gchar ** splitPath = g_strsplit(purple_user_dir(), ".purple", 5);
      gchar * legacyPath = g_strjoinv(".gaim", splitPath);

      if (strcmp(basepath, legacyPath) == 0) {
         purple_prefs_set_string("/plugins/gtk/encrypt/key_path", "");      
         basepath = 0;
      }

      g_strfreev(splitPath);
      g_free(legacyPath);
   }

   

   if (!basepath || *basepath == 0) {
      basepath = purple_user_dir();
      if (!displayedpath || strcmp(basepath, displayedpath) != 0) {
         purple_prefs_set_string("/plugins/gtk/encrypt/key_path_displayed", basepath);
      }
   }
   return basepath;
}

gboolean PE_check_base_key_path() {
   char path[4096];
   struct stat fs;

   g_snprintf(path, sizeof(path), "%s%s%s", get_base_key_path(), G_DIR_SEPARATOR_S, Private_key_file);

   if (!g_path_is_absolute(path)) {
      return FALSE;
   }

   if (stat(path, &fs) == -1) {
      /* file does not exist */
      return FALSE;
   } else {
      return TRUE;
   }
}

static KeyCheckVal PE_check_known_key(const char* filename, key_ring_data* key) {
   char line[MAX_KEY_STORLEN];
   GString *line_str, *key_str, *name_str;
   char path[4096];

   struct stat fs;
   FILE* fp;
   int fd;
   int found_name = 0;
   
   g_snprintf(path, sizeof(path), "%s%s%s", get_base_key_path(), G_DIR_SEPARATOR_S, filename);
      
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Checking key file %s for name %s\n", path, key->name);

   /* check file permissions */
   if (stat(path, &fs) == -1) {
      /* file doesn't exist, so make it */
      fd = g_open(path, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
      if (fd == -1) {
         /* Ok, maybe something else strange is going on... */
         purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error trying to create a known key file\n");
         return KEY_NOT_THERE;
      }
      fstat(fd, &fs);
      fchmod(fd, fs.st_mode & S_IRWXU);  /* zero out non-owner permissions */
      close(fd);
   } else {
#ifdef S_IWGRP
      /* WIN32 doesn't have user-based file permissions, so skips this */
      if (fs.st_mode & (S_IWGRP | S_IWOTH)) {
         fd = g_open(path, O_WRONLY, 0);
         if (fd == -1) {
            /* Ok, maybe something else strange is going on... */
            purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error trying to modify permissions on known key file\n");
            return KEY_NOT_THERE;
         }
         fstat(fd, &fs);
         fchmod(fd, fs.st_mode & S_IRWXU);  /* zero out non-owner permissions */
         close(fd);
         purple_debug(PURPLE_DEBUG_WARNING, "pidgin-encryption", "Changed file permissions on %s\n", path);
      }
#endif
   }

   /* build string from key */
   name_str = g_string_new(key->name);
   PE_escape_name(name_str);
   if (key->account) {
      g_string_append_printf(name_str, ",%s", purple_account_get_protocol_id(key->account));
   } else {
      g_string_append(name_str, ",");
   }

   line_str = g_string_new(name_str->str);
   g_string_append_printf(line_str, " %s ", key->key->proto->name);
   key_str = PE_key_to_gstr(key->key);
   g_string_append(line_str, key_str->str);

   /*   purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "built line '%s'\n", line_str->str); */

   /* look for key in file */   
   if( (fp = g_fopen(path, "r")) != NULL ) {
      while (!feof(fp)) {
         fgets(line, sizeof(line), fp);
         /* purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "checking line '%s'\n", line); */
         if ( (strchr(line, ' ') == line + name_str->len) &&
              (strncmp(line_str->str, line, name_str->len) == 0) ) {
            purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Got Name\n");
            found_name = 1;
            if (strncmp(line_str->str, line, line_str->len) == 0) {
               purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "Got Match\n");
               fclose(fp);
               g_string_free(line_str, TRUE);
               g_string_free(key_str, TRUE);
               g_string_free(name_str, TRUE);
               return KEY_MATCH;
            }
         }
      }
      fclose(fp);
   }

   g_string_free(line_str, TRUE);
   g_string_free(key_str, TRUE);
   g_string_free(name_str, TRUE);
   
   if (found_name) return KEY_CONFLICT;
   return KEY_NOT_THERE;
}

/* For now, we'll make all key files privately owned, even though the
   id.pub and known_keys files could be public.                        */
   
void PE_add_key_to_file(const char *filename, key_ring_data* key) {
   GString *line_str, *key_str;

   char path[4096];
   char errbuf[500];
   
   FILE* fp;
   int fd;
   char c;
   struct stat fdstat;
   
   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Saving key to file:%s:%p\n", key->name, key->account);

   g_snprintf(path, sizeof(path), "%s%s%s", get_base_key_path(), G_DIR_SEPARATOR_S, filename);

   fd = g_open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
   if (fd == -1) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error opening key file %s for write\n", path);
      /* WIN32 doesn't have user-based file permissions, so skips this */
#ifdef S_IRWXG
      if (chmod(path, S_IRUSR | S_IWUSR) == -1) {

         purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Unable to change file mode, aborting\n");
         g_snprintf(errbuf, sizeof(errbuf),
                    _("Error changing access mode for file: %s\nCannot save key."), filename);
         PE_ui_error(errbuf);
         return;
      }
#endif
      fd = g_open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
      if (fd == -1) {
         purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Changed mode, but still wonky.  Aborting.\n");
         g_snprintf(errbuf, sizeof(errbuf),
                    _("Error (2) changing access mode for file: %s\nCannot save key."), filename);
         PE_ui_error(errbuf);
         return;
      } else {
         purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Key file '%s' no longer read-only.\n", path);
      }
   }
   fstat(fd, &fdstat);
#ifdef S_IRWXG
   /* WIN32 doesn't have user-based file permissions, so skips this */
   if (fdstat.st_mode & (S_IRWXG | S_IRWXO)) {
      fchmod(fd, fdstat.st_mode & S_IRWXU);  /* zero out non-owner permissions */

      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Bad permissions on key file.  Changed: %s\n", path);
      g_snprintf(errbuf, sizeof(errbuf),
                 _("Permissions on key file changed for: %s\n"
                   "Pidgin-Encryption will not save keys to a world- or group-accessible file."),
                   filename);
      PE_ui_error(errbuf);
   } 
#endif

   line_str = g_string_new(key->name);
   PE_escape_name(line_str);
   if (key->account) {
      g_string_append_printf(line_str, ",%s", purple_account_get_protocol_id(key->account));
   } else {
      g_string_append(line_str, ",");
   }
   g_string_append_printf(line_str, " %s ", key->key->proto->name);
   key_str = PE_key_to_gstr(key->key);
   g_string_append(line_str, key_str->str);

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "here\n");
   /* To be nice to users... we'll allow the last key in the file to not    */
   /* have a trailing \n, so they can cut-n-paste with abandon.             */
   fp = fdopen(fd, "r");   
   fseek(fp, -1, SEEK_END);
   c = fgetc(fp);
   if (feof(fp)) c = '\n';  /*if file is empty, we don't need to write a \n */
   fclose(fp);
   
   fd = g_open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
   fp = fdopen(fd, "a+");
   fseek(fp, 0, SEEK_END);   /* should be unnecessary, but needed for WIN32 */
   
   if (c != '\n') fputc('\n', fp);
   fputs(line_str->str, fp);
   fclose(fp);

   g_string_free(key_str, TRUE);
   g_string_free(line_str, TRUE);
}

void PE_del_one_key_from_file(const char *filename, int key_num, const char *name) {
   char line[MAX_KEY_STORLEN];
   char path[4096], tmp_path[4096];

   int foundit = 0;
   FILE *fp, *tmp_fp;
   int fd;
   int line_num;

   GString *line_start, *old_style_start, *normalized_start;

   line_start = g_string_new(name);
   PE_escape_name(line_start);
   g_string_append_printf(line_start, ",");

   old_style_start = g_string_new(name);
   PE_escape_name(old_style_start);
   g_string_append_printf(old_style_start, " ");

   normalized_start = g_string_new(name);
   PE_escape_name(normalized_start);
   g_string_append_printf(normalized_start, " ");

   g_snprintf(path, sizeof(path), "%s%s%s", get_base_key_path(), G_DIR_SEPARATOR_S, filename);
   
   /* Look for name in the file.  If it's not there, we're done */
   fp = g_fopen(path, "r");

   if (fp == NULL) {
      g_string_free(line_start, TRUE);
      g_string_free(old_style_start, TRUE);
      g_string_free(normalized_start, TRUE);
      return;
   }

   for (line_num = 0; line_num <= key_num; ++line_num) {
      fgets(line, sizeof(line), fp);
   }

   if ( (strncmp(line, line_start->str, line_start->len) == 0) ||
        (strncmp(line, old_style_start->str, old_style_start->len) == 0) ||
        (strncmp(line, normalized_start->str, normalized_start->len) == 0) ) {
      foundit = 1;
   }

   fclose(fp);

   purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Delete one key: found(%d)\n", foundit);

   if (!foundit) {
      g_string_free(line_start, TRUE);
      g_string_free(old_style_start, TRUE);
      g_string_free(normalized_start, TRUE);
      return;
   }

   /* It's there.  Move file to a temporary, and copy the other lines */

   g_snprintf(tmp_path, sizeof(tmp_path), "%s.tmp", path);
   rename(path, tmp_path);
   
   fd = g_open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
   if (fd == -1) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error opening key file %s\n", path);
      perror("Error opening key file");
      g_string_free(line_start, TRUE);
      g_string_free(old_style_start, TRUE);
      g_string_free(normalized_start, TRUE);

      return;
   }
   fp = fdopen(fd, "a+");
   
   tmp_fp = g_fopen(tmp_path, "r");
   if (tmp_fp == NULL) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Wah!  I moved a file and now it is gone\n");
      fclose(fp);
      g_string_free(line_start, TRUE);
      g_string_free(old_style_start, TRUE);
      g_string_free(normalized_start, TRUE);

      return;
   }

   line_num = 0;
   while (fgets(line, sizeof(line), tmp_fp)) {
      if (line_num != key_num) {
         fputs(line, fp);
      } else {
         purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "Skipping line %d\n", line_num);
      }
      ++line_num;
   }
   
   fclose(fp);
   fclose(tmp_fp);
   unlink(tmp_path);
   g_string_free(line_start, TRUE);
}


void PE_del_key_from_file(const char *filename, const char *name, PurpleAccount *acct) {
   char line[MAX_KEY_STORLEN];
   char path[4096], tmp_path[4096];

   int foundit = 0;
   FILE *fp, *tmp_fp;
   int fd;
   GString *line_start, *old_style_start, *normalized_start;

   line_start = g_string_new(name);
   PE_escape_name(line_start);
   if (acct != 0) {
      g_string_append_printf(line_start, ",%s", purple_account_get_protocol_id(acct));
   } else {
      g_string_append_printf(line_start, ",");
   }

   old_style_start = g_string_new(name);
   PE_escape_name(old_style_start);
   g_string_append_printf(old_style_start, " ");

   normalized_start = g_string_new(name);
   PE_escape_name(normalized_start);
   g_string_append_printf(normalized_start, " ");

   g_snprintf(path, sizeof(path), "%s%s%s", get_base_key_path(), G_DIR_SEPARATOR_S, filename);
   
   /* Look for name in the file.  If it's not there, we're done */
   fp = g_fopen(path, "r");

   if (fp == NULL) {
      g_string_free(line_start, TRUE);
      g_string_free(old_style_start, TRUE);
      g_string_free(normalized_start, TRUE);
      return;
   }

   while (fgets(line, sizeof(line), fp)) {
      if ( (strncmp(line, line_start->str, line_start->len) == 0) ||
           (strncmp(line, old_style_start->str, old_style_start->len) == 0) ||
           (strncmp(line, normalized_start->str, normalized_start->len) == 0) ) {
         foundit = 1;
      }
   }
   fclose(fp);
   if (!foundit) {
      g_string_free(line_start, TRUE);
      g_string_free(old_style_start, TRUE);
      g_string_free(normalized_start, TRUE);
      return;
   }

   /* It's there.  Move file to a temporary, and copy the lines */
   /* that don't match.                                         */
   g_snprintf(tmp_path, sizeof(tmp_path), "%s.tmp", path);
   rename(path, tmp_path);
   
   fd = g_open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
   if (fd == -1) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Error opening key file %s\n", path);
      perror("Error opening key file");
      g_string_free(line_start, TRUE);
      g_string_free(old_style_start, TRUE);
      g_string_free(normalized_start, TRUE);

      return;
   }
   fp = fdopen(fd, "a+");
   
   tmp_fp = g_fopen(tmp_path, "r");
   if (tmp_fp == NULL) {
      purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Wah!  I moved a file and now it is gone\n");
      fclose(fp);
      g_string_free(line_start, TRUE);
      g_string_free(old_style_start, TRUE);
      g_string_free(normalized_start, TRUE);

      return;
   }
   while (fgets(line, sizeof(line), tmp_fp)) {
      if ( (strncmp(line, line_start->str, line_start->len) != 0) &&
           (strncmp(line, old_style_start->str, old_style_start->len) != 0) &&
           (strncmp(line, normalized_start->str, normalized_start->len) != 0) ) {
         fputs(line, fp);
      }
   }
   
   fclose(fp);
   fclose(tmp_fp);
   unlink(tmp_path);
   g_string_free(line_start, TRUE);
}



key_ring * PE_load_keys(const char *filename) {
   FILE* fp;
   char name[64], nameacct[164], proto[20], proto_name[10], proto_ver[10], key_str_buf[MAX_KEY_STORLEN];
   char path[4096];
   int rv;
   key_ring *new_ring = 0;
   key_ring_data *new_key;
   GSList* proto_node;
   gchar **nameaccount_split;
   PurpleAccount* account;

   g_snprintf(path, sizeof(path), "%s%s%s", get_base_key_path(), G_DIR_SEPARATOR_S, filename);

   /* Check permissions on file before use */
#ifdef S_IRWXG
   /* WIN32 doesn't have user-based file permissions, so skips this */
   {
      char errbuf[500];
      struct stat fdstat;
      int fd = g_open(path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
      if (fd != -1) {
         fstat(fd, &fdstat);
         if (fdstat.st_mode & (S_IRWXG | S_IRWXO)) {
            fchmod(fd, fdstat.st_mode & S_IRWXU);  /* zero out non-owner permissions */
            
            purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Bad permissions on key file.  Changed: %s\n", path);
            g_snprintf(errbuf, sizeof(errbuf),
                       _("Permissions on key file changed for: %s\n"
                         "Pidgin-Encryption will not use keys in a world- or group-accessible file."),
                       filename);
            PE_ui_error(errbuf);
         } 
         close(fd);
      }
   }
#endif

if( (fp = g_fopen(path, "r")) != NULL ) {
      do {
      	 /* 7999 = MAX_KEY_STORLEN - 1 */
         rv = fscanf(fp, "%163s %9s %9s %7999s\n", nameacct, proto_name,
                     proto_ver, key_str_buf);

         if( rv == 4 ) {
            if (strlen(key_str_buf) > MAX_KEY_STORLEN - 2) {                    
               purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Problem in key file.  Increase key buffer size.\n");
               continue;
            }
            nameaccount_split = g_strsplit(nameacct, ",", 2);
            strncpy(name, nameaccount_split[0], sizeof(name));
            name[sizeof(name)-1] = 0;
            PE_unescape_name(name);
            
            /* This will do the right thing: if no account, it will match any */
            account = purple_accounts_find(name, nameaccount_split[1]);

            purple_debug(PURPLE_DEBUG_INFO, "pidgin-encryption", "load_keys: name(%s), protocol (%s): %p\n",
                       nameaccount_split[0],
                       ((nameaccount_split[1]) ? nameaccount_split[1] : "none"),
                        account);

            g_strfreev(nameaccount_split);

            /* purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "load_keys() %i: Read: %s:%s %s %s\n",
               __LINE__, filename, name, proto_name, proto_ver); */

            /* find the make_key_from_str for this protocol */
            g_snprintf(proto, sizeof(proto), "%s %s", proto_name, proto_ver);
            proto_node = crypt_proto_list;
            while (proto_node != NULL) {
               if (strcmp(((crypt_proto *)proto_node->data)->name, proto) == 0)
                  break;
               proto_node = proto_node->next;
            }

            if (proto_node == NULL) {
               purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "load_keys() %i: invalid protocol: %s\n",
                            __LINE__, proto);
               continue;
            }

            new_key = g_malloc(sizeof(key_ring_data));
            new_key->key = 
               ((crypt_proto *)proto_node->data)->make_key_from_str(key_str_buf);
            
            new_key->account = account;
            strncpy(new_key->name, name, sizeof(new_key->name));
            purple_debug(PURPLE_DEBUG_MISC, "pidgin-encryption", "load_keys() %i: Added: %*s %s %s\n", __LINE__,
                         (unsigned)sizeof(new_key->name), new_key->name, proto_name, proto_ver);

            new_ring = g_slist_append(new_ring, new_key);
         } else if (rv > 0) {
            purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "Bad key (%s) in file: %s\n", name, path);
         }
      } while( rv != EOF );

      fclose(fp);
   } else {
      if (errno != ENOENT) {
         purple_debug(PURPLE_DEBUG_WARNING, "pidgin-encryption", "Couldn't open file:%s\n", path);
         perror("Error opening file");
      } else {
         purple_debug(PURPLE_DEBUG_WARNING, "pidgin-encryption",
                    "File %s doesn't exist (yet).  A new one will be created.\n", path);
      }
   }

   return new_ring;
}

void PE_key_rings_init() {
   GSList *proto_node;
   GList *cur_sn;
   crypt_key *pub_key = 0, *priv_key = 0;
   key_ring_data *new_key;
   char *name;
   PurpleAccount *acct;

   /* Clear any rings that have data from a previous init */
   if (PE_my_pub_ring) PE_clear_ring(PE_my_pub_ring);
   if (PE_my_priv_ring) PE_clear_ring(PE_my_priv_ring);
   if (PE_saved_buddy_ring) PE_clear_ring(PE_saved_buddy_ring);

   /* Load the keys */
   PE_my_pub_ring = PE_load_keys(Public_key_file);
   PE_my_priv_ring = PE_load_keys(Private_key_file);
   PE_saved_buddy_ring = PE_load_keys(Buddy_key_file);

   /* Create a key for each screen name if we don't already have one */
   
   for (cur_sn = purple_accounts_get_all(); cur_sn != NULL; cur_sn = cur_sn->next) {
      acct = (PurpleAccount *)cur_sn->data;
      name = acct->username;
      priv_key = PE_find_key_by_name(PE_my_priv_ring, name, acct);
      pub_key = PE_find_key_by_name(PE_my_pub_ring, name, acct);
            
      if (priv_key == NULL) { /* No key for this username.  Make one.  */
         proto_node = crypt_proto_list;
         /* make a pair using the first protocol that comes to mind. */
         /* user can override using the config tool */
         PE_make_private_pair((crypt_proto *)proto_node->data, name, (PurpleAccount*)(cur_sn->data), 1024);
      } else {  /* There is a private key  */
         if (pub_key == NULL) { /* but no public key */
            purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "No public key found for %s\n", name);
            purple_debug(PURPLE_DEBUG_ERROR, "pidgin-encryption", "  Making one from private key and saving...\n");
            pub_key = priv_key->proto->make_pub_from_priv(priv_key);
            new_key = g_malloc(sizeof(key_ring_data));
            new_key->key = pub_key;
            new_key->account = acct;
            strncpy(new_key->name, name, sizeof(new_key->name));
            PE_my_pub_ring = g_slist_append(PE_my_pub_ring, new_key);
            PE_add_key_to_file(Public_key_file, new_key);
         }
      }
   }
}

void PE_make_private_pair(crypt_proto* proto, const char* name, PurpleAccount* acct, int keylength) {
   crypt_key *pub_key, *priv_key;
   key_ring_data *new_key;

   proto->gen_key_pair(&pub_key, &priv_key, name, keylength);

   new_key = g_malloc(sizeof(key_ring_data));
   new_key->key = pub_key;
   new_key->account = acct;
   strncpy(new_key->name, name, sizeof(new_key->name));
   PE_my_pub_ring = PE_add_key_to_ring(PE_my_pub_ring, new_key);

   PE_del_key_from_file(Public_key_file, name, acct);
   PE_add_key_to_file(Public_key_file, new_key);

   new_key = g_malloc(sizeof(key_ring_data));
   new_key->key = priv_key;
   new_key->account = acct;
   strncpy(new_key->name, name,
           sizeof(new_key->name));
   PE_my_priv_ring = PE_add_key_to_ring(PE_my_priv_ring, new_key);

   PE_del_key_from_file(Private_key_file, name, acct);
   PE_add_key_to_file(Private_key_file, new_key);
}

