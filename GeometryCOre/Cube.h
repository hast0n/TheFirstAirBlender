#pragma once
#include "GraphicObject.h"
#include "Vector3f.h"

class Cube : public GraphicObject
{
public:
	Vector3f Pos;
	Vector3f Color;
	float Size;

	~Cube() {}
	Cube(const Vector3f& cubePosition, float cubeSize);

	void SetColor(const Vector3f& color) override;
	void Move(const Vector3f& vect3) override;
	void Scale(const float factor) override;

	void RTRender() const override;

	void GLRenderFaces(const Vector3f& faceColor) const;
	void GLRenderWireframe(const Vector3f& wireColor) const;
	void GLRender() const override;

private:
	Vector3f* _vertexBuffer[8];
	int _facesIndexBuffer[36];
	int _linesIndexBuffer[24];

	void LogInit() const;
	void SetVertexBuffers();
};
