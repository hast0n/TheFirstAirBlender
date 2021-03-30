#include "Camera.h"
#include <iostream>
#include "windows.h"
#include "gl/GLU.h"
#include "GLErrorHandler.h"

# define M_PI 3.14159265358979323846  /* pi */

//void Camera::set_up_vector()
//{
//	Vector3f forw = getSightAxis();
//	
//	_up_vector = Vector3f(
//		- forw.X * forw.Y,
//		forw.X * forw.X + forw.Z * forw.Z,
//		- forw.Y * forw.Z
//	);
//}

FloatMatrix4 Camera::get_roll_matrix(float angle) const
{
	float rad = angle * M_PI / 180;
	
	float roll_buffer[16] = {
		std::cos(rad), std::sin(rad), 0, 0,
		-std::sin(rad), std::cos(rad), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	return FloatMatrix4(roll_buffer);
}

FloatMatrix4 Camera::get_pitch_matrix(float angle) const
{
	float rad = angle * M_PI / 180;
	
	float pitch_buffer[16] = {
		1, 0, 0, 0,
		0, std::cos(rad), std::sin(rad), 0,
		0, -std::sin(rad), std::cos(rad), 0,
		0, 0, 0, 1
	};

	return FloatMatrix4(pitch_buffer);
}

FloatMatrix4 Camera::get_yaw_matrix(float angle) const
{
	float rad = angle * M_PI / 180;
	
	float yaw_buffer[16] = {
		std::cos(rad), 0, -std::sin(rad), 0,
		0, 1, 0, 0,
		std::sin(rad), 0, std::cos(rad), 0,
		0, 0, 0, 1
	};

	return FloatMatrix4(yaw_buffer);
}


Camera::Camera()
{
	_position = Vector3f(0, 0, 0);

	_fov = 60.0f;
	_aspect_ratio = 1.0f;

	_zNear = 0.1f;
	_zFar = 100.0f;

	_roll = 0;
	_pitch = 0;
	_yaw = 0;

	CleanState();
}


void Camera::Rotate(float pitch, float yaw, float roll)
{
	auto rotationMatrix = 
		get_roll_matrix(roll).rightMult(
			get_yaw_matrix(yaw).rightMult(
				get_pitch_matrix(pitch)
			)
		);

	_state = rotationMatrix.leftMult(_state);
}

void Camera::Translate(const Vector3f& vect)
{
	_state.setValue(3, 0, _state.getValue(3, 0) + vect.X);
	_state.setValue(3, 1, _state.getValue(3, 1) + vect.Y);
	_state.setValue(3, 2, _state.getValue(3, 2) + vect.Z);
}



void Camera::SetPosition(const Vector3f& vect)
{
	//_position = vect;
	//set_up_vector();
	_state.setValue(3, 0, vect.X);
	_state.setValue(3, 1, vect.Y);
	_state.setValue(3, 2, vect.Z);
}

//void Camera::SetTarget(const Vector3f& vect)
//{
//	_target = vect;
//	set_up_vector();
//}

void Camera::SetFOV(float fov)
{
	_fov = fov;
}

void Camera::SetAspectRatio(float aspectRatio)
{
	_aspect_ratio = aspectRatio;
}

void Camera::SetZPlanes(float zNear, float zFar)
{
	_zNear = zNear;
	_zFar = zFar;
}



void Camera::ResetPosition()
{
	this->SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
}

void Camera::ResetRotation()
{
	throw 0;//this->Rotate(Vector3f(0.0f, 1.0f, 0.0f));
}

void Camera::CleanState()
{
	float state_buffer[16] =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	_state = FloatMatrix4(state_buffer);
}

void Camera::GL_LoadState() const
{
	GLfloat* buffer = new GLfloat[16];

	std::cout << "Camera state: "; _state.print();
	
	_state.toFloatArray(buffer);
	
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glMultMatrixf(buffer);
	
	delete[] buffer;
	
	//
	//gluLookAt(
	//	_position.X,
	//	_position.Y,
	//	_position.Z,
	//	_target.X,
	//	_target.Y,
	//	_target.Z,
	//	_up_vector.X,
	//	_up_vector.Y,
	//	_up_vector.Z
	//);
}

void Camera::GL_LoadPerspective() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_fov, _aspect_ratio, _zNear, _zFar);
}



float Camera::getFOV() const {return _fov;}

float Camera::getAspectRatio() const {return _aspect_ratio;}

float Camera::getZNear() const {return _zNear;}

float Camera::getZFar() const {return _zFar;}

FloatMatrix4 Camera::getState() const {return _state;}

Vector3f Camera::getPosition() const
{
	return Vector3f(
		_state.getValue(3, 0),
		_state.getValue(3, 1),
		_state.getValue(3, 2)
	);
}

//Vector3f Camera::getTarget() const {return _target;}
//
//Vector3f Camera::getSightAxis() const
//{
//	return Vector3f(_target - _position).normalize();
//}
//
//Vector3f Camera::getRightAxis() const
//{
//	return Vector3f(getSightAxis() ^ _up_vector).normalize();
//}
//
//Vector3f Camera::getUpAxis() const
//{
//	return _up_vector.normalize();
//}
//
//Vector3f Camera::getZAxis() const
//{
//	return - getSightAxis();
//}