#include "Sphere.h"
#include "glut.h"
#include <iostream>

Sphere::Sphere(const Vector3f& center, float radius)
{
	Pos = center;
	Radius = radius;
}

void Sphere::SetColor(const Vector3f& color)
{
	Color = color;
}

void Sphere::Move(const Vector3f& vect3)
{
	this->Pos += vect3;
}

void Sphere::Scale(float factor)
{
	this->Radius *= factor;
}

void Sphere::RTRender() const
{

}

void Sphere::GLRenderFill(const Vector3f& fillColor) const
{
	glColor3f(fillColor.X, fillColor.Y, fillColor.Z);

	//glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLAddToDisplayList();
}

void Sphere::GLRenderWireframe(const Vector3f& wireColor) const
{
	glColor3f(wireColor.X, wireColor.Y, wireColor.Z);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLAddToDisplayList();
}

void Sphere::GLRender() const
{
	if (this->Color == Vector3f(NULL, NULL, NULL))
		GLRenderFill(Vector3f(1.0, 0.0, 1.0));
	else GLRenderFill(this->Color);

	GLRenderWireframe(Vector3f(1.0, 0.0, 0.0));
}

void Sphere::GLAddToDisplayList() const
{
	GLUquadric* quad = gluNewQuadric();

	glPushMatrix(); // save current position
	glTranslatef(Pos.X, Pos.Y, Pos.Z);
	gluSphere(quad, Radius, 100, 30);

	glPopMatrix(); // load previously saved position
}