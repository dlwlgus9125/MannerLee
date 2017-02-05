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

struct Box
{
	Vector pos;
	Vector size;
	Vector anchor;

	Box() {}
	Box(Vector pos, Vector size, Vector anchor = Vector(0.5f, 0.5f))
	{
		this->pos = pos;
		this->size = size;
		this->anchor = anchor;
	}

	Vector LeftTop() { return pos - size * anchor; }
	Vector RightBottom() { return LeftTop() + size; }
};

class Math : public Singleton<Math>
{
	const float PI = 3.141592f;
	const float ANGLE_TO_RADIAN = 0.0174533f;
	const float RADIAN_TO_ANGLE = 57.2958f;

public:

	template <typename T>
	T Clamp(T num, T min, T max)
	{
		if (num < min) num = min;
		if (num > max) num = max;
		return num;
	}

	float Cos(float angle) { return cosf(angle * ANGLE_TO_RADIAN); }
	float Sin(float angle) { return sinf(angle * ANGLE_TO_RADIAN); }
	float Tan(float angle) { return tanf(angle * ANGLE_TO_RADIAN); }
	float Dot(Vector a, Vector b) { return (a.x * b.x) + (a.y * b.y); }
	float CrossZ(Vector a, Vector b) { return (a.x * -b.y - -a.y * b.x); }

	float SinAngle(Vector from, Vector to)
	{
		float value = CrossZ(from, to) / (from.Magnitude() * to.Magnitude());
		return asinf(value) * RADIAN_TO_ANGLE;
	}

	float CosAngle(Vector from, Vector to)
	{
		float value = Dot(from, to) / (from.Magnitude() * to.Magnitude());
		return acosf(value) * RADIAN_TO_ANGLE;
	}

	float Angle(Vector from, Vector to)
	{
		float angle = CosAngle(from, to);
		if (SinAngle(from, to) < 0) angle = 360 - angle;
		return angle;
	}

	float Distance(Vector from, Vector to) { return (to - from).Magnitude(); }
	float SqrDistance(Vector from, Vector to) { return (to - from).SqrMagnitude(); }

	bool IsCollided(Vector point, Box box)
	{
		Vector leftTop = box.LeftTop();
		Vector rightBottom = box.RightBottom();

		return (point.x >= leftTop.x && point.x <= rightBottom.x)
			&& (point.y >= leftTop.y && point.y <= rightBottom.y);
	}

	bool IsCollided(Box a, Box b)
	{
		Vector leftTopA = a.LeftTop();
		Vector leftTopB = b.LeftTop();
		Vector rightBottomA = a.RightBottom();
		Vector rightBottomB = b.RightBottom();

		if (rightBottomA.x < leftTopB.x) return false;
		if (rightBottomA.y < leftTopB.y) return false;
		if (leftTopA.x > rightBottomB.x) return false;
		if (leftTopA.y > rightBottomB.y) return false;
		return true;
	}
};