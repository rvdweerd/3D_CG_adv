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
	void Draw(Drawable& drawable) const
	{
		drawable.ApplyTransformation(
			Mat3::Rotate(angle) * 
			Mat3::Scale(scale) *
			Mat3::Translate(-pos.x, -pos.y) 
		);
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