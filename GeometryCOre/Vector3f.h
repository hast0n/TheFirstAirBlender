#pragma once
#include <ostream>

struct Vector3f
{
	float X;
	float Y;
	float Z;

	float m[3];

	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& v);

	Vector3f operator+(float f) const;
	Vector3f operator+(const Vector3f& v1) const;
	void operator+=(const Vector3f& v2);

	Vector3f operator-() const;
	Vector3f operator-(float f) const;
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
	
	float length() const;
};

Vector3f operator/(int lhs, const Vector3f& rhs);

std::ostream& operator<<(std::ostream& out, Vector3f v);