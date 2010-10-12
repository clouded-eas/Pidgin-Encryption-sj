;;
;;  bulgarian.nsh
;;
;;  Bulgarian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1251
;;  Author: Lachezar Dobrev <l.dobrev@gmail.com>
;;  Version 1, Sep 2007
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_BULGARIAN} "Приставката Pidgin-Encryption изисква да имате инсталиран Pidgin. Трябва да инсталирате Pidgin преди Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_BULGARIAN} "Pidgin-Encryption приставка за Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_BULGARIAN} "Несъвместима версия.$\r$\n$\r$\nТази версия на приставката Pidgin-Encryption е създадена за версия на Pidgin ${PIDGIN_VERSION}. Изглежда имате инсталиран Pidgin версия"

LangString BAD_PIDGIN_VERSION_2 ${LANG_BULGARIAN} ".$\r$\n$\r$\nОтворете http://pidgin-encrypt.sourceforge.net/ за допълнителна информация."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_BULGARIAN} "Инсталаторът не успя да открие версията на инсталирания Pidgin. Моля уверете се, че имате инсталиран Pidgin версия ${PIDGIN_VERSION}."

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_BULGARIAN} "Инсталиране на Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_BULGARIAN} "Забележка: Тази версия на приставката е планирана за Pidgin версия ${PIDGIN_VERSION} и няма да се инсталира или функционира с други версии на Pidgin.\r\n\r\nПри обновяване на Pidgin, се налага да премахнете или обновите и приставката.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_BULGARIAN} "Моля укажете папката, където се намира Pidgin"
LangString DIR_INNERTEXT ${LANG_BULGARIAN} "Инсталиране в Pidgin папката:"

LangString FINISH_TITLE ${LANG_BULGARIAN} "Инсталацията на Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} приключи"
LangString FINISH_TEXT ${LANG_BULGARIAN} "Налага се да рестартирате Pidgin за да се зареди приставката, след това отворете списъка с приставки на Pidgin и включете приставката Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_BULGARIAN} "Приставката Pidgin-Encryption (encrypt.dll) ще бъде изтрита от Pidgin/plugins папката. Сигурни ли сте?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_BULGARIAN} "Pidgin-Encryption Приставка за Pidgin (само премахване)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_BULGARIAN} "Де-Инсталатора не успя да открие регистъра за инсталиране на Pidgin-Encryption.$\rВероятно инсталацията е била проведена от друг потребител."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_BULGARIAN} "Нямате права, достатъчни за премахване на приставката."
