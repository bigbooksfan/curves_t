#pragma once

#include <cmath>

#include "Point.h"

class Curve {

protected:



};

class Circle final : public Curve {

public:				// constructors
	Circle() = delete;
	explicit Circle(double rad);

public:				// methods
	const double GetRad();
	const Point GetPointByParam(double param);

private:			// fields
	double rad_ = 0;
};

/****************************************** DEFINITIONS ************************************************/

inline Circle::Circle(double rad) {
	rad_ = rad;
}

const double Circle::GetRad() {
	return rad_;
}

const Point Circle::GetPointByParam(double param) {
	double x = rad_ * std::sin(param / rad_);
	double y = rad_ * std::cos(param / rad_);
	double z = 0;

	Point ret(x, y, z);
	return ret;
}
