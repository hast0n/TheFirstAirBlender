#include "GraphicObject.h"
#include "Vector3f.h"

int GraphicObject::ID = 0;

GraphicObject::GraphicObject(): currentID(ID++) {}

Vector3f GraphicObject::getColor() const
{
	return Color;
}

int GraphicObject::GetID() const
{
	return currentID;
}
