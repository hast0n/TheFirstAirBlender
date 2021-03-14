#pragma once
#include <string>

#include "Scene.h"

class RayTracer
{
	Scene _scene;

	unsigned char* _buffer;
	unsigned int _width;
	unsigned int _height;

	float _camera_to_world_matrix[16] {};

public:
	RayTracer(Scene scene, unsigned int pixelWidth, unsigned int pixelHeight);
	
	void Render();

	void RenderAndSave(std::string file_path);

private:

	void compute_camera_to_world_matrix();
	
	Vector3f screen_space_to_world_space(unsigned x, unsigned y);
};

