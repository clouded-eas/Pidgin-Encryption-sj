;;
;;  portuguese.nsh
;;
;;  Portuguese language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Pedro Pinto <ei10066@alunos.ipb.pt>
;;  Version 21, aug 2007
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_PORTUGUESE} "O Pidgin-Encryption requer que o Pidgin esteja instalado. Deve instalar o Pidgin antes de instalar o Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_PORTUGUESE} "Plugin Pidgin-Encryption para o Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_PORTUGUESE} "Vers�o incompat�vel.$\r$\n$\r$\nEsta vers�o do plugin do Pidgin-Encryption foi gerada para o Pidgin vers�o ${PIDGIN_VERSION}.  Aparentemente, tem o Pidgin vers�o"

LangString BAD_PIDGIN_VERSION_2 ${LANG_PORTUGUESE} "instalado.$\r$\n$\r$\nV� a http://pidgin-encrypt.sourceforge.net para mais informa��es."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_PORTUGUESE} "N�o foi poss�vel determinar a vers�o do Pidgin que est� instalada. Verifique se � a vers�o ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_PORTUGUESE} "Instalador do Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_PORTUGUESE} "Nota: Esta vers�o do plugin foi feita para o Pidgin ${PIDGIN_VERSION}, e n�o ir� instalar ou funcionar com outras vers�es do Pidgin.\r\n\r\nQuando actualizar a sua vers�o do Pidgin, deve desinstalar ou actualizar tamb�m este plugin.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_PORTUGUESE} "Por favor, indique o direct�rio onde o Pidgin est� instalado"
LangString DIR_INNERTEXT ${LANG_PORTUGUESE} "Instalar nesta pasta do Pidgin:"

LangString FINISH_TITLE ${LANG_PORTUGUESE} "Instala��o do Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Completa"
LangString FINISH_TEXT ${LANG_PORTUGUESE} "� necess�rio reiniciar o Pidgin para que o plugin seja carregado, depois v� �s prefer�ncias do Pidgin e active o plugin do Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_PORTUGUESE} "O plugin encrypt.dll vai ser apagado do seu direct�rio Pidgin/plugins.  Continuar?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_PORTUGUESE} "Pidgin-Encryption Plugin (apenas remover)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_PORTUGUESE} "O desinstalador n�o conseguiu encontrar as entradas de registo para o Pidgin-Encryption.$\r� poss�vel que outro utilizador tenha instalado o plugin."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_PORTUGUESE} "N�o tem as permiss�es necess�rias para desinstalar o plugin."
