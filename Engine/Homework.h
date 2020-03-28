#pragma once
#include "Graphics.h"
#include "Star.h"

namespace homework
{
	void Tutorial1(Graphics& gfx, MainWindow& wnd)
	{
		Vec2 v1{ 100,100 };
		//gfx.DrawLine(v1, Vec2{ (float)wnd.mouse.GetPosX(), (float)wnd.mouse.GetPosY() }, Colors::White);
		std::vector<Vec2> vertices = Star::Make(175, 75, 8);

		for (auto& v : vertices)
		{
			v += {200, 200};
		}
		gfx.DrawClosedPolyline(vertices, Colors::Red);
	}
}