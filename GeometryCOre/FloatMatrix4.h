#pragma once
#include <ostream>

#include "Vector3f.h"

class FloatMatrix4
{
	float _buffer[16] {0};

	float getCofactor(int i, int j) const;


public:
	FloatMatrix4 getAdjoint() const;

	FloatMatrix4() = default;
	
	FloatMatrix4(const float buffer[16]);

	//void tempSet(float* buffer);

	

	FloatMatrix4 getTranspose() const;

	FloatMatrix4 getInverse() const;

	
	
	float getDeterminant() const;

	float getValue(int i, int j) const;
	
	void setValue(int i, int j, float value);


	void toFloatArray(float* buffer) const;

	
	//FloatMatrix4 operator*(const FloatMatrix4 mat) const;

	Vector3f operator*(const Vector3f vect) const;

	FloatMatrix4 operator/(float value) const;
	
	FloatMatrix4 operator*(const FloatMatrix4 mat) const;
};

std::ostream& operator<<(std::ostream& out, FloatMatrix4 m);