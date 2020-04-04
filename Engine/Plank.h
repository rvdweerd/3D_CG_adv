#pragma once
#include "Entity.h"
#include "Vec2.h"
#include "Drawable.h"
#include "Colors.h"

class Plank : public Entity
{
public:
	Plank( Vec2 Anchor, float freeX, float minFreeY, float maxFreeY, float fatness = 8.f , Color c = Colors::Yellow)
		:
		Entity({}, Anchor,c),
		minFreeYModel(minFreeY - Anchor.y),
		maxFreeYModel(maxFreeY - Anchor.y),
		freePtModel(freeX- Anchor.x , minFreeYModel),
		fatness(fatness)
	{
	}
	virtual Drawable GetDrawable() //override
	{
		std::vector<Vec2> model;
		model.reserve(4);
		model.emplace_back(0.0f, 0.0f);
		model.push_back(freePtModel);
		model.push_back(freePtModel + Vec2{ 0.0f,fatness });
		model.emplace_back( 0.0f,fatness );
		SetModel(std::move(model));
		return Entity::GetDrawable();
	}
	/*virtual void Translate(Vec2 vec)
	{
		freePtModel += vec*10.0f;
		freePtModel.y = std::clamp(freePtModel.y, minFreeYModel, maxFreeYModel);
	}*/
	Vec2 GetFreePt() const
	{
		return freePtModel + GetPos();
	}
	void SetFreeY(float FreeY_in)
	{
		freePtModel.y = std::clamp( FreeY_in - GetPos().y, minFreeYModel, maxFreeYModel);
	}
	void MoveFreeY(float deltaY)
	{
		SetFreeY(GetFreePt().y + deltaY);
	}
	Vec2 GetPlankSurfaceVector() const
	{
		return -freePtModel;
	}
private:
	float minFreeYModel;
	float maxFreeYModel;
	Vec2 freePtModel;
	float fatness;
};