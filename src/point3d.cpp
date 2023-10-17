#include <iostream>

class Point3D
{
public:
	Point3D(float x, float y, float z) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float GetX() const
	{
		return this->x;
	}

	float GetY() const
	{
		return this->y;
	}

	float GetZ() const
	{
		return this->z;
	}

private:
	float x;
	float y;
	float z;
};