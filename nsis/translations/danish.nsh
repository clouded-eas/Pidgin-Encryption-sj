;;
;;  danish.nsh
;;
;;  Danish language strings for the Windows Pidgin-Encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Morten Brix Pedersen <morten@wtf.dk>
;;  Version 1, sept 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_DANISH} "Pidgin-Encryption kræver at Pidgin er installeret. Du skal installere Pidgin før du installerer Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_DANISH} "Pidgin-Encryption (krypterings) modul til Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_DANISh} "Inkompatibel version.$\r$\n$\r$\nDenne version af Pidgin-Encryption var bygget til Pidgin version ${PIDGIN_VERSION}. Det ser ud til at du har Pidgin version"

LangString BAD_PIDGIN_VERSION_2 ${LANG_DANISH} "installeret.$\r$\n$\r$\nSe http://pidgin-encrypt.sourceforge.net for flere oplysninger."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_DANISH} "Jeg kan ikke se hvilken Pidgin version der er installeret. Sørg for at det er version ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_DANISH} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} installationsprogram"
LangString WELCOME_TEXT  ${LANG_DANISH} "Bemærk: Denne version af modulet er lavet til Pidgin ${PIDGIN_VERSION}, og vil ikke installere eller virke med andre versioner af Pidgin.\r\n\r\nNår du opgraderer din version af Pidgin, skal du sørge for at fjerne eller opgradere dette modul også.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_DANISH} "Vis mappen hvor Pidgin er installeret"
LangString DIR_INNERTEXT ${LANG_DANISH} "Installér i denne Pidgin mappe:"

LangString FINISH_TITLE ${LANG_DANISH} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} installation færdig"
LangString FINISH_TEXT ${LANG_DANISH} "Du skal genstarte Pidgin før modulet indlæses, derefter gå til indstillinger i Pidgin og slå Pidgin-Encryption modulet til."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_DANISH} "encrypt.dll modulet er ved at blive fjernet fra din Pidgin/plugins mappe. Fortsæt?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_DANISH} "Pidgin-Encryption modul (fjern kun)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_DANISH} "Af-installeringsprogrammet kunne ikke finde Pidgin-Encryption i registreringsdatabasen.$\rDet kan muligt at en anden bruger har installeret modulet."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_DANISH} "Du har ikke de nødvendige rettigheder til at installere modulet."



