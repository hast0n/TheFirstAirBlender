#pragma once
#include "Camera.h"
#include "GraphicObject.h"

class Scene
{
	int _nbGraphicObject = 0;
	bool _camera_modified = true;
	
public:
	Camera* Camera;
	
	GraphicObject* graphic_object_array[10]{};

	Vector3f BackgroundColor = Vector3f(0.26f, 0.26f, 0.26f);

	Scene();
	~Scene(); // Scene will only be deleted on program exit (for now)

	void Add(GraphicObject* obj);

	void Init();

	void GL_Draw();
};