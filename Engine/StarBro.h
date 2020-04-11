#pragma once
#include "Star.h"
#include "Entity.h"

class StarBro : public Entity
{
public:
	class Pulser
	{
	public:
		Pulser(float period, float ampFactor)
			:
			period(period),
			ampFactor(ampFactor)
		{}
		float period;// = 5.f;//ms
		float ampFactor;// = 1.5f;
		//float halfAmpl = (ampFactor - 1 / ampFactor);
		float timer = 0;
		float GetAngle()
		{
			return (timer / period /2) * 2 * 3.141f;
		}
		float GetScale(float dt)
		{
			timer += dt;
			if (timer > 2*period)
			{
				timer = 0;
			}
			float y = sin(6.28f * timer / period);
			if (y > 0)
			{
				return (1.f + (ampFactor - 1.0f) * y);
			}
			else
			{
				return (1.f + (1 - 1 / ampFactor) * y);
			}
		}
	};

public:
	StarBro(Vec2 pos, float radius, float innerRatio, int nFlares, Color c, float phi = 0.0f, float per=1.f, float amp = 1.f, bool axes=false)
		:
		Entity(Star::Make(radius, innerRatio * radius, nFlares,axes), pos, c),
		radius(radius),
		pulser(per, amp)
	{
		SetRotationAngle(phi);
	}
	float GetRadius() const
	{
		return radius;
	}
	void Update(float dt)
	{
		ScaleBy(pulser.GetScale(dt));
		SetRotationAngle(pulser.GetAngle());
	}
private:
	float radius;
	Pulser pulser;
};
