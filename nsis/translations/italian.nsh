;;
;;  italian.nsh
;;
;;  Italian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Giacomo Succi <giacsu@sourceforge.net>
;;  Version 1, Sep 2004
;;


; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_ITALIAN} "Pidgin-Encryption richiede che Pidgin sia installato. Dovete installare Pidgin prima di installare Pidgin-Encryption."
LangString PIDGIN-ENCRYPTION_TITLE ${LANG_ITALIAN} "Pidgin-Encryption, plugin per Pidgin"
LangString BAD_PIDGIN_VERSION_1 ${LANG_ITALIAN} "Versione incompatibile.$\r$\n$\r$\nLa presente versione di Pidgin-Encryption e' stata compilata per la versione di Pidgin ${PIDGIN_VERSION}.  Sembra che avete una versione di Pidgin incompatibile"
LangString BAD_PIDGIN_VERSION_2 ${LANG_ITALIAN} "installata.$\r$\n$\r$\nVisitate http://pidgin-encrypt.sourceforge.net per maggiori informazioni."
LangString UNKNOWN_PIDGIN_VERSION ${LANG_ITALIAN} "Non posso determinare quale versione di Pidgin sia installata.  Siate certi che la versione sia la ${PIDGIN_VERSION}"

; Overrides for default text in windows:
LangString WELCOME_TITLE ${LANG_ITALIAN} "Installatore di Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_ITALIAN} "Nota: Questo plugin e' stato pensato per Pidgin ${PIDGIN_VERSION}, e non si installera' o funzionera' con altre versioni di Pidgin.\r\n\r\nQuando aggiornerete la vostra versione di Pidgin, dovete rimuovere o aggiornare questo plugin di conseguenza.\r\n\r\n"
LangString DIR_SUBTITLE ${LANG_ITALIAN} "Perfavore indicate la cartella dove Pidgin e' installato"
LangString DIR_INNERTEXT ${LANG_ITALIAN} "Installa in questa cartella di Pidgin:"
LangString FINISH_TITLE ${LANG_ITALIAN} "Installazione completata di Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString FINISH_TEXT ${LANG_ITALIAN} "Dovete chiudere e riavviare Pidgin per far caricare il plugin, dopo di che andate nelle preferenze di Pidgin e abilitate Pidgin-Encryption Plugin."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_ITALIAN} "Il plugin encrypt.dll sta per essere rimosso dalla cartella Pidgin/plugins.  Continuare?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_ITALIAN} "Pidgin-Encryption Plugin (soltanto rimozione)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_ITALIAN} "L'uninstallatore non puo' trovare le entry nel registro per Pidgin-Encryption.$\rE' probabile che un'altro utente abbia installato il plugin."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_ITALIAN} "Non avete i diritti necessari per rimuovere il plugin."
