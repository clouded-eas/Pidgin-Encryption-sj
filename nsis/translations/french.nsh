;;
;;  french.nsh
;;
;;  French language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Davy Defaud <davy.defaud@free.fr>
;;  Version 1, sept 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_FRENCH} "Pidgin-Encryption est un greffon (plugin) pour Pidgin. Vous devez d'abord installer Pidgin avant d'installer Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_FRENCH} "Pidgin-Encryption, greffon de chiffrement pour Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_FRENCH} "Version incompatible.$\r$\n$\r$\nCette version du greffon Pidgin-Encryption a été compilée pour la version ${PIDGIN_VERSION} de Pidgin. Vous semblez posséder la version"

LangString BAD_PIDGIN_VERSION_2 ${LANG_FRENCH} "de Pidgin.$\r$\n$\r$\nPour plus d'information, veuillez consulter le site internet http://pidgin-encrypt.sourceforge.net."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_FRENCH} "Impossible de détecter la version de Pidgin installée.  Veuillez vous assurer qu'il s'agit de la version ${PIDGIN_VERSION}."

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_FRENCH} "Installateur de Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} "
LangString WELCOME_TEXT  ${LANG_FRENCH} "Note: Cette version de Pidgin-Encryption est conçue pour Pidgin ${PIDGIN_VERSION}, elle ne s'installera et ne fonctionnera pas avec d'autres versions de Pidgin.\r\n\r\nQuand vous mettez à jour votre version de Pidgin, vous devez désinstaller ou mettre également à jour Pidgin-Encryption.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_FRENCH} "Veuillez indiquer le répertoire d'installation de Pidgin."
LangString DIR_INNERTEXT ${LANG_FRENCH} "Installer dans ce dossier Pidgin:"

LangString FINISH_TITLE ${LANG_FRENCH} "Installation de Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} terminée."
LangString FINISH_TEXT ${LANG_FRENCH} "Vous devez redémarrer Pidgin pour charger le greffon, ensuite vous rendre dans les préférences de Pidgin et activer le greffon (plugin) Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_FRENCH} "Le fichier encrypt.dll est sur le point d'être effacé de votre sous-répertoire Pidgin/plugins. Voulez-vous continuer?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_FRENCH} "Désinstallation de Pidgin-Encryption"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_FRENCH} "Le désinstallateur ne peut trouver les entrées de la base de registres concernant Pidgin-Encryption.$\rIl semble qu'un autre utilisateur a installé le greffon."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_FRENCH} "Vous ne possédez pas les privilèges nécessaires pour désinstaller Pidgin-Encryption."
