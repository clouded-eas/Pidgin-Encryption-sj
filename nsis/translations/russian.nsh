;;
;;  russian.nsh
;;
;;  Russian language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 1251
;;  Author: Roman Sosenko <coloc75@yahoo.com>
;;  Version 1, Dec 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_RUSSIAN} "����� ���������� Pidgin encryption ���������� ���������� Pidgin. ���������� Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_RUSSIAN} "������ Pidgin-Encryption ��� Pidgin"

LangString BAD_PIDGIN_VERSION_1 ${LANG_RUSSIAN} "������������� ������.$\r$\n$\r$\n��� ������ ������ Pidgin-Encryption ���� ������� ��� ������ Pidgin ${PIDGIN_VERSION}. �� ����� ���������� ����������� ������ Pidgin"

LangString BAD_PIDGIN_VERSION_2 ${LANG_RUSSIAN} "�����������.$\r$\n$\r$\n�������� http://pidgin-encrypt.sourceforge.net ��� ����� ��������� ����������."

LangString UNKNOWN_PIDGIN_VERSION ${LANG_RUSSIAN} "��� ����������, ����� ������ Pidgin ����������� �� ����� ����������. ���������, ��� ��� ������ ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_RUSSIAN} "����������� Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} "
LangString WELCOME_TEXT  ${LANG_RUSSIAN} "��������: ��������� ������ ������ ������� ��� Pidgin ${PIDGIN_VERSION}, � �� ����� ���� ����������� � ��������������� � ������� �������� Pidgin.\r\n\r\n� ������ ���������� ������ Pidgin ��� ���������� ����������������� ��� �������� ����� � ������.\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_RUSSIAN} "����������, ������� �������, � ������� ���������� Pidgin"
LangString DIR_INNERTEXT ${LANG_RUSSIAN} "���������� � ��� ����� Pidgin:"

LangString FINISH_TITLE ${LANG_RUSSIAN} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} ��������� ���������"
LangString FINISH_TEXT ${LANG_RUSSIAN} "��� �������� ������ ��� ����� ���������� ��������� Pidgin ������, ����� � ������ Pidgin ������������ ������ Pidgin-Encryption."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_RUSSIAN} "������ encrypt.dll ����� ����� � ������ �������� Pidgin/������. ����������?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_RUSSIAN} "������ Pidgin-Encryption  (������ ��������)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_RUSSIAN} "������������� �� ����� ����� �������� ������� Pidgin-Encryption.$\r��������, ������ ��� ���������� ������ �������������."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_RUSSIAN} "� ��� ��� ���� ��� ������������� ������."



