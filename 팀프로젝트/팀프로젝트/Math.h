#pragma once
#include "Singleton.h"

#define MATH	Math::Instance()

struct Vector
{
	float x, y;

	Vector() { x = 0.0f; y = 0.0f; }
	Vector(float x, float y) { this->x = x; this->y = y; }
	Vector(POINT point) { x = point.x; y = point.y; }

	float Magnitude() { return sqrt(SqrMagnitude()); }
	float SqrMagnitude() { return pow(x, 2) + pow(y, 2); }
	Vector Normalize()
	{
		float mag = Magnitude();
		if (mag == 0) return Zero();
		return *this / mag;
	}

	Vector operator + (float num) { return Vector(x + num, y + num); }
	Vector operator - (float num) { return Vector(x - num, y - num); }
	Vector operator * (float num) { return Vector(x * num, y * num); }
	Vector operator / (float num) { return Vector(x / num, y / num); }
	Vector& operator += (float num) { x += num; y += num; return *this; }
	Vector& operator -= (float num) { x -= num; y -= num; return *this; }
	Vector& operator *= (float num) { x *= num; y *= num; return *this; }
	Vector& operator /= (float num) { x /= num; y /= num; return *this; }

	Vector operator + (Vector v) { return Vector(x + v.x, y + v.y); }
	Vector operator - (Vector v) { return Vector(x - v.x, y - v.y); }
	Vector operator * (Vector v) { return Vector(x * v.x, y * v.y); }
	Vector operator / (Vector v) { return Vector(x / v.x, y / v.y); }
	Vector& operator += (Vector v) { x += v.x; y += v.y; return *this; }
	Vector& operator -= (Vector v) { x -= v.x; y -= v.y; return *this; }
	Vector& operator *= (Vector v) { x *= v.x; y *= v.y; return *this; }
	Vector& operator /= (Vector v) { x /= v.x; y /= v.y; return *this; }

	bool operator == (Vector v) { return x == v.x && y == v.y; }
	bool operator != (Vector v) { return x != v.x || y != v.y; }

	static Vector Zero() { return Vector(0.0f, 0.0f); }
	static Vector One() { return Vector(1.0f, 1.0f); }
	static Vector Left() { return Vector(-1.0f, 0.0f); }
	static Vector Right() { return Vector(1.0f, 0.0f); }
	static Vector Up() { return Vector(0.0f, -1.0f); }
	static Vector Down() { return Vector(0.0f, 1.0f); }
};

class Math : public Singleton<Math>
{
public:

	template <typename T>
	T Clamp(T num, T min, T max)
	{
		if (num < min) num = min;
		if (num > max) num = max;
		return num;
	}

	float Distance(Vector from, Vector to) { return (to - from).Magnitude(); }
	float SqrDistance(Vector from, Vector to) { return (to - from).SqrMagnitude(); }
};