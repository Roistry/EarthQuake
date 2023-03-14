#pragma once
void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness);
void DrawCircle(int x, int y, int radius, RGBA* color, int segments);
void DrawFilledRect(int x, int y, int w, int h, RGBA* color);
void DrawCornerBox(int x, int y, int w, int h, int borderPx, RGBA* color);
void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness);
void DrawLine(Vector2 from, Vector2 to, RGBA* color, int thickness);
void DrawString(char* string, int x, int y, RGBA* color);