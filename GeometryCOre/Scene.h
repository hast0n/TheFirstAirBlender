#pragma once
#include "GraphicObject.h"

class Scene
{
	int _nbGraphicObject = 0;

public:
	GraphicObject* graphic_object_array[10];

	//~Scene() = delete; // Scene will only be deleted on program exit (for now)
	void Add(GraphicObject* obj);
	void Init();
	void GLDraw();
};