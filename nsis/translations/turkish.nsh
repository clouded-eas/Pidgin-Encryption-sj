;;
;;  turkish.nsh
;;
;;  Turkish language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1254
;;  Author: Ekrem Erdem <e2erdem@gmail.com>
;;  Version 1, Dec 2005
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_TURKISH} "Pidgin-Þifreleme Pidgin'in kurulu olmasýný gerektiriyor. Pidgin-Þifrelemeyi kurmadan önce Pidgin'i kurmalýsýnýz."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_TURKISH} "Pidgin için Pidgin-Þifreleme eklentisi"

LangString BAD_PIDGIN_VERSION_1 ${LANG_TURKISH} "Uyumsuz versiyon.$\r$\n$\r$\nPidgin-Þifrelemenin bu versiyonu Pidgin'in ${PIDGIN_VERSION} versiyonu için hazýrlanmýþtýr. Pidgin'in bu versiyonuna sahip görünüyorsunuz"

LangString BAD_PIDGIN_VERSION_2 ${LANG_TURKISH} "kurulum tamamlandý.$\r$\n$\r$\nDaha fazla bilgi için http://pidgin-encrypt.sourceforge.net adresine bakýnýz."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_TURKISH} "Hangi Pidgin versiyonunun kurulu olduðunu söyleyemiyorum. Kurulu versiyonun ${PIDGIN_VERSION} olduðundan emin olun"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_TURKISH} "Pidgin-Þifreleme v${PIDGIN-ENCRYPTION_VERSION} Kurucusu"
LangString WELCOME_TEXT  ${LANG_TURKISH} "Not: Eklentinin bu versiyonu Pidgin ${PIDGIN_VERSION} için tasarlanmýþtýr, Pidgin'in diðer versiyonlarý için kurulmaz ve çalýþmaz.\r\n\r\nPidgin versiyonunu yükselttiðinizde bu eklentiyi kaldýrmalý ya da versiyonunu yükseltmelisiniz.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_TURKISH} "Lütfen Pidgin'in kurulu olduðu dizini belirtiniz"
LangString DIR_INNERTEXT ${LANG_TURKISH} "Bu Pidgin dizinine kur:"

LangString FINISH_TITLE ${LANG_TURKISH} "Pidgin-Þifreleme v${PIDGIN-ENCRYPTION_VERSION} Kurulumu Tamamlandý"
LangString FINISH_TEXT ${LANG_TURKISH} "Eklentinin yüklenebilmesi için Pidgin'i yeniden baþlatmalýsýnýz. Daha sonra Pidgin tercihleri bölümünden Pidgin-Þifreleme eklentisini aktif hale getirmelisiniz."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_TURKISH} "encrypt.dll eklentisi Pidgin/plugins dizininizden silinmek üzere. Devam et?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_TURKISH} "Pidgin-Þifreleme Eklentisi (sadece silinebilir)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_TURKISH} "Kaldýrma aracý Pidgin-Þifreleme için registry girdisini bulamadý.$\rEklentiyi baþka bir kullanýcý kurmuþ olabilir."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_TURKISH} "Eklentiyi kaldýrmak için gerekli izinlere sahip deðilsiniz."



