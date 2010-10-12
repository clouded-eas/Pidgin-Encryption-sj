;;
;;  polish.nsh
;;
;;  Polish language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1250
;;  Author: Marek Habersack <grendel@caudium.net>
;;  Version 1, sept 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_POLISH} "Pidgin-Encryption wymaga by Pidgin by� zainstalowany. Nale�y zainstalowa� Pidgin przed instalacj� Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_POLISH} "Wtyczka Pidgin-Encryption dla Pidgin" 

LangString BAD_PIDGIN_VERSION_1 ${LANG_POLISH} "Nieodpowiednia wersja.$\r$\n$\r$\nTa wersja wtyczki Pidgin-Encryption zosta�a skompilowana dla wersji ${PIDGIN_VERSION} Pidgin. Wydaje si�, �e zainstalowana wersja Pidgin to" 

LangString BAD_PIDGIN_VERSION_2 ${LANG_POLISH} "$\r$\n$\r$\nOdwied� http://pidgin-encrypt.sourceforge.net by uzyska� wi�cej informacji."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_POLISH} "Nie potrafi� okre�li� wersji zainstalowanego Pidgin'a. Upewnij si�, �e jest to wersja ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_POLISH} "Instalator Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"

LangString WELCOME_TEXT  ${LANG_POLISH} "Uwaga: ta wersja wtyczki zosta�a zaprojektowana dla Pidgin ${PIDGIN_VERSION} i nie b�dzie dzia�a�a z innymi wersjami Pidgin.\r\n\r\nPrzy ka�dej aktualizacji Pidgin nale�y r�wnie� zaktualizowa� t� wtyczk�.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_POLISH} "Prosz� wskaza� katalog w kt�rym zainstalowano Pidgin"

LangString DIR_INNERTEXT ${LANG_POLISH} "Instaluj w poni�szym katalogu Pidgin:"

LangString FINISH_TITLE ${LANG_POLISH} "Instalacja Pidgin-Encryption v{PIDGIN_ENCRYPTION_VERSION} zako�czona"

LangString FINISH_TEXT ${LANG_POLISH} "Aby Pidgin m�g� u�ywa� nowej wtyczki nale�y go zrestartowa� a nast�pnie uaktywni� wtyczk� w okienku konfiguracyjnym Pidgin."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_POLISH} "Wtyczka encrypt.dll zostanie usuni�ta z katalogu wtyczek Pidgin. Kontynuowa�?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_POLISH} "Wtyczka Pidgin-Encryption (tylko usuwanie)"

LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_POLISH} "Skrypt deinstalacyjny nie m�g� usun�� wpis�w w rejestrze dotycz�cych wtyczki Pidgin-Encryption.$\rJest prawdopodobne, �e inny u�ytkownik r�wnie� zainstalowa� wtyczk�."

LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_POLISH} "Nie posiadasz wystarczaj�cych uprawnien aby zainstalowa� wtyczk�."

