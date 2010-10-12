;;
;;  lithuanian.nsh
;;
;;  Lithuanian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1257
;;  Author: Andrius Ðtikonas <stikonas@gmail.com>
;;  Version 1, Feb 2006
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_LITHUANIAN} "Pidgin-Encryption reikia ádiegto Pidgin. Jûs privalote ádiegti Pidgin prieð instaliuodami Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_LITHUANIAN} "Pidgin-Encryption áskiepis Pidgin programai"

LangString BAD_PIDGIN_VERSION_1 ${LANG_LITHUANIAN} "Nesuderinama versija.$\r$\n$\r$\nÐi Pidgin-Encryption áskiepio versija buvo sukurta Pidgin versijai ${PIDGIN_VERSION}.  Atrodo, kad jûs turite instaliuotà Pidgin"

LangString BAD_PIDGIN_VERSION_2 ${LANG_LITHUANIAN} "versijà.$\r$\n$\r$\nPlaèiau þiûrëti http://pidgin-encrypt.sourceforge.net."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_LITHUANIAN} "Að negaliu pasakyti, kuri Pidgin versija ádiegta. Ásitikinkite, kad tai {PIDGIN_VERSION} versija"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_LITHUANIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} diegimo programa"
LangString WELCOME_TEXT  ${LANG_LITHUANIAN} "Pastaba: ði áskiepio versija sukurta Pidgin ${PIDGIN_VERSION}, ir negali bûti instaliuota ar funkcionuoti su kitomis Pidgin versijomis.\r\n\r\nKai atnaujinate Pidgin, taip pat turite iðinstaliuoti arba atnaujinti ðá áskiepá.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_LITHUANIAN} "Nurodykite katalogà, kuriame ádiegtas Pidgin"
LangString DIR_INNERTEXT ${LANG_LITHUANIAN} "Ádiegti á ðá Pidgin katalogà:"

LangString FINISH_TITLE ${LANG_LITHUANIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} diegimas baigtas"
LangString FINISH_TEXT ${LANG_LITHUANIAN} "Jûs turite perkrauti Pidgin tam, kad áskiepis bûtø pakrautas, tada eikite á pidgin nustatymus ir ágalinkite Pidgin-Encryption áskiepá."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_LITHUANIAN} "encrypt.dll áskiepis bus iðtrintas ið Pidgin/plugins katalogo.  Tæsti?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_LITHUANIAN} "Pidgin-Encryption áskiepis (tik paðalinti)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_LITHUANIAN} "Ðalinimo vedlys negali rasti Pidgin-Encryption registro áraðø .$\rMatyt kitas vartotojas áskiepá jau iðtrynë."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_LITHUANIAN} "Jûs neturite teisiø, bûtinø áskiepio paðalinimui."



