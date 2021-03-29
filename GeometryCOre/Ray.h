#pragma once
#include "Vector3f.h"

struct Ray
{
	Vector3f Direction;
	Vector3f Destination;
	Vector3f Origin;
	
	Ray(Vector3f origin, Vector3f dest);
};

