#pragma once

#include <cmath>

#include "Point.h"
#include "3Dvector.h"

template <typename T>
class Curve {

public:
	
	virtual const Point<T> GetPointByParam(T param) const {
		return Point<T>(0.0, 0.0, 0.0);
	}

	virtual const TriDvector<T> GetDerivativeByParam(T param) const {
		return TriDvector<T>(0.0, 0.0, 0.0);
	}

	virtual const bool IsCircle() const {
		return false;
	}
};
