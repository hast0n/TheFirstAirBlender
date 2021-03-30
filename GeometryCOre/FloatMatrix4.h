#pragma once
#include <ostream>
#include "Vector3f.h"

class FloatMatrix4
{
	float _buffer[16] {0};

	float getCofactor(int row, int col) const;


public:
	FloatMatrix4 getAdjoint() const;

	FloatMatrix4() = default;
	
	FloatMatrix4(const float buffer[16]);

	//void tempSet(float* buffer);

	

	FloatMatrix4 getTranspose() const;

	FloatMatrix4 getInverse() const;

	
	
	float getDeterminant() const;

	float getValue(int row, int col) const;
	
	void setValue(int row, int col, float value);


	void toFloatArray(float* buffer) const;
	

	Vector3f leftMult(const Vector3f& vect) const;

	Vector3f rightMult(const Vector3f& vect) const;
	
	
	FloatMatrix4 leftMult(const FloatMatrix4& mat) const;

	FloatMatrix4 rightMult(const FloatMatrix4& mat) const;

	FloatMatrix4 operator/(float value) const;

	void print() const;
};

std::ostream& operator<<(std::ostream& out, FloatMatrix4 m);