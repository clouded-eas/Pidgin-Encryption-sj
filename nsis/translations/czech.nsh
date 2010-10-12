;;
;;  czech.nsh
;;
;;  Czech language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1250
;;  Author: Luboš Stanìk <lubek@users.sourceforge.net>
;;  Version 1, Nov 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_CZECH} "Doplnìk Pidgin-Encryption vyžaduje nainstalovaný Pidgin. Musíte nainstalovat Pidgin pøed instalací doplòku Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_CZECH} "Doplnìk Pidgin-Encryption pro Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_CZECH} "Nekompatibilní verze.$\r$\n$\r$\nTato verze doplòku Pidgin-Encryption byla vytvoøena pro Pidgin ve verzi ${PIDGIN_VERSION}. Zdá se, že máte nainstalovánu verzi"

LangString BAD_PIDGIN_VERSION_2 ${LANG_CZECH} "programu Pidgin.$\r$\n$\r$\nVíce informací získáte návštìvou http://pidgin-encrypt.sourceforge.net."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_CZECH} "Nelze zjistit, jaká verze programu Pidgin je nainstalována. Ujistìte se, že je to verze ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_CZECH} "Instalace doplòku Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_CZECH} "Poznámka: Tato verze doplòku je navržena pro Pidgin ${PIDGIN_VERSION}, nenainstaluje se ani nebude fungovat s jinými verzemi programu Pidgin.\r\n\r\nKdyž aktualizujete svou verzi programu Pidgin, musíte odinstalovat nebo aktualizovat také tento doplnìk.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_CZECH} "Lokalizujte prosím složku, kam je nainstalován program Pidgin"
LangString DIR_INNERTEXT ${LANG_CZECH} "Instalovat do této složky programu Pidgin:"

LangString FINISH_TITLE ${LANG_CZECH} "Instalace doplòku Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} je dokonèena"
LangString FINISH_TEXT ${LANG_CZECH} "Je tøeba restartovat Pidgin, aby se doplnìk naèetl. Pak jdìte do nastavení programu Pidgin a povolte doplnìk Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_CZECH} "Doplnìk encrypt.dll má být vymazán z vaší složky doplòkù programu Pidgin. Pokraèovat?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_CZECH} "Pidgin-Encryption doplnìk (pouze odebrat)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_CZECH} "Odinstalátor nemùže najít položky registru pro Pidgin-Encryption.$\rNejspíše instaloval doplnìk jiný uživatel."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_CZECH} "Nemáte dostateèná oprávnìní pro odinstalaci doplòku."



