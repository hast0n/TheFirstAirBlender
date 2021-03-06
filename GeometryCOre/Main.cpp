#include <windows.h>  // For MS Windows
#include <glut.h>
#include <iostream>
#include "Cube.h"
#include "Sphere.h"
#include "Scene.h"

Scene scene;
int* prevX = new int(NULL);
int* prevY = new int (NULL);

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

	Cube* cube1 = new Cube(Vector3f(0, 0, 0), 1);
	cube1->SetColor(Vector3f(0.583f, 0.771f, 0.014f));
	scene.Add(cube1);

	Cube* cube2 = new Cube(Vector3f(0, 0, -3), 1);
	cube2->SetColor(Vector3f(0.195f, 0.548f, 0.859f));
	scene.Add(cube2);

	Cube* cube3 = new Cube(Vector3f(-2, 0, -3), 1);
	cube3->SetColor(Vector3f(0.053f, 0.959f, 0.120f));
	scene.Add(cube3);

	Sphere* sphere1 = new Sphere(Vector3f(0, 0, 0), 0.6f);
	sphere1->SetColor(Vector3f(0.0, 1.0, 0.0));
	scene.Add(sphere1);
	
	Sphere* sphere2 = new Sphere(Vector3f(2, 0, -3), 1.0f);
	sphere2->SetColor(Vector3f(1.0f, 1.0f, 1.0f));
	scene.Add(sphere2);
}

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
	//glutPostRedisplay();
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

	//glEnable( GL_DEBUG_OUTPUT );
	//glDebugMessageCallback( MessageCallback, 0 );

	// Initialiser la sc�ne avec un cube, une sphere, un plan

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