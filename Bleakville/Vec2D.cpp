#include "Vec2D.h"

Vec2D::Vec2D()
{
	x = 0;
	y = 0;
}

Vec2D::Vec2D(float inX, float inY)
{
	x = inX;
	y = inY;
}

Vec2D Vec2D::Zero()
{
	return Vec2D(0, 0);
}

void Vec2D::Clear()
{
	x = 0;
	y = 0;
}

void Vec2D::Set(float inX, float inY)
{
	x = inX;
	y = inY;
}