#include "FloatMatrix4.h"
#include "FloatMatrix3.h"

FloatMatrix4 FloatMatrix4::getTranspose() const
{
	auto transpose = FloatMatrix4();
	
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float value = getValue(i, j);
			transpose.setValue(j, i, value);
		}
	}

	return transpose;
}

FloatMatrix4 FloatMatrix4::getInverse() const
{
	float det = getDeterminant();
	if (!det) throw 0;
	
	return getAdjoint() / det;
}

float FloatMatrix4::getDeterminant() const
{
	float det = 0;
	
	for (int i = 0; i < 4; ++i)
	{
		det += getCofactor(i, 0);
	}

	return det;
}

FloatMatrix4 FloatMatrix4::getAdjoint() const
{
	auto adj = FloatMatrix4();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float cof = this->getCofactor(i, j);
			adj.setValue(i, j, cof);
		}
	}
		
	return adj.getTranspose();
}

//void FloatMatrix4::tempSet(float* buffer)
//{
//	for (int i = 0; i < 16; ++i)
//	{
//		float value = buffer[i];
//		_buffer[i] = value;
//	}
//}

float FloatMatrix4::getCofactor(int i, int j) const
{
	int sign = (i + j + 2) % 2 ? -1 : 1;

	auto subm = FloatMatrix3();

	int index = 0;
	
	for (int l = 0; l < 4; ++l)
	{
		if (l == i) continue;
		
		for (int c = 0; c < 4; ++c)
		{
			if (c == j) continue;

			subm.setValue((int)index/3, index % 3, this->getValue(l, c));

			index++;
		}
	}

	return sign * subm.getDeterminant();
}

float FloatMatrix4::getValue(int i, int j) const
{ 	
	return _buffer[i * 4 + j];
}

void FloatMatrix4::setValue(int i, int j, float value)
{
	_buffer[i * 4 + j] = value;
}

FloatMatrix4 FloatMatrix4::operator/(float value) const
{
	auto m =  FloatMatrix4();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; ++j)
		{
			float c = getValue(i, j);
			m.setValue(i, j, c / value);
		}
	}

	return m;
}

std::ostream& operator<<(std::ostream& out, FloatMatrix4 m)
{
	out << "4 by 4 float matrix :" << std::endl;

	for (int k = 0; k < 16; ++k)
	{
		int i = (int)(k / 4);
		int j = k % 4;

		if(!j) {out << "(";}

		out << m.getValue(i, j);
		
		if(j == 3) {out << ")" << std::endl;}
		else {out << ", ";}
	}

	return out;
}
