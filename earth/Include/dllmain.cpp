#include "pch.h"
#define PlayerHeight 0.50f
#define PlayerWidth 0.20f

struct refdef_t
{
    int           x, y, width, height;
    float         fov_x, fov_y;
    Vector3       vieworg;
    Vector3       viewaxis[3];
};

Vector2 WorldToScreen(Vector3 src, Vector3 dst, refdef_t* refdef)
{
    Vector3 transform;
    float xc, yc;
    float px, py;
    float z;

    px = tan(refdef->fov_x * 3.141f / 360.0);
    py = tan(refdef->fov_y * 3.141f / 360.0);

    transform = dst - src;

    xc = refdef->width / 2.0;
    yc = refdef->height / 2.0;

    z = transform.DotProduct(refdef->viewaxis[0]); //left

    Vector2 screenCords;
    if (z <= 0.1)
        return screenCords;

    screenCords.x = xc - transform.DotProduct(refdef->viewaxis[1]) * xc / (z * px); //up
    screenCords.y = yc - transform.DotProduct(refdef->viewaxis[2]) * yc / (z * py); //forward

    return screenCords;
}

auto quakeliveModuleBase = (uintptr_t)GetModuleHandleW(L"quakelive_steam.exe");
auto qagamex86ModuleBase = (uintptr_t)GetModuleHandleW(L"qagamex86.dll");
refdef_t* refdef = (refdef_t*)(*(uintptr_t*)(*(uintptr_t*)(quakeliveModuleBase + 0x1316EB8) * 4 + quakeliveModuleBase + 0x1345A78) + 0xB04D8);
auto* entityList = *(EntityList**)(quakeliveModuleBase + 0x00F33774);

bool windowsIsFocused = false;
bool status = true;
WNDPROC lastProcedure;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wideparam, LPARAM lowparam);
LRESULT CALLBACK NewWindowProcedure(HWND hwnd, UINT msg, WPARAM wideparam, LPARAM lowparam)
{
    ImGui_ImplWin32_WndProcHandler(hwnd, msg, wideparam, lowparam);
    return CallWindowProcA(lastProcedure, hwnd, msg, wideparam, lowparam);
}

typedef int(__stdcall* tWglSwapBuffers)(HDC hDC);
tWglSwapBuffers oWglSwapBuffers;
bool contextCreated = true;
HGLRC myContext;
HGLRC gameContext;
int __stdcall WglSwapBuffers(HDC hDC)
{
    gameContext = wglGetCurrentContext();
    if (contextCreated)
    {
        //Create new context
        myContext = wglCreateContext(hDC);

        //Make thread use our context
        wglMakeCurrent(hDC, myContext);

        //Setup our context
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, refdef->width, refdef->height, 0.0, 1.0, -1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClearColor(0, 0, 0, 1.0);
        contextCreated = false;
    }

    wglMakeCurrent(hDC, myContext);

    ImGui_ImplWin32_NewFrame();
    ImGui_ImplOpenGL2_NewFrame();
    ImGui::NewFrame();

    if (status)
    {
        static RGBA* red = new RGBA(255, 0, 0, 255);

        Vector3 vec3PlayerHead = entityList->aEntities[0].pos;
        Vector3 vec3TargetHead = entityList->aEntities[1].pos;

        float distance = vec3PlayerHead.Distance(vec3TargetHead);

        Vector2 TargetMiddle = WorldToScreen(vec3PlayerHead, Vector3(vec3TargetHead.x, vec3TargetHead.y, vec3TargetHead.z - PlayerHeight / 2), refdef);
        Vector2 TargetTopLeft = Vector2(TargetMiddle.x - (PlayerWidth) * distance, TargetMiddle.y + (PlayerHeight) * distance);
        Vector2 TargetBottomRight = Vector2(TargetMiddle.x + (PlayerWidth) * distance, TargetMiddle.y - (PlayerHeight) * distance);

        if (TargetMiddle.x != 0 || TargetMiddle.y != 0)
        {
            //aimbot
            if (windowsIsFocused)
                if (GetAsyncKeyState(VK_LBUTTON))
                    mouse_event(MOUSEEVENTF_MOVE, TargetMiddle.x - (refdef->width / 2), TargetMiddle.y - (refdef->height / 2), NULL, NULL);
        }
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    wglMakeCurrent(hDC, gameContext);

    if (GetAsyncKeyState(VK_F9) & 1)
        status = !status;

    return oWglSwapBuffers(hDC);
}

double a11; int a22; int* a33; int a44; float* a55; int a66; int a77; char a88; int a99;

std::vector<uintptr_t> entities;

typedef int(__cdecl* tDecrementHealth)(double a1, int a2, int* a3, int a4, float* a5, int a6, int a7, char a8, int a9);
tDecrementHealth oDecrementHealth;
int __cdecl DecrementHealth(double a1, int a2, int* a3, int a4, float* a5, int a6, int a7, char a8, int a9)
{
    //a5 = knockback and depends on the knockback you take dmg
    //a7 = guntype

    //a6 = 0;

    //a7 = 0;

    //a5 = (float*)100;
    //a5 = (float*)0;

    //a1 = 0.0;
    //a2 = 0;
    //a3 = nullptr;
    //a4 = 0;
    //a5 = nullptr;
    //a6 = 0;
    //a7 = 19;

    uintptr_t entity;
    __try
    {
        entity = *(uintptr_t*)(a2 + 0x23C);
    }
    __except(1)
    {
        return oDecrementHealth(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

    bool bNewEntity = true;
    for (size_t i = 0; i < entities.size(); i++)
    {
        if (entities[i] == entity)
        {
            bNewEntity = false;
            break;
        }
    }

    if (bNewEntity)
        entities.push_back(entity);


    //float temp1 = *(float*)(&a2);
    //int* temp2 = (int*)LODWORD(temp1);
    //printf("temp2[200]: %d\n", temp2[200]);

    //a11 = a1;
    //a22 = a2;
    //a33 = a3;
    //a44 = a4;
    //a55 = a5;
    //a66 = a6;
    //a77 = a7;
    //a88 = a8;
    //a99 = a9;

    //printf("a1: %lf, a2: %d, a3: %p, a4: %d, a5: %p, a6: %d, a7: %d, a8: %c, a9: %d\n", a1, a2, a3, a4, a5, a6, a7, a8, a9);
    return oDecrementHealth(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

uintptr_t Thread(HMODULE hModule)
{
    AllocConsole();
	auto* f = new FILE;
    freopen_s(&f, "CONOUT$", "w", stdout);

    HWND hwnd = FindWindowA(NULL, "Quake Live");
    lastProcedure = (WNDPROC)SetWindowLongA(hwnd, GWLP_WNDPROC, (LONG)NewWindowProcedure);
    ImGui::SetCurrentContext(ImGui::CreateContext());
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL2_Init();

    oWglSwapBuffers = (tWglSwapBuffers)GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");
    x86Hook* hkWglSwapBuffers = new x86Hook(new x86Detour((BYTE*)oWglSwapBuffers, (BYTE*)WglSwapBuffers, 5));
    oWglSwapBuffers = (tWglSwapBuffers)hkWglSwapBuffers->Init();

    oDecrementHealth = reinterpret_cast<tDecrementHealth>(qagamex86ModuleBase + 0x48C30);
    x86Hook hkDecrementHealth(new x86Detour((BYTE*)(oDecrementHealth), (BYTE*)(DecrementHealth), 6));
    oDecrementHealth = reinterpret_cast<tDecrementHealth>(hkDecrementHealth.Init());

    //float* velocityScaler = (float*)(qagamex86ModuleBase + 0x908F4 + 0x28);
    //int* allScaler = (int*)(qagamex86ModuleBase + 0x908F4 + 0x2C);
    //int* numberOfBots = (int*)(qagamex86ModuleBase + 0x5E36B8);

    while (!GetAsyncKeyState(VK_DELETE))
    {
        if (GetAsyncKeyState(VK_DOWN) & 1 && false)
            printf("decrement health returned: %d\n", oDecrementHealth(a11, a22, a33, a44, a55, a66, a77, a88, a99));

        if (GetAsyncKeyState(VK_UP) & 1)
        {
            for (size_t i = 0; i < entities.size(); i++)
                printf("entity %d: %p\n", i, entities[i]);
        }

        if (GetForegroundWindow() == hwnd)
            windowsIsFocused = true;
        else
            windowsIsFocused = false;
    }

    SetWindowLongA(hwnd, GWLP_WNDPROC, (LONG)lastProcedure);
    hkWglSwapBuffers->UnInit();
    hkDecrementHealth.UnInit();
    ImGui_ImplWin32_Shutdown();
    ImGui_ImplOpenGL2_Shutdown();
    ImGui::DestroyContext();

    FreeConsole();
    fclose(f);
    FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID pReserved)
{
    auto thread = INVALID_HANDLE_VALUE;
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:

        thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Thread), hModule, 0, nullptr);
        if (thread)
            CloseHandle(thread);
        break;
    case DLL_PROCESS_DETACH:
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    default:
        break;
    }
    return TRUE;
}

