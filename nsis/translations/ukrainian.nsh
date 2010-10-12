;;
;;  ukrainian.nsh
;;
;;  Ukrainian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1251
;;  Author: Roman Sosenko <coloc75@yahoo.com>
;;  Version 1, Jan 2005
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_UKRAINIAN} "����� ������������� Pidgin encryption ��������� ���������� Pidgin. ��������� Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_UKRAINIAN} "������ Pidgin-Encryption ��� Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_UKRAINIAN} "�������� �����.$\r$\n$\r$\n�� ����� ������ Pidgin-Encryption ���� �������� ��� ���� Pidgin ${PIDGIN_VERSION}. �� ������ ����'���� ����������� ����� Pidgin"

LangString BAD_PIDGIN_VERSION_2 ${LANG_UKRAINIAN} "�����������.$\r$\n$\r$\n������� http://pidgin-encrypt.sourceforge.net ��� ���� �������� ����������."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_UKRAINIAN} "��� �������, ��� ����� Pidgin ����������� �� ������ ����'����. �������������, �� �� ����� ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_UKRAINIAN} "���������� Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} "
LangString WELCOME_TEXT  ${LANG_UKRAINIAN} "�����: �� ����� ������ �������� ��� Pidgin ${PIDGIN_VERSION}, � �� ���� ���� ������������ � ��������� � ������ ������� Pidgin.\r\n\r\n� ������� ��������� ���� Pidgin ��� ��������� ������������� �� �������� ����� � ������.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_UKRAINIAN} "���� �����, ������� �������, � ����� ����������� Pidgin"
LangString DIR_INNERTEXT ${LANG_UKRAINIAN} "���������� � �� ����� Pidgin:"

LangString FINISH_TITLE ${LANG_UKRAINIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} ������������ ���������"
LangString FINISH_TEXT ${LANG_UKRAINIAN} "��� ������������ ������ ��� ���� ��������� ��������� Pidgin ��������, ���� ���� � ������ Pidgin ���������� ������ Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_UKRAINIAN} "������ encrypt.dll ���� ��������� � ������ �������� Pidgin/������. ����������?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_UKRAINIAN} "������ Pidgin-Encryption  (���� ���������)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_UKRAINIAN} "����������� �� ���� ������ �������� ������ Pidgin-Encryption.$\r�������, ������ ��� ������������ ����� ������������."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_UKRAINIAN} "� ��� ���� ���� ��� ����������� ������."



