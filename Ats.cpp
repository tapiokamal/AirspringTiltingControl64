// Ats.cpp : DLL �A�v���P�[�V�����p�̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "AirspringTiltingControl64Ini.h"
#include "atsplugin.h"
#include "Ats.h"

int R, C ;
float t,t1,t2,a,b,d;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                    LPVOID lpReserved
					 )
{
	//�t�@�C���p�X�i�[
	char filePath[_MAX_PATH + 1] = _T("");
	//����������ւ̃|�C���^
	char* posIni;
	//Ats.dll�̃t�@�C���p�X���擾
	::GetModuleFileName((HMODULE)hModule, filePath, _MAX_PATH);
	//�p�X����.dll�̈ʒu������
	posIni = strstr(filePath, ".dll");
	//.dll��.ini�ɒu��
	memmove(posIni, ".ini", 4);

    return TRUE;
}

ATS_API int WINAPI GetPluginVersion()
{
	return ATS_VERSION;
}

ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC vehicleSpec)
{
	g_svcBrake = vehicleSpec.BrakeNotches;
	g_emgBrake = g_svcBrake + 1;
}

ATS_API void WINAPI Initialize(int brake)
{
	C = 0;
	R = 0;
	t = 0;
	t2 = -1;
	a = ini.Values.a;
	b = ini.Values.b;
	d = ini.Values.d;
}

ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vehicleState, int *panel, int *sound)
{
	g_deltaT = vehicleState.Time - g_time;
	g_time = vehicleState.Time/1000;
	v = vehicleState.Speed;

	//sound[200] = ATS_SOUND_STOP;//�z�C���Đ���~

	t = (a * v * v / R) - (b* C) - d;//�z�C���֐�[s]

//�z�C���o��


	if (R>0) {
		if (t2 < 0) {
			
			if (t > 0) {
				MessageBox(NULL, TEXT("called"), TEXT("���b�Z�[�W�{�b�N�X"), MB_OK);
				sound[200] = ATS_SOUND_PLAYLOOPING;//�z�C���Đ��J�n
				t1 = vehicleState.Time / 1000;//�n��q�ʉߎ���[s]
				t2 = t1 + t;//�z�C����~�\�莞��[s]

			}
		}else {
			if (g_time >= t2) {
//				MessageBox(NULL, TEXT("Sound end"), TEXT("���b�Z�[�W�{�b�N�X"), MB_OK);
				sound[200] = ATS_SOUND_STOP;//�z�C���Đ���~
				R = 0;
			}
			else {
				sound[200] = ATS_SOUND_PLAYLOOPING;//�z�C���Đ���~
			}
		}
	}else{
		t = 0;
		t2 = -1;
		sound[200] = ATS_SOUND_STOP;//�z�C���Đ���~
	}




	// �n���h���o��
	g_output.Brake = g_brakeNotch;
	g_output.Power = g_powerNotch;
	g_output.ConstantSpeed = ATS_CONSTANTSPEED_CONTINUE;


    return g_output;
}

ATS_API void WINAPI SetPower(int notch)
{
	g_powerNotch = notch;

}

ATS_API void WINAPI SetBrake(int notch)
{
	g_brakeNotch = notch;
}

ATS_API void WINAPI SetReverser(int pos)
{
	g_reverser = pos;
}

ATS_API void WINAPI KeyDown(int atsKeyCode)
{
}

ATS_API void WINAPI KeyUp(int hornType)
{
}

ATS_API void WINAPI HornBlow(int atsHornBlowIndex)
{
}

ATS_API void WINAPI DoorOpen()
{
	g_pilotlamp = false;
}

ATS_API void WINAPI DoorClose()
{
	g_pilotlamp = true;
}

ATS_API void WINAPI SetSignal(int signal)
{
}

ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA beaconData){


	if (beaconData.Type == 3000) {
		R = beaconData.Optional/ 1000;
		C = beaconData.Optional - (1000 * R);

	}
}
ATS_API void WINAPI Load() {}
ATS_API void WINAPI Dispose() {}