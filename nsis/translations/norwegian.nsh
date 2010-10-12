;;
;;  norwegian_nynorsk.nsh
;;
;;  Norwegian (Nynorsk) language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Y J Landro <nynorsk@strilen.net>
;;  Version 1, 2006-02
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_NORWEGIAN} "Pidgin-Encryption nyttar Pidgin. Installer Pidgin før du installerer Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_NORWEGIAN} "Pidgin-Encryption: programtillegg for Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_NORWEGIAN} "Ikkje-kompatibel versjon.$\r$\n$\r$\nDenne versjonen av programtillegget Pidgin-Encryption blei laga for Pidgin versjon ${PIDGIN_VERSION}.  Det ser ut til at du har Pidgin versjon"

LangString BAD_PIDGIN_VERSION_2 ${LANG_NORWEGIAN} "installert.$\r$\n$\r$\nSida http://pidgin-encrypt.sourceforge.net gjev deg meir informasjon."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_NORWEGIAN} "Eg kan ikkje sjå kva for versjon av Pidgin som er installert. Sjå til at det er versjon ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_NORWEGIAN} "Installasjonsprogram for Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_NORWEGIAN} "Hugs: denne versjonen av programtillegget er laga for Pidgin ${PIDGIN_VERSION} og vil ikkje kunne installerast eller fungera med andre versjonar.\r\n\r\nNår du oppdaterer Pidgin-versjonen din, må du anten av-installera eller oppgradera dette programtillegget òg.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_NORWEGIAN} "Finn programkatalogen til Pidgin"
LangString DIR_INNERTEXT ${LANG_NORWEGIAN} "Installer i denne Pidgin-mappa:"

LangString FINISH_TITLE ${LANG_NORWEGIAN} "Installasjonen av Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} er ferdig."
LangString FINISH_TEXT ${LANG_NORWEGIAN} "Du må starta om Pidgin for at programtillegget skal fungera. Deretter må du gå til innstillingane og aktivera Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_NORWEGIAN} "Programtillegget encrypt.dll vil bli sletta frå Pidgin sin programtilleggskatalog.  Vil du fortsetja?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_NORWEGIAN} "Programtilleggget Pidgin-Encryption (berre fjerna)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_NORWEGIAN} "Avinstallasjonsprogrammet fann ingen registerpostar for Pidgin-Encryption.$\rEin annan brukar kan ha installert programtillegget."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_NORWEGIAN} "Du har ikkje dei nødvendige rettane til å avinstallera programtillegget."


