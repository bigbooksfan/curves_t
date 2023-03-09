#pragma once

template <typename T>
class Circle final : public Curve<T> {

private:			// fields
	const T rad_ = 0;

public:				// constructors
	Circle() = delete;
	explicit Circle(T rad);

public:				// methods
	const T GetRad() const;
	const Point<T> GetPointByParam(T param) const;
	const TriDvector<T> GetDerivativeByParam(T param) const;

	const bool IsCircle() const;
};

/****************************************** DEFINITIONS ************************************************/

template <typename T>
Circle<T>::Circle(T rad) : rad_(rad) {
	if (!std::is_floating_point<T>::value)
		throw std::logic_error("Circle coordinate is NOT floating type");
	if (rad <= 0)
		throw std::logic_error("Radii must be positive");
}

template <typename T>
const T Circle<T>::GetRad() const {
	return rad_;
}

template <typename T>
const Point<T> Circle<T>::GetPointByParam(T param) const {
	T x = rad_ * std::cos(param);
	T y = rad_ * std::sin(param);
	T z = 0;

	Point<T> ret(x, y, z);
	return ret;
}

template <typename T>
const TriDvector<T> Circle<T>::GetDerivativeByParam(T param) const {
	T x = (-1) * std::sin(param);
	T y = std::cos(param);
	T z = 0;

	TriDvector<T> ret(x, y, z);
	ret.Normalize();
	return ret;
}

template<typename T>
const bool Circle<T>::IsCircle() const {
	return true;
}
