#include "GraphicObject.h"
#include "Vector3f.h"

int GraphicObject::ID = 0;

GraphicObject::GraphicObject(): currentID(ID++)
{
	SetColor(RGBAColor(1.0, 0.0, 1.0));
	SetMaterial(Materials::Default);
}

RGBAColor GraphicObject::getColor() const
{
	return Material.finish;
}

Materials::Material GraphicObject::getMaterial() const
{
	return Material;
}

int GraphicObject::GetID() const
{
	return currentID;
}
