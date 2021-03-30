#include <windows.h>  // For MS Windows
#include <glut.h>
#include <iostream>
#include "Cube.h"
#include "Sphere.h"
#include "Scene.h"
#include "PNGExporter.h"
#include "RayTracer.h"

static int width  = 512;
static int height = width; //square;
static int ctr = 0;

static Scene* scene = new Scene();
static RayTracer rt = RayTracer(scene, width, height);

static int* prevX = new int(NULL);
static int* prevY = new int(NULL);

void add_axis_cubes_to_scene()
{
	Cube* cube1 = new Cube(Vector3f(0.0f, 0.0f, -1.0f), .1); // front rouge
	Cube* cube2 = new Cube(Vector3f(1.0f, 0.0f, 0.0f), .1); // right vert
	Cube* cube3 = new Cube(Vector3f(0.0f, 0.0f, 1.0f), .1); // back bleu
	Cube* cube4 = new Cube(Vector3f(-1.0f, 0.0f, 0.0f), .1); // left jaune
	Cube* cube5 = new Cube(Vector3f(0.0f, 1.0f, 0.0f), .1); // top cyan
	Cube* cube6 = new Cube(Vector3f(0.0f, -1.0f, 0.0f), .1); // bottom violet

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
}

void add_spheres_to_scene()
{
	Sphere* sphere1 = new Sphere(Vector3f(0.2, 0, -1), 0.2f);
	sphere1->SetColor(Vector3f(0.0, 1.0, 0.0));
	scene->Add(sphere1);

	Sphere* sphere2 = new Sphere(Vector3f(-0.2, 0, -1), 0.2f);
	sphere2->SetColor(Vector3f(1.0, 0.0, 0.0));
	scene->Add(sphere2);
}

void initScene()
{
	scene->Camera->SetFOV(60.0f);
	scene->Camera->SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
	scene->Camera->Rotate(0, 0, 0);
	//scene->Camera->SetTarget(Vector3f(0.0f, 0.0f, -10.0f));

	add_axis_cubes_to_scene();
	add_spheres_to_scene();
	
	//Cube* cube1 = new Cube(Vector3f(-0.0f, 0.0f, -1.0f), 0.05);
	//cube1->SetColor(Vector3f(0.583f, 0.771f, 0.014f));
	//scene->Add(cube1);

	//Cube* cube2 = new Cube(Vector3f(0, 0, -3), 1);
	//cube2->SetColor(Vector3f(0.195f, 0.548f, 0.859f));
	//scene->Add(cube2);

	//Cube* cube3 = new Cube(Vector3f(-2, 0, -2), 1);
	//cube3->SetColor(Vector3f(0.053f, 0.959f, 0.120f));
	//scene->Add(cube3);

	//Plane* plane1 = new Plane(Vector3f(0.0f, -.5f, 0.0f), 3.0f);
	//plane1->SetColor(Vector3f(0.0f, 0.0f, 1.0f));
	//scene->Add(plane1);
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
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	std::cout << "[KEYBOARD] Key: " << key << ", X: " << x << ", Y: " << y << std::endl;
	
	ctr = ++ctr % 2;	
	auto t = Vector3f();
	auto r = Vector3f();

	float rotate_unit = 5.0f;
	float translate_unit = .1f;

	auto nb = scene->getGraphicObjectNumber();
	
	switch (key)
	{
	case 'z':
		t.Z = -translate_unit;
		break;
	case 'q':
		t.X = -translate_unit;
		break;
	case 's':
		t.Z = translate_unit;
		break;
	case 'd':
		t.X = translate_unit;
		break;
	case 'c':
		t.Y = -translate_unit;
		break;
	case ' ':
		t.Y = translate_unit;
		break;
	case '7':
		r.Z = rotate_unit;
		break;
	case '9':
		r.Z = -rotate_unit;
		break;
	case '8':
		r.X = -rotate_unit;
		break;
	case '6':
		r.Y = rotate_unit;
		break;
	case '2':
		r.X = rotate_unit;
		break;
	case '4':
		r.Y = -rotate_unit;
		break;
	case 'r':
		rt.RenderAndSave("./test.png");
		break;
	case 't':
		//Delete rt generated pixel cubes
		for (int i = 0; i < nb; i++)
		{
			scene->Remove(i);
		}
		
		add_axis_cubes_to_scene();
		add_spheres_to_scene();
		
		rt.Render();
		break;
	case 'p':
		scene->Camera->ResetPosition();
		break;
	case 'o':
		scene->Camera->ResetRotation();
		break;
	case 'i':
		scene->Camera->CleanState();
		break;
	}

	// Validate refresh (simulate flickering)
	//if (ctr) glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
	//else glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Apply transform on Camera
	scene->Camera->Rotate(r.X, r.Y, r.Z);
	scene->Camera->Translate(-t); // translating the world, relative to camera

	glMatrixMode(GL_MODELVIEW);
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	    glVertex3f(0, 0, 0);
	    glVertex3f(0, 0, -0.5);
	glEnd();
	
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
	rt.Render();
}

void glTest(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
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
	glShadeModel(GL_FLAT);

	scene->GL_Init();
	
	glutMainLoop();	
}

int main(int argc, char** argv)
{
	initScene();
	
	//rtTest();
	glTest(argc, argv);
	
	return 0;
}