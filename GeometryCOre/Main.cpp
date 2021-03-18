#include <windows.h>  // For MS Windows
#include <glut.h>
#include <iostream>
#include "Cube.h"
#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include "PNGExporter.h"
#include "RayTracer.h"

Scene scene;
int* prevX = new int(NULL);
int* prevY = new int(NULL);

void initScene()
{
	Cube* cube1 = new Cube(Vector3f(0, 0, 0), 1);
	cube1->SetColor(Vector3f(0.583f, 0.771f, 0.014f));
	scene.Add(cube1);

	Cube* cube2 = new Cube(Vector3f(0, 0, -3), 1);
	cube2->SetColor(Vector3f(0.195f, 0.548f, 0.859f));
	scene.Add(cube2);

	Cube* cube3 = new Cube(Vector3f(-2, 0, -2), 1);
	cube3->SetColor(Vector3f(0.053f, 0.959f, 0.120f));
	scene.Add(cube3);

	Sphere* sphere1 = new Sphere(Vector3f(0, 0, 0), 0.6f);
	sphere1->SetColor(Vector3f(0.0, 1.0, 0.0));
	scene.Add(sphere1);
	
	Sphere* sphere2 = new Sphere(Vector3f(2, 0, -3), 1.0f);
	sphere2->SetColor(Vector3f(1.0f, 1.0f, 1.0f));
	scene.Add(sphere2);

	Plane* plane1 = new Plane(Vector3f(0.0f, -.5f, 0.0f), 3.0f);
	plane1->SetColor(Vector3f(0.0f, 0.0f, 1.0f));
	scene.Add(plane1);

	// Camera's default perspective is ok here
	scene.Camera->SetPosition(Vector3f(0.0f, 1.0f, 2.0f));
	scene.Camera->RotateTo(Vector3f(0.0f, 2.0f, -1.8f));	
	scene.Camera->SetTarget(Vector3f(0.0f, 0.0f, 0.0f));
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
	scene.GL_Draw();
	glFlush();
}

void TestRed()
{
	int width = 100;
	int height = 50;
	
	unsigned char* image = new unsigned char[width*height*4];

	for(unsigned y = 0; y < height; y++) {
		for(unsigned x = 0; x < width; x++) {
		    image[4 * width * y + 4 * x + 0] = 255;
		    image[4 * width * y + 4 * x + 1] = 0;
		    image[4 * width * y + 4 * x + 2] = 0;
		    image[4 * width * y + 4 * x + 3] = 255;
		}
	}

	
	PNGExporter exporter = PNGExporter(image, 10, 5);
	exporter.Export("test.png");
}

void rtTest()
{
	int width = 10;
	int height = 10;
	
	RayTracer rt = RayTracer(scene, width, height);
	// rt.Render();

	std::cout << scene.Camera->getForwardAxis() << std::endl;
	std::cout << scene.Camera->getUpAxis() << std::endl;
	std::cout << scene.Camera->getRightAxis() << std::endl;
	
}

void glTest(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	std::cout << glGetString(GL_VERSION) << std::endl; // 4.6.0 NVIDIA 456.87
	std::cout << "C++ version " << __cplusplus << std::endl;

	// Set basic color & shade model
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	glutMainLoop();	
}

int main(int argc, char** argv)
{
	initScene();
	
	// glTest(argc, argv);
	
	rtTest();
	
	return 0;
}