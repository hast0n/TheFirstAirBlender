#pragma once
#include <ostream>

class FloatMatrix4
{
	float _buffer[16] {0};

	float getCofactor(int i, int j) const;


public:
	FloatMatrix4 getAdjoint() const;

	FloatMatrix4() = default;

	//void tempSet(float* buffer);

	

	FloatMatrix4 getTranspose() const;

	FloatMatrix4 getInverse() const;

	
	
	float getDeterminant() const;

	float getValue(int i, int j) const;
	
	void setValue(int i, int j, float value);



	FloatMatrix4 operator/(float value) const;
};

std::ostream& operator<<(std::ostream& out, FloatMatrix4 m);