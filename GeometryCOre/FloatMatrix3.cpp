#include "FloatMatrix3.h"

float FloatMatrix3::get2x2Determinant(int i, int j) const
{
	float subm[4] {0};
	int index = 0;
	
	for (int k = 0; k < 9; ++k)
	{
		int l =  (int)(k / 3);
		int c = k % 3;
		
		bool cross = l == i || c == j;

		if (!cross && index < 4)
		{
			subm[index++] = getValue(l, c);
		}
	}

	return subm[0] * subm[3] - subm[1] * subm[2];
}

void FloatMatrix3::setValue(int i, int j, float value) 
{
	_buffer[i * 3 + j] = value;
}

float FloatMatrix3::getValue(int i, int j) const
{
	return _buffer[i * 3 + j];
}

float FloatMatrix3::getDeterminant() const
{
	float det = 0;
	
	for (int k = 0; k < 3; ++k)
	{
		int sign = k % 2 ? -1 : 1;

		det += sign * getValue(0, k) * get2x2Determinant(0, k);
	}

	return det;
}

std::ostream& operator<<(std::ostream& out, FloatMatrix3 m)
{
	out << "3 by 3 float matrix :" << std::endl;

	for (int k = 0; k < 9; ++k)
	{
		int i = (int)(k / 3);
		int j = k % 3;

		if(!j) {out << "(";}

		out << m.getValue(i, j);
		
		if(j == 2) {out << ")" << std::endl;}
		else {out << ", ";}
	}

	return out;
}
