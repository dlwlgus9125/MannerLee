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

struct Line
{
	Vector point;
	Vector dir;
	float length;

	Line(Vector startPos, Vector endPos)
	{
		point = startPos;
		dir = (endPos - startPos).Normalize();
		length = (endPos - startPos).Magnitude();
	}

	Vector StartPoint() { return point; }
	Vector EndPoint() { return point + dir * length; }
	float Slope() { return (EndPoint().y - StartPoint().y) / (EndPoint().x - StartPoint().x); }
};

// 원
struct Circle
{
	Vector center;
	float radius;

	Circle(){ }
	Circle(Vector center, float radius)
	{
		this->center = center;
		this->radius = radius;
	}
};

// 사각형
struct Box
{
	Vector leftTop;
	Vector width, height;

	Box() {}
	Box(Vector center, Vector size)
	{
		leftTop = center - size * 0.5f;
		width = Vector::Right() * size.x;
		height = Vector::Down() * size.y;
	}

	Vector Center() { return LeftTop() + width * 0.5f + height * 0.5f; }
	Vector LeftTop() { return leftTop; }
	Vector LeftBottom() { return LeftTop() + height; }
	Vector RightTop() { return leftTop + width; }
	Vector RightBottom() { return LeftTop() + width + height; }
	Vector Size() { return Vector(width.Magnitude(), height.Magnitude()); }
};

// 삼각형
struct Triangle
{
	Vector p0, p1, p2;

	Triangle(Vector point0, Vector point1, Vector point2)
	{
		p0 = point0;
		p1 = point1;
		p2 = point2;
	}
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

	float Distance(Vector from, Vector to) { return (to - from).Magnitude(); }
	float SqrDistance(Vector from, Vector to) { return (to - from).SqrMagnitude(); }
	Vector ToDirection(float angle) { return Vector(Cos(angle), -Sin(angle)); }

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

	float ToAngle(Vector dir)
	{
		float angle = CosAngle(Vector::Right(), dir);
		if (SinAngle(Vector::Right(), dir) < 0) angle = 360 - angle;
		return angle;
	}

	float MoveForward(float from, float to, float delta)
	{
		float t = delta / abs(from - to);
		t = Clamp(t, 0.0f, 1.0f);
		return from + (to - from) * t;
	}

	Vector MoveForward(Vector from, Vector to, float delta)
	{
		float t = delta / (to - from).Magnitude();
		t = Clamp(t, 0.0f, 1.0f);
		return from * (1.0f - t) + to * t;
	}

	// 점에서 선까지 가장 가까운 점 반환
	Vector ClosestPoint(Vector point, Line line)
	{
		Vector vToPoint = point - line.StartPoint();
		float length = Dot(vToPoint, line.dir);
		length = Clamp(length, 0.0f, line.length);
		return line.StartPoint() + line.dir * length;
	}

	// 1차 함수 그래프
	float LinearGraph(Vector point, float slope, float x)
	{
		return slope * (x - point.x) + point.y;
	}

	// 2차 함수 그래프
	float QuadricGraph(Vector point, Vector vertex, float x)
	{
		float a = (point.y - vertex.y) / pow(point.x - vertex.x, 2);
		return a * pow(x - vertex.x, 2) + vertex.y;
	}

	// Sin 함수 그래프
	Vector SinGraph(float width, float height, float angle)
	{
		float x = width * (angle / 180.0f);
		float y = Sin(angle) * -height;
		return Vector(x, y);
	}

	// Cos 함수 그래프
	Vector CosGraph(float width, float height, float angle)
	{
		float x = width * (angle / 180.0f);
		float y = Cos(angle) * -height;
		return Vector(x, y);
	}

	// 점과 선 충돌
	bool IsCollided(Vector point, Line line)
	{
		float y = LinearGraph(line.point, line.Slope(), point.x);
		if (abs(point.y - y) < 0.01)
		{
			// 방향 체크
			return Dot(point - line.StartPoint(), point - line.EndPoint()) < 0;
		}
		return false;
	}

	// 점과 원 충돌
	bool IsCollided(Vector point, Circle circle)
	{
		float sqrDistance = SqrDistance(point, circle.center);
		return sqrDistance <= circle.radius * circle.radius;
	}

	// 점과 박스 충돌
	bool IsCollided(Vector point, Box box)
	{
		if (abs(point.x - box.Center().x) > box.Size().x * 0.5f) return false;
		if (abs(point.y - box.Center().y) > box.Size().y * 0.5f) return false;
		return true;
	}

	// 점과 삼각형 충돌
	bool IsCollided(Vector point, Triangle tri)
	{
		bool dir0 = CrossZ(tri.p1 - tri.p0, point - tri.p1) > 0;
		bool dir1 = CrossZ(tri.p2 - tri.p1, point - tri.p2) > 0;
		bool dir2 = CrossZ(tri.p0 - tri.p2, point - tri.p0) > 0;
		return dir0 == dir1 && dir0 == dir2;
	}

	// 원과 선 충돌
	bool IsCollided(Circle circle, Line line)
	{
		Vector point = ClosestPoint(circle.center, line);
		return SqrDistance(point, circle.center) <= circle.radius * circle.radius;
	}

	// 원과 원 충돌
	bool IsCollided(Circle a, Circle b)
	{
		float totalRadius = a.radius + b.radius;
		return SqrDistance(a.center, b.center) <= totalRadius * totalRadius;
	}

	// 원과 박스 충돌
	bool IsCollided(Circle circle, Box box)
	{
		if (IsCollided(circle.center, box)) return true;
		if (IsCollided(circle, Line(box.LeftTop(), box.RightTop()))) return true;
		if (IsCollided(circle, Line(box.LeftTop(), box.LeftBottom()))) return true;
		if (IsCollided(circle, Line(box.RightBottom(), box.RightTop()))) return true;
		if (IsCollided(circle, Line(box.RightBottom(), box.LeftBottom()))) return true;
		return false;
	}

	// 원과 삼각형 충돌
	bool IsCollided(Circle circle, Triangle triangle)
	{
		if (IsCollided(circle.center, triangle)) return true;
		if (IsCollided(circle, Line(triangle.p0, triangle.p1))) return true;
		if (IsCollided(circle, Line(triangle.p1, triangle.p2))) return true;
		if (IsCollided(circle, Line(triangle.p2, triangle.p0))) return true;
		return false;
	}
};