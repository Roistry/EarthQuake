#pragma once

// TODO: REFACTOR ME
namespace RGB {
	inline Vector3 red(255, 0, 0);
	inline Vector3 green(0, 255, 0);
	inline Vector3 gray(55, 55, 55);
	inline Vector3 lightgray(192, 192, 192);
	inline Vector3 black(0, 0, 0);
	inline Vector3 white(255, 255, 255);
}

namespace GL {
	void SetupOrtho();
	void RestoreGL();

	void DrawFilledRect(float x, float y, float width, float height, Vector3 color);
	void DrawOutline(float x, float y, float width, float height, float linewidth, Vector3 color);
	void DrawLine(Vector2 src, Vector2 dst, float linewidth, Vector3 color);
	void DrawCornerBox(float x, float y, float width, float height, float linewidth, float scale, Vector3 color);
}