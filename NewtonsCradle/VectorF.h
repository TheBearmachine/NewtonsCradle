#pragma once
#include <SFML/System/Vector2.hpp>

class VectorF
{
public:
	VectorF();
	VectorF(float x, float y);
	VectorF(const VectorF &v);
	VectorF(const sf::Vector2f &v);

	sf::Vector2f toSfVec();

	float magnitude() const;
	float magnitudeSquared() const;
	void normalize();
	static VectorF normalize(const VectorF &v);
	float dotProduct(const VectorF &v);
	static float dotProduct(const VectorF &v1, const VectorF &v2);

	static float angleBetweenVectors(const VectorF &v1, const VectorF &v2);

	VectorF project(const VectorF &v);


	float x, y;
};
VectorF operator+(const VectorF &v1, const VectorF &v2);
VectorF& operator+=(VectorF &v1, const VectorF &v2);

VectorF operator-(const VectorF &v1, const VectorF &v2);
VectorF& operator-=(VectorF &v1, const VectorF &v2);

VectorF operator*(const VectorF &v, const float &f);
VectorF& operator*=(VectorF &v, const float &f);

VectorF operator/(const VectorF &v, const float &f);
VectorF& operator/=(VectorF &v, const float &f);

bool operator!=(const VectorF &v1, const VectorF &v2);
bool operator==(const VectorF &v1, const VectorF &v2);
