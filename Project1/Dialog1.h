#pragma once
#include <Windows.h>
class Dialog1
{
	LPARAM dwInitParam;
	HBRUSH hBrush;
	Dialog1(HWND hDlg, LPARAM dwInitParam);

	void DrawItem(const DRAWITEMSTRUCT& r) noexcept;
	void ChangeColor(HWND hDlg) noexcept;
	       INT_PTR          DialogProc3(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) noexcept;
	static INT_PTR CALLBACK DialogProc2(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) noexcept;
	static INT_PTR CALLBACK DialogProc1(HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam) noexcept;
public:
	~Dialog1();
	static INT_PTR DialogBoxParamW(_In_opt_ HWND hWndParent, _In_ LPARAM dwInitParam) noexcept;
};

