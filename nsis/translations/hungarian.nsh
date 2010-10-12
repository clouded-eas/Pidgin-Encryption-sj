;;
;;  hungarian.nsh
;;
;;  Hungarian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1250
;;  Author: Peter Tutervai <mrbay@csevego.net>
;;  Version 1, nov 2004 
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_HUNGARIAN} "A Pidgin-Encryption telep�t�s�hez sz�ks�g van a Pidginra. Fel kell telep�tened a Pidgin-ot a Pidgin-Encryption telep�t�se el�tt."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_HUNGARIAN} "Pidgin-Encryption plugin a Pidginhoz"

LangString BAD_PIDGIN_VERSION_1 ${LANG_HUNGARIAN} "Nem kompatibilis verzi�.$\r$\n$\r$\nA Pidgin-Encryption plugin ezen verzi�ja a Pidgin ${PIDGIN_VERSION} verzi�j�hoz lett leford�tva. Neked a "

LangString BAD_PIDGIN_VERSION_2 ${LANG_HUNGARIAN} "verzi�j� Pidgin van feltelep�tve.$\r$\n$\r$\nN�zd meg a http://pidgin-encrypt.sourceforge.net webhelyet tov�bbi inform�ci�k�rt."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_HUNGARIAN} "A feltelep�tett Pidgin verzi�ja ismeretlen. Bizonyosodjon meg r�la, hogy a verzi�ja ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_HUNGARIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Telep�t�"
LangString WELCOME_TEXT  ${LANG_HUNGARIAN} "Fontos: A plugin ezen verzi�ja a Pidgin ${PIDGIN_VERSION} verzi�j�hoz lett leford�tva, �s nem lesz telep�tve vagy nem fog futni a Pidgin m�s verzi�ival.\r\n\r\nHa friss�ti a Pidginot, t�r�lje vagy friss�tse a plugint is.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_HUNGARIAN} "K�rlek, add meg a Pidgin hely�t"
LangString DIR_INNERTEXT ${LANG_HUNGARIAN} "Telep�t�s ebbe a Pidgin k�nyvt�rba:"

LangString FINISH_TITLE ${LANG_HUNGARIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Telep�t�se befejez�d�tt"
LangString FINISH_TEXT ${LANG_HUNGARIAN} "�jra kell ind�tanod a Pidginot, hogy bet�lts�n a plugin, majd a Pidgin be�ll�t�sokban be kell kapcsolnod Pidgin-Encryption Plugint."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_HUNGARIAN} "Az encrypt.dll plugin t�r�lve lesz a Pidgin/plugins k�nyvt�rb�l. Folytassam?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_HUNGARIAN} "Pidgin-Encryption Plugin (csak t�r�lhet�)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_HUNGARIAN} "Az uninstaller nem tal�lt bejegyz�seket a registryben a Pidgin-Encryptionh�z.$\rVal�sz�n�leg m�sik felhaszn�l� telep�tette a Pidgin-Encryptiont."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_HUNGARIAN} "Nincs jogod a Pidgin-Encryption t�rl�s�hez."



