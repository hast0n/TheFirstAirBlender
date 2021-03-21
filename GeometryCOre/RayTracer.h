#pragma once
#include <string>


#include "FloatMatrix4.h"
#include "Scene.h"

class RayTracer
{
	Scene _scene;

	unsigned char* _buffer;
	unsigned int _width;
	unsigned int _height;

	FloatMatrix4 _camera_to_world_matrix;
	FloatMatrix4 _world_to_camera_matrix;

public:
	RayTracer(Scene scene, unsigned int pixelWidth, unsigned int pixelHeight);
	
	void Render();

	void RenderAndSave(std::string file_path);

private:

	void compute_camera_to_world_matrix();
	
	Vector3f to_world_space(unsigned x, unsigned y);
};

