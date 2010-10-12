;;
;;  japanese.nsh
;;
;;  Default language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 932
;;
;;  Author: Takeshi AIHANA <aihana@gnome.gr.jp>
;;  Version 1, sept 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_JAPANESE} "Pidgin-Encryption を利用するには Pidgin がインストールされている必要があります。Pidgin-Encryption をインストールする前に Pidgin をインストールして下さい。"

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_JAPANESE} "Pidgin 向けの Pidgin-Encryption プラグイン"

LangString BAD_PIDGIN_VERSION_1 ${LANG_JAPANESE} "バージョンが合っていません。$\r$\n$\r$\nこのバージョンの Pidgin-Encryption プラグインは Pidgin バージョン ${PIDGIN_VERSION} 向けに開発されたものです。次の Pidgin バージョンをインストールしていると表示されます:"

LangString BAD_PIDGIN_VERSION_2 ${LANG_JAPANESE} "$\r$\n$\r$\nさらに詳細な情報な情報については http://pidgin-encrypt.sourceforge.net をご覧下さい。"

LangString UNKNOWN_PIDGIN_VERSION ${LANG_JAPANESE} "インストールされている Pidgin のバージョンを取得できませんでした。バージョン ${PIDGIN_VERSION} であることを確認して下さい。"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_JAPANESE} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} インストーラ"
LangString WELCOME_TEXT  ${LANG_JAPANESE} "注意: このバージョンのプラグインは、Pidgin バージョン ${PIDGIN_VERSION} 向けに設計されたもので、それ以外のバージョンではインストール、または動作しないかもしれません。\r\n\r\nお使いの Pidgin をアップグレードする際は同様に、このプラグインもアンインストール、またはアップグレードして下さい。\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_JAPANESE} "Pidgin がインストールされているフォルダを指定して下さい"
LangString DIR_INNERTEXT ${LANG_JAPANESE} "この Pidgin フォルダの中にインストールする:"

LangString FINISH_TITLE ${LANG_JAPANESE} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} のインストールが完了しました"
LangString FINISH_TEXT ${LANG_JAPANESE} "プラグインを読み込むために Pidgin を再起動し、Pidgin の設定ダイアログから Pidgin-Encryption プラグインを有効にして下さい。"

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_JAPANESE} "お使いの Pidgin/プラグイン・フォルダからファイル encrypt.dll を削除します。続行してもよろしいですか?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_JAPANESE} "Pidgin-Encryption プラグイン (削除専用)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_JAPANESE} "アンインストーラは Pidgin-Encryption に対するレジストリのエントリを見つけることができませんでした。$\rおそらく誰か他のユーザがプラグインをインストールしたと思われます。"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_JAPANESE} "このプラグインをアンインストールするのに必要な権限がありません。"



