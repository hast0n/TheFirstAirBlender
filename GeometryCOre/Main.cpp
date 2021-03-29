#include <windows.h>  // For MS Windows
#include <glut.h>
#include <iostream>
#include "Cube.h"
#include "FloatMatrix3.h"
#include "FloatMatrix4.h"
#include "GLErrorHandler.h"
#include "Sphere.h"
#include "Plane.h"
#include "Scene.h"
#include "PNGExporter.h"
#include "RayTracer.h"

Scene* scene = new Scene();
int* prevX = new int(NULL);
int* prevY = new int(NULL);

void initScene()
{
	Cube* cube1 = new Cube(Vector3f(0.0f, 0.0f, -1.0f), .5); // front rouge
	Cube* cube2 = new Cube(Vector3f(1.0f, 0.0f, 0.0f), .5); // right vert
	Cube* cube3 = new Cube(Vector3f(0.0f, 0.0f, 1.0f), .5); // back bleu
	Cube* cube4 = new Cube(Vector3f(-1.0f, 0.0f, 0.0f), .5); // left jaune
	Cube* cube5 = new Cube(Vector3f(0.0f, 1.0f, 0.0f), .5); // top cyan
	Cube* cube6 = new Cube(Vector3f(0.0f, -1.0f, 0.0f), .5); // bottom violet

	cube1->SetColor(Vector3f(1, 0, 0)); // rouge
	cube2->SetColor(Vector3f(0, 1, 0)); // vert
	cube3->SetColor(Vector3f(0, 0, 1)); // bleu
	cube4->SetColor(Vector3f(1, 1, 0)); // jaune
	cube5->SetColor(Vector3f(0, 1, 1)); // cyan
	cube6->SetColor(Vector3f(1, 0, 1)); // violet
	
	scene->Add(cube1);
	scene->Add(cube2);
	scene->Add(cube3);
	scene->Add(cube4);
	scene->Add(cube5);
	scene->Add(cube6);
	
	//Cube* cube1 = new Cube(Vector3f(-0.0f, 0.0f, -1.0f), 0.05);
	//cube1->SetColor(Vector3f(0.583f, 0.771f, 0.014f));
	//scene->Add(cube1);

	//Cube* cube2 = new Cube(Vector3f(0, 0, -3), 1);
	//cube2->SetColor(Vector3f(0.195f, 0.548f, 0.859f));
	//scene->Add(cube2);

	//Cube* cube3 = new Cube(Vector3f(-2, 0, -2), 1);
	//cube3->SetColor(Vector3f(0.053f, 0.959f, 0.120f));
	//scene->Add(cube3);

	//Sphere* sphere1 = new Sphere(Vector3f(0, 0, 0), 0.6f);
	//sphere1->SetColor(Vector3f(0.0, 1.0, 0.0));
	//scene->Add(sphere1);

	//Sphere* sphere2 = new Sphere(Vector3f(2, 0, -3), 1.0f);
	//sphere2->SetColor(Vector3f(1.0f, 1.0f, 1.0f));
	//scene->Add(sphere2);

	//Plane* plane1 = new Plane(Vector3f(0.0f, -.5f, 0.0f), 3.0f);
	//plane1->SetColor(Vector3f(0.0f, 0.0f, 1.0f));
	//scene->Add(plane1);
	
	scene->Camera->SetFOV(60.0f);
	
	scene->Camera->SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
	//scene->Camera->Rotate(0, 0, 0);

	//scene->Camera->SetTarget(Vector3f(0.0f, 0.0f, -10.0f));
	
}

void mouse(int button, int state, int x, int y)
{
	std::cout << "[MOUSE] Button: " << button << ", State: " << state << ", X: " << x << ", Y: " << y << std::endl;
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
	scene->GL_Draw();
	glFlush();
}

static int ctr = 0;
void keyboard(unsigned char key, int x, int y)
{
	ctr = ++ctr % 2;	
	std::cout << "[KEYBOARD] Key: " << key << ", X: " << x << ", Y: " << y << std::endl;
	auto m = Vector3f();
	auto r = Vector3f();
	
	switch (key)
	{
	case 'z':
		m.Z = -0.1;
		break;
	case 'q':
		m.X = -0.1;
		break;
	case 's':
		m.Z = 0.1;
		break;
	case 'd':
		m.X = 0.1;
		break;
	case 'a':
		r.Y = -1;
		break;
	case 'e':
		r.Y = 1;
		break;
	case '8':
		r.X = -1;
		break;
	case '6':
		r.Z = 1;
		break;
	case '2':
		r.X = 1;
		break;
	case '4':
		r.Z = -1;
		break;
	case 'c':
		m.Y = -.1;
		break;
	case ' ':
		m.Y = .1;
		break;
	}

	if (ctr) glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
	else glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	scene->Camera->Rotate(r.X, r.Y, r.Z);
	scene->Camera->Translate(m);
	
	scene->Camera->GL_LoadState();

	//std::cout << "New position: " << scene->Camera->getPosition() << std::endl;
	//std::cout << "New target: " << scene->Camera->getTarget() << std::endl;
	//glFlush();
	glutPostRedisplay();
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
	//float a_buffer[16] = {
	//	5, 2, 6, 1,
	//	0, 6, 2, 0,
	//	3, 8, 1, 4,
	//	1, 8, 5, 6
	//};
	//
	//float b_buffer[16] = {
	//	7, 5, 8, 0,
	//	1, 8, 2, 6,
	//	9, 4, 3, 8,
	//	5, 3, 7, 9
	//};
	//
	//auto a = FloatMatrix4(a_buffer);
	//auto b = FloatMatrix4(b_buffer); //.getInverse();
	//auto c = a * b;
	//
	//std::cout << c << std::endl;
	
	int width  = 2;
	int height = width; //2;

	//RayTracer rt = RayTracer(scene, width, height);
	//rt.Render();
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
	glutKeyboardFunc(keyboard);

	std::cout << glGetString(GL_VERSION) << std::endl; // 4.6.0 NVIDIA 456.87
	std::cout << "C++ version " << __cplusplus << std::endl;

	// Set basic color & shade model
	auto clrC = scene->BackgroundColor;
	glClearColor(clrC.X, clrC.Y, clrC.Z, 0.0);
	GLCall(glShadeModel(GL_FLAT));
	
	glutMainLoop();	
}

int main(int argc, char** argv)
{
	initScene();
	
	glTest(argc, argv);
	rtTest();
	
	
	return 0;
}