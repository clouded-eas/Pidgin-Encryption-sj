;;
;;  romanian.nsh
;;
;;  English language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1250
;;  Author: Mi�u Moldovan <dumol@gnome.ro>
;;  Version 1, Nov 2003
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_ROMANIAN} "Modulul de criptare Pidgin necesit� programul Pidgin. Instala�i Pidgin �nainte s� instala�i criptarea Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_ROMANIAN} "Modul de criptare a discu�iilor Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_ROMANIAN} "Versiune incompatibil�.$\r$\n$\r$\nAceast� versiune a modulului de criptare Pidgin a fost compilat� pentru Pidgin versiunea ${PIDGIN_VERSION}. Se pare c� ave�i Pidgin versiunea"

LangString BAD_PIDGIN_VERSION_2 ${LANG_ROMANIAN} "instalat�.$\r$\n$\r$\nVizita�i http://pidgin-encrypt.sourceforge.net pentru detalii."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_ROMANIAN} "Nu se poate detecta versiunea Pidgin instalat�. Asigura�i-v� c� este versiunea ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_ROMANIAN} "Instalare Criptare Pidgin v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_ROMANIAN} "Not�: Aceast� versiune a modulului de criptare Pidgin este compilat� pentru Pidgin ${PIDGIN_VERSION} �i nu va func�iona corect cu alte versiuni Pidgin.\r\n\r\nC�nd ve�i instala o alt� versiune Pidgin va trebui s� dezinstala�i ori s� actualiza�i acest modul.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_ROMANIAN} "Localiza�i directorul �n care e instalat Pidgin"
LangString DIR_INNERTEXT ${LANG_ROMANIAN} "Instalare �n directorul Pidgin:"

LangString FINISH_TITLE ${LANG_ROMANIAN} "Instalarea modulului de criptare Pidgin v${PIDGIN-ENCRYPTION_VERSION} s-a terminat"
LangString FINISH_TEXT ${LANG_ROMANIAN} "Pentru �nc�rcarea modulului nou instalat va trebui s� reporni�i Pidgin �i s� activa�i modulul �Criptare Pidgin� �n preferin�ele Pidgin."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_ROMANIAN} "Fi�ierul encrypt.dlleste pe cale s� fie �ters din directorul cu module Pidgin. Continua�i?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_ROMANIAN} "Modul de criptare Pidgin (doar dezinstalare)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_ROMANIAN} "Nu s-au g�sit �n regi�tri intr�ri specifice modulului de criptare Pidgin.$\rProbabil un alt utilizator a instalat acest modul."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_ROMANIAN} "Nu ave�i drepturile necesare pentru a dezinstala acest modul."



