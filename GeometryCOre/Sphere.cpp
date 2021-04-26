#include "Sphere.h"
#include "glut.h"
#include <iostream>

Sphere::Sphere(const Vector3f& center, float radius): GraphicObject()
{
	Pos = center;
	Radius = radius;
}

Sphere::Sphere()
{
	Pos = Vector3f();
	Radius = 1.f;
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

void Sphere::GLRenderFill() const
{
	auto c = getColor();
	glColor3f(c.r, c.g, c.b);

	//glMatrixMode(GL_MODELVIEW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	GLAddToDisplayList();
}

void Sphere::GLRenderWireframe() const
{
	auto c = getColor();
	glColor3f(c.r, c.g, c.b);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLAddToDisplayList();
}

void Sphere::GLRender() const
{
	//GLRenderFill(this->Color);
	GLRenderFill();

	//GLRenderWireframe(Vector3f(1.0, 0.0, 0.0));
}

bool Sphere::Intersects(const Ray& ray, Vector3f& intersect, Vector3f& normal)
{
	// inspired from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
    float i0, i1;

	// get origin to sphere center vector
	const Vector3f tsc = Pos - ray.Origin; 

	// get distance to sphere center level on ray path
	float dtsc = tsc * ray.Direction;

	// get ray path to sphere center minimum distance squarred (where perpendicular to ray path)
	// Pythagore (sideLength� = hypotenuse� - otherSideLength�)
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
    intersect = ray.Origin + ray.Direction * i0;
	normal = (intersect - Pos).normalized();

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
