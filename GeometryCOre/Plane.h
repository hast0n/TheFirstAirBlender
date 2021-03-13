#pragma once
#include "Vector3f.h"
#include "GraphicObject.h"

class Plane : public GraphicObject
{
public:
	Vector3f Pos;
	Vector3f Color1;
	Vector3f Color2;
	float Size;

	~Plane();
	Plane(const Vector3f& center, float planeSize);
	Plane(const Vector3f& center, float nbSquareHeight, float nbSquareWidth);

	void SetColor(const Vector3f& color);
	void SetColors(const Vector3f& color1, const Vector3f& color2);
	void Move(const Vector3f& vect3);
	void Scale(float factor);

	void RTRender() const;

	void GLRenderFill(const Vector3f& fillColor) const;
	void GLRenderWireframe(const Vector3f& wireColor) const;
	void GLRender() const;

private:
	Vector3f* _vertexBuffer[4];
	int _facesIndexBuffer[6];
	//int _linesIndexBuffer[24];

	void GenerateVertexBuffer();
};
