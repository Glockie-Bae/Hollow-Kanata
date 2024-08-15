#pragma once
#include<cmath>

class Vector2D {
public:
	float x = 0;
	float y = 0;

public:
	Vector2D() {}
	~Vector2D() {}
	Vector2D(float x, float y)
		: x(x), y(y){}

	Vector2D operator+(const Vector2D& v) {
		return Vector2D(x + v.x, y + v.y);
	}

	void operator+= (const Vector2D& v) {
		x += v.x;
		y += v.y;
	}

	Vector2D operator+(const Vector2D& v) const {
		return Vector2D(x + v.x, y + v.y);
	}

	void operator+= (const Vector2D& v) {
		x += v.x;
		y += v.y;
	}

	Vector2D operator-(const Vector2D& v) const {
		return Vector2D(x - v.x, y - v.y);
	}

	void operator-= (const Vector2D& v) {
		x -= v.x;
		y -= v.y;
	}

	Vector2D operator*(float val) const {
		return Vector2D(x * val, y * val);
	}

	float operator*(const Vector2D& v) const {
		return x * v.x + y * v.y;
	}

	void operator*= (float val) {
		x *= val;
		y *= val;
	}

	float Length() {
		return sqrt(x * x + y * y);
	}

	Vector2D Normalize() {
		float length = Length();
		if(length == 0)
			return Vector2D(0, 0);
		return Vector2D(x / length, y / length);
	}
};