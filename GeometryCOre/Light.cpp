#include "Light.h"

#include "Material.h"

Light::Light(Vector3f position, RGBAColor color) :Pos(position), Color(color) {}

Vector3f Light::getPosition() const
{
	return Pos;
}

RGBAColor Light::getColor() const
{
	return Color;
}
