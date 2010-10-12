;;
;;  slovenian.nsh
;;
;;  Slovenian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1250
;;  Author: Martin Srebotnjak <miles@filmsi.net>
;;  Version 2, Dec 2005
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_SLOVENIAN} "Šifriranje Pidgin zahteva namešèeni Pidgin. Pred namestitvijo Šifriranja Pidgin morate namestiti Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_SLOVENIAN} "Vstavek Šifriranje Pidgin za Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_SLOVENIAN} "Nekompatibilna razlièica.$\r$\n$\r$\nTa razlièica vstavka Šifriranja Pidgin je prirejena za Pidgin razlièice ${PIDGIN_VERSION}.  Kot kaže, imate namešèeno Pidgin razlièice "

LangString BAD_PIDGIN_VERSION_2 ${LANG_SLOVENIAN} ".$\r$\n$\r$\nZa veè informacij si poglejte stran http://pidgin-encrypt.sourceforge.net."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_SLOVENIAN} "Ni mogoèe ugotoviti, katera razlièica Pidgina je namešèena.  Preprièajte se, da je to razlièica ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_SLOVENIAN} "Namestitev Šifriranja Pidgin v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_SLOVENIAN} "Opomba: Ta razlièica vstavka je prirejena za Pidgin ${PIDGIN_VERSION} in ne bo namešèena ali delovala z drugimi razlièicami Pidgina.\r\n\r\nKo nadgradite razlièico Pidgina, ga morate odstraniti ali prav tako nadgraditi ta vstavek.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_SLOVENIAN} "Prosimo, poišèite mapo, kjer je namešèen Pidgin"
LangString DIR_INNERTEXT ${LANG_SLOVENIAN} "Namesti v to mapo Pidgin:"

LangString FINISH_TITLE ${LANG_SLOVENIAN} "Namestitev Šifriranja Pidgin v${PIDGIN-ENCRYPTION_VERSION} dokonèana"
LangString FINISH_TEXT ${LANG_SLOVENIAN} "Za nalaganje vstavka morate ponovno zagnati Pidgin ter v Možnostih Pidgina omogoèiti vstavek Šifriranje Pidgin."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_SLOVENIAN} "Datoteka encrypt.dll bo zbrisana iz mape Pidgin/plugins.  Želite nadaljevati?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_SLOVENIAN} "Vstavek Šifriranje Pidgin (samo odstrani)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_SLOVENIAN} "Program za odstranitev programa v registru ne najde vnosov za Šifriranje Pidgin.$\rVerjetno je vstavek namestil drug uporabnik."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_SLOVENIAN} "Nimate potrebnih pravic za odstranitev vstavka."



