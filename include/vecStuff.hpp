#pragma once

#include <iostream>

struct Vector2f
{
	Vector2f()
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y)
	{}

	void print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	Vector2f operator+(const Vector2f& other) const {
        return Vector2f(x + other.x, y + other.y);
    }

    Vector2f operator*(float scalar) const {
        return Vector2f(x * scalar, y * scalar);
    }

	Vector2f operator/(float scalar) const {
		return Vector2f(x / scalar, y / scalar);
	}

	float x, y;
};