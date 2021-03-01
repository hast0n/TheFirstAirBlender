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
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
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
//
//class Sphere : public GraphicObject
//{
//public:
//};
//

// -----
class Cube : public GraphicObject
{
	bool _lines;
	bool _faces;

public:
	Vector3f Pos;
	float Size;

	Cube(const Vector3f& cubePosition, float cubeSize)
	{
		Pos = cubePosition;
		Size = cubeSize;

		_lines = true;
		_faces = true;

		SetVertexBuffers();

		Logger::Write("cube created at ", LogLevel::INFO);
	}

	~Cube() {}

	void Move(const Vector3f& vect3) override
	{

	}

	void Scale(float factor) override
	{

	}

	void RTRender() const override
	{

	}

	void SetGLRender(bool lines, bool faces) 
	{
		_lines = lines; _faces = faces;
	}

	void GLRender() const override
	{
		glColor3f(1.0, 1.0, 0.0);

		if (_faces) {
			glBegin(GL_TRIANGLES);


			for (int i = 0; i < 36; i++)
			{
				int index = _facesIndexBuffer[i];
				Vector3f vect = *_vertexBuffer[index];

				glVertex3f(vect.X, vect.Y, vect.Z);
			}

			glEnd();
		}

		glColor3f(1.0, 0.0, 0.0);
		if (_lines) {
			glBegin(GL_LINES);

			for (int i = 0; i < 24; i++)
			{
				int index = _linesIndexBuffer[i];
				Vector3f vect = *_vertexBuffer[index];

				glVertex3f(vect.X, vect.Y, vect.Z);
			}

			glEnd();
		}
	}

private:
	Vector3f* _vertexBuffer[8];
	int _facesIndexBuffer[36];
	int _linesIndexBuffer[24];

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
		// .^^^^^^^^^^^^^....................
		// Error: expression must a modifiable lvalue
				
		for (int i = 0; i < 36; i++) 
		{ 
			int index = facesIndexBuffer[i]; 
			_facesIndexBuffer[i] = index;
		}
		// .^^^^^^^^^^^^^^^^^...............
		// Error: expression must a modifiable lvalue
		
		for (int i = 0; i < 24; i++) 
		{ 
			int index = linesIndexBuffer[i]; 
			_linesIndexBuffer[i] = index;
		}
		// .^^^^^^^^^^^^^^^^^...............
		// Error: expression must a modifiable lvalue
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
		Add(cube1);

		Cube* cube2 = new Cube(Vector3f(0, 0, -3), 1);
		Add(cube2);

		Cube* cube3 = new Cube(Vector3f(-2, 0, -3), 1);
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

	void Draw()
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

void mouse(int button, int state, int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0, 0.1, 100); // equi glFrustum
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
	//glOrtho(1.1, 1.1, 0.1, 1.1, 1.1, 1.1);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 0.0);
	scene.Draw();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	// Initialiser la scène avec un cube, une sphere, un plan

	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);

	std::cout << glGetString(GL_VERSION) << std::endl; // 4.6.0 NVIDIA 456.87
	std::cout << "C++ version " << __cplusplus << std::endl; // 4.6.0 NVIDIA 456.87

	init();
	scene.Init();

	glutMainLoop();

	return 0;
}