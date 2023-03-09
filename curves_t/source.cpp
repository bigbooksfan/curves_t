#include <vector>
#include <list>
#include <random>
#include <execution>
#include <algorithm>

#include <iostream>

#include "curve.h"
#include "tests.h"

int main() {
	MyUnitTests::RunTests();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distrib_d(1.0, 100.0);
	
	Circle<double> c1(distrib_d(rd));
	Circle<double> c2(distrib_d(rd));
	Circle<double> c3(distrib_d(rd));
	Circle<double> c4(distrib_d(rd));
	Circle<double> c5(distrib_d(rd));

	Ellipsis<double> e1(distrib_d(rd), distrib_d(rd));
	Ellipsis<double> e2(distrib_d(rd), distrib_d(rd));
	Ellipsis<double> e3(distrib_d(rd), distrib_d(rd));
	Ellipsis<double> e4(distrib_d(rd), distrib_d(rd));
	Ellipsis<double> e5(distrib_d(rd), distrib_d(rd));

	Helix<double> h1(distrib_d(rd), distrib_d(rd));
	Helix<double> h2(distrib_d(rd), distrib_d(rd));
	Helix<double> h3(distrib_d(rd), distrib_d(rd));
	Helix<double> h4(distrib_d(rd), distrib_d(rd));
	Helix<double> h5(distrib_d(rd), distrib_d(rd));

	// populating vector of any curves
	std::vector<Curve<double>*> v1;
	v1.reserve(15);
	v1.push_back(&c1); v1.push_back(&c2); v1.push_back(&c3); v1.push_back(&c4); v1.push_back(&c5);
	v1.push_back(&e1); v1.push_back(&e2); v1.push_back(&e3); v1.push_back(&e4); v1.push_back(&e5);
	v1.push_back(&h1); v1.push_back(&h2); v1.push_back(&h3); v1.push_back(&h4); v1.push_back(&h5);

	std::shuffle(v1.begin(), v1.end(), gen);

	std::for_each(
		std::execution::seq,
		v1.begin(), v1.end(),
		[](const Curve<double>* cur) { 
			Point<double> p = cur->GetPointByParam(3.14159265358979323846 / 4);
			p.PrintOut();
		}
	);

	std::vector<Circle<double>*> v2;
	std::for_each(							// populate second container
		std::execution::par,
		v1.begin(), v1.end(),
		[&v2](Curve<double>* cur) { 
			if (cur->IsCircle())
				v2.push_back(static_cast<Circle<double>*>(&*cur));
		}
	);

	std::sort(								// sort by radiis - from less to greater
		v2.begin(), v2.end(),
		[](const Circle<double>* lhs, const Circle<double>* rhs) { 
			return lhs->GetRad() < rhs->GetRad();
		}
	);

	double total_sum = 0.0;
	std::for_each(							// std::accumulate doesn't fit...
		std::execution::par,
		v2.begin(), v2.end(),
		[&total_sum](const Circle<double>* cur) {
			total_sum += cur->GetRad();
		}			
	);

	return 0;
}