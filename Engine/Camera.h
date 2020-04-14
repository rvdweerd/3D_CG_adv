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
		pos += offset;// *camSpeed;
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
	void Draw(Drawable& drawable) const
	{

		drawable.Translate(-pos);
		
		drawable.Scale(scale);
		drawable.Rotate(angle);
		ct.Draw( drawable );
	}
	void Scale(float scaler)
	{
		scale *= scaler;
	}
	float GetScale() const
	{
		return scale;
	}
	float GetSpeed() const
	{
		return camSpeed;
	}
	float GetAngle() const
	{
		return angle;
	}
	void SetAngle(float angle_in)
	{
		angle = angle_in;
	}
private:
	CoordinateTransformer& ct;
	Vec2 pos = { 0,0 };
	float camSpeed = 13.f;
	float angle = 0.f;
	float scale = 1.0f;
};