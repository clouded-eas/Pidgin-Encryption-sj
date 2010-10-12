;;
;;  hungarian.nsh
;;
;;  Hungarian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1250
;;  Author: Peter Tutervai <mrbay@csevego.net>
;;  Version 1, nov 2004 
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_HUNGARIAN} "A Pidgin-Encryption telepítéséhez szükség van a Pidginra. Fel kell telepítened a Pidgin-ot a Pidgin-Encryption telepítése elõtt."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_HUNGARIAN} "Pidgin-Encryption plugin a Pidginhoz"

LangString BAD_PIDGIN_VERSION_1 ${LANG_HUNGARIAN} "Nem kompatibilis verzió.$\r$\n$\r$\nA Pidgin-Encryption plugin ezen verziója a Pidgin ${PIDGIN_VERSION} verziójához lett lefordítva. Neked a "

LangString BAD_PIDGIN_VERSION_2 ${LANG_HUNGARIAN} "verziójú Pidgin van feltelepítve.$\r$\n$\r$\nNézd meg a http://pidgin-encrypt.sourceforge.net webhelyet további információkért."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_HUNGARIAN} "A feltelepített Pidgin verziója ismeretlen. Bizonyosodjon meg róla, hogy a verziója ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_HUNGARIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Telepítõ"
LangString WELCOME_TEXT  ${LANG_HUNGARIAN} "Fontos: A plugin ezen verziója a Pidgin ${PIDGIN_VERSION} verziójához lett lefordítva, és nem lesz telepítve vagy nem fog futni a Pidgin más verzióival.\r\n\r\nHa frissíti a Pidginot, törölje vagy frissítse a plugint is.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_HUNGARIAN} "Kérlek, add meg a Pidgin helyét"
LangString DIR_INNERTEXT ${LANG_HUNGARIAN} "Telepítés ebbe a Pidgin könyvtárba:"

LangString FINISH_TITLE ${LANG_HUNGARIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Telepítése befejezõdött"
LangString FINISH_TEXT ${LANG_HUNGARIAN} "Újra kell indítanod a Pidginot, hogy betöltsön a plugin, majd a Pidgin beállításokban be kell kapcsolnod Pidgin-Encryption Plugint."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_HUNGARIAN} "Az encrypt.dll plugin törölve lesz a Pidgin/plugins könyvtárból. Folytassam?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_HUNGARIAN} "Pidgin-Encryption Plugin (csak törölhetõ)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_HUNGARIAN} "Az uninstaller nem talált bejegyzéseket a registryben a Pidgin-Encryptionhöz.$\rValószínüleg másik felhasználó telepítette a Pidgin-Encryptiont."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_HUNGARIAN} "Nincs jogod a Pidgin-Encryption törléséhez."



