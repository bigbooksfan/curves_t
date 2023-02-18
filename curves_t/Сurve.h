#pragma once

#include <cmath>

#include "Point.h"

class Curve {

protected:



};

template <typename T>
class Circle final : public Curve {

public:				// constructors
	Circle() = delete;
	explicit Circle(T rad);

public:				// methods
	const T GetRad();
	const Point<T> GetPointByParam(double param);

private:			// fields
	T rad_ = 0;
};

/****************************************** DEFINITIONS ************************************************/

template <typename T>
Circle<T>::Circle(T rad) : rad_(rad) {
	if (!std::is_floating_point<T>::value)
		throw std::logic_error("Circle coordinate is NOT floating type");
}

template <typename T>
const T Circle<T>::GetRad() {
	return rad_;
}

template <typename T>
const Point<T> Circle<T>::GetPointByParam(double param) {
	T x = rad_ * std::cos(param / rad_);
	T y = rad_ * std::sin(param / rad_);
	T z = 0;

	Point<T> ret(x, y, z);
	return ret;
}
