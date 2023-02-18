#pragma once

#include <iostream>
#include <type_traits>
#include <stdexcept>
#include <cmath>

template <typename T>
class Point {
private:			// fields
	T x_ = 0;
	T y_ = 0;
	T z_ = 0; 

public:				// constructors
	Point() = delete;
	Point(T x, T y, T z);

public:				// methods
	const T GetX() const;
	const T GetY() const;
	const T GetZ() const;

public:				// operators
	//std::ostream& operator<<(std::ostream& os);		// do i need it?

};

/*********************************** METHOD DEFINITIONS ***************************************/

template<typename T>
Point<T>::Point(T x, T y, T z) : x_(x), y_(y), z_(z) {
	if (!std::is_floating_point<T>::value)
		throw std::logic_error("Point coordinate is NOT floating type");
	// Should i do it via 
	//template <typename Floating,
	//	std::enable_if_t<std::is_floating_point<Floating>::value, bool> = true >
	// ?
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
std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
	os << "{ " << point.GetX() << " , " << point.GetY() << " , " << point.GetZ() << " }";
	return os;
}

// disable massive amount of "possible loss of data" warnings
// from T to U conversion
#pragma warning(disable:4244)

// Return distance with TYPE of first point
template <typename T, typename U>
const T Distance(const Point<T>& lhs, const Point<U>& rhs) {
	T ret = 0;
	ret += std::powf((lhs.GetX() - rhs.GetX()), 2);
	ret += std::powf((lhs.GetY() - rhs.GetY()), 2);
	ret += std::powf((lhs.GetZ() - rhs.GetZ()), 2);
	ret = std::sqrtf(ret);
	return ret;
}

// comparsion in less precision type
template <typename T, typename U>
bool AlmostEqual(const Point<T>& lhs, const Point<U>& rhs) {
	// max of (T and U epsilons) - didn't work well
	//const auto precision_max = std::fmax(std::numeric_limits<T>::epsilon(), std::numeric_limits<U>::epsilon());
	const T Dist = Distance(lhs, rhs);
	T PRECISION = static_cast<T>(1e-6);
	return Dist < PRECISION;
}

template <typename T, typename U>
bool operator==(const Point<T>& lhs, const Point<U>& rhs) {
	return AlmostEqual(lhs, rhs);
}

template <typename T, typename U>
bool operator!=(const Point<T>& lhs, const Point<U>& rhs) {
	return !(lhs == rhs);
}

#pragma warning(default:4244)
