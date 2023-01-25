#pragma once

#include <iostream>

class Point {
public:				// constructors
	Point() = delete;
	Point(double x, double y, double z) : x_(x), y_(y), z_(z) { }

public:				// methods
	const double GetX() const;
	const double GetY() const;
	const double GetZ() const;

public:				// operators
	std::ostream& operator<<(std::ostream& os);

private:			// fields
	double x_ = 0;
	double y_ = 0;
	double z_ = 0;
};

/*********************************** METHOD DEFINITIONS ***************************************/

const double Point::GetX() const {
	return x_;
}

const double Point::GetY() const {
	return y_;
}

const double Point::GetZ() const {
	return z_;
}

std::ostream& Point::operator<<(std::ostream& os) {
	os << "{ " << x_ << " , " << y_ << " , " << z_ << " }";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
	os << "{ " << point.GetX() << " , " << point.GetY() << " , " << point.GetZ() << " }";
	return os;
}

bool operator==(const Point& lhs, const Point& rhs) {
	if (lhs.GetX() != rhs.GetX()) return false;
	if (lhs.GetY() != rhs.GetY()) return false;
	if (lhs.GetZ() != rhs.GetZ()) return false;
	return true;
}

bool operator!=(const Point& lhs, const Point& rhs) {
	return !(lhs == rhs);
}


