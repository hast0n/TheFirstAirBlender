#include "Camera.h"
#include "windows.h"
#include "gl/GLU.h"

void Camera::set_up_vector()
{
	Vector3f forw = getForwardAxis();
	
	_up_vector = Vector3f(
		- forw.X * forw.Y,
		forw.X * forw.X + forw.Z * forw.Z,
		- forw.Y * forw.Z
	);
}



Camera::Camera()
{
	_position.Z = 1;
	_up_vector.Y = 1;

	_fov = 60.0f;
	_aspect_ratio = 1.0f;

	_zNear = 0.1f;
	_zFar = 100.0f;
}




void Camera::RotateTo(const Vector3f& vect)
{
	_up_vector = vect;
}

void Camera::Rotate(const Vector3f& vect)
{
	_up_vector += vect;
}

void Camera::Translate(const Vector3f& vect)
{
	_position += vect;
}




void Camera::SetPosition(const Vector3f& vect)
{
	_position = vect;
	set_up_vector();
}

void Camera::SetTarget(const Vector3f& vect)
{
	_target = vect;
	set_up_vector();
}

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
	this->SetPosition(Vector3f(0.0f, 0.0f, 1.0f));
}

void Camera::ResetRotation()
{
	this->RotateTo(Vector3f(0.0f, 1.0f, 0.0f));
}

void Camera::GL_Init() const
{
	gluPerspective(_fov, _aspect_ratio, _zNear, _zFar);
	
	gluLookAt(
		_position.X,
		_position.Y,
		_position.Z,
		_target.X,
		_target.Y,
		_target.Z,
		_up_vector.X,
		_up_vector.Y,
		_up_vector.Z
	);
}




float Camera::getFOV() const {return _fov;}

float Camera::getAspectRatio() const {return _aspect_ratio;}

float Camera::getZNear() const {return _zNear;}

float Camera::getZFar() const {return _zFar;}

Vector3f Camera::getPosition() const {return _position;}

Vector3f Camera::getTarget() const {return _target;}

Vector3f Camera::getForwardAxis() const
{
	return - Vector3f(_position - _target).normalize();
}

Vector3f Camera::getRightAxis() const
{
	return Vector3f(getForwardAxis() ^ _up_vector).normalize();
}

Vector3f Camera::getUpAxis() const
{
	return _up_vector.normalize();
}
