#include "Camera.h"
#include "windows.h"
#include "gl/GLU.h"

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

void Camera::SetPosition(const Vector3f& vect)
{
	_position = vect;
}

void Camera::Translate(const Vector3f& vect)
{
	_position += vect;
}

void Camera::SetTarget(const Vector3f& vect)
{
	_target = vect;
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

Vector3f Camera::getPosition() const
{
	return Vector3f(_position.X, _position.Y, _position.Z);
}
