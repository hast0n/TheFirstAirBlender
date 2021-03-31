#include "Sphere.h"
#include "glut.h"
#include <iostream>

Sphere::Sphere(const Vector3f& center, float radius): GraphicObject()
{
	Pos = center;
	Radius = radius;
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

	//GLRenderWireframe(Vector3f(1.0, 0.0, 0.0));
}

bool Sphere::Intersects(const Ray& ray, Vector3f* intersect)
{
	// inspired from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
    float i0, i1;

	// get origin to sphere center vector
	const Vector3f tsc = Pos - ray.Origin; 

	// get distance to sphere center level on ray path
	float dtsc = tsc * ray.Direction;

	// get ray path to sphere center minimum distance squarred (where perpendicular to ray path)
	// Pythagore (sideLength² = hypotenuse² - otherSideLength²)
    float rptsc2 = tsc * tsc - dtsc * dtsc;

	// sphere radius squarred
	float radius2 = Radius * Radius;

	// check if intersection occurs
    if (rptsc2 > radius2) 
		return false; 

	// sort the 2 intersection points (closest & farthest)
	// get half the distance the ray travels while inside the sphere
	float rhd = sqrt(radius2 - rptsc2);

	// determine each 2 intersection points distance from ray origin (entry & exit)
    i0 = dtsc - rhd; 
    i1 = dtsc + rhd; 

	// if entry is farther than exit, swap them
    if (i0 > i1) std::swap(i0, i1); 

	// if entry is behind camera eye, use exit to show sphere interior
    if (i0 < 0) {
    	
        i0 = i1;

    	// if exit also is behind eye, cancel intersection
    	if (i0 < 0) 
			return false;
    } 

	// set out variable to give back intersection point
    *intersect = ray.Origin + ray.Direction * i0; 

    return true;
}

void Sphere::GLAddToDisplayList() const
{
	GLUquadric* quad = gluNewQuadric();

	glPushMatrix(); // save current position
	glTranslatef(Pos.X, Pos.Y, Pos.Z);
	gluSphere(quad, Radius, 100, 30);

	glPopMatrix(); // load previously saved position
}
