;;
;;  spanish.nsh
;;
;;  Spanish language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Javier Fernández-Sanguino Peña <jfs@computer.org>
;;  Version 1, sept 2004 
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_SPANISH} "Pidgin-Encryption necesita que Pidgin esté instalado. Debe instalar Pidgin antes de instalar Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_SPANISH} "Complemento de Cifrado de Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_SPANISH} "Versión incompatible.$\r$\n$\r$\nEsta versión del complemento de Cifrado de Pidgin se preparó para la versión ${PIDGIN_VERSION} de Pidgin.  Parece que vd. tiene la versión de Pidgin"

LangString BAD_PIDGIN_VERSION_2 ${LANG_SPANISH} "instalada.$\r$\n$\r$\nPara más información consulte http://pidgin-encrypt.sourceforge.net"

LangString UNKNOWN_PIDGIN_VERSION ${LANG_SPANISH} "No puedo determinar la versión de Pidgin que tiene instalada. Asegúrese de que es la versión ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_SPANISH} "Instalador de Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_SPANISH} "Aviso: Esta versión del complemento fue diseñada para la versión ${PIDGIN_VERSION} de Pidgin y no se podrá instalar ni funcionará con otras versiones.\r\n\r\nCuando actualice su versión de Pidgin debe desinstalar o actualizar este complemento.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_SPANISH} "Por favor, localice el directorio donde está instalado Pidgin"
LangString DIR_INNERTEXT ${LANG_SPANISH} "Instalar en este directorio de Pidgin:"

LangString FINISH_TITLE ${LANG_SPANISH} "Se ha completado la instalación de Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString FINISH_TEXT ${LANG_SPANISH} "Deberá reiniciar Pidgin para que se cargue el complemento, después vaya a las preferencias de Pidgin y active el complemento de Cifrado de Pidgin."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_SPANISH} "Se va a borrar el complemento encrypt.dll de su directorio de complementos de Pidgin. ¿Desea continuar?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_SPANISH} "Complemento Pidgin-Encryption Plugin (sólo desinstalación)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_SPANISH} "El desinstalador no pudo encontrar las entradas de registro de Pidgin-Encryption.$\rEs posible que otro usuario haya instalado el complemento."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_SPANISH} "No tiene los permisos necesarios para desinstalar el complemento."



