// �ȉ��� ifdef �u���b�N�� DLL ����ȒP�ɃG�N�X�|�[�g������}�N�����쐬����W���I�ȕ��@�ł��B 
// ���� DLL ���̂��ׂẴt�@�C���̓R�}���h���C���Œ�`���ꂽ ATS_EXPORTS �V���{��
// �ŃR���p�C������܂��B���̃V���{���͂��� DLL ���g�p����ǂ̃v���W�F�N�g��ł�����`�łȂ�
// ��΂Ȃ�܂���B���̕��@�ł̓\�[�X�t�@�C���ɂ��̃t�@�C�����܂ނ��ׂẴv���W�F�N�g�� DLL 
// ����C���|�[�g���ꂽ���̂Ƃ��� ATS_API �֐����Q�Ƃ��A���̂��߂��� DLL �͂��̃}�N 
// ���Œ�`���ꂽ�V���{�����G�N�X�|�[�g���ꂽ���̂Ƃ��ĎQ�Ƃ��܂��B
//#pragma data_seg(".shared")
//#pragma data_seg()

#define ATS_BEACON_S 0 // S�����O
#define ATS_BEACON_SN 1 // SN����
#define ATS_BEACON_SNRED 2 // SN��o���h�~
#define ATS_BEACON_P 3 // P��~�M��
#define ATS_BEACON_EMG 4 // P����(���)
#define ATS_BEACON_SVC 5 // P����(��p)
#define ATS_BEACON_SPDLIM 6 // P����푬�x����
#define ATS_BEACON_SPDMAX 7 // P�ō����x
#define ATS_BEACON_SPP 8 // ��ԉw�ʉߖh�~���u


int g_emgBrake; // ���m�b�`
int g_svcBrake; // ��p�ő�m�b�`
int g_brakeNotch; // �u���[�L�m�b�`
int g_powerNotch; // �͍s�m�b�`
int g_reverser; // ���o�[�T
bool g_pilotlamp; // �p�C���b�g�����v
int g_time; // ���ݎ���
float v; // ���x�v�̑��x[km/h]
int g_deltaT; // �t���[������[ms/frame]
float g_current;//�d���@�d��[A]
int Type;//�n��q�ԍ�
int Optional;//Senddeta

AirspringTiltingControl64Ini ini;

ATS_HANDLES g_output; // �o��

