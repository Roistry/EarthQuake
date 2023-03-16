#pragma comment(lib, "opengl32.lib")

#include <iostream>
#include <vector>

#include <Windows.h>
#include <gl/GL.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_opengl2.h"

#include "Feature/FeatureBase/FeatureBase.h"
#include "Feature/FeatureManager/FeatureManager.h"

#include "Detour-Hook/x86Detour/x86Detour.h"
#include "Detour-Hook/x86Hook/x86Hook.h"

#include "Game classes/utils.h"
#include "Game classes/reclass.h"
#include "Game classes/SDK.h"

#include "Opengl-Imgui/Draw/glDraw.h"
#include "Opengl-Imgui/WindowProedure/WindowProcedureHook.h"
#include "Opengl-Imgui/Opengl/OpenglHook.h"

#include "Globals/globals.h"