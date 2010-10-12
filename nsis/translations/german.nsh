;;
;;  german.nsh
;;
;;  German language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Bj�rn Voigt <bjoern@cs.tu-berlin.de>
;;          Karim Malhas <karim@malhas.de>
;;  Version 1, sept 2004 
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_GERMAN} "Pidgin-Encryption ben�tigt eine installierte Pidgin-Version. Sie m�ssen Pidgin installieren bevor sie Pidgin-Encryption installieren."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_GERMAN} "Pidgin-Encryption Plugin f�r Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_GERMAN} "Inkompatible Version.$\r$\n$\r$\nDiese Pidgin-Encryption Plugin-Version wurde f�r Pidgin Version ${PIDGIN_VERSION} erstellt.  Sie scheinen Pidgin Version"

LangString BAD_PIDGIN_VERSION_2 ${LANG_GERMAN} "installiert zu haben.$\r$\n$\r$\nBesuchen sie http://pidgin-encrypt.sourceforge.net f�r weitere Informationen."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_GERMAN} "Ich kann nicht feststellen, welche Pidgin-Version installiert ist.  Vergewissern sie sich das es Version ${PIDGIN_VERSION} ist."

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_GERMAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Installationsprogramm"
LangString WELCOME_TEXT  ${LANG_GERMAN} "Anmerkung: Diese Version des Plugins wurde f�r Pidgin Version ${PIDGIN_VERSION} erstellt, und wird mit anderen Versionen von Pidgin weder installierbar sein noch funktionieren.\r\n\r\nWenn sie Pidgin upgraden, m�ssen sie dieses Plugin entweder deinstallieren oder auch upgraden.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_GERMAN} "Bitte w�hlen sie das Verzeichnis aus in dem Pidgin installiert ist"
LangString DIR_INNERTEXT ${LANG_GERMAN} "Pidgin in diesem Ordner installieren:"

LangString FINISH_TITLE ${LANG_GERMAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Installation abgeschlossen"
LangString FINISH_TEXT ${LANG_GERMAN} "Sie m�ssen Pidgin neu starten damit das Plugin geladen wird. Dann k�nnen sie das Plugin in den Pidgin-Einstellungen aktivieren."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_GERMAN} "Das encrypt.dll Plugin wird jetzt aus ihrem Pidgin/Plugin Verzeichnis gel�scht.  Fortfahren?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_GERMAN} "Pidgin-Encryption Plugin (nur entfernen)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_GERMAN} "Das Deinstallationsprogram konnte keine Registry Eintr�ge f�r Pidgin-Encryption finden.$\rWarscheinlich hat ein anderer Benutzer das Plugin installiert."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_GERMAN} "Sie haben nicht die n�tigen Rechte um das Plugin zu deinstallieren."







