;;
;;  bulgarian.nsh
;;
;;  Bulgarian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1251
;;  Author: Lachezar Dobrev <l.dobrev@gmail.com>
;;  Version 1, Sep 2007
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_BULGARIAN} "����������� Pidgin-Encryption ������� �� ����� ���������� Pidgin. ������ �� ����������� Pidgin ����� Pidgin-Encryption."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_BULGARIAN} "Pidgin-Encryption ��������� �� Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_BULGARIAN} "������������ ������.$\r$\n$\r$\n���� ������ �� ����������� Pidgin-Encryption � ��������� �� ������ �� Pidgin ${PIDGIN_VERSION}. �������� ����� ���������� Pidgin ������"

LangString BAD_PIDGIN_VERSION_2 ${LANG_BULGARIAN} ".$\r$\n$\r$\n�������� http://pidgin-encrypt.sourceforge.net/ �� ������������ ����������."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_BULGARIAN} "������������ �� ���� �� ������ �������� �� ������������ Pidgin. ���� ������� ��, �� ����� ���������� Pidgin ������ ${PIDGIN_VERSION}."

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_BULGARIAN} "����������� �� Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION}"
LangString WELCOME_TEXT  ${LANG_BULGARIAN} "���������: ���� ������ �� ����������� � ��������� �� Pidgin ������ ${PIDGIN_VERSION} � ���� �� �� ��������� ��� ����������� � ����� ������ �� Pidgin.\r\n\r\n��� ���������� �� Pidgin, �� ������ �� ���������� ��� �������� � �����������.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_BULGARIAN} "���� ������� �������, ������ �� ������ Pidgin"
LangString DIR_INNERTEXT ${LANG_BULGARIAN} "����������� � Pidgin �������:"

LangString FINISH_TITLE ${LANG_BULGARIAN} "������������ �� Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} ��������"
LangString FINISH_TEXT ${LANG_BULGARIAN} "������ �� �� ������������ Pidgin �� �� �� ������ �����������, ���� ���� �������� ������� � ��������� �� Pidgin � �������� ����������� Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_BULGARIAN} "����������� Pidgin-Encryption (encrypt.dll) �� ���� ������� �� Pidgin/plugins �������. ������� �� ���?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_BULGARIAN} "Pidgin-Encryption ��������� �� Pidgin (���� ����������)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_BULGARIAN} "��-����������� �� ���� �� ������ ��������� �� ����������� �� Pidgin-Encryption.$\r�������� ������������ � ���� ��������� �� ���� ����������."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_BULGARIAN} "������ �����, ���������� �� ���������� �� �����������."
