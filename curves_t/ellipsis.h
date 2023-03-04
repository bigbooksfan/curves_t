#pragma once

template <typename T>
class Ellipsis final : public Curve {

public:				// constructors
	Ellipsis() = delete;
	explicit Ellipsis(T radX, T radY);

public:				// methods
	const T GetRadX();
	const T GetRadY();
	const Point<T> GetPointByParam(double param);
	const TriDvector<T> GetDerivativeByParam(double param);

private:			// fields
	T radX_ = 0;
	T radY_ = 0;
};

/****************************************** DEFINITIONS ************************************************/

template<typename T>
Ellipsis<T>::Ellipsis(T radX, T radY) : radX_(radX), radY_(radY) {
	if (!std::is_floating_point<T>::value)
		throw std::logic_error("Ellipsis coordinate is NOT floating type");
	if (radX <= 0 || radY <= 0)
		throw std::logic_error("Radii must be positive");
}

template<typename T>
const T Ellipsis<T>::GetRadX() {
	return radX_;
}

template<typename T>
const T Ellipsis<T>::GetRadY() {
	return radY_;
}

template<typename T>
const Point<T> Ellipsis<T>::GetPointByParam(double param) {		// Mistake
	T x = radX_ * std::cos(param);
	T y = radY_ * std::sin(param);
	T z = 0;

	Point<T> ret(x, y, z);
	return ret;
}
