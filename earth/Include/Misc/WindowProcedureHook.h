#pragma once

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wideparam, LPARAM lowparam);
LRESULT CALLBACK NewWindowProcedure(HWND hwnd, UINT msg, WPARAM wideparam, LPARAM lowparam);

class WindowProcedureHook
{
private:
	HWND hwnd;
	WNDPROC newWindowProcedure;
public:
	static WNDPROC previousWindowProcedure;

	WindowProcedureHook(HWND hwnd);
	void SetNewWindowProcedure();
	void SetPreviousWindowProcedure();
};