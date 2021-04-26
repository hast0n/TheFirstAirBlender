#include <windows.h>  // For MS Windows
#include <glut.h>
#include <iostream>
#include <sstream>
#include "Cube.h"
#include "Sphere.h"
#include "Scene.h"
#include "RayTracer.h"

//https://stackoverflow.com/a/686373
#define randFloat() (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))
#define randFloatFromTo(LO, HI) (LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO))))
#define randInt(LO, HI) (LO + (rand() % static_cast<int>(HI - LO + 1)))
#define degToRad(deg) (deg * 3.14159265358979323846 / 180)

static unsigned int rtWidth  = 1000;
static unsigned int rtHeight = 1000;
static unsigned int ctr = 0;

static unsigned int glWidth = 1000;
static unsigned int glHeight = 1000;

static const float newXunit = static_cast<float>(rtWidth) / static_cast<float>(glWidth);
static const float newYunit = static_cast<float>(rtHeight) / static_cast<float>(glHeight);

static Scene* scene = new Scene();
static RayTracer rt = RayTracer(scene, rtWidth, rtHeight);

Materials::Material mat_array[3] = {
	Materials::Plastic,
	Materials::MirrorLike,
	Materials::Default
};

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
	float posMin = -30;
	float posMax = 30;
	
	float sizeMin = 1;
	float sizeMax = 4;

	Materials::Material mat_array[3] = {
		Materials::Plastic,
		Materials::MirrorLike,
		Materials::Default
	};

	for (int i = 0; i < 50; ++i)
	{
		auto a = randInt(0, 2);
		Materials::Material mat = mat_array[a];
		Sphere* sphere = new Sphere(
			Vector3f(
				randFloatFromTo(posMin, posMax),
				randFloatFromTo(posMin, posMax),
				randFloatFromTo(posMin, posMax)
			), 
			randFloatFromTo(sizeMin, sizeMax));
		sphere->SetMaterial(mat); 
		sphere->SetColor(RGBAColor(randFloat(), randFloat(), randFloat()));
		scene->AddObject(sphere);
	}
}

void add_random_cubes_to_scene()
{
	float posMin = -30;
	float posMax = 30;
	
	float sizeMin = 1;
	float sizeMax = 5;
	
	for (int i = 0; i < 50; ++i)
	{
		auto a = randInt(0, 2);
		Materials::Material mat = mat_array[a];
		Cube* cube = new Cube(
			Vector3f(
				randFloatFromTo(posMin, posMax),
				randFloatFromTo(posMin, posMax),
				randFloatFromTo(posMin, posMax)
			), 
			randFloatFromTo(sizeMin, sizeMax));
		cube->SetMaterial(mat); 
		cube->SetColor(RGBAColor(randFloat(), randFloat(), randFloat()));
		scene->AddObject(cube);
	}
}

void render_frames_360_animation(const float dist, const float height)
{	
	const int fps = 24; // frame rate
	const int duration = 6; // secondes

	const float angle = 360;
	const int nbFrames = fps * duration;
	const float unit = static_cast<float>(angle) / static_cast<float>(nbFrames); // one rotation around scene
		
	std::string folderPath = "./animation/";
	std::cout << "[ANIMATION] Render started < " << duration << "s | " << fps << "fps >" <<  std::endl;

	std::ostringstream repeated;
	fill_n(std::ostream_iterator<std::string>(repeated), 30, std::string(" "));
	std::cout << "[ANIMATION] [" << repeated.str() << "] - 0%" << '\r';
	
	for (int i = 0; i < nbFrames; i++)
	{
		scene->Camera->Reset();
		scene->Camera->Rotate(0, - i * unit, 0);
		scene->Camera->Translate(Vector3f(0, height, dist));
		
		std::ostringstream filename;
		filename << "animationFrame_" << i << ".png";

		std::string filePath = folderPath + filename.str();

		rt.RenderAndSave(2, filePath);

		const float done = static_cast<float>(i) / nbFrames;
		const int hashtags = static_cast<int>(30 * done);

		repeated.str(""); repeated.clear();
		fill_n(std::ostream_iterator<std::string>(repeated), hashtags, std::string("#"));
		fill_n(std::ostream_iterator<std::string>(repeated), 30 - hashtags, std::string(" "));
		std::cout << "[ANIMATION] [" << repeated.str() << "] - " << static_cast<int>(done * 100) << "%  " << '\r';
	}

	std::cout << "[ANIMATION] Render complete. Files saved in " << folderPath << " folder." << std::endl;
}

// 1 light; 2 spheres
void set_rt_test_scene()
{
	Light* light1 = new Light(Vector3f(0, 10, 0), RGBAColor(1, 1, 1));
	scene->AddLight(light1);	
	
	//Sphere* sphere1 = new Sphere(Vector3f(-1.f, 0.5f, -1.f), .8f);
	//Sphere* sphere2 = new Sphere(Vector3f(1.f, 0.5f, -1.f), .8f);
	Sphere* sphere1 = new Sphere(Vector3f(.0f, .0f, -.55f), .5f);
	Sphere* sphere2 = new Sphere(Vector3f(.0f, .0f, .55f), .5f);
	
	sphere1->SetMaterial(Materials::MirrorLike);
	sphere2->SetMaterial(Materials::Plastic);

	sphere1->SetColor(RGBAColor(0.92, .8, .2));
	sphere2->SetColor(RGBAColor(0., 1., 1));
		
	scene->AddObject(sphere1);
	scene->AddObject(sphere2);

	scene->Camera->SetPosition(Vector3f(0, 0, 2));
	scene->Camera->Rotate(0, 0, 0);

	//render_frames_360_animation();
}

// 4 lights; 1 sphere
void set_rt_test_scene_2()
{
	Light* light1 = new Light(Vector3f(0, 10, 0), RGBAColor(1, 1, 1));
	scene->AddLight(light1);	
	Light* light2 = new Light(Vector3f(0, 10, 0), RGBAColor(1, 1, 1));
	scene->AddLight(light2);	
	Light* light3 = new Light(Vector3f(0, 10, 0), RGBAColor(1, 1, 1));
	scene->AddLight(light3);	
	Light* light4 = new Light(Vector3f(0, 10, 0), RGBAColor(1, 1, 1));
	scene->AddLight(light4);
	
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
	//scene->BackgroundColor = RGBAColor{1.f, 1.f, 1.f, 1.f};
	scene->BackgroundColor = RGBAColor{0.26f, 0.26f, 0.26f, 1.0f};
	scene->AmbientLighting = RGBAColor();
	scene->Camera->SetFOV(80.0f);
	scene->Camera->SetZPlanes(0.1f, 50.0f);
	scene->Camera->SetAspectRatio(static_cast<float>(rtWidth) / rtHeight);	

	Light* light1 = new Light(Vector3f(-5, 10, -5), RGBAColor(1, 1, 1));
	scene->AddLight(light1);
	Light* light2 = new Light(Vector3f(-5, 10, 5), RGBAColor(1, 1, 1));
	scene->AddLight(light2);	
	Light* light3 = new Light(Vector3f(5, 10, -5), RGBAColor(1, 1, 1));
	scene->AddLight(light3);	
	Light* light4 = new Light(Vector3f(5, 10, 5), RGBAColor(1, 1, 1));
	scene->AddLight(light4);
	
	//add_axis_cubes_to_scene();
	add_random_spheres_to_scene();
	add_random_cubes_to_scene();
	//set_rt_test_scene();

	render_frames_360_animation(30, 0);
}

GraphicObject* pick(int x, int y)
{
	rt.initTransformMatrix();

	const Vector3f pixel_pos = rt.getRasterToWorldSpaceCoordinates(x * newXunit, y * newYunit);
	const auto cameraPos = rt.getCameraToWorldMatrix().leftMult(Vector3f(0, 0, 0));

	const Vector3f dir = (pixel_pos - cameraPos).normalized();

	auto ray = Ray(cameraPos, dir);

	GraphicObject* nearest = nullptr;
	Vector3f normal, intersect;
	
	return rt.getNearest(ray, normal, intersect);
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
	float small_translate_unit = .1f;
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
	case 'Z':
		t.Z = -small_translate_unit;
		break;
	case 'Q':
		t.X = -small_translate_unit;
		break;
	case 'S':
		t.Z = small_translate_unit;
		break;
	case 'D':
		t.X = small_translate_unit;
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
		std::cout << "[RAYTRACING] Render started | No global illumination | max_depth = 0" << std::endl;
		rt.RenderAndSaveFlat(0, "./test_flat.png");
		std::cout << "[RAYTRACING] Done! Saved as 'test_flat.png'" << std::endl;
		break;
	case 'k':
		std::cout << "[RAYTRACING] Render started | max_depth = 0" << std::endl;
		rt.RenderAndSave(0, "./test_depth_0.png");
		std::cout << "[RAYTRACING] Done! Saved as 'test_depth_0.png'" << std::endl;
		break;
	case 'l':
		std::cout << "[RAYTRACING] Render started | max_depth = 1" << std::endl;
		rt.RenderAndSave(1, "./test_depth_1.png");
		std::cout << "[RAYTRACING] Done! Saved as 'test_depth_1.png'" << std::endl;
		break;
	case 'm':
		std::cout << "[RAYTRACING] Render started | max_depth = 2" << std::endl;
		rt.RenderAndSave(2, "./test_depth_2.png");
		std::cout << "[RAYTRACING] Done! Saved as 'test_depth_2.png'" << std::endl;
		break;
	case 'p':
		scene->Camera->ResetPosition();
		break;
	case 'o':
		scene->Camera->ResetRotation();
		break;
	case 'i':
		scene->Camera->Reset();
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
	scene->Camera->Translate(t); // translating the world, relative to camera
	
	glutPostRedisplay();
}

void glInit(int argc, char** argv)
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
	// init rand seed
	srand(time(NULL));
	
	initScene();
	glInit(argc, argv);
	
	return 0;
}