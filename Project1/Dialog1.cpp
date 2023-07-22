#include "Dialog1.h"
#include "resource.h"
#include <type_traits>
#include <memory>
extern "C" extern std::remove_pointer_t<HINSTANCE> __ImageBase;
Dialog1::Dialog1(HWND /*hDlg*/, LPARAM dwInitParam)
	: dwInitParam(dwInitParam)
	, hBrush(CreateSolidBrush(RGB(0x00, 0x00, 0x00)))
{
}
Dialog1::~Dialog1()
{
	DeleteObject(hBrush);
}
void Dialog1::DrawItem(const DRAWITEMSTRUCT& r) noexcept
{
	FillRect(r.hDC, &r.rcItem, hBrush);
}
void Dialog1::ChangeColor(HWND hDlg) noexcept
{
	COLORREF color = 0;
	color |= IsDlgButtonChecked(hDlg, IDC_CHECK_Red  ) ? RGB(0xff, 0x00, 0x00) : COLORREF();
	color |= IsDlgButtonChecked(hDlg, IDC_CHECK_Green) ? RGB(0x00, 0xff, 0x00) : COLORREF();
	color |= IsDlgButtonChecked(hDlg, IDC_CHECK_Blue ) ? RGB(0x00, 0x00, 0xff) : COLORREF();
	if (const auto newBrush = CreateSolidBrush(color)) {
		DeleteObject(hBrush);
		hBrush = newBrush;
		//çƒï`âÊ
		const auto hwndColor = GetDlgItem(hDlg, IDC_STATIC_Color);
		InvalidateRect(hwndColor, nullptr, true);
		UpdateWindow(hwndColor);
	}
}
INT_PTR Dialog1::DialogProc3(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (Msg) {
	case WM_DRAWITEM:
		DrawItem(*LPDRAWITEMSTRUCT(lParam));
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return true;
		case IDC_CHECK_Red  :
		case IDC_CHECK_Green:
		case IDC_CHECK_Blue :
			ChangeColor(hDlg);
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}
INT_PTR Dialog1::DialogProc2(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) noexcept
{
	const auto pThis = reinterpret_cast<Dialog1*>(GetWindowLongPtrW(hDlg, DWLP_USER));
	const auto retval = pThis->DialogProc3(hDlg, Msg, wParam, lParam);
	if (Msg == WM_NCDESTROY/*ç≈èIìIÇ»îjä¸*/)
		delete pThis;
	return retval;
}
INT_PTR Dialog1::DialogProc1(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (Msg == WM_INITDIALOG) {
		std::unique_ptr<Dialog1> pThis(new Dialog1(hDlg, lParam));
		SetWindowLongPtrW(hDlg, DWLP_DLGPROC, LONG_PTR(DialogProc2));
		SetWindowLongPtrW(hDlg, DWLP_USER   , LONG_PTR(pThis.get()));
		pThis.release();
		return true;
	}
	else
		return false;
}

INT_PTR Dialog1::DialogBoxParamW(_In_opt_ HWND hWndParent, _In_ LPARAM dwInitParam) noexcept
{
	return /*WINUSERAPI INT_PTR WINAPI*/::DialogBoxParamW
	( /*_In_opt_ HINSTANCE hInstance     */&__ImageBase
	, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG1)
	, /*_In_opt_ HWND      hWndParent    */hWndParent
	, /*_In_opt_ DLGPROC   lpDialogFunc  */DialogProc1
	, /*_In_     LPARAM    dwInitParam   */dwInitParam
	);

	return INT_PTR();
}
