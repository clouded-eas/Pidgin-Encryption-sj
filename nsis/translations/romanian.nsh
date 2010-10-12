;;
;;  romanian.nsh
;;
;;  English language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1250
;;  Author: Miºu Moldovan <dumol@gnome.ro>
;;  Version 1, Nov 2003
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_ROMANIAN} "Modulul de criptare Pidgin necesitã programul Pidgin. Instalaþi Pidgin înainte sã instalaþi criptarea Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_ROMANIAN} "Modul de criptare a discuþiilor Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_ROMANIAN} "Versiune incompatibilã.$\r$\n$\r$\nAceastã versiune a modulului de criptare Pidgin a fost compilatã pentru Pidgin versiunea ${PIDGIN_VERSION}. Se pare cã aveþi Pidgin versiunea"

LangString BAD_PIDGIN_VERSION_2 ${LANG_ROMANIAN} "instalatã.$\r$\n$\r$\nVizitaþi http://pidgin-encrypt.sourceforge.net pentru detalii."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_ROMANIAN} "Nu se poate detecta versiunea Pidgin instalatã. Asiguraþi-vã cã este versiunea ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_ROMANIAN} "Instalare Criptare Pidgin v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_ROMANIAN} "Notã: Aceastã versiune a modulului de criptare Pidgin este compilatã pentru Pidgin ${PIDGIN_VERSION} ºi nu va funcþiona corect cu alte versiuni Pidgin.\r\n\r\nCând veþi instala o altã versiune Pidgin va trebui sã dezinstalaþi ori sã actualizaþi acest modul.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_ROMANIAN} "Localizaþi directorul în care e instalat Pidgin"
LangString DIR_INNERTEXT ${LANG_ROMANIAN} "Instalare în directorul Pidgin:"

LangString FINISH_TITLE ${LANG_ROMANIAN} "Instalarea modulului de criptare Pidgin v${PIDGIN-ENCRYPTION_VERSION} s-a terminat"
LangString FINISH_TEXT ${LANG_ROMANIAN} "Pentru încãrcarea modulului nou instalat va trebui sã reporniþi Pidgin ºi sã activaþi modulul „Criptare Pidgin” în preferinþele Pidgin."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_ROMANIAN} "Fiºierul encrypt.dlleste pe cale sã fie ºters din directorul cu module Pidgin. Continuaþi?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_ROMANIAN} "Modul de criptare Pidgin (doar dezinstalare)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_ROMANIAN} "Nu s-au gãsit în regiºtri intrãri specifice modulului de criptare Pidgin.$\rProbabil un alt utilizator a instalat acest modul."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_ROMANIAN} "Nu aveþi drepturile necesare pentru a dezinstala acest modul."



