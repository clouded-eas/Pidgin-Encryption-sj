;;
;;  trad-chinese.nsh
;;
;;  Traditional Chinese language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 950
;;  Author: Tim Hsu <timhsu@info.sayya.org>
;;  Version 1, Dec 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_TRADCHINESE} "Pidgin-Encryption 需要 Pidgin. 請在安裝 Pidgin-Encryption 前先安裝 Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_TRADCHINESE} "Pidgin-Encryption 加密模組"

LangString BAD_PIDGIN_VERSION_1 ${LANG_TRADCHINESE} "不相容的版本.$\r$\n$\r$\n此版本的 Pidgin-Encryption 模組和 Pidgin 版本 ${PIDGIN_VERSION} 無法相容."

LangString BAD_PIDGIN_VERSION_2 ${LANG_TRADCHINESE} "已安裝.$\r$\n$\r$\n想了解更多的資訊請連至 http://pidgin-encrypt.sourceforge.net"

LangString UNKNOWN_PIDGIN_VERSION ${LANG_TRADCHINESE} "無法分辨 Pidgin 的版本. 請確定 Pidgin 版本為 ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_TRADCHINESE} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} 安裝程式"
LangString WELCOME_TEXT  ${LANG_TRADCHINESE} "注意: 此版模組是針對 Pidgin ${PIDGIN_VERSION} 所設計, 其它版本的 Pidgin 將無法正常使用.\r\n\r\n當你要升級新的 Pidgin 時, 你必須先移除或之後再重新升級此模組\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_TRADCHINESE} "請指出 Pidgin 所安裝的目錄路徑"
LangString DIR_INNERTEXT ${LANG_TRADCHINESE} "安裝至此 Pidgin 目錄:"

LangString FINISH_TITLE ${LANG_TRADCHINESE} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} 安裝完成"
LangString FINISH_TEXT ${LANG_TRADCHINESE} "請重新啟動 Pidgin 以載入本模組, 記得在偏好設定裡啟動 Pidgin-Encryption 模組."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_TRADCHINESE} "此動作將從 Pidgin/plugins 目錄裡移除 encrypt.dll 模組.  是否確定要繼續?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_TRADCHINESE} "Pidgin-Encryption 模組 (移除)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_TRADCHINESE} "移除程式找不到 Pidgin-Encryption.$\r也許是其它使用者安裝了此模組."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_TRADCHINESE} "權限不足, 無法移除此模組"



