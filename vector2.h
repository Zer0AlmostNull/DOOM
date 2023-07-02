#include "types.h"

#pragma once

template <typename T>
class Vector2 {
public:
	T x, y;

	Vector2() :x(0),y(0) {}
	Vector2(const Vector2& v) : x(v.x), y(v.y) {}

	Vector2(int, int);
	Vector2(f32, f32);
		
		
	Vector2 operator+(const Vector2&) const;
	Vector2 operator-(const Vector2&) const;
	Vector2 operator*(const Vector2& ) const;
	Vector2 operator/(const Vector2& ) const;
	Vector2 operator*(int) const;
	Vector2 operator/(int) const;
	Vector2 operator*(float) const;
	Vector2 operator/(float) const;


	bool operator==(const Vector2&) const;

};

class Vector2i : public Vector2<int> {
public:
	Vector2i() : Vector2<int>(0, 0) {}
	Vector2i(int x_, int y_) : Vector2<int>(x_, y_) {}
	Vector2i(const Vector2i& v) : Vector2<int>(v) {}

	Vector2i& operator=(const Vector2i&);

	static const Vector2i ZERO;
	static const Vector2i UP;
	static const Vector2i DOWN;
	static const Vector2i LEFT;
	static const Vector2i RIGHT;
};

class Vector2f : public Vector2<float> {
public:
	Vector2f() : Vector2<float>(0.0f, 0.0f) {}
	Vector2f(float _x, float _y) : Vector2<float>(_x, _y) {}
	Vector2f(const Vector2f& v) : Vector2<float>(v) {}

	Vector2f& operator=(const Vector2f&);

	static const Vector2f ZERO;
	static const Vector2f UP;
	static const Vector2f DOWN;
	static const Vector2f LEFT;
	static const Vector2f RIGHT;
};


typedef Vector2f  v2;
typedef Vector2i  v2_i;