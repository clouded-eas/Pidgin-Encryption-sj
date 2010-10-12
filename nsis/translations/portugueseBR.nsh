;;
;;  portugueseBR.nsh
;;
;;  Portuguese language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Aury Fink Filho <nuny@aury.com.br>
;;  Version 1, oct 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_PORTUGUESEBR} "Pidgin-Encryption requer que o Pidgin esteja instalado. Você deve instalar o Pidgin antes de instalar o Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_PORTUGUESEBR} "Pidgin-Encryption plugin para Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_PORTUGUESEBR} "Versão incompatível.$\r$\n$\r$\nEsta versão do plugin do Pidgin-Encryption foi gerada para o Pidgin versão ${PIDGIN_VERSION}.  Aparentemente, você tem o Pidgin versão"

LangString BAD_PIDGIN_VERSION_2 ${LANG_PORTUGUESEBR} "instalado.$\r$\n$\r$\nVeja http://pidgin-encrypt.sourceforge.net para mais informações."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_PORTUGUESEBR} "Eu não posso dizer qual versão do Pidgin está instalada. Verifique se é a versão ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_PORTUGUESEBR} "Instalador do Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_PORTUGUESEBR} "Nota: Essa versão do plugin foi feita para o Pidgin ${PIDGIN_VERSION}, e não irá instalar ou funcionar com outras versões do Pidgin.\r\n\r\nQuando você atualizar sua versão do Pidgin, você deve desinstalar ou atualizar esse plugin também.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_PORTUGUESEBR} "Por favor, localize o diretório aonde o Pidgin está instalado"
LangString DIR_INNERTEXT ${LANG_PORTUGUESEBR} "Instale nessa pasta do Pidgin:"

LangString FINISH_TITLE ${LANG_PORTUGUESEBR} "Instalação do Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} Finalizada"
LangString FINISH_TEXT ${LANG_PORTUGUESEBR} "Você necessita reiniciar o Pidgin para o plugin ser carregado, então vá para as preferências do Pidgin e habilite o plugin do Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_PORTUGUESEBR} "O plugin encrypt.dll está para ser deletado de seu diretório Pidgin/plugins.  Continuar?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_PORTUGUESEBR} "Pidgin-Encryption Plugin (apenas remover)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_PORTUGUESEBR} "O desintalador não pode encontrar as entradas no registro para o Pidgin-Encryption.$\rAparentemente, outro usuário instalou o plugin."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_PORTUGUESEBR} "Você não tem as permissões necessárias para desinstalar o plugin."
