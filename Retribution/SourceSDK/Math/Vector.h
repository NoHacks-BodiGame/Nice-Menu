#pragma once
#include <math.h>

typedef class Vector
{
public:
	float x, y, z;
	Vector();
	Vector(float X, float Y, float Z);
	Vector(float val);
	void Init(float ix, float iy, float iz);
	__forceinline float operator[](int i) const;
	__forceinline void Normalize();
	__forceinline float LengthSqr();
	__forceinline float Length();
	__forceinline float Dot(Vector vec);
	__forceinline void ClampAngles();
	__forceinline bool IsZero();
public:
	__forceinline operator bool() const;
	__forceinline bool operator!() const;
	__forceinline Vector operator-();
	__forceinline bool operator==(const Vector& v);
	__forceinline bool operator==(const Vector& v) const;
	__forceinline bool operator!=(const Vector& v);
	__forceinline bool operator!=(const Vector& v) const;
	__forceinline Vector& operator-=(const Vector &v);
	__forceinline Vector operator*=(const float n);
	__forceinline Vector operator-(const Vector& v) const;
	__forceinline Vector operator+(const Vector& v) const;
	__forceinline Vector operator*(const float n);
	__forceinline Vector operator/(const float n);
	__forceinline Vector operator/(const Vector& v);
} QAngle;

inline Vector::Vector()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

inline Vector::Vector(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

inline Vector::Vector(float val)
{
	x = val;
	y = val;
	z = val;
}

inline void Vector::Init(float ix, float iy, float iz)
{
	x = ix;
	y = iy;
	z = iz;
}

__forceinline float Vector::operator[](int i) const 
{ 
	if (i == 0) return x; 
	if (i == 1) return y;
	return z; 
};

__forceinline void Vector::Normalize()
{
	float length = LengthSqr();
	if (length)
	{
		x = x / length;
		y = y / length;
		z = z / length;
	}
	else
		x = y = 0.0f; z = 1.0f;
}

__forceinline float Vector::LengthSqr()
{
	return (x*x + y*y + z*z);
}

__forceinline float Vector::Length()
{
	return (float)sqrt(LengthSqr());
}

__forceinline float Vector::Dot(Vector vec)
{
	return x * vec.x + y * vec.y + z * vec.z;
}

__forceinline void Vector::ClampAngles()
{
	if (this->x < -89.0f)
		this->x = -89.0f;

	if (this->x >  89.0f)
		this->x = 89.0f;

	while (this->y < -180.0f)
		this->y += 360.0f;

	while (this->y >  180.0f)
		this->y -= 360.0f;

	this->z = 0.0f;
}

__forceinline bool Vector::IsZero()
{
	return (x < 0.01f && x > -0.01f && y < 0.01f && y > -0.01f);
}

__forceinline Vector::operator bool() const
{
	return (x != 0.f && y != 0.f && z != 0.f);
}

__forceinline bool Vector::operator!() const
{
	return (!x && !y && !z);
}

__forceinline Vector Vector::operator-()
{
	return Vector(-x, -y, -z);
}

__forceinline bool Vector::operator==(const Vector& v)
{
	return (x == v.x) && (y == v.y) && (z == v.z);
}

__forceinline bool Vector::operator==(const Vector& v) const
{
	return (x == v.x) && (y == v.y) && (z == v.z);
}

__forceinline bool Vector::operator!=(const Vector& v)
{
	return (x != v.x) || (y != v.y) || (z != v.z);
}

__forceinline bool Vector::operator!=(const Vector& v) const
{
	return (x != v.x) || (y != v.y) || (z != v.z);
}

__forceinline Vector& Vector::operator-=(const Vector &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z; 
	return *this;
}

__forceinline Vector Vector::operator*=(const float n)
{
	return Vector(x *= n, y *= n, z *= n);
}

__forceinline Vector Vector::operator-(const Vector& v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

__forceinline Vector Vector::operator+(const Vector& v)  const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

__forceinline Vector Vector::operator*(const float n)
{
	return Vector(x * n, y * n, z * n);
}

__forceinline Vector Vector::operator/(const float n)
{
	return Vector(x / n, y / n, z / n);
}

__forceinline Vector Vector::operator/(const Vector& v) 
{
	return Vector(x / v.x, y / v.y, z / v.z); 
}