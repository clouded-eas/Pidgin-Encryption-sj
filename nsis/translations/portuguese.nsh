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

LangString BAD_PIDGIN_VERSION_1 ${LANG_PORTUGUESE} "Versão incompatível.$\r$\n$\r$\nEsta versão do plugin do Pidgin-Encryption foi gerada para o Pidgin versão ${PIDGIN_VERSION}.  Aparentemente, tem o Pidgin versão"

LangString BAD_PIDGIN_VERSION_2 ${LANG_PORTUGUESE} "instalado.$\r$\n$\r$\nVá a http://pidgin-encrypt.sourceforge.net para mais informações."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_PORTUGUESE} "Não foi possível determinar a versão do Pidgin que está instalada. Verifique se é a versão ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_PORTUGUESE} "Instalador do Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_PORTUGUESE} "Nota: Esta versão do plugin foi feita para o Pidgin ${PIDGIN_VERSION}, e não irá instalar ou funcionar com outras versões do Pidgin.\r\n\r\nQuando actualizar a sua versão do Pidgin, deve desinstalar ou actualizar também este plugin.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_PORTUGUESE} "Por favor, indique o directório onde o Pidgin está instalado"
LangString DIR_INNERTEXT ${LANG_PORTUGUESE} "Instalar nesta pasta do Pidgin:"

LangString FINISH_TITLE ${LANG_PORTUGUESE} "Instalação do Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Completa"
LangString FINISH_TEXT ${LANG_PORTUGUESE} "É necessário reiniciar o Pidgin para que o plugin seja carregado, depois vá às preferências do Pidgin e active o plugin do Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_PORTUGUESE} "O plugin encrypt.dll vai ser apagado do seu directório Pidgin/plugins.  Continuar?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_PORTUGUESE} "Pidgin-Encryption Plugin (apenas remover)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_PORTUGUESE} "O desinstalador não conseguiu encontrar as entradas de registo para o Pidgin-Encryption.$\rÉ possível que outro utilizador tenha instalado o plugin."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_PORTUGUESE} "Não tem as permissões necessárias para desinstalar o plugin."
