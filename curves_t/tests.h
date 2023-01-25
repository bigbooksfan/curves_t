#pragma once

#include <cassert>
#include <string>
#include <iostream>

#include "curve.h"
#include "Point.h"

namespace MyUnitTests {

    using std::string;
    using std::cerr;

    template <typename T, typename U>
    void AssertEqualImpl(const T& t, const U& u, const string& t_str, const string& u_str, const string& file, const string& func, unsigned line, const string& hint) {
        if (t != u) {
            cerr << std::boolalpha;
            cerr << file << "(" << line << "): " << func << ": ";
            cerr << "ASSERT_EQUAL(" << t_str << ", " << u_str << ") failed: ";
            cerr << t << " != " << u << ".";
            if (!hint.empty()) {
                cerr << " Hint: " << hint;
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

    void CircleConstruction() {

    }

    void CircleGetPointOfParam() {
        {
            Circle a(1);
            Point p0 = a.GetPointByParam(0);
            Point p0c(0, 1, 0);
            ASSERT_EQUAL_HINT(p0, p0c, "Wrong circle point of param = 0");
        }


    }

    void RunTests() {
        RUN_TEST(CircleConstruction);
        RUN_TEST(CircleGetPointOfParam);
        cerr << "Tests done\n";
    }

}