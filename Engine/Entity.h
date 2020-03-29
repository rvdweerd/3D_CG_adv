#pragma once
#include <vector>
#include "Vec2.h"


class Entity
{
public:
	Entity(std::vector<Vec2> vertices, Vec2 pos)
		:
		verts(std::move(vertices)),
		pos(pos)
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
	std::vector<Vec2> GetPolyLine() const
	{
		std::vector<Vec2> mod = verts;
		for (auto& v : mod)
		{
			v *= scaler;
			v += pos;
		}
		return std::move(mod);
	}

private:
	Vec2 pos{ 0,0 };
	float scaler = 1.f;
	std::vector<Vec2> verts;
	float speed = 2.f;
};
