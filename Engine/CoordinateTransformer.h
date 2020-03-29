#pragma once
#include "Graphics.h"
#include "Vec2.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer(Graphics& gfx)
		:
		gfx(gfx)
	{}
	void DrawClosedPolyline(std::vector<Vec2> vert, Color c)
	{
		const Vec2 offset = Vec2{ Graphics::ScreenWidth / 2,Graphics::ScreenHeight / 2 };
		//const Vec2 offset = { 0,0 };
		for (auto& v : vert)
		{
			v.y *= -1.f;
			v += offset;
		}
		gfx.DrawClosedPolyline(vert, c);
	}

private:
	Graphics& gfx;
};