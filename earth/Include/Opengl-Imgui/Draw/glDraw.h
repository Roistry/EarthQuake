#pragma once

class GL
{
public:
	static bool contextCreated;
	static HGLRC myContext;
	static HGLRC gameContext;

	static void SetupOrtho();
	static void RestoreGL();

	static void DrawFilledRect(float x, float y, float width, float height, Vector3 color);
	static void DrawOutline(float x, float y, float width, float height, float linewidth, Vector3 color);
	static void DrawLine(Vector2 src, Vector2 dst, float linewidth, Vector3 color);
	static void DrawCornerBox(float x, float y, float width, float height, float linewidth, float scale, Vector3 color);
};