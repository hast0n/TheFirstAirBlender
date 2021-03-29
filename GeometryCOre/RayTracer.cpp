#include "RayTracer.h"
#include <iostream>
#include <string>

#include "Cube.h"
#include "PNGExporter.h"

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
	
	std::cout << "Camera position: " << _scene->Camera->getPosition() << std::endl;
	std::cout << "Camera target: " << _scene->Camera->getTarget() << std::endl;
	std::cout << "Vector3f(1, 1, 1) in camera space: " << _camera_to_world_matrix * Vector3f(1,1,1) << std::endl;

	//return;
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			unsigned char R = 0;
			unsigned char G = 0;
			unsigned char B = 0;
			unsigned char A = 255;

			// TODO: 1. Get screen pixel position in world
			Vector3f pixel_pos = raster_to_world_space(x, y);
			
			//std::cout << pixel_pos << std::endl;

			auto* a = new Cube(pixel_pos, 0.005);
			_scene->Add(a);

			// TODO: 2. Cast ray from camera origin through pixel position

			// TODO: 3. Determine collision with objects form the scene (cascade)

			// TODO: 4. Get properties from encountered object and process final pixel color
						
			//_buffer[4 * _width * y + 4 * x + 0] = R;
		 //   _buffer[4 * _width * y + 4 * x + 1] = G;
		 //   _buffer[4 * _width * y + 4 * x + 2] = B;
		 //   _buffer[4 * _width * y + 4 * x + 3] = A;
		}
	}
	
}

void RayTracer::compute_camera_to_world_matrix()
{
	// World to camera matrix be like :
	// 
	//	M00  M01  M02  tx
	//  M10  M11  M12  ty
	//  M20  M21  M22  tz
	//  0    0    0    1
	//  
	// M is the rotation transformation matrix
	// t is the position transformation vector
	// the 4th line is the homogeneous part (whatever)
	// https://stackoverflow.com/questions/695043/how-does-one-convert-world-coordinates-to-camera-coordinates

	// Pitch: X-axis
	// Yaw:   Y-axis
	// Roll:  Z-axis

	const Vector3f rightAxis = _scene->Camera->getRightAxis();
	const Vector3f upAxis    = _scene->Camera->getUpAxis();
	const Vector3f ZAxis     = _scene->Camera->getZAxis();
	const Vector3f cameraPos = _scene->Camera->getPosition();
	
	// Rotation sub-matrix
	_world_to_camera_matrix.setValue(0, 0, rightAxis.X);
	_world_to_camera_matrix.setValue(1, 0, rightAxis.Y);
	_world_to_camera_matrix.setValue(2, 0, rightAxis.Z);
	_world_to_camera_matrix.setValue(0, 1, upAxis.X);
	_world_to_camera_matrix.setValue(1, 1, upAxis.Y);
	_world_to_camera_matrix.setValue(2, 1, upAxis.Z);
	_world_to_camera_matrix.setValue(0, 2, ZAxis.X);
	_world_to_camera_matrix.setValue(1, 2, ZAxis.Y);
	_world_to_camera_matrix.setValue(2, 2, ZAxis.Z);
	
	//_world_to_camera_matrix.setValue(0, 0, rightAxis.X);
	//_world_to_camera_matrix.setValue(0, 1, rightAxis.Y);
	//_world_to_camera_matrix.setValue(0, 2, rightAxis.Z);
	//_world_to_camera_matrix.setValue(1, 0, upAxis.X);
	//_world_to_camera_matrix.setValue(1, 1, upAxis.Y);
	//_world_to_camera_matrix.setValue(1, 2, upAxis.Z);
	//_world_to_camera_matrix.setValue(2, 0, ZAxis.X);
	//_world_to_camera_matrix.setValue(2, 1, ZAxis.Y);
	//_world_to_camera_matrix.setValue(2, 2, ZAxis.Z);
	//
	//_world_to_camera_matrix.setValue(0, 0, rightAxis * Vector3f(1, 0, 0));
	//_world_to_camera_matrix.setValue(0, 1, rightAxis * Vector3f(0, 1, 0));
	//_world_to_camera_matrix.setValue(0, 2, rightAxis * Vector3f(0, 0, 1));
	//_world_to_camera_matrix.setValue(1, 0, upAxis * Vector3f(1, 0, 0));
	//_world_to_camera_matrix.setValue(1, 1, upAxis * Vector3f(0, 1, 0));
	//_world_to_camera_matrix.setValue(1, 2, upAxis * Vector3f(0, 0, 1));
	//_world_to_camera_matrix.setValue(2, 0, ZAxis * Vector3f(1, 0, 0));
	//_world_to_camera_matrix.setValue(2, 1, ZAxis * Vector3f(0, 1, 0));
	//_world_to_camera_matrix.setValue(2, 2, ZAxis * Vector3f(0, 0, 1));
	//
	//_world_to_camera_matrix.setValue(0, 0, rightAxis * Vector3f(1, 0, 0));
	//_world_to_camera_matrix.setValue(1, 0, rightAxis * Vector3f(0, 1, 0));
	//_world_to_camera_matrix.setValue(2, 0, rightAxis * Vector3f(0, 0, 1));
	//_world_to_camera_matrix.setValue(0, 1, upAxis * Vector3f(1, 0, 0));
	//_world_to_camera_matrix.setValue(1, 1, upAxis * Vector3f(0, 1, 0));
	//_world_to_camera_matrix.setValue(2, 1, upAxis * Vector3f(0, 0, 1));
	//_world_to_camera_matrix.setValue(0, 2, ZAxis * Vector3f(1, 0, 0));
	//_world_to_camera_matrix.setValue(1, 2, ZAxis * Vector3f(0, 1, 0));
	//_world_to_camera_matrix.setValue(2, 2, ZAxis * Vector3f(0, 0, 1));
			
	// position vector
	_world_to_camera_matrix.setValue(0, 3, - cameraPos.X);
	_world_to_camera_matrix.setValue(1, 3, - cameraPos.Y);
	_world_to_camera_matrix.setValue(2, 3, - cameraPos.Z);

	// homogeneous part
	_world_to_camera_matrix.setValue(3, 3, 1);

	// invert matrix
	_camera_to_world_matrix = _world_to_camera_matrix.getInverse();

	std::cout << "wtc:" << _world_to_camera_matrix << std::endl;
	std::cout << "ctw:" << _camera_to_world_matrix << std::endl;
}

Vector3f RayTracer::raster_to_world_space(unsigned x, unsigned y)
{
	float zNear = _scene->Camera->getZNear();
	float fov = _scene->Camera->getFOV();
	float ar = _scene->Camera->getAspectRatio();
	
	float raster_space_width = 2 * zNear * std::sin(fov / 2 * M_PI / 180);
	float raster_space_height = raster_space_width / ar;

	float x_unit = raster_space_width / this->_width;
	float y_unit = raster_space_height / this->_height;

	float newX = - (raster_space_width / 2) + (x_unit * x) + x_unit / 2;
	float newY = (raster_space_height / 2) - (y_unit * y) - y_unit / 2;

	return _camera_to_world_matrix * Vector3f(newX, newY, - zNear);
}

void RayTracer::RenderAndSave(std::string file_path)
{
	this->Render();
	
	PNGExporter exporter = PNGExporter(_buffer, 10, 5);
	exporter.Export(file_path);
}