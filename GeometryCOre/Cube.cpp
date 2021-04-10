#include "glut.h"
#include "Cube.h"

#include <windows.h>

Cube::Cube(const Vector3f& cubePosition, float cubeSize): GraphicObject()
{
	Pos = cubePosition;
	Size = cubeSize;

	Color = Vector3f(1.0, 0.0, 1.0);
	
	GenerateVertexBuffers();
	LogInit();
}

void Cube::Move(const Vector3f& vect3)
{
	// TODO: use matrix states instead
	this->Pos += vect3;
	// GenerateVertexBuffers();
}

void Cube::Scale(const float factor)
{
	this->Size *= factor;
	GenerateVertexBuffers();
}

void Cube::RTRender() const
{

}

void Cube::GLRenderFaces(const Vector3f& faceColor) const
{
	glMatrixMode(GL_MODELVIEW);
	glColor3f(faceColor.X, faceColor.Y, faceColor.Z);

	//glPopMatrix();
	
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_TRIANGLES);

			for (int i = 0; i < 36; i++)
			{
				int index = _facesIndexBuffer[i];
				Vector3f vect = *_vertexBuffer[index];

				glVertex3f(vect.X, vect.Y, vect.Z);
			}

		glEnd();

	//glPushMatrix();
}

void Cube::GLRenderWireframe(const Vector3f& wireColor) const
{
	glColor3f(wireColor.X, wireColor.Y, wireColor.Z);

	glBegin(GL_LINES);

	for (int i = 0; i < 24; i++)
	{
		int index = _linesIndexBuffer[i];
		Vector3f vect = *_vertexBuffer[index];

		glVertex3f(vect.X, vect.Y, vect.Z);
	}

	glEnd();
}

void Cube::GLRender() const
{
	GLRenderFaces(this->Color);

	//GLRenderWireframe(Vector3f(1.0, 0.0, 0.0));
}

bool Cube::Intersects(const Ray& ray, Vector3f& intersect, Vector3f& normal)
{
	// mainly inspired from https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection

	const Vector3f invdir = 1 / ray.Direction; 
	const float halfSize = Size / 2;

	Vector3f bounds[] = {
		Pos - halfSize,
		Pos + halfSize
	};
	
    int sign[] = {
	    sign[0] = (invdir.X < 0), 
	    sign[1] = (invdir.Y < 0),
	    sign[2] = (invdir.Z < 0)
    };

    float tmin = (bounds[sign[0]].X - ray.Origin.X) * invdir.X; 
    float tmax = (bounds[1 - sign[0]].X - ray.Origin.X) * invdir.X; 
    float tymin = (bounds[sign[1]].Y - ray.Origin.Y) * invdir.Y; 
    float tymax = (bounds[1 - sign[1]].Y - ray.Origin.Y) * invdir.Y; 

    if ((tmin > tymax) || (tymin > tmax)) return false; 

    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    float tzmin = (bounds[sign[2]].Z - ray.Origin.Z) * invdir.Z;
    float tzmax = (bounds[1 - sign[2]].Z - ray.Origin.Z) * invdir.Z;

    if ((tmin > tzmax) || (tzmin > tmax)) return false; 

    if (tzmin > tmin) tmin = tzmin; 
    if (tzmax < tmax) tmax = tzmax; 

	float t = tmin;
	
	if (t < 0) { 
        t = tmax; 
        if (t < 0) return false; 
    } 
	
    intersect = ray.Origin + ray.Direction * t;
	//normal = ;
	
    return true; 
}

void Cube::LogInit()
{
	//char* a = Pos.X;
	//char* x = new char[, Pos.Y, Size]
	//std::format("cube created at [{}; {}] with size {}", );

	//Logger::Write(log_string, LogLevel::INFO);
	//delete x[];
}

void Cube::GenerateVertexBuffers() {

	// Compute vertex buffer array

	// 8 points:
	//
	//      E ---- F    +Y
	//     /|     /|     |
	//    A ---- B |     |/
	//    | H .--| G  -- . ------ +X
	//    |/     |/     /|
	//    D ---- C     /
	//               +Z 

	// Compute all 8 vertices that makes a cube
	float hs = Size / 2; // half size

	Vector3f* A = new Vector3f(Pos.X - hs, Pos.Y + hs, Pos.Z + hs);
	Vector3f* B = new Vector3f(Pos.X + hs, Pos.Y + hs, Pos.Z + hs);
	Vector3f* C = new Vector3f(Pos.X + hs, Pos.Y - hs, Pos.Z + hs);
	Vector3f* D = new Vector3f(Pos.X - hs, Pos.Y - hs, Pos.Z + hs);
	Vector3f* E = new Vector3f(Pos.X - hs, Pos.Y + hs, Pos.Z - hs);
	Vector3f* F = new Vector3f(Pos.X + hs, Pos.Y + hs, Pos.Z - hs);
	Vector3f* G = new Vector3f(Pos.X + hs, Pos.Y - hs, Pos.Z - hs);
	Vector3f* H = new Vector3f(Pos.X - hs, Pos.Y - hs, Pos.Z - hs);

	// Create list of vertices to populate private property _vertexBuffer
	Vector3f* vertexBuffer[8] = { A, B, C, D, E, F, G, H };

	// Create list of indices to populate private property _facesIndexBuffer
	int* facesIndexBuffer = new int[36]{
		0, 1, 2,
		0, 3, 2,
		1, 2, 5,
		2, 6, 5,
		6, 7, 5,
		5, 4, 7,
		7, 4, 3,
		3, 4, 0,
		0, 1, 4,
		1, 5, 4,
		3, 2, 7,
		2, 6, 7
	};

	// Create list of indices to populate private property _linesIndexBuffer
	int* linesIndexBuffer = new int[24]{
		0, 1,
		0, 3,
		2, 3,
		2, 1,
		2, 6,
		1, 5,
		5, 6,
		7, 4,
		4, 5,
		7, 6,
		3, 7,
		0, 4
	};

	// Populate private properties with arrays

	for (int i = 0; i < 8; i++)
	{
		Vector3f* vert = vertexBuffer[i];
		_vertexBuffer[i] = vert;
	}

	for (int i = 0; i < 36; i++)
	{
		int index = facesIndexBuffer[i];
		_facesIndexBuffer[i] = index;
	}

	for (int i = 0; i < 24; i++)
	{
		int index = linesIndexBuffer[i];
		_linesIndexBuffer[i] = index;
	}
}