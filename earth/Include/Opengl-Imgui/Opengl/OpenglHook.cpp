#include "pch.h"
#include "OpenglHook.h"

tWglSwapBuffers OpenglHook::oWglSwapBuffers;
bool GL::contextCreated;
HGLRC GL::myContext;
HGLRC GL::gameContext;

int __stdcall WglSwapBufferss(HDC hDC)
{
	//Opengl start frame
	{
		//Get current game context
		GL::gameContext = wglGetCurrentContext();
		if (GL::contextCreated)
		{
			//Create new context
			GL::myContext = wglCreateContext(hDC);

			//Make thread use our context
			wglMakeCurrent(hDC, GL::myContext);

			//Setup our context
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0.0, Globals::Game::refdef->width, Globals::Game::refdef->height, 0.0, 1.0, -1.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glClearColor(0, 0, 0, 1.0);
			GL::contextCreated = false;
		}

		wglMakeCurrent(hDC, GL::myContext);
	}
	//Imgui start frame
	{
		ImGui_ImplWin32_NewFrame();
		ImGui_ImplOpenGL2_NewFrame();
		ImGui::NewFrame();
	}

	//Start Drawing
	Globals::Game::featureManager.RenderAll();

	//get closest entity
	size_t closestEntityIndex = 0;
	float smallestDistance = 10000.0f;
	for (size_t i = 1; i <= *Globals::Game::numberOfBots; i++)
	{
		if (Globals::Game::entityList->aEntities[i].health <= 0 || IsVisible(Globals::Game::entityList->aEntities[i]))
			continue;
		float distance = Globals::Game::entityList->aEntities[0].pos.Distance(Globals::Game::entityList->aEntities[i].pos);
		if (distance < smallestDistance)
		{
			smallestDistance = distance;
			closestEntityIndex = i;
		}
	}

	//aimbot
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (closestEntityIndex != 0)
		{
			Vector2 screen = Globals::Game::refdef->WorldToScreen(Globals::Game::entityList->aEntities[0].pos, Globals::Game::entityList->aEntities[closestEntityIndex].pos);
			if (screen.x > 0)
				if (Globals::Window::windowsIsFocused)
					mouse_event(MOUSEEVENTF_MOVE, screen.x - (Globals::Game::refdef->width / 2), screen.y - (Globals::Game::refdef->height / 2), NULL, NULL);
		}
	}
	//Finish Drawing

	//Imgui end frame
	{
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}
	//Opengl end frame
	{
		wglMakeCurrent(hDC, GL::gameContext);
	}

    return OpenglHook::oWglSwapBuffers(hDC);
}

OpenglHook::OpenglHook(HWND hwnd)
{
	this->wndProcHook = new WindowProcedureHook(hwnd);
	OpenglHook::oWglSwapBuffers = (tWglSwapBuffers)GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");
	this->hkWglSwapBuffers = new x86Hook(new x86Detour((BYTE*)OpenglHook::oWglSwapBuffers, (BYTE*)WglSwapBufferss, 5));
	GL::contextCreated = true;
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