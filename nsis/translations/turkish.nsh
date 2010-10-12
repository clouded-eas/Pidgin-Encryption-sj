;;
;;  turkish.nsh
;;
;;  Turkish language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1254
;;  Author: Ekrem Erdem <e2erdem@gmail.com>
;;  Version 1, Dec 2005
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_TURKISH} "Pidgin-�ifreleme Pidgin'in kurulu olmas�n� gerektiriyor. Pidgin-�ifrelemeyi kurmadan �nce Pidgin'i kurmal�s�n�z."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_TURKISH} "Pidgin i�in Pidgin-�ifreleme eklentisi"

LangString BAD_PIDGIN_VERSION_1 ${LANG_TURKISH} "Uyumsuz versiyon.$\r$\n$\r$\nPidgin-�ifrelemenin bu versiyonu Pidgin'in ${PIDGIN_VERSION} versiyonu i�in haz�rlanm��t�r. Pidgin'in bu versiyonuna sahip g�r�n�yorsunuz"

LangString BAD_PIDGIN_VERSION_2 ${LANG_TURKISH} "kurulum tamamland�.$\r$\n$\r$\nDaha fazla bilgi i�in http://pidgin-encrypt.sourceforge.net adresine bak�n�z."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_TURKISH} "Hangi Pidgin versiyonunun kurulu oldu�unu s�yleyemiyorum. Kurulu versiyonun ${PIDGIN_VERSION} oldu�undan emin olun"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_TURKISH} "Pidgin-�ifreleme v${PIDGIN-ENCRYPTION_VERSION} Kurucusu"
LangString WELCOME_TEXT  ${LANG_TURKISH} "Not: Eklentinin bu versiyonu Pidgin ${PIDGIN_VERSION} i�in tasarlanm��t�r, Pidgin'in di�er versiyonlar� i�in kurulmaz ve �al��maz.\r\n\r\nPidgin versiyonunu y�kseltti�inizde bu eklentiyi kald�rmal� ya da versiyonunu y�kseltmelisiniz.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_TURKISH} "L�tfen Pidgin'in kurulu oldu�u dizini belirtiniz"
LangString DIR_INNERTEXT ${LANG_TURKISH} "Bu Pidgin dizinine kur:"

LangString FINISH_TITLE ${LANG_TURKISH} "Pidgin-�ifreleme v${PIDGIN-ENCRYPTION_VERSION} Kurulumu Tamamland�"
LangString FINISH_TEXT ${LANG_TURKISH} "Eklentinin y�klenebilmesi i�in Pidgin'i yeniden ba�latmal�s�n�z. Daha sonra Pidgin tercihleri b�l�m�nden Pidgin-�ifreleme eklentisini aktif hale getirmelisiniz."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_TURKISH} "encrypt.dll eklentisi Pidgin/plugins dizininizden silinmek �zere. Devam et?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_TURKISH} "Pidgin-�ifreleme Eklentisi (sadece silinebilir)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_TURKISH} "Kald�rma arac� Pidgin-�ifreleme i�in registry girdisini bulamad�.$\rEklentiyi ba�ka bir kullan�c� kurmu� olabilir."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_TURKISH} "Eklentiyi kald�rmak i�in gerekli izinlere sahip de�ilsiniz."



