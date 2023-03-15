#pragma once

namespace Globals
{
	namespace Game
	{
		inline const float PLAYER_HEIGHT = 5.3f;
		inline const float PLAYER_WIDTH = 2.0f;
		inline const float EYE_HEIGHT = 4.5f;

		inline const float PLAYER_ASPECT_RATIO = PLAYER_HEIGHT / PLAYER_WIDTH;
		inline const int GAME_UNIT_MAGIC = 4000;

		inline auto quakeliveModuleBase = (uintptr_t)GetModuleHandleW(L"quakelive_steam.exe");
		inline auto qagamex86ModuleBase = (uintptr_t)GetModuleHandleW(L"qagamex86.dll");
		inline refdef_t* refdef = (refdef_t*)(*(uintptr_t*)(*(uintptr_t*)(quakeliveModuleBase + 0x1316EB8) * 4 + quakeliveModuleBase + 0x1345A78) + 0xB04D8);
		inline auto* entityList = *(EntityList**)(quakeliveModuleBase + 0x00F33774);
		inline int* numberOfBots = (int*)(qagamex86ModuleBase + 0x5E36B8);
	}
	namespace Window
	{
		inline bool windowsIsFocused = false;
	}
}