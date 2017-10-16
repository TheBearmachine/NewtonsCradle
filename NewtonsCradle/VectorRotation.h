#pragma once
#include "VectorF.h"
#include <cmath>

constexpr double PI = 3.141592653589793238463;

class VectorRotation
{
public:
	VectorRotation() : real(1), fake(0) {}
	VectorRotation(float real, float imaginary) : real(real), fake(imaginary) {}
	VectorRotation(float radians) : real(cosf(radians)), fake(sinf(radians)) {}
	VectorRotation(VectorF v) : real(v.x), fake(v.y) {}
	VectorRotation(const VectorRotation &vr) : real(vr.real), fake(vr.fake) {}

	static VectorRotation inDegrees(float degrees)
	{
		return VectorRotation(degrees * PI / 180.f);
	}

	VectorRotation operator+(const VectorRotation &vr2)
	{
		return VectorRotation(real + vr2.real, fake + vr2.fake);
	}
	void operator+=(const VectorRotation &vr2)
	{
		real += vr2.real;
		fake += vr2.fake;
	}

	VectorRotation operator-() { return VectorRotation(-real, -fake); }
	void operator-=(const VectorRotation &vr2)
	{
		real -= vr2.real;
		fake -= fake;
	}

	VectorRotation operator*(const float &f)
	{
		return VectorRotation(real * f, fake * f);
	}
	VectorRotation operator*(const VectorRotation &vr2)
	{
		return VectorRotation(real * vr2.real - fake * vr2.fake,
							  real * vr2.fake + fake * vr2.real);
	}

	float length()
	{
		return sqrtf(real * real + fake * fake);
	}

	void normalize()
	{
		float l = length();
		if (l > 0.f)
		{
			real *= 1.0f / l;
			fake *= 1.0f / l;
		}
	}

	VectorF toVector() { return VectorF(real, fake); }

	float real;
	float fake;
};