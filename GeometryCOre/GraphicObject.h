#pragma once
#include "Material.h"
#include "Ray.h"
#include "Vector3f.h"

class GraphicObject
{
	static int ID;

protected:
	const int currentID;
	RGBAColor Color;
	Materials::Material Material;


public:
	GraphicObject();
	
	virtual ~GraphicObject() = default;
	
	virtual void RTRender() const = 0;

	virtual void GLRender() const = 0;


	virtual void Move(const Vector3f& vect3) = 0;

	virtual void Scale(float factor) = 0;

	//TODO: Add rotation to objects
	//virtual void Rotate(float factor) = 0;

	virtual bool Intersects(const Ray& ray, Vector3f& intersect, Vector3f& normal) = 0;
	
	void SetColor(const RGBAColor& color) {Material.finish = color;}
	
	void SetMaterial(const Materials::Material material) { Material = material;}

	RGBAColor getColor() const;

	Materials::Material getMaterial() const;
	
	int GetID() const;
};
