#pragma once
#include "Entity.h"
#include "Vec2.h"
#include "Drawable.h"
#include "Colors.h"

class Plank : public Entity
{
public:
	Plank()
		:
		Entity({}, { 0,0 }, Colors::Red, 1.f, 1.f)
	{
	}
	virtual Drawable GetDrawable(float dt) //override
	{
		plank = { this->GetPos(), this->GetPos() + Vec2{0,h}, fixture + Vec2{0,h}, fixture };
		Drawable d(plank, Colors::Red);
		return d;
	}
private:
	Vec2 fixture = { 200,0 };
	std::vector<Vec2> plank = {};
	static constexpr float h = 20;
};