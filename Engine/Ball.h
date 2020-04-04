#pragma once
#include "Entity.h"
#include "Vec2.h"
#include "Drawable.h"
#include "Colors.h"
#include "Star.h"
class Ball : public Entity
{
public:
	Ball(float Radius, Vec2 pos0, Vec2 vel0, Color c)
		:
		Entity(Star::Make(Radius, Radius, 8), pos0, c),
		Radius(Radius),
		vel(vel0)
	{}
	void Update(float dt)
	{
		//SetPos(GetPos() + vel);
		TranslateBy(vel * dt);
	}
	float GetRadius() const
	{
		return Radius;
	}
	void SetVel(Vec2 vel_in)
	{
		vel = vel_in;
	}
	Vec2 GetVelocityVector() const
	{
		return vel;
	}
	
private:
	float Radius;
	Vec2 vel;
};