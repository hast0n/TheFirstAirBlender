#pragma once
#include "Vector3f.h"


class Camera
{
	Vector3f* _position; // eye at x, y, z
	Vector3f* _reference; // eye looking at x, y, z
	Vector3f* _rotation; // eye pitch (up vector)
	
	float _fov;
	float _ar;

	float _zNear;
	float _zFar;

public:
	Camera();

	~Camera();

	void Rotate(const Vector3f& vect);

	void RotateTo(const Vector3f& vect);
	
	void Translate(const Vector3f& vect);

	void TranslateTo(const Vector3f& vect);

	void LookAt(const Vector3f& vect);
	
	void SetFOV(float fov);

	void SetAspectRatio(float ar);

	void SetZPlane(float zNear, float zFar);

	void ResetPosition();

	void ResetRotation();

	void GL_Init();
};