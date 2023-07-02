#include "vector2.h"
#include "math.h"



template<typename T>
inline Vector2<T>::Vector2(int _x, int _y)
{
	x = static_cast<T>(_x);
	y = static_cast<T>(_y);
}

template<typename T>
inline Vector2<T>::Vector2(f32 _x, f32 _y)
{
	x = static_cast<T>(_x);
	y = static_cast<T>(_y);
}



template<typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& v) const
{
	return Vector2<T>(x + v.x, y + v.y);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& v) const
{
	return Vector2<T>(x - v.x, y - v.y);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator*(const Vector2<T>& v) const
{
	return Vector2<T>(x * v.x, y * v.y);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator/(const Vector2<T>& v) const
{
	return Vector2<T>(x / v.x, y / v.y);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator*(int scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator/(int scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator*(float scalar) const
{
	return Vector2(static_cast<T>(x * scalar), static_cast<T>(y * scalar));
}

template<typename T>
inline Vector2<T> Vector2<T>::operator/(float scalar) const
{
	return Vector2(static_cast<T>(x / scalar), static_cast<T>(y / scalar));
}


template<typename T>
inline bool Vector2<T>::operator==(const Vector2& v) const
{
	return (x == v.x && y == v.y);
}



Vector2i& Vector2i::operator=(const Vector2i& other)
{
	if (this != &other) {
		x = other.x;
		y = other.y;
	}
	return *this;
}

Vector2f& Vector2f::operator=(const Vector2f& other)
{
	if (this != &other) {
		x = other.x;
		y = other.y;
	}
	return *this;
}

const Vector2f Vector2f::ZERO = Vector2f(0.0f, 0.0f);
const Vector2f Vector2f::UP = Vector2f(0.0f, 1.0f);
const Vector2f Vector2f::DOWN = Vector2f(0.0f, -1.0f);
const Vector2f Vector2f::LEFT = Vector2f(-1.0f, 0.0f);
const Vector2f Vector2f::RIGHT = Vector2f(1.0f, 0.0f);


const Vector2i Vector2i::ZERO = Vector2i(0, 0);
const Vector2i Vector2i::UP = Vector2i(0, 1);
const Vector2i Vector2i::DOWN = Vector2i(0, -1);
const Vector2i Vector2i::LEFT = Vector2i(-1, 0);
const Vector2i Vector2i::RIGHT = Vector2i(1, 0);
