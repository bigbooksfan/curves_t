#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <cassert>
#include <cstring>              // for strcmp in throw-catch check

#include "Ñurve.h"
#include "circle.h"
#include "ellipsis.h"
#include "Point.h"
#include "3Dvector.h"

double PI = 3.14159265358979323846;

namespace MyUnitTests {

    using std::string;
    using std::cerr;

    template <typename T, typename U>
    void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file, const string& func, unsigned line, const string& hint) {
        if (t != u) {
            cerr << std::boolalpha;
            cerr << file << "(" << line << "): \n" << func << ":\n";
            cerr << "ASSERT_EQUAL(" << t_str << ", " << u_str << ") failed:";
            cerr << t << " != " << u << ".\n";
            if (!hint.empty()) {
                cerr << "Hint: " << hint;
            }
            cerr << std::endl;
            abort();
        }
    }

    void AssertImpl(bool value, const string& expr_str, const string& file, const string& func, unsigned line, const string& hint) {
        if (!value) {
            cerr << file << "(" << line << "): " << func << ": ";
            cerr << "ASSERT(" << expr_str << ") failed.";
            if (!hint.empty()) {
                cerr << " Hint: " << hint;
            }
            cerr << std::endl;
            abort();
        }
    }

    template <typename T>
    void RunTestImpl(const T& func, const string& func_name) {
        func();
        cerr << func_name << " OK\n";
    }

//#define ASSERT(expr) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, "")
//
#define ASSERT_HINT(expr, hint) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))
//
//#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, "")

#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

#define RUN_TEST(func) RunTestImpl((func), #func)

    /******************************** MODULE TESTS ****************************************/

    double DELTA = 1e-6;

    void PointConstruction() {
        {       // OK case
            Point<double> p(0.0, 0.0, .0);
        }
        {       // non-floating type point construction
            try {
                Point<long> p(long(1), long(2), long(3));
                ASSERT_HINT(false, "No exception by Point constructed with non-floating type\n");
            }
            catch (const std::logic_error&) {
                // OK
            }
            catch (...) {
                ASSERT_HINT(false, "Point constructed with non-floating type\n");
            }
        }
        {
            const Point<double> p(1, 2, 3);
            const Point<float> p1(1.0, 2.0, 3.0);
            ASSERT_EQUAL_HINT(p, p1, "Point<double> != Point<float> with same coordinates");
        }
    }

    void PointEqualityCheck() {
        {       // Point<float> == Point<float>
            Point<float> p(float(1), float(2), float(3));
            Point<float> p1(1, 2, 3);
            ASSERT_EQUAL_HINT(p, p1, "Equal points ain't equal somewhy");
        }
        {
            Point<double> p(1, 2, 3);
            Point<float> p1(1, 2, 3);
            ASSERT_EQUAL_HINT(p, p1, "Point<double> and Point<float> ain't equal somewhy");
        }
        {
            Point<long double> p(-1, -2, -3);
            Point<float> p1(-1, -2, -3);
            ASSERT_EQUAL_HINT(p, p1, "Point<long double> and Point<float> ain't equal somewhy");
        }
        {       // Point<float> == const Point<float>
            Point<float> p(float(1), float(2), float(3));
            const Point<float> p1(1, 2, 3);
            ASSERT_EQUAL_HINT(p, p1, "Equal point ain't equal to const Point somewhy");
        }
        {       // AlmostEquality check
            Point<double> p1(0, 0, 0.1000001);
            Point<double> p2(0, 0, 0.0999999);
            ASSERT_EQUAL_HINT(p1, p2, "Almost equal point ain't equal somewhy");
        }
    }

    void CircleConstruction() {
        {
            Circle<double> a(5);
        }
        {       // non-floating type Circle construction
            try {
                Circle<int> p(1);
                ASSERT_HINT(false, "No exception by Circle constructed with non-floating type\n");                  // abort
            }
            catch (const std::logic_error& e) {
                if (std::strcmp(e.what(), "Circle coordinate is NOT floating type") == 0) {         // equal
                    // OK
                }
                else {
                    throw;
                }
            }
            catch (...) {
                ASSERT_HINT(false, "Circle constructed with non-floating type\n");
            }
        }
        {
            try {
                Circle<double> p(-5.0);
                ASSERT_HINT(false, "No exception by Circle constructed with radii <= 0\n");                  // abort
            }
            catch (const std::logic_error& e) {
                if (std::strcmp(e.what(), "Radii must be positive") == 0) {
                    // OK
                }
                else {
                    throw;
                }
            }
            catch (...) {
                ASSERT_HINT(false, "Circle constructed with radii <= 0\n");
            }
        }
    }

    void CircleGetPointOfParam() {
        {
            Circle<double> a(1.0);
            const Point<double> p0 = a.GetPointByParam(0.0);
            Point<double> p0c(1, 0, 0);
            ASSERT_EQUAL_HINT(p0, p0c, "Wrong circle point of param = 0");
        }
        {
            Circle<double> a(1.0);
            const Point<double> p0 = a.GetPointByParam(PI);
            Point<double> p0c(-1.0, 0.0, 0.0);
            ASSERT_EQUAL_HINT(p0, p0c, "Wrong circle point of param = PI");
        }
        {
            Circle<double> a(2.0);
            const Point<double> p0 = a.GetPointByParam(PI);
            Point<double> p0c(0, 2, 0);
            ASSERT_EQUAL_HINT(p0, p0c, "Wrong circle point of param = PI");
        }
    }

    void TriDvectorConstruction() {
        {
            TriDvector<double> v(0.0, 0.0, 0.0);
        }
        {
            TriDvector<double> v(1.0, 2.0, 3.0);
            TriDvector<float> v1(1.0, 2.0, 3.0);
            ASSERT_EQUAL_HINT(v, v1, "3Dvector<double> != 3Dvector<float> with same coordinates");
        }
        {       // non-floating type 3DVector construction
            try {
                TriDvector<int> p(1, 2, 3);
                ASSERT_HINT(false, "No exception by 3Dvector constructed with non-floating type\n");
            }
            catch (const std::logic_error& e) {
                if (std::strcmp(e.what(), "3Dvector coordinate is NOT floating type") == 0) {           // equal
                    // OK
                }
                else {
                    throw;
                }
            }
            catch (...) {
                ASSERT_HINT(false, "3Dvector constructed with non-floating type\n");
            }
        }
        {       // non-floating type 3DVector construction
            try {
                TriDvector<unsigned int> p(1, 2, 3);
                ASSERT_HINT(false, "No exception by 3Dvector constructed with non-floating type\n");
            }
            catch (const std::logic_error& e) {
                if (std::strcmp(e.what(), "3Dvector coordinate is NOT floating type") == 0) {           // equal
                    // OK
                }
                else {
                    throw;
                }
            }
            catch (...) {
                ASSERT_HINT(false, "3Dvector constructed with non-floating type\n");
            }
        }
    }

    void CircleDerivative() {
        {
            Circle<double> p(1);
            TriDvector<double> a(0.0, 1.0, 0.0);
            TriDvector<double> b = p.GetDerivativeByParam(0.0);
            ASSERT_EQUAL_HINT(a, b, "Derivative by param 0 is wrong");
        }
        {
            Circle<double> p(1);
            TriDvector<double> correct(-1.0, 0.0, 0.0);
            TriDvector<double> getted = p.GetDerivativeByParam(PI/2);
            ASSERT_EQUAL_HINT(correct, getted, "Derivative by param PI/2 is wrong");
        }
        {
            Circle<double> p(1);
            TriDvector<double> correct(0.0, -1.0, 0.0);
            TriDvector<double> getted = p.GetDerivativeByParam(PI);
            ASSERT_EQUAL_HINT(correct, getted, "Derivative by param PI is wrong");
        }
        {
            Circle<double> p(10);
            TriDvector<double> correct(-0.4794255386042030, 0.8775825618903727, 0.0);
            TriDvector<double> getted = p.GetDerivativeByParam(5);
            ASSERT_EQUAL_HINT(correct, getted, "Derivative by param 5 is wrong");
        }
    }

    void EllipsisConstruction() {
        {
            Ellipsis<double> a(5, 10);
        }
        {       // non-floating type Circle construction
            try {
                Ellipsis<int> p(1, 2);
                ASSERT_HINT(false, "No exception by Ellipsis constructed with non-floating type\n");                  // abort
            }
            catch (const std::logic_error& e) {
                if (std::strcmp(e.what(), "Ellipsis coordinate is NOT floating type") == 0) {         // equal
                    // OK
                }
                else {
                    throw;
                }
            }
            catch (...) {
                ASSERT_HINT(false, "Ellipsis constructed with non-floating type\n");
            }
        }
        {
            try {
                Ellipsis<double> p(-5.0, 6);
                ASSERT_HINT(false, "No exception by Ellipsis constructed with radii <= 0\n");                  // abort
            }
            catch (const std::logic_error& e) {
                if (std::strcmp(e.what(), "Radii must be positive") == 0) {
                    // OK
                }
                else {
                    throw;
                }
            }
            catch (...) {
                ASSERT_HINT(false, "Ellipsis constructed with radii <= 0\n");
            }
        }
    }

    void EllipsisGetPointOfParam() {
        {
            Ellipsis<double> a(2.0, 1.0);
            const Point<double> getted = a.GetPointByParam(0.0);
            Point<double> correct(2, 0, 0);
            ASSERT_EQUAL_HINT(correct, getted, "Wrong ellipsis point of param = 0");
        }
        {
            Ellipsis<double> a(1.0, 1.0);           // actual circle
            const Point<double> getted = a.GetPointByParam(PI/2);
            Point<double> correct(0.0, 1.0, 0.0);
            ASSERT_EQUAL_HINT(correct, getted, "Wrong ellipsis point of param = PI/2");
        }
        {
            Ellipsis<double> a(2.0, 4.0);
            const Point<double> getted = a.GetPointByParam(5);
            Point<double> correct(0, 4, 0);
            ASSERT_EQUAL_HINT(correct, getted, "Wrong ellipsis point of param ~= 5");
        }
    }

    void RunTests() {
        RUN_TEST(PointConstruction);
        RUN_TEST(PointEqualityCheck);
        RUN_TEST(CircleConstruction);
        RUN_TEST(CircleGetPointOfParam);
        RUN_TEST(TriDvectorConstruction);
        RUN_TEST(CircleDerivative);
        RUN_TEST(EllipsisConstruction);
        RUN_TEST(EllipsisGetPointOfParam);
        cerr << "Tests done\n";
    }

}       // namespace MyUnitTests