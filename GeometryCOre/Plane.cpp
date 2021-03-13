#include "Plane.h"
#include "glut.h"

Plane::~Plane() {}

Plane::Plane(const Vector3f& center, float planeSize)
{
	Pos = center; Size = planeSize;
	GenerateVertexBuffer();
}

//Plane::Plane(const Vector3f& center, float nbSquareZ, float nbSquareX)
//{
//	
//}

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
	glColor3f(fillColor.X, fillColor.Y, fillColor.Z);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < 6; i++)
	{
		int index = _facesIndexBuffer[i];
		Vector3f vect = *_vertexBuffer[index];

		glVertex3f(vect.X, vect.Y, vect.Z);
	}

	glEnd();
}

void Plane::GLRenderWireframe(const Vector3f& wireColor) const
{
	
}

void Plane::GLRender() const
{
	GLRenderFill(this->Color1);
}

void Plane::GenerateVertexBuffer()
{
	// Temporary simple generating method

	float hs = Size / 2; // half size
	
	Vector3f* BL = new Vector3f(Pos.X - hs, Pos.Y, Pos.Z - hs);
	Vector3f* BR = new Vector3f(Pos.X + hs, Pos.Y, Pos.Z - hs);
	Vector3f* FL = new Vector3f(Pos.X - hs, Pos.Y, Pos.Z + hs);
	Vector3f* FR = new Vector3f(Pos.X + hs, Pos.Y, Pos.Z + hs);

	Vector3f* vertexBuffer[4] = { BL, BR, FL, FR };
	
	int* facesIndexBuffer = new int[6] { 0, 1, 2, 1, 2, 3 };

	for (int i = 0; i < 4; i++)
	{
		Vector3f* vert = vertexBuffer[i];
		_vertexBuffer[i] = vert;
	}

	for (int i = 0; i < 6; i++)
	{
		int index = facesIndexBuffer[i];
		_facesIndexBuffer[i] = index;
	}
}
