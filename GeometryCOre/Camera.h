#pragma once
#include "Vector3f.h"

class Camera
{
	Vector3f _position; // eye at x, y, z
	Vector3f _target; // eye looking at x, y, z
	Vector3f _up_vector; // eye pitch (up vector)
	
	float _fov;
	float _aspect_ratio;

	float _zNear;
	float _zFar;

public:
	Camera();

	~Camera() = default;

	void Rotate(const Vector3f& vect);

	void RotateTo(const Vector3f& vect);
	
	void Translate(const Vector3f& vect);

	void SetPosition(const Vector3f& vect);

	void SetTarget(const Vector3f& vect);
	
	void SetFOV(float fov);

	void SetAspectRatio(float aspectRatio);

	void SetZPlanes(float zNear, float zFar);

	void ResetPosition();

	void ResetRotation();

	// TODO: namespaces 3DCore --|> OpenGL
	void GL_Init() const;

	Vector3f getPosition() const;
};
