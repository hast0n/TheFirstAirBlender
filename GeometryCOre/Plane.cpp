#include "Plane.h"

Plane::~Plane() {}

Plane::Plane(const Vector3f& center, float planeSize) : Pos(center), Size(planeSize)
{
	
}

Plane::Plane(const Vector3f& center, float nbSquareHeight, float nbSquareWidth)
{
	
}

void Plane::SetColor(const Vector3f& color)
{
	Color1 = color;
}

void Plane::SetColors(const Vector3f& color1, const Vector3f& color2)
{
	Color1 = color1; Color2 = color2;
}

void Plane::Move(const Vector3f& vect3)
{
	this->Pos += vect3;
}

void Plane::Scale(float factor)
{
	this->Size *= factor;
}

void Plane::RTRender() const
{
}

void Plane::GLRenderFill(const Vector3f& fillColor) const
{
	
}

void Plane::GLRenderWireframe(const Vector3f& wireColor) const
{
	
}

void Plane::GLRender() const
{
	
}

void Plane::GenerateVertexBuffer()
{
	
}
