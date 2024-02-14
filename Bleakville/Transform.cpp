#include "Transform.h"


void Transform::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	return;
}

const Vec2D Transform::GetPosition()
{
	return position;
}

void Transform::SetScale(float w, float h)
{
	scale.x = w;
	scale.y = h;
}

const Vec2D Transform::GetScale()
{
	return scale;
}