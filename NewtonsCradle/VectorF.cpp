#include "VectorF.h"
#include <cmath>

VectorF::VectorF() :
	x(0.0f), y(0.0f)
{
}

VectorF::VectorF(float x, float y) :
	x(x), y(y)
{
}

VectorF::VectorF(const VectorF & v) :
	x(v.x), y(v.y)
{
}

VectorF::VectorF(const sf::Vector2f & v) :
	x(v.x), y(v.y)
{
}

sf::Vector2f VectorF::toSfVec()
{
	return sf::Vector2f(x, y);
}

float VectorF::magnitude() const
{
	return std::sqrtf(magnitudeSquared());
}

float VectorF::magnitudeSquared() const
{
	return (pow(x, 2) + pow(y, 2));
}

void VectorF::normalize()
{
	float m = magnitude();
	if (m < 0.01) return; // Cannot divide by zero
	x = x / m;
	y = y / m;
}

VectorF VectorF::normalize(const VectorF & v)
{
	float m = v.magnitude();
	if (m < 0.01) return VectorF(); // Cannot divide by zero
	VectorF newVec = v;
	newVec.x /= m;
	newVec.y /= m;

	return newVec;
}

float VectorF::dotProduct(const VectorF & v)
{
	return (x * v.x + y* v.y);
}

float VectorF::dotProduct(const VectorF & v1, const VectorF & v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

float VectorF::angleBetweenVectors(const VectorF & v1, const VectorF & v2)
{
	float l1 = v1.magnitude(), l2 = v2.magnitude();
	return acosf(dotProduct(v1, v2) / (l1*l2));
}

VectorF VectorF::project(const VectorF & v)
{
	if (v == VectorF(0.0f, 0.0f))return VectorF(0.0f, 0.0f);
	VectorF newVec = v;
	newVec = newVec * (dotProduct(newVec) / newVec.magnitudeSquared());
	return newVec;
}

VectorF operator+(const VectorF &v1, const VectorF &v2)
{
	return VectorF(v1.x + v2.x, v1.y + v2.y);
}

VectorF& operator+=(VectorF &v1, const VectorF &v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

VectorF operator-(const VectorF &v1, const VectorF &v2)
{
	return VectorF(v1.x - v2.x, v1.y - v2.y);
}

VectorF& operator-=(VectorF &v1, const VectorF &v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}

VectorF operator*(const VectorF &v, const float &f)
{
	return VectorF(v.x * f, v.y * f);
}

VectorF& operator*=(VectorF &v, const float &f)
{
	v.x *= f;
	v.y *= f;
	return v;
}

VectorF operator/(const VectorF &v, const float &f)
{
	if (f == 0.0f) return VectorF();
	return VectorF(v.x / f, v.y / f);
}

VectorF& operator/=(VectorF &v, const float &f)
{
	if (f == 0.0f) return v;
	v.x /= f;
	v.y /= f;
	return v;
}

bool operator!=(const VectorF & v1, const VectorF & v2)
{
	return (v1.x != v2.x || v1.y != v2.y);
}

bool operator==(const VectorF & v1, const VectorF & v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}
