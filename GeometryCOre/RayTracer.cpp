#include "RayTracer.h"
#include <iostream>
#include <string>

#include "Windows.h"
#include "gl/GLU.h"

#include "Cube.h"
#include "PNGExporter.h"
#include "Ray.h"

# define M_PI 3.14159265358979323846  /* pi */

RayTracer::RayTracer(Scene* scene, unsigned pixelWidth, unsigned pixelHeight)
{
	_scene = scene;
	_width = pixelWidth;
	_height = pixelHeight;

	_buffer = new unsigned char[pixelHeight * pixelWidth * 4];
}

void RayTracer::Render()
{
	this->compute_camera_to_world_matrix();
	//auto cameraPos4 = _world_to_camera_matrix.rightMult(_scene->Camera->getPosition());
	auto cameraPos = _camera_to_world_matrix.leftMult(Vector3f(0, 0, 0));

	//std::cout << "camera position : " << -cameraPos << std::endl;
	//std::cout << "camera position : " << -cameraPos1 << std::endl;
	//std::cout << "camera position 2 : " << -cameraPos2 << std::endl;
	//std::cout << "camera position : " << -cameraPos3 << std::endl;
	//std::cout << "camera position 4 : " << -cameraPos4 << std::endl;
	//std::cout << "camera position 5 : " << cameraPos5 << std::endl;
	//std::cout << "camera position : " << cameraPos6 << std::endl;
	//std::cout << "camera position : " << cameraPos7 << std::endl;
	//std::cout << "camera position : " << cameraPos8 << std::endl;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			Vector3f pixel_pos = raster_to_world_space(x, y);
			//std::cout << "pixel position : "<< pixel_pos << std::endl;

			//auto* a = new Cube(pixel_pos, 0.0005);
			//_scene->Add(a);
			
			auto ray = Ray(cameraPos, pixel_pos);
			//glMatrixMode(GL_MODELVIEW);
			//glColor3f(1, 0, 0);
			//glBegin(GL_LINES);
			//    glVertex3f(cameraPos.X, cameraPos.Y, cameraPos.Z);
			//    glVertex3f(
			//		ray.Direction.X * 100,
			//		ray.Direction.Y * 100,
			//		ray.Direction.Z * 100
			//	);
			//glEnd();
			
			float distMin = INFINITY;
			
			Vector3f color = _scene->BackgroundColor;
			Vector3f intersect;
			GraphicObject* nearest = nullptr;
			
			for (int i = 0; i < _scene->nbGraphicObject; ++i)
			{
				GraphicObject* obj = _scene->getGraphicObject(i);

				if (obj->Intersects(ray, &intersect))
				{
					const float dist = (intersect - ray.Origin).length();

					if (dist < distMin)
					{
						nearest = obj;
						distMin = dist;
					}
				}
			}

			if (nearest != nullptr)
			{
				color = nearest->getColor();
				//color = this->Illuminate(nearest->getColor(), intersect);
			}
									
			_buffer[4 * _width * y + 4 * x + 0] = static_cast<unsigned char>(color.X * 255);
		    _buffer[4 * _width * y + 4 * x + 1] = static_cast<unsigned char>(color.Y * 255);
		    _buffer[4 * _width * y + 4 * x + 2] = static_cast<unsigned char>(color.Z * 255);
		    _buffer[4 * _width * y + 4 * x + 3] = 255;
		}
	}
}

void RayTracer::compute_camera_to_world_matrix()
{
	_world_to_camera_matrix = _scene->Camera->getState();		
	_camera_to_world_matrix = _world_to_camera_matrix.getInverse();
}

Vector3f RayTracer::raster_to_world_space(unsigned x, unsigned y)
{
	float zNear = _scene->Camera->getZNear();
	float fov = _scene->Camera->getFOV(); // horizontal fov
	float ar = _scene->Camera->getAspectRatio();
	
	float raster_space_width = 2 * zNear * std::tan(fov / 2 * M_PI / 180);
	float raster_space_height = raster_space_width / ar;

	float x_unit = raster_space_width / this->_width;
	float y_unit = raster_space_height / this->_height;

	float newX = - (raster_space_width / 2) + (x_unit * x) + x_unit / 2;
	float newY = (raster_space_height / 2) - (y_unit * y) - y_unit / 2;

	return _camera_to_world_matrix.leftMult(Vector3f(newX, newY, - zNear));
}

void RayTracer::RenderAndSave(std::string file_path)
{
	this->Render();
	
	PNGExporter exporter = PNGExporter(_buffer, _width, _height);
	exporter.Export(file_path);
}