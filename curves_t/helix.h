#pragma once

#include "curve.h"

template <typename T>
class Helix final : public Curve {
private:		// fields
	const T rad_;
	const T step_;

public:			// constructors
	Helix() = delete;
	explicit Helix(T rad, T step);

public:			// methods
	T GetRad();
	Point<T> GetPointByParam();
	TriDvector<T> GetDerivativeByParam();
};

/****************************************** DEFINITIONS ************************************************/

template<typename T>
Helix<T>::Helix(T rad, T step) : rad_(rad), step_(step) {
	if (!std::is_floating_point<T>::value)
		throw std::logic_error("Helix coordinate is NOT floating type");
	if (rad <= 0)
		throw std::logic_error("Radii must be positive");
}