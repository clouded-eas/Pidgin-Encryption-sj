;;
;;  spanish.nsh
;;
;;  Spanish language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Javier Fern�ndez-Sanguino Pe�a <jfs@computer.org>
;;  Version 1, sept 2004 
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_SPANISH} "Pidgin-Encryption necesita que Pidgin est� instalado. Debe instalar Pidgin antes de instalar Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_SPANISH} "Complemento de Cifrado de Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_SPANISH} "Versi�n incompatible.$\r$\n$\r$\nEsta versi�n del complemento de Cifrado de Pidgin se prepar� para la versi�n ${PIDGIN_VERSION} de Pidgin.  Parece que vd. tiene la versi�n de Pidgin"

LangString BAD_PIDGIN_VERSION_2 ${LANG_SPANISH} "instalada.$\r$\n$\r$\nPara m�s informaci�n consulte http://pidgin-encrypt.sourceforge.net"

LangString UNKNOWN_PIDGIN_VERSION ${LANG_SPANISH} "No puedo determinar la versi�n de Pidgin que tiene instalada. Aseg�rese de que es la versi�n ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_SPANISH} "Instalador de Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_SPANISH} "Aviso: Esta versi�n del complemento fue dise�ada para la versi�n ${PIDGIN_VERSION} de Pidgin y no se podr� instalar ni funcionar� con otras versiones.\r\n\r\nCuando actualice su versi�n de Pidgin debe desinstalar o actualizar este complemento.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_SPANISH} "Por favor, localice el directorio donde est� instalado Pidgin"
LangString DIR_INNERTEXT ${LANG_SPANISH} "Instalar en este directorio de Pidgin:"

LangString FINISH_TITLE ${LANG_SPANISH} "Se ha completado la instalaci�n de Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString FINISH_TEXT ${LANG_SPANISH} "Deber� reiniciar Pidgin para que se cargue el complemento, despu�s vaya a las preferencias de Pidgin y active el complemento de Cifrado de Pidgin."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_SPANISH} "Se va a borrar el complemento encrypt.dll de su directorio de complementos de Pidgin. �Desea continuar?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_SPANISH} "Complemento Pidgin-Encryption Plugin (s�lo desinstalaci�n)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_SPANISH} "El desinstalador no pudo encontrar las entradas de registro de Pidgin-Encryption.$\rEs posible que otro usuario haya instalado el complemento."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_SPANISH} "No tiene los permisos necesarios para desinstalar el complemento."



