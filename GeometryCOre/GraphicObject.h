#pragma once
#include "Ray.h"
#include "Vector3f.h"

class GraphicObject
{
	static int ID;

protected:
	const int currentID;
	Vector3f Color;


public:
	GraphicObject();
	
	virtual ~GraphicObject() = default;
	
	virtual void RTRender() const = 0;

	virtual void GLRender() const = 0;


	virtual void Move(const Vector3f& vect3) = 0;

	virtual void Scale(float factor) = 0;

	virtual bool Intersects(const Ray& ray, Vector3f& intersect, Vector3f& normal) = 0;
	
	void SetColor(const Vector3f& color) {Color = color;}

	Vector3f getColor() const;

	int GetID() const;
};
