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
LangString PIDGIN_NEEDED ${LANG_JAPANESE} "Pidgin-Encryption �𗘗p����ɂ� Pidgin ���C���X�g�[������Ă���K�v������܂��BPidgin-Encryption ���C���X�g�[������O�� Pidgin ���C���X�g�[�����ĉ������B"

LangString PIDGIN-ENCRYPTION_TITLE ${LANG_JAPANESE} "Pidgin ������ Pidgin-Encryption �v���O�C��"

LangString BAD_PIDGIN_VERSION_1 ${LANG_JAPANESE} "�o�[�W�����������Ă��܂���B$\r$\n$\r$\n���̃o�[�W������ Pidgin-Encryption �v���O�C���� Pidgin �o�[�W���� ${PIDGIN_VERSION} �����ɊJ�����ꂽ���̂ł��B���� Pidgin �o�[�W�������C���X�g�[�����Ă���ƕ\������܂�:"

LangString BAD_PIDGIN_VERSION_2 ${LANG_JAPANESE} "$\r$\n$\r$\n����ɏڍׂȏ��ȏ��ɂ��Ă� http://pidgin-encrypt.sourceforge.net �������������B"

LangString UNKNOWN_PIDGIN_VERSION ${LANG_JAPANESE} "�C���X�g�[������Ă��� Pidgin �̃o�[�W�������擾�ł��܂���ł����B�o�[�W���� ${PIDGIN_VERSION} �ł��邱�Ƃ��m�F���ĉ������B"

; Overrides for default text in windows:

LangString WELCOME_TITLE ${LANG_JAPANESE} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} �C���X�g�[��"
LangString WELCOME_TEXT  ${LANG_JAPANESE} "����: ���̃o�[�W�����̃v���O�C���́APidgin �o�[�W���� ${PIDGIN_VERSION} �����ɐ݌v���ꂽ���̂ŁA����ȊO�̃o�[�W�����ł̓C���X�g�[���A�܂��͓��삵�Ȃ���������܂���B\r\n\r\n���g���� Pidgin ���A�b�v�O���[�h����ۂ͓��l�ɁA���̃v���O�C�����A���C���X�g�[���A�܂��̓A�b�v�O���[�h���ĉ������B\r\n\r\n"

LangString DIR_SUBTITLE ${LANG_JAPANESE} "Pidgin ���C���X�g�[������Ă���t�H���_���w�肵�ĉ�����"
LangString DIR_INNERTEXT ${LANG_JAPANESE} "���� Pidgin �t�H���_�̒��ɃC���X�g�[������:"

LangString FINISH_TITLE ${LANG_JAPANESE} "Pidgin-Encryption v${PIDGIN-ENCRYPTION_VERSION} �̃C���X�g�[�����������܂���"
LangString FINISH_TEXT ${LANG_JAPANESE} "�v���O�C����ǂݍ��ނ��߂� Pidgin ���ċN�����APidgin �̐ݒ�_�C�A���O���� Pidgin-Encryption �v���O�C����L���ɂ��ĉ������B"

; during install uninstaller
LangString PIDGIN_ENCRYPTION_PROMPT_WIPEOUT ${LANG_JAPANESE} "���g���� Pidgin/�v���O�C���E�t�H���_����t�@�C�� encrypt.dll ���폜���܂��B���s���Ă���낵���ł���?"

; for windows uninstall
LangString PIDGIN_ENCRYPTION_UNINSTALL_DESC ${LANG_JAPANESE} "Pidgin-Encryption �v���O�C�� (�폜��p)"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_1 ${LANG_JAPANESE} "�A���C���X�g�[���� Pidgin-Encryption �ɑ΂��郌�W�X�g���̃G���g���������邱�Ƃ��ł��܂���ł����B$\r�����炭�N�����̃��[�U���v���O�C�����C���X�g�[�������Ǝv���܂��B"
LangString un.PIDGIN_ENCRYPTION_UNINSTALL_ERROR_2 ${LANG_JAPANESE} "���̃v���O�C�����A���C���X�g�[������̂ɕK�v�Ȍ���������܂���B"



