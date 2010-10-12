;;
;;  lithuanian.nsh
;;
;;  Lithuanian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1257
;;  Author: Andrius �tikonas <stikonas@gmail.com>
;;  Version 1, Feb 2006
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_LITHUANIAN} "Pidgin-Encryption reikia �diegto Pidgin. J�s privalote �diegti Pidgin prie� instaliuodami Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_LITHUANIAN} "Pidgin-Encryption �skiepis Pidgin programai"

LangString BAD_PIDGIN_VERSION_1 ${LANG_LITHUANIAN} "Nesuderinama versija.$\r$\n$\r$\n�i Pidgin-Encryption �skiepio versija buvo sukurta Pidgin versijai ${PIDGIN_VERSION}.  Atrodo, kad j�s turite instaliuot� Pidgin"

LangString BAD_PIDGIN_VERSION_2 ${LANG_LITHUANIAN} "versij�.$\r$\n$\r$\nPla�iau �i�r�ti http://pidgin-encrypt.sourceforge.net."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_LITHUANIAN} "A� negaliu pasakyti, kuri Pidgin versija �diegta. �sitikinkite, kad tai {PIDGIN_VERSION} versija"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_LITHUANIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} diegimo programa"
LangString WELCOME_TEXT  ${LANG_LITHUANIAN} "Pastaba: �i �skiepio versija sukurta Pidgin ${PIDGIN_VERSION}, ir negali b�ti instaliuota ar funkcionuoti su kitomis Pidgin versijomis.\r\n\r\nKai atnaujinate Pidgin, taip pat turite i�instaliuoti arba atnaujinti �� �skiep�.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_LITHUANIAN} "Nurodykite katalog�, kuriame �diegtas Pidgin"
LangString DIR_INNERTEXT ${LANG_LITHUANIAN} "�diegti � �� Pidgin katalog�:"

LangString FINISH_TITLE ${LANG_LITHUANIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} diegimas baigtas"
LangString FINISH_TEXT ${LANG_LITHUANIAN} "J�s turite perkrauti Pidgin tam, kad �skiepis b�t� pakrautas, tada eikite � pidgin nustatymus ir �galinkite Pidgin-Encryption �skiep�."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_LITHUANIAN} "encrypt.dll �skiepis bus i�trintas i� Pidgin/plugins katalogo.  T�sti?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_LITHUANIAN} "Pidgin-Encryption �skiepis (tik pa�alinti)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_LITHUANIAN} "�alinimo vedlys negali rasti Pidgin-Encryption registro �ra�� .$\rMatyt kitas vartotojas �skiep� jau i�tryn�."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_LITHUANIAN} "J�s neturite teisi�, b�tin� �skiepio pa�alinimui."



