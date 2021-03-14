#include "RayTracer.h"

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
			Vector3f pixel_pos = screen_space_to_world_space(x, y);

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
	float world_to_camera_matrix[16] {};
	
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
	
	
	// Rotation sub-matrix
	Vector3f camera_world_roll;
	Vector3f camera_world_pitch;
	Vector3f camera_world_yaw;
	
	world_to_camera_matrix[0]  = camera_world_roll.X;
	world_to_camera_matrix[1]  = camera_world_roll.Y;
	world_to_camera_matrix[2]  = camera_world_roll.Z;
	world_to_camera_matrix[4]  = camera_world_pitch.X;
	world_to_camera_matrix[5]  = camera_world_pitch.Y;
	world_to_camera_matrix[6]  = camera_world_pitch.Z;
	world_to_camera_matrix[8]  = camera_world_yaw.X;
	world_to_camera_matrix[9]  = camera_world_yaw.Y;
	world_to_camera_matrix[10] = camera_world_yaw.Z;

	// position vector
	Vector3f camera_world_pos = _scene.Camera->getPosition();
	
	world_to_camera_matrix[3]  = - camera_world_pos.X;
	world_to_camera_matrix[7]  = - camera_world_pos.Y;
	world_to_camera_matrix[11] = - camera_world_pos.Z;

	// homogeneous part
	// array initialization set values to 0.0f
	world_to_camera_matrix[15] = 0;

	// invert matrix
	// TODO: find a way to invert matrix

	// _camera_to_world_matrix = inv(world_to_camera_matrix);
}

Vector3f RayTracer::screen_space_to_world_space(unsigned x, unsigned y)
{
	// transform x, y, z coordinates using camera_to_world_matrix
	// z is camera position + zNear
	
	return Vector3f();
}

void RayTracer::RenderAndSave(std::string file_path)
{
	this->Render();
	
	PNGExporter exporter = PNGExporter(_buffer, 10, 5);
	exporter.Export(file_path);
}