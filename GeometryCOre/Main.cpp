#include <windows.h>  // For MS Windows
#include <glut.h>
#include <iostream>
#include "Cube.h"
#include "Sphere.h"
#include "Scene.h"
#include "PNGExporter.h"
#include "RayTracer.h"

//https://stackoverflow.com/a/686373
#define randFloat() (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))
#define randFloatFromTo(LO, HI) (LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO))))

static unsigned int glWidth = 1000;
static unsigned int glHeight = 1000;


static unsigned int rtWidth  = 1000;
static unsigned int rtHeight = rtWidth; //square;
static unsigned int ctr = 0;

static const float newXunit = static_cast<float>(rtWidth) / static_cast<float>(glWidth);
static const float newYunit = static_cast<float>(rtHeight) / static_cast<float>(glHeight);

static Scene* scene = new Scene();
static RayTracer rt = RayTracer(scene, rtWidth, rtHeight);

void add_axis_cubes_to_scene()
{
	Cube* cube1 = new Cube(Vector3f(0.0f, 0.0f, -1.0f), .1); // front rouge
	Cube* cube2 = new Cube(Vector3f(1.0f, 0.0f, 0.0f), .1); // right vert
	Cube* cube3 = new Cube(Vector3f(0.0f, 0.0f, 1.0f), .1); // back bleu
	Cube* cube4 = new Cube(Vector3f(-1.0f, 0.0f, 0.0f), .1); // left jaune
	Cube* cube5 = new Cube(Vector3f(0.0f, 1.0f, 0.0f), .1); // top cyan
	Cube* cube6 = new Cube(Vector3f(0.0f, -1.0f, 0.0f), .1); // bottom violet

	cube1->SetColor(RGBAColor(1, 0, 0)); // rouge
	cube2->SetColor(RGBAColor(0, 1, 0)); // vert
	cube3->SetColor(RGBAColor(0, 0, 1)); // bleu
	cube4->SetColor(RGBAColor(1, 1, 0)); // jaune
	cube5->SetColor(RGBAColor(0, 1, 1)); // cyan
	cube6->SetColor(RGBAColor(1, 0, 1)); // violet
	
	scene->AddObject(cube1);
	scene->AddObject(cube2);
	scene->AddObject(cube3);
	scene->AddObject(cube4);
	scene->AddObject(cube5);
	scene->AddObject(cube6);
}

void add_random_spheres_to_scene()
{
	//Sphere* sphere1 = new Sphere(Vector3f(0.2, 0, -1), 0.2f);
	//sphere1->SetColor(Vector3f(0.0, 1.0, 0.0));
	//scene->Add(sphere1);

	//Sphere* sphere2 = new Sphere(Vector3f(-0.2, 0, -1), 0.2f);
	//sphere2->SetColor(Vector3f(1.0, 1.0, 1.0));
	//scene->Add(sphere2);

	float posMin = -8;
	float posMax = 8;
	
	float sizeMin = 1;
	float sizeMax = 5;
	
	for (int i = 0; i < 20; ++i)
	{
		Sphere* sphere = new Sphere(
			Vector3f(
				randFloatFromTo(posMin, posMax),
				randFloatFromTo(posMin, posMax),
				randFloatFromTo(posMin, posMax)
			), 
			randFloatFromTo(sizeMin, sizeMax));
		sphere->SetMaterial(Materials::MirrorLike); 
		sphere->SetColor(RGBAColor(0.9, .9, .9));
		//sphere->SetColor(RGBAColor(randFloat(), randFloat(), randFloat()));
		scene->AddObject(sphere);
	}
}

void add_random_cubes_to_scene()
{
	//Sphere* sphere1 = new Sphere(Vector3f(0.2, 0, -1), 0.2f);
	//sphere1->SetColor(Vector3f(0.0, 1.0, 0.0));
	//scene->Add(sphere1);

	//Sphere* sphere2 = new Sphere(Vector3f(-0.2, 0, -1), 0.2f);
	//sphere2->SetColor(Vector3f(1.0, 1.0, 1.0));
	//scene->Add(sphere2);

	float posMin = -8;
	float posMax = 8;
	
	float sizeMin = 5;
	float sizeMax = 5;
	
	for (int i = 0; i < 2; ++i)
	{
		Cube* cube = new Cube(
			Vector3f(
				randFloatFromTo(posMin, posMax),
				randFloatFromTo(posMin, posMax),
				randFloatFromTo(posMin, posMax)
			), 
			randFloatFromTo(sizeMin, sizeMax));
		cube->SetColor(RGBAColor(randFloat(), randFloat(), randFloat()));
		scene->AddObject(cube);
	}
}

void set_rt_test_scene()
{
	Light* light1 = new Light(Vector3f(0, 10, 0), RGBAColor(1, 1, 1));
	scene->AddLight(light1);	
	
	//Sphere* sphere1 = new Sphere(Vector3f(-1.f, 0.5f, -1.f), .8f);
	//Sphere* sphere2 = new Sphere(Vector3f(1.f, 0.5f, -1.f), .8f);
	Sphere* sphere1 = new Sphere(Vector3f(.0f, .0f, -1.f), .5f);
	Sphere* sphere2 = new Sphere(Vector3f(.0f, .0f, -2.f), .5f);
	
	sphere1->SetMaterial(Materials::MirrorLike);
	sphere2->SetMaterial(Materials::Plastic);

	sphere1->SetColor(RGBAColor(0.92, .8, .2));
	sphere2->SetColor(RGBAColor(1., 1., 0));
		
	scene->AddObject(sphere1);
	scene->AddObject(sphere2);
}

void initScene()
{
	//scene->BackgroundColor = RGBAColor{0.26f, 0.26f, 0.26f, 1.0f};
	scene->BackgroundColor = RGBAColor{1.f, 1.f, 1.f, 1.f};
	scene->AmbientLighting = RGBAColor();
	//scene->AmbientLighting = RGBAColor{.2f, .2f, .2f, 1.f};
	//scene->AmbientLighting = RGBAColor{1.f, 0.f, 0.f, 1.f};
	scene->Camera->SetFOV(60.0f);
	scene->Camera->SetZPlanes(0.1f, 50.0f);
	//scene->Camera->SetPosition(Vector3f(0.0f, 1.5f, 5.0f));
	//scene->Camera->SetPosition(Vector3f(.0f, .0f, .0f));
	scene->Camera->Rotate(0, 0, 0);

	//add_axis_cubes_to_scene();
	//add_random_spheres_to_scene();
	//add_random_cubes_to_scene();

	set_rt_test_scene();
	
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

GraphicObject* pick(int x, int y)
{
	rt.initTransformMatrix();

	const Vector3f pixel_pos = rt.getRasterToWorldSpaceCoordinates(x * newXunit, y * newYunit);
	const auto cameraPos = rt.getCameraToWorldMatrix().leftMult(Vector3f(0, 0, 0));

	const Vector3f dir = (pixel_pos - cameraPos).normalize();

	auto ray = Ray(cameraPos, dir);
	GraphicObject* nearest = new Sphere();
	
	rt.cast(ray, &nearest, 1 ,false);
	
	return nearest;
}

void mouse(int button, int state, int x, int y)
{
	//std::cout << "[MOUSE] Button: " << button << ", State: " << state << ", X: " << x << ", Y: " << y << std::endl;

	GraphicObject* obj = nullptr;
	
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_UP)
		{
			obj = pick(x, y);
			if (obj != nullptr) std::cout << "[PICKING] GraphicObject ID: " << obj->GetID() << std::endl;
		}
	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	default:
		break;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->GL_Draw();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	//std::cout << "[KEYBOARD] Key: " << key << ", X: " << x << ", Y: " << y << std::endl;
	
	ctr = ++ctr % 2;	
	auto t = Vector3f();
	auto r = Vector3f();

	float rotate_unit = 5.0f;
	float translate_unit = .5f;
	float zFar_unit = 2.0f;
	float fov_unit = 5.0f;

	auto nb = scene->getGraphicObjectNumber();
	auto zFar = scene->Camera->getZFar();
	auto zNear = scene->Camera->getZNear();
	auto fov = scene->Camera->getFOV();
	
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
	case '9':
		r.Z = rotate_unit;
		break;
	case '7':
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
	case 'j':
		std::cout << "[RAYTRACING] started rendering (max_depth = 0) and exporting to png..." << std::endl;
		rt.RenderAndSave(0, "./test.png");
		std::cout << "[RAYTRACING] done!" << std::endl;
		break;
	case 'k':
		std::cout << "[RAYTRACING] started rendering (max_depth = 1) and exporting to png..." << std::endl;
		rt.RenderAndSave(1, "./test.png");
		std::cout << "[RAYTRACING] done!" << std::endl;
		break;
	case 'l':
		std::cout << "[RAYTRACING] started rendering (max_depth = 2) and exporting to png..." << std::endl;
		rt.RenderAndSave(2, "./test.png");
		std::cout << "[RAYTRACING] done!" << std::endl;
		break;
	case 't':
		std::cout << "[RAYTRACING] shuffling scene..." << std::endl;
		//Delete rt generated pixel cubes
		for (int i = 0; i < nb; i++)
		{
			scene->Remove(i);
		}
		
		add_axis_cubes_to_scene();
		add_random_spheres_to_scene();
		
		std::cout << "[RAYTRACING] started rendering..." << std::endl;
		rt.Render(1);
		std::cout << "[RAYTRACING] done!" << std::endl;
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
	case '+':
		scene->Camera->SetZPlanes(zNear, zFar + zFar_unit);
		scene->Camera->GL_LoadPerspective();
		std::cout << "[CAMERA] set zFar plane to " << zFar + zFar_unit << std::endl;
		break;
	case '-':
		scene->Camera->SetZPlanes(zNear, zFar - zFar_unit);
		scene->Camera->GL_LoadPerspective();
		std::cout << "[CAMERA] set zFar plane to " << zFar - zFar_unit << std::endl;
		break;
	case '*':
		scene->Camera->SetFOV(fov + fov_unit);
		scene->Camera->GL_LoadPerspective();
		std::cout << "[CAMERA] set FOV to " << fov + fov_unit << std::endl;
		break;
	case '/':
		scene->Camera->SetFOV(fov - fov_unit);
		scene->Camera->GL_LoadPerspective();
		std::cout << "[CAMERA] set FOV to " << fov - fov_unit << std::endl;
		break;
	//case '&':
	//	std::cout << "[CAMERA] current state: " << scene->Camera->getState() << std::endl;
	//	break;
	case '<':
		std::cout << "[SCENE] reset scene!" << std::endl;
		for (int i = 0; i < nb; i++)
		{
			scene->Remove(i);
		}
		break;
	case 'w':
		std::cout << "[SCENE] generate cubes!" << std::endl;
		add_random_cubes_to_scene();
		break;
	case 'x':
		std::cout << "[SCENE] generate spheres!" << std::endl;
		add_random_spheres_to_scene();
		break;
	}

	// Apply transform on Camera
	scene->Camera->Rotate(r.X, r.Y, r.Z);
	scene->Camera->Translate(-t); // translating the world, relative to camera
	
	glutPostRedisplay();
}

void TestRed()
{
	unsigned int width = 100;
	unsigned int height = 50;
	
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
	rt.Render(5);
}

void glTest(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(glWidth, glHeight);
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
	auto clrC = scene->BackgroundColor * scene->AmbientLighting;
	glClearColor(clrC.r, clrC.g, clrC.b, clrC.a);
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