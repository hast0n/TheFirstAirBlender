#include <iostream>
#include "Vector3f.h"

Vector3f::Vector3f()
{
	X = NULL;
	Y = NULL;
	Z = NULL;
}

Vector3f::Vector3f(float x, float y, float z) :X(x), Y(y), Z(z) {}

Vector3f::Vector3f(const Vector3f& v)
{
	X = v.X;
	Y = v.Y;
	Z = v.Z;
}

Vector3f Vector3f::operator+(float f) const
{
	return Vector3f(X + f, Y + f, Z + f);
}

Vector3f Vector3f::operator+(const Vector3f& v1) const
{
	return Vector3f(
		v1.X + X,
		v1.Y + Y,
		v1.Z + Z
	);
}

void Vector3f::operator+=(const Vector3f& v2)
{
	X += v2.X;
	Y += v2.Y;
	Z += v2.Z;
}

Vector3f Vector3f::operator-() const
{
	return Vector3f(-X, -Y, -Z);
}

Vector3f Vector3f::operator-(float f) const
{
	return Vector3f(X - f, Y - f, Z - f);
}

Vector3f Vector3f::operator-(const Vector3f& v2) const
{
	return Vector3f(
		X - v2.X,
		Y - v2.Y,
		Z - v2.Z
	);
}

void Vector3f::operator-=(const Vector3f& v2)
{
	X -= v2.X;
	Y -= v2.Y;
	Z -= v2.Z;
}

float Vector3f::operator*(const Vector3f& v2) const // produit scalaire
{
	return X * v2.X + Y * v2.Y + Z * v2.Z;
}

Vector3f Vector3f::operator*(float scalar) const
{
	return Vector3f(
		scalar * X,
		scalar * Y,
		scalar * Z
	);
}

void Vector3f::operator*=(float scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
}

float Vector3f::operator/(const Vector3f& v2) const
{
	return X / v2.X + Y / v2.Y + Z / v2.Z;
}

Vector3f Vector3f::operator/(float scalar) const
{
		return Vector3f(
		scalar / X,
		scalar / Y,
		scalar / Z
	);
}

void Vector3f::operator/=(float scalar)
{
	X /= scalar;
	Y /= scalar;
	Z /= scalar;
}

bool Vector3f::operator==(const Vector3f& v2) const
{
	return
		X == v2.X &&
		Y == v2.Y &&
		Z == v2.Z;
}

//Vector3f& Vector3f::operator=(const Vector3f& v2)
//{
//	X = v2.X;
//	Y = v2.Y;
//	Z = v2.Z;
//	return *this;
//}

Vector3f Vector3f::operator^(const Vector3f& v2) const // Produit vectoriel (normale - wedge product)
{
	return Vector3f(
		Y * v2.Z - Z * v2.Y,
		Z * v2.X - X * v2.Z,
		X * v2.Y - Y * v2.X
	);
}

Vector3f Vector3f::normalize() const
{
	float length = this->length();
	return Vector3f(X / length, Y / length, Z / length);
}

float Vector3f::length() const
{
	return sqrt((X * X) + (Y * Y) + (Z * Z));
}

std::ostream& operator<<(std::ostream& out, Vector3f v)
{
	out << "Vector3f(" << v.X << ", " << v.Y << ", " << v.Z <<")";
	return out;
}
