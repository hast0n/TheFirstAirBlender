#pragma once
#include "Vector3f.h"
#include "FloatMatrix4.h"

class Camera
{
	Vector3f _position; // eye at x, y, z (world space)
	Vector3f _target; // eye looking at x, y, z (world space)
	Vector3f _up_vector; // up vector (world space)
	
	float _fov;
	float _aspect_ratio;

	float _zNear;
	float _zFar;

	// around Z-axis
	float _roll;
	
	// around X-axis
	float _pitch;
	
	// around Y-axis
	float _yaw;

	FloatMatrix4 _state;

	//void set_up_vector();

	FloatMatrix4 get_roll_matrix(float angle) const;
	FloatMatrix4 get_pitch_matrix(float angle) const;
	FloatMatrix4 get_yaw_matrix(float angle) const;

public:
	Camera();

	~Camera() = default;

	// Add pitch, yaw and roll (X, Y, Z - unit is °)
	void Rotate(float pitch, float yaw, float roll);

	void RotateY(float deg);
	
	void Translate(const Vector3f& vect);

	

	void SetPosition(const Vector3f& vect);

	//void SetTarget(const Vector3f& vect);
	
	void SetFOV(float fov);

	void SetAspectRatio(float aspectRatio);

	void SetZPlanes(float zNear, float zFar);



	void ResetPosition();

	void ResetRotation();

	void Reset();


	
	// TODO: namespaces 3DCore --|> OpenGL
	void GL_LoadState() const;

	void GL_LoadPerspective() const;


	
	float getFOV() const;
	
	float getAspectRatio() const;
	
	float getZNear() const;

	float getZFar() const;

	FloatMatrix4 getState() const;

	Vector3f getPosition() const;
	
	FloatMatrix4 getRotation() const;
	
	//Vector3f getTarget() const;
	//
	//Vector3f getSightAxis() const;
	//
	//Vector3f getRightAxis() const;

	//Vector3f getUpAxis() const;

	//Vector3f getZAxis() const;
};
