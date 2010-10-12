;;
;;  czech.nsh
;;
;;  Czech language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1250
;;  Author: Lubo� Stan�k <lubek@users.sourceforge.net>
;;  Version 1, Nov 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_CZECH} "Dopln�k Pidgin-Encryption vy�aduje nainstalovan� Pidgin. Mus�te nainstalovat Pidgin p�ed instalac� dopl�ku Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_CZECH} "Dopln�k Pidgin-Encryption pro Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_CZECH} "Nekompatibiln� verze.$\r$\n$\r$\nTato verze dopl�ku Pidgin-Encryption byla vytvo�ena pro Pidgin ve verzi ${PIDGIN_VERSION}. Zd� se, �e m�te nainstalov�nu verzi"

LangString BAD_PIDGIN_VERSION_2 ${LANG_CZECH} "programu Pidgin.$\r$\n$\r$\nV�ce informac� z�sk�te n�v�t�vou http://pidgin-encrypt.sourceforge.net."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_CZECH} "Nelze zjistit, jak� verze programu Pidgin je nainstalov�na. Ujist�te se, �e je to verze ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_CZECH} "Instalace dopl�ku Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_CZECH} "Pozn�mka: Tato verze dopl�ku je navr�ena pro Pidgin ${PIDGIN_VERSION}, nenainstaluje se ani nebude fungovat s jin�mi verzemi programu Pidgin.\r\n\r\nKdy� aktualizujete svou verzi programu Pidgin, mus�te odinstalovat nebo aktualizovat tak� tento dopln�k.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_CZECH} "Lokalizujte pros�m slo�ku, kam je nainstalov�n program Pidgin"
LangString DIR_INNERTEXT ${LANG_CZECH} "Instalovat do t�to slo�ky programu Pidgin:"

LangString FINISH_TITLE ${LANG_CZECH} "Instalace dopl�ku Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} je dokon�ena"
LangString FINISH_TEXT ${LANG_CZECH} "Je t�eba restartovat Pidgin, aby se dopln�k na�etl. Pak jd�te do nastaven� programu Pidgin a povolte dopln�k Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_CZECH} "Dopln�k encrypt.dll m� b�t vymaz�n z va�� slo�ky dopl�k� programu Pidgin. Pokra�ovat?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_CZECH} "Pidgin-Encryption dopln�k (pouze odebrat)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_CZECH} "Odinstal�tor nem��e naj�t polo�ky registru pro Pidgin-Encryption.$\rNejsp�e instaloval dopln�k jin� u�ivatel."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_CZECH} "Nem�te dostate�n� opr�vn�n� pro odinstalaci dopl�ku."



