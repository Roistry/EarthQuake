#include "pch.h"

#include "Features/ESP/ESP.h"
#include "Features/Traceline/Traceline.h"

#if 0
double a11; int a22; int* a33; int a44; float* a55; int a66; int a77; char a88; int a99;

//std::vector<uintptr_t> entities;

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
#endif

uintptr_t Thread(HMODULE hModule)
{
    AllocConsole();
	auto* f = new FILE;
    freopen_s(&f, "CONOUT$", "w", stdout);

    HWND hwnd = FindWindowA(NULL, "Quake Live");
    OpenglHook hkOpengl(hwnd);
    hkOpengl.ActiveHook();

    Globals::Game::featureManager.AddFeature("ESP", new ESP());
    
    //oDecrementHealth = reinterpret_cast<tDecrementHealth>(qagamex86ModuleBase + 0x48C30);
    //x86Hook hkDecrementHealth(new x86Detour((BYTE*)(oDecrementHealth), (BYTE*)(DecrementHealth), 6));
    //oDecrementHealth = reinterpret_cast<tDecrementHealth>(hkDecrementHealth.Init());

    //float* velocityScaler = (float*)(qagamex86ModuleBase + 0x908F4 + 0x28);
    //int* allScaler = (int*)(qagamex86ModuleBase + 0x908F4 + 0x2C);

    while (!GetAsyncKeyState(VK_DELETE))
    {
        Globals::Game::featureManager.LoopAll();

        //if (GetAsyncKeyState(VK_DOWN) & 1 && false)
            //printf("decrement health returned: %d\n", oDecrementHealth(a11, a22, a33, a44, a55, a66, a77, a88, a99));

        //if (GetAsyncKeyState(VK_UP) & 1)
        //{
            //for (size_t i = 0; i < entities.size(); i++)
                //printf("entity %d: %p\n", i, entities[i]);
        //}

        if (GetForegroundWindow() == hwnd)
            Globals::Window::windowsIsFocused = true;
        else
            Globals::Window::windowsIsFocused = false;
    }

    hkOpengl.DisableHook();

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

