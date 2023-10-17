#include <iostream>

class Point3D
{
public:
	Point3D(float x, float y, float z);
	float GetX();
	float GetY();
	float GetZ();

private:
	float x;
	float y;
	float z;
};