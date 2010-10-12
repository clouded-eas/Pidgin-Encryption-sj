;;
;;  simp-chinese.nsh
;;
;;  Simplified Chinese language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 936
;;  Author: Strong Chen <sctronlinux@gmail.com>
;;  Version 1, Aug 2007
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_SIMPCHINESE} "Pidgin-Encryption 需要 Pidgin 支持. 请在安裝 Pidgin-Encryption 前, 先安裝 Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_SIMPCHINESE} "Pidgin-Encryption 加密插件"

LangString BAD_PIDGIN_VERSION_1 ${LANG_SIMPCHINESE} "不兼容的版本.$\r$\n$\r$\n此版本的 Pidgin-Encryption 插件与 Pidgin 版本 ${PIDGIN_VERSION} 无法兼容."

LangString BAD_PIDGIN_VERSION_2 ${LANG_SIMPCHINESE} "已安裝.$\r$\n$\r$\n想了解更多的信息请链接到 http://pidgin-encrypt.sourceforge.net"

LangString UNKNOWN_PIDGIN_VERSION ${LANG_SIMPCHINESE} "无法识别 Pidgin 的版本. 请确认 Pidgin 版本为 ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_SIMPCHINESE} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} 安裝程序"
LangString WELCOME_TEXT  ${LANG_SIMPCHINESE} "注意: 此版本插件是针对 Pidgin ${PIDGIN_VERSION} 设计, 其它版本的 Pidgin 将无法正常使用.\r\n\r\n当您要升级 Pidgin 版本时, 您重新安装或者同时升级该插件.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_SIMPCHINESE} "请指定 Pidgin 所安裝的目录路径"
LangString DIR_INNERTEXT ${LANG_SIMPCHINESE} "安裝 Pidgin 到此目录:"

LangString FINISH_TITLE ${LANG_SIMPCHINESE} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} 安裝完成"
LangString FINISH_TEXT ${LANG_SIMPCHINESE} "请重新启动 Pidgin 以载入本插件, 请在 Pidgin 插件设置（Plugins）中启用 Pidgin-Encryption 插件."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_SIMPCHINESE} "将从 Pidgin/plugins 目录中删除 encrypt.dll 模块.  是否确定要继续?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_SIMPCHINESE} "Pidgin-Encryption 插件（删除程序）"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_SIMPCHINESE} "删除程序找不到 Pidgin-Encryption.$\r可能是其它使用者安裝了此插件."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_SIMPCHINESE} "权限不足, 无法删除此插件"



