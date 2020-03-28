#pragma once
#include "Graphics.h"

namespace homework
{
	void Tutorial1(Graphics& gfx, MainWindow& wnd)
	{
		Vec2 v1{ 100,100 };
		//gfx.DrawLine(v1, Vec2{ (float)wnd.mouse.GetPosX(), (float)wnd.mouse.GetPosY() }, Colors::White);
		std::vector<Vec2> vertices = { {100,100},{200,100},{150,200} };
		gfx.DrawClosedPolyline(vertices, Colors::Red);
	}
}