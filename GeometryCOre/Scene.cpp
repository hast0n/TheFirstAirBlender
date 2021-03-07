#include "Header.h"

//Scene::~Scene()
//{
//	for (int i = 0; i < _nbGraphicObject; i++)
//	{
//		GraphicObject* obj = graphic_object_array[i];
//		delete obj;
//	}
//}

void Scene::Add(GraphicObject* obj)
{
	graphic_object_array[_nbGraphicObject] = obj;
	_nbGraphicObject++;
}

void Scene::Init()
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

void Scene::GLDraw()
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