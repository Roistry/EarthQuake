#include "pch.h"
#include "OpenglHook.h"

tWglSwapBuffers OpenglHook::oWglSwapBuffers;

int __stdcall WglSwapBuffers(HDC hDC)
{
    return OpenglHook::oWglSwapBuffers(hDC);
}

OpenglHook::OpenglHook(HWND hwnd)
{
	this->wndProcHook = new WindowProcedureHook(hwnd);
	OpenglHook::oWglSwapBuffers = (tWglSwapBuffers)GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");
	this->hkWglSwapBuffers = new x86Hook(new x86Detour((BYTE*)OpenglHook::oWglSwapBuffers, (BYTE*)0x0, 5));
}

void OpenglHook::ActiveHook()
{
	this->wndProcHook->SetNewWindowProcedure();
	ImGui::SetCurrentContext(ImGui::CreateContext());
	ImGui_ImplWin32_Init(this->wndProcHook->hwnd);
	ImGui_ImplOpenGL2_Init();
	OpenglHook::oWglSwapBuffers = (tWglSwapBuffers)this->hkWglSwapBuffers->Init();
}

void OpenglHook::DisableHook()
{
	this->wndProcHook->SetPreviousWindowProcedure();
	this->hkWglSwapBuffers->UnInit();
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplOpenGL2_Shutdown();
	ImGui::DestroyContext();
}