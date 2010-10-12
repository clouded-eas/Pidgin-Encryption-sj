;;
;;  slovenian.nsh
;;
;;  Slovenian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1250
;;  Author: Martin Srebotnjak <miles@filmsi.net>
;;  Version 2, Dec 2005
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_SLOVENIAN} "�ifriranje Pidgin zahteva name��eni Pidgin. Pred namestitvijo �ifriranja Pidgin morate namestiti Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_SLOVENIAN} "Vstavek �ifriranje Pidgin za Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_SLOVENIAN} "Nekompatibilna razli�ica.$\r$\n$\r$\nTa razli�ica vstavka �ifriranja Pidgin je prirejena za Pidgin razli�ice ${PIDGIN_VERSION}.  Kot ka�e, imate name��eno Pidgin razli�ice "

LangString BAD_PIDGIN_VERSION_2 ${LANG_SLOVENIAN} ".$\r$\n$\r$\nZa ve� informacij si poglejte stran http://pidgin-encrypt.sourceforge.net."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_SLOVENIAN} "Ni mogo�e ugotoviti, katera razli�ica Pidgina je name��ena.  Prepri�ajte se, da je to razli�ica ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_SLOVENIAN} "Namestitev �ifriranja Pidgin v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_SLOVENIAN} "Opomba: Ta razli�ica vstavka je prirejena za Pidgin ${PIDGIN_VERSION} in ne bo name��ena ali delovala z drugimi razli�icami Pidgina.\r\n\r\nKo nadgradite razli�ico Pidgina, ga morate odstraniti ali prav tako nadgraditi ta vstavek.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_SLOVENIAN} "Prosimo, poi��ite mapo, kjer je name��en Pidgin"
LangString DIR_INNERTEXT ${LANG_SLOVENIAN} "Namesti v to mapo Pidgin:"

LangString FINISH_TITLE ${LANG_SLOVENIAN} "Namestitev �ifriranja Pidgin v${PIDGIN-ENCRYPTION_VERSION} dokon�ana"
LangString FINISH_TEXT ${LANG_SLOVENIAN} "Za nalaganje vstavka morate ponovno zagnati Pidgin ter v Mo�nostih Pidgina omogo�iti vstavek �ifriranje Pidgin."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_SLOVENIAN} "Datoteka encrypt.dll bo zbrisana iz mape Pidgin/plugins.  �elite nadaljevati?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_SLOVENIAN} "Vstavek �ifriranje Pidgin (samo odstrani)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_SLOVENIAN} "Program za odstranitev programa v registru ne najde vnosov za �ifriranje Pidgin.$\rVerjetno je vstavek namestil drug uporabnik."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_SLOVENIAN} "Nimate potrebnih pravic za odstranitev vstavka."



