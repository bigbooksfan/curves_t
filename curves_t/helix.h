#pragma once

#include "curve.h"

template <typename T>
class Helix final : public Curve<T> {
private:		// fields
	const T rad_;
	const T step_;

public:			// constructors
	Helix() = delete;
	explicit Helix(T rad, T step);

public:			// methods
	const T GetRad() const;
	const Point<T> GetPointByParam(T param) const;
	const TriDvector<T> GetDerivativeByParam(double param) const;

	const bool IsCircle() const;
};

/****************************************** DEFINITIONS ************************************************/

template<typename T>
Helix<T>::Helix(T rad, T step) : rad_(rad), step_(step) {
	if (!std::is_floating_point<T>::value)
		throw std::logic_error("Helix coordinate is NOT floating type");
	if (rad <= 0)
		throw std::logic_error("Radii must be positive");
}

template<typename T>
const T Helix<T>::GetRad() const {
	return rad_;
}

template<typename T>
const Point<T> Helix<T>::GetPointByParam(T param) const {
	double PI = 3.14159265358979323846;
	T PI_t = static_cast<T>(PI);

	T x = rad_ * std::cos(param);
	T y = rad_ * std::sin(param);
	T z = (param / (2 * PI_t) ) * step_;

	Point<T> ret(x, y, z);
	return ret;
}

template<typename T>
const TriDvector<T> Helix<T>::GetDerivativeByParam(double param) const {
	double PI = 3.14159265358979323846;
	T PI_t = static_cast<T>(PI);
	
	T x = (-1) * std::sin(param);
	T y = std::cos(param);
	T z = step_* (2 * PI_t / rad_);		// not sure about it

	TriDvector<T> ret(x, y, z);
	ret.Normalize();
	return ret;
}

template<typename T>
const bool Helix<T>::IsCircle() const {
	return false;
}
