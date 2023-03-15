#include "pch.h"
#include "glDraw.h"

void GL::SetupOrtho() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void GL::RestoreGL() {
	glPopMatrix();
	glPopAttrib();
}

void GL::DrawFilledRect(float x, float y, float width, float height, Vector3 color) {
	glColor3ub(color.x, color.y, color.z);

	glBegin(GL_QUADS);

	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);

	glEnd();
}

void GL::DrawOutline(float x, float y, float width, float height, float linewidth, Vector3 color) {
	glLineWidth(linewidth);

	glBegin(GL_LINE_STRIP);

	glColor3ub(color.x, color.y, color.z);
	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5F, y - 0.5f);

	glEnd();
}

void GL::DrawLine(Vector2 src, Vector2 dst, float linewidth, Vector3 color) {
	glLineWidth(linewidth);

	glBegin(GL_LINES);

	glColor3ub(color.x, color.y, color.z);
	glVertex2f(src.x, src.y);
	glVertex2f(dst.x, dst.y);

	glEnd();
}

void GL::DrawCornerBox(float x, float y, float width, float height, float linewidth, float scale, Vector3 color) {
	// Top Left
	GL::DrawLine(Vector2(x, y), Vector2(x, y + height / scale), linewidth, color);
	GL::DrawLine(Vector2(x, y), Vector2(x + width / scale, y), linewidth, color);

	// Top Right
	GL::DrawLine(Vector2(x + width, y), Vector2(x + width - width / scale, y), linewidth, color);
	GL::DrawLine(Vector2(x + width, y), Vector2(x + width, y + height / scale), linewidth, color);


	// Bottom Left
	GL::DrawLine(Vector2(x, y + height), Vector2(x, y + height - height / scale), linewidth, color);
	GL::DrawLine(Vector2(x, y + height), Vector2(x + width / scale, y + height), linewidth, color);

	// Bottom Right
	GL::DrawLine(Vector2(x + width, y + height), Vector2(x + width, y + height - height / scale), linewidth, color);
	GL::DrawLine(Vector2(x + width, y + height), Vector2(x + width - width / scale, y + height), linewidth, color);
}