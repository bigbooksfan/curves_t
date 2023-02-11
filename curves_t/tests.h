#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <cassert>

#include "Ñurve.h"
#include "Point.h"

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
//#define ASSERT_HINT(expr, hint) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))
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
            }
            catch (const std::logic_error&) {
                // OK
            }
            catch (...) {
                cerr << "Point constructed with non-floating type\n";
            }
        }
        {
            const Point<double> p(1, 2, 3);
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
    }

    void CircleConstruction() {

    }

    void CircleGetPointOfParam() {
        {
            Circle<double> a(1.0);
            const Point<double> p0 = a.GetPointByParam(0.0);
            Point<double> p0c(0, 1, 0);
            ASSERT_EQUAL_HINT(p0, p0c, "Wrong circle point of param = 0");
        }


    }

    void RunTests() {
        RUN_TEST(PointConstruction);
        RUN_TEST(PointEqualityCheck);
        RUN_TEST(CircleConstruction);
        RUN_TEST(CircleGetPointOfParam);
        cerr << "Tests done\n";
    }

}