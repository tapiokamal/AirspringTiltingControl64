// Ats.cpp : DLL アプリケーション用のエントリ ポイントを定義します。
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
	//ファイルパス格納
	char filePath[_MAX_PATH + 1] = _T("");
	//検索文字列へのポインタ
	char* posIni;
	//Ats.dllのファイルパスを取得
	::GetModuleFileName((HMODULE)hModule, filePath, _MAX_PATH);
	//パスから.dllの位置を検索
	posIni = strstr(filePath, ".dll");
	//.dllを.iniに置換
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

	//sound[200] = ATS_SOUND_STOP;//吸気音再生停止

	t = (a * v * v / R) - (b* C) - d;//吸気音関数[s]

//吸気音出力


	if (R>0) {
		if (t2 < 0) {
			
			if (t > 0) {
				MessageBox(NULL, TEXT("called"), TEXT("メッセージボックス"), MB_OK);
				sound[200] = ATS_SOUND_PLAYLOOPING;//吸気音再生開始
				t1 = vehicleState.Time / 1000;//地上子通過時刻[s]
				t2 = t1 + t;//吸気音停止予定時刻[s]

			}
		}else {
			if (g_time >= t2) {
//				MessageBox(NULL, TEXT("Sound end"), TEXT("メッセージボックス"), MB_OK);
				sound[200] = ATS_SOUND_STOP;//吸気音再生停止
				R = 0;
			}
			else {
				sound[200] = ATS_SOUND_PLAYLOOPING;//吸気音再生停止
			}
		}
	}else{
		t = 0;
		t2 = -1;
		sound[200] = ATS_SOUND_STOP;//吸気音再生停止
	}




	// ハンドル出力
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