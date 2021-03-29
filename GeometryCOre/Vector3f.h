#pragma once
#include <ostream>

struct Vector3f
{
	float X;
	float Y;
	float Z;

	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& v);

	Vector3f operator+(const Vector3f& v1) const;
	void operator+=(const Vector3f& v2);

	Vector3f operator-() const;
	Vector3f operator-(const Vector3f& v2) const;
	void operator-=(const Vector3f& v2);

	float operator*(const Vector3f& v2) const;
	Vector3f operator*(float scalar) const;
	void operator*=(float scalar);
	
	float operator/(const Vector3f& v2) const;
	Vector3f operator/(float scalar) const;
	void operator/=(float scalar);

	bool operator==(const Vector3f& v2) const;
	Vector3f&  operator=( const Vector3f& v2)=default;
	
	Vector3f operator^(const Vector3f& v2) const;
	
	Vector3f normalize() const;
};

std::ostream& operator<<(std::ostream& out, Vector3f v);