/*                    Configure dialog UI                                 */
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

#ifndef CONFIG_UI_H
#define CONFIG_UI_H

#include <plugin.h>

extern GtkWidget* PE_get_config_frame(PurplePlugin *plugin);
extern void PE_config_cancel_regen(void);
extern void PE_config_update();
extern void PE_config_unload(void);
extern void PE_config_show_invalid_keypath();
extern void PE_config_show_nonabsolute_keypath();
#endif
