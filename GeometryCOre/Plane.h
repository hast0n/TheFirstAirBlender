#pragma once
#include "Vector3f.h"
#include "GraphicObject.h"

class Plane : public GraphicObject
{
public:
	Vector3f Pos;
	Vector3f Color;
	float Size;

	~Plane();
	Plane(const Vector3f& center, float size);

	void SetColor(const Vector3f& color);
	void Move(const Vector3f& vect3);
	void Scale(float factor);

	void RTRender() const;

	void GLRenderFill(const Vector3f& fillColor) const;
	void GLRenderWireframe(const Vector3f& wireColor) const;
	void GLRender() const;
};
