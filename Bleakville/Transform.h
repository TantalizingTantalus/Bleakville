#pragma once
#include "Vec2D.h"

class Transform
{
public:
	

	Vec2D position;
	void SetPosition(float x, float y);
	const Vec2D GetPosition();

	Vec2D scale;
	void SetScale(float w, float h);
	const Vec2D GetScale();
	
};