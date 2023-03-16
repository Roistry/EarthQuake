#pragma once
typedef int(__stdcall* tWglSwapBuffers)(HDC hDC);
int __stdcall WglSwapBufferss(HDC hDC);

class OpenglHook
{
private:
	WindowProcedureHook* wndProcHook;
public:
	static tWglSwapBuffers oWglSwapBuffers;
private:
	x86Hook* hkWglSwapBuffers;
public:
	OpenglHook(HWND hwnd);
	void ActiveHook();
	void DisableHook();
};