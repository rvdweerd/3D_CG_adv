#pragma once
#include <vector>
#include "Vec2.h"
#include "Graphics.h"

class Drawable
{
public:
	Drawable(std::vector<Vec2> model, Color c)
		:
		model(std::move(model)),
		c(c)
	{
	}
	void Scale(float s)
	{
		scale_X *= s;
		scale_Y *= s;
		translation *= s;
	}
	void ScaleIndependent(float s_X, float s_Y)
	{
		scale_X *= s_X;
		scale_Y *= s_Y;
		translation.x *= s_X;
		translation.y *= s_Y;
	}
	void Translate(Vec2 offset)
	{
		translation += offset;
	}
	void Render(Graphics& gfx)
	{
		bool render = false;
		for (Vec2& v : model)
		{
			v.x *= scale_X;
			v.y *= scale_Y;
			v += translation;
			if (!render&& Graphics::OnScreen(v))
			{
				render = true;
			}
		}
		if (render)
		{
			gfx.DrawClosedPolyline(model, c);
		}
	}

private:
	std::vector<Vec2> model;
	Color c;
	Vec2 translation = { 0.f,0.f };
	float scale_X = 1.f;
	float scale_Y = 1.f;
};
