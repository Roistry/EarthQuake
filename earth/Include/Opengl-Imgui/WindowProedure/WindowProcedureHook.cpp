#include "pch.h"
#include "WindowProcedureHook.h"

WNDPROC WindowProcedureHook::previousWindowProcedure;

LRESULT CALLBACK NewWindowProcedure(HWND hwnd, UINT msg, WPARAM wideparam, LPARAM lowparam)
{
	ImGui_ImplWin32_WndProcHandler(hwnd, msg, wideparam, lowparam);
	return CallWindowProcA(WindowProcedureHook::previousWindowProcedure, hwnd, msg, wideparam, lowparam);
}

WindowProcedureHook::WindowProcedureHook(HWND hwnd)
{
	this->hwnd = hwnd;
	this->newWindowProcedure = (WNDPROC)NewWindowProcedure;
	WindowProcedureHook::previousWindowProcedure = (WNDPROC)GetWindowLongA(hwnd, GWLP_WNDPROC);
}

void WindowProcedureHook::SetNewWindowProcedure()
{
	SetWindowLongA(this->hwnd, GWLP_WNDPROC, (LONG)this->newWindowProcedure);
}

void WindowProcedureHook::SetPreviousWindowProcedure()
{
	SetWindowLongA(this->hwnd, GWLP_WNDPROC, (LONG)WindowProcedureHook::previousWindowProcedure);
}