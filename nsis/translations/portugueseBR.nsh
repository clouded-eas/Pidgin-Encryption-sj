;;
;;  portugueseBR.nsh
;;
;;  Portuguese language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Aury Fink Filho <nuny@aury.com.br>
;;  Version 1, oct 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_PORTUGUESEBR} "Pidgin-Encryption requer que o Pidgin esteja instalado. Voc� deve instalar o Pidgin antes de instalar o Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_PORTUGUESEBR} "Pidgin-Encryption plugin para Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_PORTUGUESEBR} "Vers�o incompat�vel.$\r$\n$\r$\nEsta vers�o do plugin do Pidgin-Encryption foi gerada para o Pidgin vers�o ${PIDGIN_VERSION}.  Aparentemente, voc� tem o Pidgin vers�o"

LangString BAD_PIDGIN_VERSION_2 ${LANG_PORTUGUESEBR} "instalado.$\r$\n$\r$\nVeja http://pidgin-encrypt.sourceforge.net para mais informa��es."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_PORTUGUESEBR} "Eu n�o posso dizer qual vers�o do Pidgin est� instalada. Verifique se � a vers�o ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_PORTUGUESEBR} "Instalador do Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_PORTUGUESEBR} "Nota: Essa vers�o do plugin foi feita para o Pidgin ${PIDGIN_VERSION}, e n�o ir� instalar ou funcionar com outras vers�es do Pidgin.\r\n\r\nQuando voc� atualizar sua vers�o do Pidgin, voc� deve desinstalar ou atualizar esse plugin tamb�m.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_PORTUGUESEBR} "Por favor, localize o diret�rio aonde o Pidgin est� instalado"
LangString DIR_INNERTEXT ${LANG_PORTUGUESEBR} "Instale nessa pasta do Pidgin:"

LangString FINISH_TITLE ${LANG_PORTUGUESEBR} "Instala��o do Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Finalizada"
LangString FINISH_TEXT ${LANG_PORTUGUESEBR} "Voc� necessita reiniciar o Pidgin para o plugin ser carregado, ent�o v� para as prefer�ncias do Pidgin e habilite o plugin do Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_PORTUGUESEBR} "O plugin encrypt.dll est� para ser deletado de seu diret�rio Pidgin/plugins.  Continuar?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_PORTUGUESEBR} "Pidgin-Encryption Plugin (apenas remover)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_PORTUGUESEBR} "O desintalador n�o pode encontrar as entradas no registro para o Pidgin-Encryption.$\rAparentemente, outro usu�rio instalou o plugin."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_PORTUGUESEBR} "Voc� n�o tem as permiss�es necess�rias para desinstalar o plugin."
