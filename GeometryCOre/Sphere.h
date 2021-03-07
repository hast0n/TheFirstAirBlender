#pragma once
#include "GraphicObject.h"
#include "Vector3f.h"

class Sphere : public GraphicObject
{
public:
	Vector3f Pos;
	Vector3f Color;
	float Radius;

	~Sphere() {}
	Sphere(const Vector3f& center, float radius);

	void SetColor(const Vector3f& color);
	void Move(const Vector3f& vect3);
	void Scale(float factor);

	void RTRender() const;

	void GLRenderFill(const Vector3f& fillColor) const;
	void GLRenderWireframe(const Vector3f& wireColor) const;
	void GLRender() const;

private:
	void GLAddToDisplayList() const;
};
