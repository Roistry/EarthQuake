#include "pch.h"
#include "ImguiDraw.h"

void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness) {
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0, color->a / 255.0)), 0, 0, thickness);
}

void DrawCircle(int x, int y, int radius, RGBA* color, int segments) {
	ImGui::GetForegroundDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0, color->a / 255.0)), segments);
}

void DrawFilledRect(int x, int y, int w, int h, RGBA* color) {
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0, color->a / 255.0)), 0, 0);
}

void DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color) {
	DrawFilledRect(x + borderPx, y, w / 3, borderPx, color);
	DrawFilledRect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color);
	DrawFilledRect(x, y, borderPx, h / 3, color);
	DrawFilledRect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
	DrawFilledRect(x + borderPx, y + h + borderPx, w / 3, borderPx, color);
	DrawFilledRect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color);
	DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color);
	DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
}

void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness) {
	ImGui::GetForegroundDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0, color->a / 255.0)), thickness);
}

void DrawLine(Vector2 from, Vector2 to, RGBA* color, int thickness) {
	DrawLine(from.x, from.y, to.x, to.y, color, thickness);
}

void DrawString(char* string, int x, int y, RGBA* color) {
	ImGui::GetForegroundDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(),
		ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->r / 255.0, color->g / 255.0, color->b / 255.0, color->a / 255.0)), string);
}