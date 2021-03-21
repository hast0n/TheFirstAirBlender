#include "RayTracer.h"

#include <iostream>
#include <string>
#include "PNGExporter.h"

RayTracer::RayTracer(Scene scene, unsigned pixelWidth, unsigned pixelHeight)
{
	_scene = scene;
	_width = pixelWidth;
	_height = pixelHeight;

	_buffer = new unsigned char[pixelHeight * pixelWidth * 4];
}

void RayTracer::Render()
{
	this->compute_camera_to_world_matrix();
	
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			unsigned char R = 0;
			unsigned char G = 0;
			unsigned char B = 0;
			unsigned char A = 255;

			// TODO: 1. Get screen pixel position in world
			Vector3f pixel_pos = to_world_space(x, y);

			// TODO: 2. Cast ray from camera origin through pixel position

			// TODO: 3. Determine collision with objects form the scene (cascade)

			// TODO: 4. Get properties from encountered object and process final pixel color
						
			_buffer[4 * _width * y + 4 * x + 0] = R;
		    _buffer[4 * _width * y + 4 * x + 1] = G;
		    _buffer[4 * _width * y + 4 * x + 2] = B;
		    _buffer[4 * _width * y + 4 * x + 3] = A;
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


	const Vector3f rightAxis = _scene.Camera->getRightAxis();
	const Vector3f upAxis = _scene.Camera->getUpAxis();
	const Vector3f forwardAxis = _scene.Camera->getForwardAxis();
	const Vector3f cameraPos = _scene.Camera->getPosition();
	
	// Rotation sub-matrix
	_world_to_camera_matrix.setValue(0, 0, rightAxis.X);
	_world_to_camera_matrix.setValue(0, 1, rightAxis.Y);
	_world_to_camera_matrix.setValue(0, 2, rightAxis.Z);
	_world_to_camera_matrix.setValue(1, 0, upAxis.X);
	_world_to_camera_matrix.setValue(1, 1, upAxis.Y);
	_world_to_camera_matrix.setValue(1, 2, upAxis.Z);
	_world_to_camera_matrix.setValue(2, 0, forwardAxis.X);
	_world_to_camera_matrix.setValue(2, 1, forwardAxis.Y);
	_world_to_camera_matrix.setValue(2, 2, forwardAxis.Z);

	// position vector
	_world_to_camera_matrix.setValue(0, 3, - cameraPos.X);
	_world_to_camera_matrix.setValue(1, 3, - cameraPos.Y);
	_world_to_camera_matrix.setValue(2, 3, - cameraPos.Z);

	// homogeneous part
	_world_to_camera_matrix.setValue(3, 3, 0);

	// invert matrix
	_camera_to_world_matrix = _world_to_camera_matrix.getInverse();

}

Vector3f RayTracer::to_world_space(unsigned x, unsigned y)
{
	// X, Y, Z coordinates into camera space
	float zNear = _scene.Camera->getZNear();
	float fov = _scene.Camera->getFOV();
	float ar = _scene.Camera->getAspectRatio();
	
	float raster_space_width = 2 * zNear * std::sin(fov/2);
	float raster_space_height = raster_space_width / ar;

	float x_unit = raster_space_width / this->_width;
	float y_unit = raster_space_height / this->_height;

	float newX = - (raster_space_width / 2) + (x_unit * x);
	float newY = (raster_space_height / 2) - (y_unit * y);

	std::cout << Vector3f(newX, newY, - zNear) << std::endl;
	//return _camera_to_world_matrix * Vector3f(newX, newY, - zNear);
	return Vector3f(newX, newY, - zNear);
}

void RayTracer::RenderAndSave(std::string file_path)
{
	this->Render();
	
	PNGExporter exporter = PNGExporter(_buffer, 10, 5);
	exporter.Export(file_path);
}