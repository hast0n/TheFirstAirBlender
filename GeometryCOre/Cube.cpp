#include "Header.h"

Cube::Cube(const Vector3f& cubePosition, float cubeSize)
{
	Pos = cubePosition;
	Size = cubeSize;

	SetVertexBuffers();
	LogInit();
}

void Cube::SetColor(const Vector3f& color)
{
	Color = color;
}

void Cube::Move(const Vector3f& vect3)
{
	this->Pos += vect3;
}

void Cube::Scale(const float factor)
{
	this->Size *= factor;
	SetVertexBuffers();
}

void Cube::RTRender() const
{

}

void Cube::GLRenderFaces(const Vector3f& faceColor) const
{
	glColor3f(faceColor.X, faceColor.Y, faceColor.Z);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < 36; i++)
	{
		int index = _facesIndexBuffer[i];
		Vector3f vect = *_vertexBuffer[index];

		glVertex3f(vect.X, vect.Y, vect.Z);
	}

	glEnd();
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
	if (this->Color == Vector3f(NULL, NULL, NULL))
		GLRenderFaces(Vector3f(1.0, 0.0, 1.0));
	else GLRenderFaces(this->Color);

	GLRenderWireframe(Vector3f(1.0, 0.0, 0.0));
}

void Cube::LogInit() const
{
	//char* a = Pos.X;
	//char* x = new char[, Pos.Y, Size]
	//std::format("cube created at [{}; {}] with size {}", );

	//Logger::Write(log_string, LogLevel::INFO);
	//delete x[];
}

void Cube::SetVertexBuffers() {

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
