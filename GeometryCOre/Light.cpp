#include "Light.h"

#include "Material.h"

Light::Light(Vector3f position, RGBAColor color) :Pos(position), Color(color) {}

Vector3f Light::getPosition() const
{
	return Pos;
}

void Light::setPosition(Vector3f newPos)
{
	Pos = newPos;
}

RGBAColor Light::getColor() const
{
	return Color;
}
