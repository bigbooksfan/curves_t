#pragma once

#include "point.h"

template <typename T>
class TriDvector {
private:		// fields
	T x_ = 0;
	T y_ = 0;
	T z_ = 0;

public:			// constructors

	TriDvector() = delete;
	TriDvector(T x, T y, T z);

public:			// methods

	const T GetX() const;
	const T GetY() const;
	const T GetZ() const;

	void Normalize();

	Point<T> MakePoint() const;
};

/*********************************** METHOD DEFINITIONS ***************************************/

template<typename T>
TriDvector<T>::TriDvector(T x, T y, T z) : x_(x), y_(y), z_(z) {
	if (!std::is_floating_point<T>::value)
		throw std::logic_error("3Dvector coordinate is NOT floating type");
}

template<typename T>
const T TriDvector<T>::GetX() const {
	return x_;
}

template<typename T>
const T TriDvector<T>::GetY() const {
	return y_;
}

template<typename T>
const T TriDvector<T>::GetZ() const {
	return z_;
}

template<typename T>
void TriDvector<T>::Normalize() {
	T len = Distance(
		Point<T>(0.0, 0.0, 0.0),
		MakePoint()	// End-of-vector point
	);
	x_ /= len;
	y_ /= len;
	z_ /= len;
}

template<typename T>
Point<T> TriDvector<T>::MakePoint() const {
	return Point<T>(x_, y_, z_);
}

/*********************************** Out-of-class fuctions ***************************************/

template <typename T>
std::ostream& operator<<(std::ostream& os, const TriDvector<T>& v) {
	os << "{ " << v.GetX() << " , " << v.GetY() << " , " << v.GetZ() << " }";
	return os;
}

// disable massive amount of "possible loss of data" warnings
// from T to U conversion
#pragma warning(disable:4244)

template <typename T, typename U>
bool operator==(const TriDvector<T>& lhs, const TriDvector<U>& rhs) {
	return AlmostEqual(lhs.MakePoint(), rhs.MakePoint());
}

template <typename T, typename U>
bool operator!=(const TriDvector<T>& lhs, const TriDvector<U>& rhs) {
	return !(lhs == rhs);
}

#pragma warning(default:4244)