#pragma once
#include "Graphics.h"
#include "Vec2.h"
#include "Drawable.h"

class CoordinateTransformer
{
public:
	CoordinateTransformer(Graphics& gfx)
		:
		gfx(gfx)
	{}
	void Draw(Drawable& drawable) const
	{
		drawable.ApplyTransformation(
			Mat3::Translate(offset.x, offset.y) *
			Mat3::ScaleXY(1.0f,-1.0f) 
		);
		drawable.Render(gfx);
	}

private:
	const Vec2 offset = Vec2{ Graphics::ScreenWidth / 2,Graphics::ScreenHeight / 2 };
	Graphics& gfx;
};