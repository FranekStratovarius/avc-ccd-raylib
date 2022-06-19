#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D {
	public:
		float x, y;
		Vector2D();
		Vector2D(float x, float y);
		float norm();
		void print() {
			std::cout << "Vector2D: (x: "<< x << ", y: " << y << ")\n";
		}
	friend Vector2D operator+(Vector2D& o1, Vector2D& o2);
	friend Vector2D operator-(Vector2D& o1, Vector2D& o2);
	friend float operator*(Vector2D& o1, Vector2D& o2);
};

#endif // VECTOR2D_H