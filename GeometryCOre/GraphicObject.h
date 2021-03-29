#pragma once
#include "Ray.h"
#include "Vector3f.h"

class GraphicObject
{
public:
	virtual ~GraphicObject() = default;
	
	virtual void RTRender() const = 0;

	virtual void GLRender() const = 0;

	//virtual Vector3f* GetVertexBuffer() const = 0;

	void SetColor(const Vector3f& color);

	virtual void Move(const Vector3f& vect3) = 0;

	virtual void Scale(float factor) = 0;

	virtual bool Intersects(const Ray& ray, Vector3f* intersect) = 0;

	[[nodiscard]] Vector3f getColor() const {return Color;}

protected:
	Vector3f Color;
};

inline void GraphicObject::SetColor(const Vector3f& color)
{
	Color = color;
}

