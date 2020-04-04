#pragma once
#include <vector>
#include "Vec2.h"
#include "Drawable.h"


class Entity
{
	class Pulser
	{
	public:
		Pulser(float period, float ampFactor)
			:
			period(period),
			ampFactor(ampFactor)
		{}
		float period = 5.f;//ms
		float ampFactor = 1.5f;
		float halfAmpl = (ampFactor - 1 / ampFactor);
		float timer = 0;
		float GetScale(float dt)
		{
			timer += dt;
			if (timer > period)
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
				return (1.f + ( 1 - 1 / ampFactor) * y);
			}
		}
	};

public:
	Entity(std::vector<Vec2> vertices, Vec2 pos, Color col = Colors::Red, float period = 1.0f, float ampFactor = 1.0f)
		:
		verts(std::move(vertices)),
		pos(pos),
		c(col),
		pulser(period,ampFactor)
	{
		float radiusSq = 0;
		for (const Vec2& v : verts)
		{
			radiusSq = std::max(radiusSq, (v).LenSq() );
		}
		radius_outer = sqrt(radiusSq);
	}
	float GetOuterRadius() const
	{
		return radius_outer;
	}
	Vec2 GetPos() const
	{
		return { (float)pos.x,(float)pos.y };
	}
	float GetSpeed() const
	{
		return speed;
	}
	void SetModel(std::vector<Vec2> model)
	{
		verts = model;
	}
	void SetPos(Vec2 pos)
	{
		this->pos = pos;
	}
	virtual void TranslateBy(Vec2 vec)
	{
		this->pos += vec;
	}
	void Scale(float k)
	{
		scaler *= k;
	}
	void Accelerate(float q)
	{
		speed *= q;
	}
	//std::vector<Vec2> GetPolyLine() const
	//{
	//	std::vector<Vec2> mod = verts;
	//	for (auto& v : mod)
	//	{
	//		v *= scaler;
	//		v += pos;
	//	}
	//	return std::move(mod);
	//}

	virtual Drawable GetDrawable(float dt) 
	{
		Drawable d(verts, c);
		d.Scale( pulser.GetScale(dt) * scaler );
		d.Translate(pos);
		return d;
	}
private:
	Pulser pulser;
	Vec2 pos{ 0.f,0.f };
	float scaler = 1.f;
	std::vector<Vec2> verts;
	Color c;
	float speed = 1.0f;
	float radius_outer;
};
