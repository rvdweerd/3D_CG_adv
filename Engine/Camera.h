#pragma once
#include "Vec2.h"
#include "CoordinateTransformer.h"

class Camera
{
public:
	Camera( CoordinateTransformer& ct)
		:
		ct(ct)
	{}
	Vec2 GetPos()
	{
		return pos;
	}
	void MoveTo(Vec2 pos_in)
	{
		pos = pos_in;
	}
	void MoveBy(Vec2 offset)
	{
		pos += offset * camSpeed;
	}
	//void DrawClosedPolyline(std::vector<Vec2> verts, Color c)
	//{
	//	for (Vec2& v : verts)
	//	{
	//		v -= pos;
	//		v *= scale;
	//	}
	//	ct.DrawClosedPolyline(std::move(verts),c);
	//}
	void Draw(Drawable& drawable)
	{
		drawable.Translate(-pos);
		drawable.Scale(scale);
		ct.Draw(std::move(drawable));
	}
	void Scale(float scaler)
	{
		scale *= scaler;
	}
private:
	CoordinateTransformer& ct;
	Vec2 pos = { 0,0 };
	float camSpeed = 3.f;
	float scale = 1.f;
};