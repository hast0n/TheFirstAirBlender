#pragma once
#include "Material.h"
#include "Vector3f.h"

class Light
{
	RGBAColor Color {};
	Vector3f Pos {};
	
	float decay = 0;

public:
	Light(Vector3f position, RGBAColor color);

	Vector3f getPosition() const;
	
	void setPosition(Vector3f newPos);
	
	RGBAColor getColor() const;
		
};

