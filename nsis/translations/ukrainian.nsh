;;
;;  ukrainian.nsh
;;
;;  Ukrainian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1251
;;  Author: Roman Sosenko <coloc75@yahoo.com>
;;  Version 1, Jan 2005
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_UKRAINIAN} "Перед встановленням Pidgin encryption необхідно встановити Pidgin. Встановіть Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_UKRAINIAN} "Модуль Pidgin-Encryption для Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_UKRAINIAN} "Несумісна версія.$\r$\n$\r$\nЦя версія модуля Pidgin-Encryption була створена для версії Pidgin ${PIDGIN_VERSION}. На Вашому комп'ютері встановлена версія Pidgin"

LangString BAD_PIDGIN_VERSION_2 ${LANG_UKRAINIAN} "Встановлено.$\r$\n$\r$\nДивіться http://pidgin-encrypt.sourceforge.net для більш детальної інформації."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_UKRAINIAN} "Нам невідомо, яка версія Pidgin встановлена на Вашому комп'ютері. Переконайтеся, що це версія ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_UKRAINIAN} "Інсталятор Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} "
LangString WELCOME_TEXT  ${LANG_UKRAINIAN} "Увага: Ця версія модуля створена для Pidgin ${PIDGIN_VERSION}, і не може бути встановленою і працювати з іншими версіями Pidgin.\r\n\r\nУ випадку оновлення версії Pidgin Вам необхідно дезінсталювати чи обновити також і модуль.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_UKRAINIAN} "Будь ласка, знайдіть каталог, у якому встановлено Pidgin"
LangString DIR_INNERTEXT ${LANG_UKRAINIAN} "Встановити у цб папку Pidgin:"

LangString FINISH_TITLE ${LANG_UKRAINIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Встановлення завершено"
LangString FINISH_TEXT ${LANG_UKRAINIAN} "Для завантаження модуля Вам буде необхідно запустити Pidgin повторно, після чого в опціях Pidgin активувати модуль Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_UKRAINIAN} "Модуль encrypt.dll буде видалений з Вашого каталога Pidgin/модуль. Продовжити?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_UKRAINIAN} "Модуль Pidgin-Encryption  (лише видалення)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_UKRAINIAN} "Деінсталятор не може знайти елементи реєстра Pidgin-Encryption.$\rЙмовірно, модуль був установлений іншим користувачем."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_UKRAINIAN} "У Вас немає прав для деінсталяції модуля."



