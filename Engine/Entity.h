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
	{}
	Vec2 GetPos() const
	{
		return pos;
	}
	void SetPos(Vec2 pos)
	{
		this->pos = pos;
	}
	void Translate(Vec2 vec)
	{
		this->pos += vec*speed;
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
	Drawable GetDrawable() const
	{
		Drawable d(verts, c);
		d.Scale(scaler);
		d.Translate(pos);
		return d;
	}

private:
	Vec2 pos{ 0,0 };
	float scaler = 1.f;
	std::vector<Vec2> verts;
	Color c;
	float speed = 2.f;
};
