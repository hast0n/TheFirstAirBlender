#include "Sphere.h"
#include "glut.h"
#include <iostream>

Sphere::Sphere(const Vector3f& center, float radius)
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

	GLRenderWireframe(Vector3f(1.0, 0.0, 0.0));
}

bool Sphere::Intersects(const Ray& ray, Vector3f* intersect)
{
    float t0, t1; // solutions for t if the ray intersects
    
    // geometric solution
    Vector3f L = Pos - ray.Origin; 
    float tca = L * ray.Direction;
    // if (tca < 0) return false;
    float d2 = L * L - tca * tca;
	float radius2 = Radius * Radius;

    if (d2 > radius2) 
		return false; 

	float thc = sqrt(radius2 - d2); 
    t0 = tca - thc; 
    t1 = tca + thc; 

    if (t0 > t1) std::swap(t0, t1); 

    if (t0 < 0) { 
        t0 = t1; // if t0 is negative, let's use t1 instead 

    	if (t0 < 0) 
			return false; // both t0 and t1 are negative 
    } 

    *intersect = ray.Origin + ray.Direction * t0; 

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
