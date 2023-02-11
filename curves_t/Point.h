#pragma once

#include <iostream>
#include <type_traits>
#include <stdexcept>
#include <cmath>

template <typename T>
class Point {
public:				// constructors
	Point() = delete;
	Point(T x, T y, T z);

public:				// methods
	const T GetX() const;
	const T GetY() const;
	const T GetZ() const;

public:				// operators
	std::ostream& operator<<(std::ostream& os);		// do i need it?

private:			// fields
	T x_ = 0;
	T y_ = 0;
	T z_ = 0;
};

/*********************************** METHOD DEFINITIONS ***************************************/

template<typename T>
Point<T>::Point(T x, T y, T z) : x_(x), y_(y), z_(z) {
	if (!std::is_floating_point<T>::value)
		throw std::logic_error("Point coordinate is NOT floating type");
	// Should i do it via 
	//template <typename Floating,
	//	std::enable_if_t<std::is_floating_point<Floating>::value, bool> = true >
}

template <typename T>
const T Point<T>::GetX() const {
	return x_;
}

template <typename T>
const T Point<T>::GetY() const {
	return y_;
}

template <typename T>
const T Point<T>::GetZ() const {
	return z_;
}

/*********************************** Out-of-class fuctions ***************************************/

template <typename T>
std::ostream& Point<T>::operator<<(std::ostream& os) {
	os << "{ " << x_ << " , " << y_ << " , " << z_ << " }";
	return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
	os << "{ " << point.GetX() << " , " << point.GetY() << " , " << point.GetZ() << " }";
	return os;
}

// Return distance with TYPE of first point
template <typename T, typename U>
const T Distance(const Point<T>& lhs, const Point<U>& rhs) {
	T ret = 0;
	ret += std::powf((lhs.GetX() - static_cast<T>(rhs.GetX())), 2);
	ret += std::powf((lhs.GetY() - static_cast<T>(rhs.GetY())), 2);
	ret += std::powf((lhs.GetZ() - static_cast<T>(rhs.GetZ())), 2);
	ret = std::sqrtf(ret);
	return ret;
}

template <typename T, typename U>
bool AlmostEqual(const Point<T>& lhs, const Point<U>& rhs) {
	// std::max EPSILON
	// distance
	return true;
}

template <typename T, typename U>
bool operator==(const Point<T>& lhs, const Point<U>& rhs) {
	if (lhs.GetX() == rhs.GetX() &&
		lhs.GetY() == rhs.GetY() &&
		lhs.GetZ() == rhs.GetZ())
			return true;
	return false;
}

template <typename T, typename U>
bool operator!=(const Point<T>& lhs, const Point<U>& rhs) {
	return !(lhs == rhs);
}