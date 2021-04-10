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
	
	void Move(const Vector3f& vect3) override;
	void Scale(float factor) override;

	void RTRender() const override;

	void GLRenderFill(const Vector3f& fillColor) const;
	void GLRenderWireframe(const Vector3f& wireColor) const;
	void GLRender() const override;

	bool Intersects(const Ray& ray, Vector3f& intersect, Vector3f& normal) override;

private:
	void GLAddToDisplayList() const;
};
