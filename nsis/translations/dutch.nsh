;;
;;  dutch.nsh
;;
;;  Default language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1252
;;  Author: Menno Jonkers <pidgin-encryption@jonkers.com>
;;  Version 1, September 5, 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_DUTCH} "Pidgin-encryptie vereist dat Pidgin geïnstalleerd is.  U moet Pidgin installeren voordat u Pidgin-encryptie installeert."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_DUTCH} "Pidgin-encryptie plugin voor Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_DUTCH} "Incompatibele versie.$\r$\n$\r$\nDeze versie van de Pidgin-encryptie plugin is gemaakt voor Pidgin versie ${PIDGIN_VERSION}.  Het lijkt erop dat u Pidgin versie"

LangString BAD_PIDGIN_VERSION_2 ${LANG_DUTCH} "geïnstalleerd heeft.$\r$\n$\r$\nZie http://pidgin-encrypt.sourceforge.net voor meer informatie."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_DUTCH} "Er kan niet worden vastgesteld welke versie van Pidgin u geïnstalleerd heeft.  Controleert u dat dit versie ${PIDGIN_VERSION} is"


; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_DUTCH} "Pidgin-encryptie v${PIDGIN-ENCRYPTION_VERSION} Installatie"
LangString WELCOME_TEXT  ${LANG_DUTCH} "Let op: deze versie van de plugin is gemaakt voor Pidgin ${PIDGIN_VERSION} en zal niet installeren of werken met andere versies van Pidgin.\r\n\r\nWanneer u uw versie van Pidgin opwaardeert, dient u deze plugin ook te verwijderen of op te waarderen.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_DUTCH} "Blader naar de map waarin Pidgin is geïnstalleerd"
LangString DIR_INNERTEXT ${LANG_DUTCH} "Installeer in deze Pidgin map:"

LangString FINISH_TITLE ${LANG_DUTCH} "Pidgin-encryptie v${PIDGIN-ENCRYPTION_VERSION} Installatie Voltooid"
LangString FINISH_TEXT ${LANG_DUTCH} "U dient Pidgin te herstarten om de plugin beschikbaar te maken.  Ga dan in Pidgin naar Voorkeuren en stel bij Plugins in dat Pidgin-encryptie geladen wordt."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_DUTCH} "De encrypt.dll plugin staat op het punt verwijderd te worden uit uw Pidgin/plugins map.  Doorgaan?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_DUTCH} "Pidgin-encryptie plugin (alleen verwijderen)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_DUTCH} "Het verwijderpogramma kon in het register geen onderdelen vinden van Pidgin-encryptie.$\rWaarschijnlijk is de plugin door een andere gebruiker geïnstalleerd."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_DUTCH} "U heeft niet de noodzakelijke rechten om de plugin te verwijderen."



