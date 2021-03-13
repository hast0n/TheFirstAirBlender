#include "Camera.h"
#include "windows.h"
#include "gl/GLU.h"

Camera::Camera()
{
	_position = new Vector3f(0.0f, 0.0f, 1.0f);
	_reference = new Vector3f(0.0f, 0.0f, 0.0f);
	_rotation = new Vector3f(0.0f, 1.0f, 0.0f);

	_fov = 60.0f;
	_ar = 1.0f;

	_zNear = 0.1f;
	_zFar = 100.0f;
}

Camera::~Camera()
{
	delete _position;
	delete _rotation;
	delete _reference;
}

void Camera::RotateTo(const Vector3f& vect)
{
	delete _rotation;
	_rotation = new Vector3f(vect);
}

void Camera::Rotate(const Vector3f& vect)
{
	// TODO: Uhh... Is it ok ??
	
	Vector3f currentV = *_rotation;
	delete _rotation;
	_rotation = new Vector3f(vect + currentV);
}

void Camera::TranslateTo(const Vector3f& vect)
{
	delete _position;
	_position = new Vector3f(vect);
}

void Camera::Translate(const Vector3f& vect)
{
	// TODO: Uhh... Is it ok ?? (2)
	
	Vector3f currentV = *_position;
	delete _position;
	_position = new Vector3f(vect + currentV);
}

void Camera::LookAt(const Vector3f& vect)
{
	delete _reference;
	_reference = new Vector3f(vect);
}

void Camera::SetFOV(float fov)
{
	_fov = fov;
}

void Camera::SetAspectRatio(float ar)
{
	_ar = ar;
}

void Camera::SetZPlane(float zNear, float zFar)
{
	_zNear = zNear;
	_zFar = zFar;
}

void Camera::ResetPosition()
{
	this->TranslateTo(Vector3f(0.0f, 0.0f, 1.0f));
}

void Camera::ResetRotation()
{
	this->RotateTo(Vector3f(0.0f, 1.0f, 0.0f));
}

void Camera::GL_Init()
{
	gluPerspective(
		this->_fov,
		this->_ar,
		this->_zNear,
		this->_zFar
	);
	
	gluLookAt(
		this->_position->X,
		this->_position->Y,
		this->_position->Z,
		this->_reference->X,
		this->_reference->Y,
		this->_reference->Z,
		this->_rotation->X,
		this->_rotation->Y,
		this->_rotation->Z
	);
}
