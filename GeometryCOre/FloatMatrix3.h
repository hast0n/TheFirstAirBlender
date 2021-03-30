#pragma once
#include <ostream>

class FloatMatrix3
{
	float _buffer[9] {0};

	float get2x2Determinant(int i, int j) const;
public:
	void setValue(int row, int col, float value);

	float getValue (int row, int col) const;

	float getDeterminant() const;

};

std::ostream& operator<<(std::ostream& out, FloatMatrix3 m);
