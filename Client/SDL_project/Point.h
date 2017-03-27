#pragma once
class Point
{
public:

	Point() : x(0), y(0) { }
	Point(int x, int y) : x(x), y(y) { }

	int getX() const { return x; }
	int getY() const { return y; }

private:
	int x, y;
};

