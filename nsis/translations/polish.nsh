;;
;;  polish.nsh
;;
;;  Polish language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1250
;;  Author: Marek Habersack <grendel@caudium.net>
;;  Version 1, sept 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_POLISH} "Pidgin-Encryption wymaga by Pidgin by³ zainstalowany. Nale¿y zainstalowaæ Pidgin przed instalacj¹ Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_POLISH} "Wtyczka Pidgin-Encryption dla Pidgin" 

LangString BAD_PIDGIN_VERSION_1 ${LANG_POLISH} "Nieodpowiednia wersja.$\r$\n$\r$\nTa wersja wtyczki Pidgin-Encryption zosta³a skompilowana dla wersji ${PIDGIN_VERSION} Pidgin. Wydaje siê, ¿e zainstalowana wersja Pidgin to" 

LangString BAD_PIDGIN_VERSION_2 ${LANG_POLISH} "$\r$\n$\r$\nOdwiedŸ http://pidgin-encrypt.sourceforge.net by uzyskaæ wiêcej informacji."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_POLISH} "Nie potrafiê okreœliæ wersji zainstalowanego Pidgin'a. Upewnij siê, ¿e jest to wersja ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_POLISH} "Instalator Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"

LangString WELCOME_TEXT  ${LANG_POLISH} "Uwaga: ta wersja wtyczki zosta³a zaprojektowana dla Pidgin ${PIDGIN_VERSION} i nie bêdzie dzia³a³a z innymi wersjami Pidgin.\r\n\r\nPrzy ka¿dej aktualizacji Pidgin nale¿y równie¿ zaktualizowaæ tê wtyczkê.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_POLISH} "Proszê wskazaæ katalog w którym zainstalowano Pidgin"

LangString DIR_INNERTEXT ${LANG_POLISH} "Instaluj w poni¿szym katalogu Pidgin:"

LangString FINISH_TITLE ${LANG_POLISH} "Instalacja Pidgin-Encryption v{PIDGIN_ENCRYPTION_VERSION} zakoñczona"

LangString FINISH_TEXT ${LANG_POLISH} "Aby Pidgin móg³ u¿ywaæ nowej wtyczki nale¿y go zrestartowaæ a nastêpnie uaktywniæ wtyczkê w okienku konfiguracyjnym Pidgin."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_POLISH} "Wtyczka encrypt.dll zostanie usuniêta z katalogu wtyczek Pidgin. Kontynuowaæ?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_POLISH} "Wtyczka Pidgin-Encryption (tylko usuwanie)"

LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_POLISH} "Skrypt deinstalacyjny nie móg³ usun¹æ wpisów w rejestrze dotycz¹cych wtyczki Pidgin-Encryption.$\rJest prawdopodobne, ¿e inny u¿ytkownik równie¿ zainstalowa³ wtyczkê."

LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_POLISH} "Nie posiadasz wystarczaj¹cych uprawnien aby zainstalowaæ wtyczkê."

