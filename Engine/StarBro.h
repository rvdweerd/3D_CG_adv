#pragma once
#include "Star.h"
#include "Entity.h"

class StarBro : public Entity
{
public:
	StarBro(Vec2 pos, float radius, float innerRatio, int nFlares, Color c, float per=1.f, float amp = 1.f )
		:
		Entity(Star::Make(radius, innerRatio * radius, nFlares), pos, c, per,amp),
		radius(radius)
	{
	}
	float GetRadius() const
	{
		return radius;
	}
private:
	float radius;
};
