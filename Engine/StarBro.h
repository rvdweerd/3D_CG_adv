#pragma once
#include "Star.h"
#include "Entity.h"

class StarBro : public Entity
{
public:
	StarBro(Vec2 pos, float radius, float innerRatio, int nFlares, Color c, float per=1.f, float amp = 1.f, float rotSpeed = 0.f)
		:
		Entity(Star::Make(radius, innerRatio * radius, nFlares), pos, c, per,amp),
		radius(radius),
		rotSpeed(rotSpeed)
	{
	}
	float GetRadius() const
	{
		return radius;
	}
	void Update(float dt)
	{
		time += dt;
		//Entity::SetAngle(Entity::GetAngle() + rotSpeed*dt );
		Entity::SetAngle(rotSpeed * time);
	}
private:
	float radius;
	float rotSpeed;
	float time=0.f;
};
