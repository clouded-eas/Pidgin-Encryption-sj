;;
;;  trad-chinese.nsh
;;
;;  Traditional Chinese language strings for the Windows Pidgin-encryption NSIS installer.
;;  Windows Code page: 950
;;  Author: Tim Hsu <timhsu@info.sayya.org>
;;  Version 1, Dec 2004
;;

; Startup Pidgin check
LangString PIDGIN_NEEDED ${LANG_TRADCHINESE} "Pidgin-Encryption �ݭn Pidgin. �Цb�w�� Pidgin-Encryption �e���w�� Pidgin."

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_TRADCHINESE} "Pidgin-Encryption �[�K�Ҳ�"

LangString BAD_PIDGIN_VERSION_1 ${LANG_TRADCHINESE} "���ۮe������.$\r$\n$\r$\n�������� Pidgin-Encryption �ҲթM Pidgin ���� ${PIDGIN_VERSION} �L�k�ۮe."

LangString BAD_PIDGIN_VERSION_2 ${LANG_TRADCHINESE} "�w�w��.$\r$\n$\r$\n�Q�F�ѧ�h����T�гs�� http://pidgin-encrypt.sourceforge.net"

LangString UNKNOWN_PIDGIN_VERSION ${LANG_TRADCHINESE} "�L�k���� Pidgin ������. �нT�w Pidgin ������ ${PIDGIN_VERSION}"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_TRADCHINESE} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} �w�˵{��"
LangString WELCOME_TEXT  ${LANG_TRADCHINESE} "�`�N: �����ҲլO�w�� Pidgin ${PIDGIN_VERSION} �ҳ]�p, �䥦������ Pidgin �N�L�k���`�ϥ�.\r\n\r\n��A�n�ɯŷs�� Pidgin ��, �A�����������Τ���A���s�ɯŦ��Ҳ�\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_TRADCHINESE} "�Ы��X Pidgin �Ҧw�˪��ؿ����|"
LangString DIR_INNERTEXT ${LANG_TRADCHINESE} "�w�˦ܦ� Pidgin �ؿ�:"

LangString FINISH_TITLE ${LANG_TRADCHINESE} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} �w�˧���"
LangString FINISH_TEXT ${LANG_TRADCHINESE} "�Э��s�Ұ� Pidgin �H���J���Ҳ�, �O�o�b���n�]�w�̱Ұ� Pidgin-Encryption �Ҳ�."

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_TRADCHINESE} "���ʧ@�N�q Pidgin/plugins �ؿ��̲��� encrypt.dll �Ҳ�.  �O�_�T�w�n�~��?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_TRADCHINESE} "Pidgin-Encryption �Ҳ� (����)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_TRADCHINESE} "�����{���䤣�� Pidgin-Encryption.$\r�]�\�O�䥦�ϥΪ̦w�ˤF���Ҳ�."
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_TRADCHINESE} "�v������, �L�k�������Ҳ�"



