#include <windows.h>  // For MS Windows
#include <glut.h>
#include <iostream>

// -----
enum class LogLevel { INFO = 0, WARNING = 1, FATAL = 2 };

class Logger
{
	//static LogLevel m_LogLevel;

	static std::string GetFlag(LogLevel logLevel)
	{
		std::string flag;

		switch (logLevel)
		{
		case LogLevel::INFO:
			flag = "[INFO] ";
			break;
		case LogLevel::WARNING:
			flag = "[WARNING] ";
			break;
		case LogLevel::FATAL:
			flag = "[FATAL] ";
			break;
		}

		return flag;
	}

	Logger() = delete;

public:

	//static void SetLogLevel(LogLevel newLogLevel)
	//{
	//	m_LogLevel = newLogLevel;
	//}

	static void Write(std::string message, LogLevel logLevel)
	{
		std::cout << GetFlag(logLevel) << message << std::endl;
	}
};

struct Vector3f {
	float X;
	float Y;
	float Z;

	Vector3f()
	{
		X = NULL;
		Y = NULL;
		Z = NULL;
	}
	Vector3f(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
	Vector3f(const Vector3f& v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
	}
	
	Vector3f operator+(const Vector3f& v1) const
	{
		return Vector3f(
			v1.X + X,
			v1.Y + Y,
			v1.Z + Z
		);
	}
	void operator+=(const Vector3f& v2)
	{
		X += v2.X;
		Y += v2.Y;
		Z += v2.Z;
	}

	Vector3f operator-() const
	{
		return Vector3f(-X, -Y, -Z);
	}
	Vector3f operator-(const Vector3f& v2) const
	{
		return Vector3f(
			X - v2.X,
			Y - v2.Y,
			Z - v2.Z
		);
	}
	void operator-=(const Vector3f& v2)
	{
		X -= v2.X;
		Y -= v2.Y;
		Z -= v2.Z;
	}
	
	float operator*(const Vector3f& v2) const // produit scalaire
	{
		return X * v2.X + Y * v2.Y + Z * v2.Z;
	}
	Vector3f operator*(float scalar) const
	{
		return Vector3f(
			scalar * X,
			scalar * Y,
			scalar * Z
		);
	}
	Vector3f operator*=(float scalar)
	{
		X *= scalar;
		Y *= scalar;
		Z *= scalar;
	}

	bool operator==(const Vector3f& v2) const
	{
		return
			X == v2.X &&
			Y == v2.Y &&
			Z == v2.Z;
	}
	void operator=(const Vector3f& v2)
	{
		X = v2.X;
		Y = v2.Y;
		Z = v2.Z;
	}
		
	Vector3f operator^(const Vector3f& v2) const // Produit vectoriel (normale)
	{
		return Vector3f(
			Y * v2.Z - Z * v2.Y,
			Z * v2.X - X * v2.Z,
			X * v2.Y - Y * v2.X
		);
	}
};

// -----
class GraphicObject
{
public:
	virtual void RTRender() const = 0;
	virtual void GLRender() const = 0;
	//virtual Vector3f* GetVertexBuffer() const = 0;
	virtual void SetColor(const Vector3f& color) = 0;
	virtual void Move(const Vector3f& vect3) = 0;
	virtual void Scale(float factor) = 0;
};

// -----
//class Frustum
//{
//public:
//};
//
//class Plane : public GraphicObject
//{
//public:
//};

class Sphere : public GraphicObject
{
public:
	Vector3f Pos;
	Vector3f Color;
	float Radius;

	~Sphere() {}
	Sphere(const Vector3f& center, float radius) 
	{
		Pos = center;
		Radius = radius;
	}

	void SetColor(const Vector3f& color) override
	{
		Color = color;
	}
	void Move(const Vector3f& vect3)
	{
		this->Pos += vect3;
	}
	void Scale(float factor) override
	{
		this->Radius *= factor;
	}

	void RTRender() const override 
	{

	}

	void GLRenderFill(const Vector3f& fillColor) const
	{
		glColor3f(fillColor.X, fillColor.Y, fillColor.Z);

		//glMatrixMode(GL_MODELVIEW);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		GLAddToDisplayList();
	}
	void GLRenderWireframe(const Vector3f& wireColor) const
	{
		glColor3f(wireColor.X, wireColor.Y, wireColor.Z);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		GLAddToDisplayList();
	}
	void GLRender() const override
	{
		if (this->Color == Vector3f(NULL, NULL, NULL))
			GLRenderFill(Vector3f(1.0, 0.0, 1.0));
		else GLRenderFill(this->Color);

		GLRenderWireframe(Vector3f(1.0, 0.0, 0.0));
	}

private:
	void GLAddToDisplayList() const
	{
		GLUquadric* quad = gluNewQuadric();

		glPushMatrix(); // save current position
			glTranslatef(Pos.X, Pos.Y, Pos.Z);
			gluSphere(quad, Radius, 100, 30);

		glPopMatrix(); // load previously saved position
	}
};

// -----
class Cube : public GraphicObject
{
public:
	Vector3f Pos;
	Vector3f Color;
	float Size;

	~Cube() {}
	Cube(const Vector3f& cubePosition, float cubeSize)
	{
		Pos = cubePosition;
		Size = cubeSize;

		SetVertexBuffers();
		LogInit();
	}

	void SetColor(const Vector3f& color) override
	{
		Color = color;
	}
	void Move(const Vector3f& vect3) override
	{
		this->Pos += vect3;
	}
	void Scale(const float factor) override
	{
		this->Size *= factor;
		SetVertexBuffers();
	}

	void RTRender() const override
	{

	}

	void GLRenderFaces(const Vector3f& faceColor) const
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
	void GLRenderWireframe(const Vector3f& wireColor) const
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
	void GLRender() const override
	{
		if (this->Color == Vector3f(NULL, NULL, NULL))
			GLRenderFaces(Vector3f(1.0, 0.0, 1.0));
		else GLRenderFaces(this->Color);

		GLRenderWireframe(Vector3f(1.0, 0.0, 0.0));
	}

private:
	Vector3f* _vertexBuffer[8];
	int _facesIndexBuffer[36];
	int _linesIndexBuffer[24];

	void LogInit() const
	{
		//char* a = Pos.X;
		//char* x = new char[, Pos.Y, Size]
		//std::format("cube created at [{}; {}] with size {}", );

		//Logger::Write(log_string, LogLevel::INFO);
		//delete x[];
	}

	void SetVertexBuffers() {

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
		int* facesIndexBuffer = new int[36] {
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
		int* linesIndexBuffer = new int[24] {
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
		
		for (int i = 0; i <  8; i++) 
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
};


// -----
class Scene
{
	int _nbGraphicObject = 0;

public:
	GraphicObject* graphic_object_array[10];
	//Frustum* viewing_frustum;

	~Scene()
	{
		for (int i = 0; i < _nbGraphicObject; i++)
		{
			GraphicObject* obj = graphic_object_array[i];
			delete obj;
		}
	}

	void Add(GraphicObject* obj) 
	{
		graphic_object_array[_nbGraphicObject] = obj;
		_nbGraphicObject++;
	}

	void Init()
	{
		Cube* cube1 = new Cube(Vector3f(0, 0, 0), 1);
		cube1->SetColor(Vector3f(0.583f, 0.771f, 0.014f));
		Add(cube1);

		Sphere* sphere1 = new Sphere(Vector3f(0, 0, 0), 0.6);
		sphere1->SetColor(Vector3f(0.0, 1.0, 0.0));
		Add(sphere1);

		Cube* cube2 = new Cube(Vector3f(0, 0, -3), 1);
		cube2->SetColor(Vector3f(0.195f, 0.548f, 0.859f));
		Add(cube2);

		Cube* cube3 = new Cube(Vector3f(-2, 0, -3), 1);
		cube3->SetColor(Vector3f(0.053f, 0.959f, 0.120f));
		Add(cube3);


		//Vector3f v1 = Vector3f(1, 1, 1);
		//Vector3f v2 = Vector3f(1, 1, 1);
		//Vector3f v3 = v1 + v2;
		//float scalarProduct1 = v1 * v2;
		//Vector3f wedgeProduct1 = v1 ^ v2;
		//Vector3f v4(1, 2, 3);
		//Vector3f v5(5, 6, 7);
		//float scalarProduct2 = v4 * v5;
		//Vector3f wedgeProduct2 = v4 ^ v5;
	}

	void GLDraw()
	{
		for (int i = 0; i < 10; i++)
		{
			GraphicObject* obj = graphic_object_array[i];
			
			if (obj != NULL)
			{
				obj->GLRender();
			}
		}
	}
};


Scene scene;

// -----
void init()
{
	// Set basic color & shade model
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	// set perspective
	//glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0, 1.0, 0.1, 100); // equi glFrustum
	//glMatrixMode(GL_MODELVIEW);
	gluLookAt(0.0, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, -1.8);

	// switch back to modelview matrix mode
	glMatrixMode(GL_MODELVIEW);
}

int* prevX = new int(NULL);
int* prevY = new int (NULL);

// GLUT dependent
void mouse(int button, int state, int x, int y)
{

	//if (button == GLUT_LEFT_BUTTON)
	//{
	//	switch (state)
	//	{
	//	case GLUT_DOWN:
	//		if (*prevX == NULL || *prevY == NULL)
	//		{
	//			*prevX = x;
	//			*prevY = y;
	//			break;
	//		}
	//		std::cout << "GLUT_DOWN at [" << x << "," << y << "] prevx: " << *prevX << ", prevY: " << *prevY << std::endl;

	//		*prevX = x;
	//		*prevY = y;
	//		glLoadIdentity();
	//		gluLookAt(x/1000, y/1000, 1.0, 0.0, 0.0, 0.0, 0.0, 2.0, -1.8);
	//		break;

	//	case GLUT_UP:
	//		*prevX = NULL;
	//		*prevY = NULL;
	//		break;
	//	}

	//}

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//gluPerspective(60.0, 1.0, 0.1, 100); // equi glFrustum
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glutPostRedisplay();
	//glOrtho(1.1, 1.1, 0.1, 1.1, 1.1, 1.1);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.GLDraw();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Initialiser la scène avec un cube, une sphere, un plan

	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	std::cout << glGetString(GL_VERSION) << std::endl; // 4.6.0 NVIDIA 456.87
	std::cout << "C++ version " << __cplusplus << std::endl;

	init();
	scene.Init();

	glutMainLoop();

	return 0;
}