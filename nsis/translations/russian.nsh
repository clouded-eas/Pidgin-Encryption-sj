;;
;;  russian.nsh
;;
;;  Russian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1251
;;  Author: Roman Sosenko <coloc75@yahoo.com>
;;  Version 1, Dec 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_RUSSIAN} "Перед установкой Pidgin encryption необходимо установить Pidgin. Установите Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_RUSSIAN} "Модуль Pidgin-Encryption для Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_RUSSIAN} "Несовместимая версия.$\r$\n$\r$\nЭта версия модуля Pidgin-Encryption была создана для версии Pidgin ${PIDGIN_VERSION}. На Вашем компьютере установлена версия Pidgin"

LangString BAD_PIDGIN_VERSION_2 ${LANG_RUSSIAN} "установлено.$\r$\n$\r$\nСмотрите http://pidgin-encrypt.sourceforge.net для более подробной информации."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_RUSSIAN} "Нам неизвестно, какая версия Pidgin установлена на Вашем компьютере. Убедитесь, что это версия ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_RUSSIAN} "Инсталлятор Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} "
LangString WELCOME_TEXT  ${LANG_RUSSIAN} "Внимание: Настоящая версия модуля создана для Pidgin ${PIDGIN_VERSION}, и не может быть установлена и функционировать с другими версиями Pidgin.\r\n\r\nВ случае обновления версии Pidgin Вам необходимо дезинсталлировать или обновить также и модуль.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_RUSSIAN} "Пожалуйста, найдите каталог, в котором установлен Pidgin"
LangString DIR_INNERTEXT ${LANG_RUSSIAN} "Установить в эту папку Pidgin:"

LangString FINISH_TITLE ${LANG_RUSSIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Установка завершена"
LangString FINISH_TEXT ${LANG_RUSSIAN} "Для загрузки модуля Вам будет необходимо запустить Pidgin заново, затем в опциях Pidgin активировать модуль Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_RUSSIAN} "Модуль encrypt.dll будет удалён с Вашего каталога Pidgin/модуль. Продолжить?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_RUSSIAN} "Модуль Pidgin-Encryption  (только удаление)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_RUSSIAN} "Деинсталлятор не может найти элементы реестра Pidgin-Encryption.$\rВероятно, модуль был установлен другим пользователем."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_RUSSIAN} "У Вас нет прав для деинсталляции модуля."



