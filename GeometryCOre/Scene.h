#pragma once
#include "Camera.h"
#include "GraphicObject.h"
#include "Light.h"

class Scene
{
	bool _camera_modified = true;
	
public:
	int nbGraphicObject = 0;
	int nbLights = 0;

	Camera* Camera;
	Light* lights_array[10]{};
	GraphicObject* graphic_object_array[1000000]{};

	RGBAColor BackgroundColor = RGBAColor{.0f, .0f, .0f, 1.f};
	RGBAColor AmbientLighting = RGBAColor{1.f, 1.f, 1.f, 1.f};

	Scene();
	~Scene();

	void AddObject(GraphicObject* obj);

	void AddLight(Light* obj);

	void Init();

	void GL_Draw();
	
	void GL_Init();

	//void Delete(GraphicObject* ptr);

	void Remove(int index);

	int getGraphicObjectNumber() const;
	
	int getLightNumber() const;
	
	GraphicObject* getGraphicObject(int i);
	
	Light* getLight(int i);
};
