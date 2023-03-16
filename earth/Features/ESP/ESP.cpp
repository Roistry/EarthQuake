#include "pch.h"
#include "ESP.h"

void ESP::OnInit()
{

}

void ESP::OnLoop()
{

}

void ESP::OnUnInit()
{

}

void ESP::OnRender()
{
	for (size_t i = 1; i <= *Globals::Game::numberOfBots; i++)
	{
		Vector3 vec3PlayerHead = Globals::Game::entityList->aEntities[0].pos;
		Vector3 vec3TargetHead = Globals::Game::entityList->aEntities[i].pos;
		Vector2 screen = Globals::Game::refdef->WorldToScreen(vec3PlayerHead, vec3TargetHead);

		float distance = vec3PlayerHead.Distance(vec3TargetHead);

		float scale = (Globals::Game::GAME_UNIT_MAGIC / distance) * (Globals::Game::refdef->width / Globals::Game::refdef->width);
		float x = screen.x - scale;
		float y = screen.y - scale;
		float width = scale * 2;
		float height = scale * Globals::Game::PLAYER_ASPECT_RATIO * 2;

		//GL::DrawOutline(x, y, width, height, 2.0f, color);
		GL::DrawCornerBox(x, y, width, height, 2.0f, 3.0f, IsVisible(Globals::Game::entityList->aEntities[i]) ? Globals::glColors::green : Globals::glColors::red);
	}
}