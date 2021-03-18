#include "Scene.h"
#include <iostream>

Scene::~Scene()
{
	for (int i = 0; i < _nbGraphicObject; i++)
	{
		GraphicObject* obj = graphic_object_array[i];
		//delete obj;
		// TODO: Why deletion not working ?
	}
}

Scene::Scene()
{
	Camera = new ::Camera();
}

void Scene::Add(GraphicObject* obj)
{
	graphic_object_array[_nbGraphicObject] = obj;
	_nbGraphicObject++;
}

void Scene::Init()
{
	//
}

void Scene::GL_Draw()
{
	if (_camera_modified) this->Camera->GL_Init();
	
	for (int i = 0; i < 10; i++)
	{
		GraphicObject* obj = graphic_object_array[i];

		if (obj != NULL)
		{
			obj->GLRender();
		}
	}
}
