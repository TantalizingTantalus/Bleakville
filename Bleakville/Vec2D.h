#pragma once

class Vec2D
{
public:
	float x = 0;
	float y = 0;

	Vec2D(float inX, float inY);
	Vec2D();

	static Vec2D Zero();

	void Clear();

	void Set(float inX, float inY);
};