#include <Windows.h>
#include <time.h>//C����̃w�b�_

class Sample {
};



int WINAPI WinMain
( _In_     HINSTANCE hInstance
, _In_opt_ HINSTANCE //hPrevInstance
, _In_     LPSTR     lpCmdLine
, _In_     int       nCmdShow
)
{
	

	Sample a, b;

	const auto pNtHeader = PIMAGE_NT_HEADERS(LPBYTE(hInstance) + PIMAGE_DOS_HEADER(hInstance)->e_lfanew);
	pNtHeader->FileHeader.TimeDateStamp;//�r���h�������킩��
	tm t;
	_localtime32_s(&t, (const __time32_t*) & pNtHeader->FileHeader.TimeDateStamp);
	char buf[256];
	wsprintfA(buf, "%u/%02u/%02u %02u:%02u:%02u"
	, t.tm_year + 1900
	, t.tm_mon + 1    
	, t.tm_mday       
	, t.tm_hour       
	, t.tm_min        
	, t.tm_sec        
	);
	MessageBoxA(nullptr, buf, "���v���O�����̃r���h����", MB_ICONINFORMATION);

	



	return 0;
}
