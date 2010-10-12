;;
;;  english.nsh
;;
;;  English language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Bill Tompkins <tompkins@icarion.com>
;;  Version 1, Nov 2003
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_ENGLISH} "Pidgin-Encryption requires that Pidgin be installed. You must install Pidgin before installing Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_ENGLISH} "Pidgin-Encryption plugin for Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_ENGLISH} "Incompatible version.$\r$\n$\r$\nThis version of the Pidgin-Encryption plugin was built for Pidgin version ${PIDGIN_VERSION}.  It appears that you have Pidgin version"

LangString BAD_PIDGIN_VERSION_2 ${LANG_ENGLISH} "installed.$\r$\n$\r$\nSee http://pidgin-encrypt.sourceforge.net for more information."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_ENGLISH} "I can't tell what version of Pidgin is installed.  Make sure that it is version ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_ENGLISH} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Installer"
LangString WELCOME_TEXT  ${LANG_ENGLISH} "Note: This version of the plugin is designed for Pidgin ${PIDGIN_VERSION}, and will not install or function with other versions of Pidgin.\r\n\r\nWhen you upgrade your version of Pidgin, you must uninstall or upgrade this plugin as well.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_ENGLISH} "Please locate the directory where Pidgin is installed"
LangString DIR_INNERTEXT ${LANG_ENGLISH} "Install in this Pidgin folder:"

LangString FINISH_TITLE ${LANG_ENGLISH} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Install Complete"
LangString FINISH_TEXT ${LANG_ENGLISH} "You will need to restart Pidgin for the plugin to be loaded, then go the Pidgin preferences and enable the Pidgin-Encryption Plugin."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_ENGLISH} "The encrypt.dll plugin is about to be deleted from your Pidgin/plugins directory.  Continue?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_ENGLISH} "Pidgin-Encryption Plugin (remove only)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_ENGLISH} "The uninstaller could not find registry entries for Pidgin-Encryption.$\rIt is likely that another user installed the plugin."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_ENGLISH} "You do not have the permissions necessary to uninstall the plugin."



