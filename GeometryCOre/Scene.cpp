#include "Scene.h"
#include <iostream>

Scene::~Scene()
{
	for (int i = 0; i < nbGraphicObject; i++)
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

void Scene::AddObject(GraphicObject* obj)
{
	graphic_object_array[nbGraphicObject] = obj;
	nbGraphicObject++;
}

void Scene::AddLight(Light* obj)
{
	lights_array[nbLights] = obj;
	nbLights++;
}

int Scene::getLightNumber() const
{
	return nbLights;
}

Light* Scene::getLight(int i)
{
	return this->lights_array[i];
}

void Scene::Init()
{

}

void Scene::GL_Draw()
{
	this->Camera->GL_LoadState();
	
	for (int i = 0; i < nbGraphicObject; i++)
	{
		GraphicObject* obj = graphic_object_array[i];

		if (obj != nullptr)
		{
			obj->GLRender();
		}
	}
}

void Scene::GL_Init()
{
	this->Camera->GL_LoadPerspective();
	this->Camera->GL_LoadState();
}

void Scene::Remove(int index)
{
	GraphicObject* ptr = graphic_object_array[index];
	graphic_object_array[index] = nullptr;

	delete ptr;

	nbGraphicObject--;
}

int Scene::getGraphicObjectNumber() const
{
	return nbGraphicObject;
}

GraphicObject* Scene::getGraphicObject(int i)
{
	return this->graphic_object_array[i];
}
