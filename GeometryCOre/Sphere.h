#pragma once
#include "GraphicObject.h"
#include "Vector3f.h"

class Sphere : public GraphicObject
{
public:
	Vector3f Pos;
	float Radius;

	~Sphere() override = default;
	Sphere(const Vector3f& center, float radius);
	
	void Move(const Vector3f& vect3);
	void Scale(float factor);

	void RTRender() const;

	void GLRenderFill(const Vector3f& fillColor) const;
	void GLRenderWireframe(const Vector3f& wireColor) const;
	void GLRender() const;

	bool Intersects(const Ray& ray, Vector3f* intersect) override;

private:
	void GLAddToDisplayList() const;
};
