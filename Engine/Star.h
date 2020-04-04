#pragma once
#pragma once
#include <vector>
#include "Vec2.h"

class Star
{
public:
	static std::vector<Vec2> Make(float outerRadius, float innerRadius, int nFlares = 5, bool AxesOn = false)
	{
		std::vector<Vec2> star;
		if (AxesOn)
		{
			star.reserve(nFlares * 2+9);
			star.emplace_back(0.f, 0.f);
			star.emplace_back(-300.f, 0.f);
			star.emplace_back(0.f, 0.f);
			star.emplace_back(100.f, 0.f);
			star.emplace_back(0.f, 0.f);
			star.emplace_back(0.f, 100.f);
			star.emplace_back(0.f, 0.f);
			star.emplace_back(0.f, -100.f);
			star.emplace_back(0.f, 0.f);
		}
		else
		{
			star.reserve(nFlares * 2);
		}
		const float dTheta = 2.0f * 3.14159f / float(nFlares * 2);
		for (int i = 0; i < nFlares * 2; i++)
		{
			const float rad = (i % 2 == 0) ? outerRadius : innerRadius;
			star.emplace_back(
				rad * cos(float(i) * dTheta),
				rad * sin(float(i) * dTheta)
				);
		}
		return star;
	}
};