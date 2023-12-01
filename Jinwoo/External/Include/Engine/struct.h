#pragma once


struct Vec2
{
public:
	float x;
	float y;

public:
	Vec2() : x(0.f), y(0.f)
	{

	}

	Vec2(float _x, float _y) : x(_x), y(_y)
	{

	}

	Vec2(int _x, int _y) : x((float)_x), y((float)_y)
	{

	}

	Vec2(UINT _x, UINT _y) : x((float)_x), y((float)_y)
	{

	}

	Vec2(POINT _point) : x((float)_point.x), y((float)_point.y)
	{

	}
};