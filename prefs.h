/*  Pidgin-Encryption Preferences file interface                          */
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


#ifndef PREFS_H
#define PREFS_H

#include <debug.h>
#include <gtkdialogs.h>
#include <prefs.h>

void PE_prefs_changed_cb(const char* name, PurplePrefType type, gconstpointer val, gpointer data);

void PE_convert_legacy_prefs(void);

#endif
