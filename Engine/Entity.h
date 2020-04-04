#pragma once
#include <vector>
#include "Vec2.h"
#include "Drawable.h"


class Entity
{
public:
	Entity(std::vector<Vec2> vertices, Vec2 pos, Color col = Colors::Red)
		:
		verts(std::move(vertices)),
		pos(pos),
		c(col)
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
	void ScaleBy(float k)
	{
		scaler = scale_orig * k;
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
	float GetScale() const
	{
		return scaler;
	}
	virtual Drawable GetDrawable() 
	{
		Drawable d(verts, c);
		d.Scale( GetScale() );
		d.Translate(pos);
		return d;
	}
private:
	Vec2 pos{ 0.f,0.f };
	float scaler = 1.f;
	float scale_orig = 1.f;
	std::vector<Vec2> verts;
	Color c;
	float speed = 1.0f;
	float radius_outer;
};
