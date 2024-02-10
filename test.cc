#include <iostream>
#include <math.h>

#include "fraction.h"
#include "euclidian.h"


int test_euclidian()
{
	std::cout << "Test vector operations:\n";
	Vector<int> u1({1,2,2});
	Vector<int> v1({3,2,1});

	std::cout << "u1 = " << u1 << "\nv1 = " << v1 << '\n';
	std::cout << "u1 - v1 = " << u1 - v1 << '\n';
	std::cout << "u1 + v1 = " << u1 + v1 << '\n';
	std::cout << "u1 * v1 = " << u1*v1 << '\n';
	std::cout << "u1 * 3 = " << u1*3 << '\n';
	std::cout << "3 * v1 = " << 3*v1 << '\n';
	std::cout << "u1 / 3 = " << u1/3 << '\n';
	std::cout << "Length of u1: " << sqrt(u1.get_squared_length()) << '\n';
	std::cout << "Length of v1: " << sqrt(v1.get_squared_length()) << '\n';
	

	Vector<Frac> u2({{1,2},{3,4},{-3,2}});
	Vector<Frac> v2({2,{2,2},{1,3}});

	std::cout << "u2 = " << u2 << "\nv2 = " << v2 << '\n';
	std::cout << "u2 - v2 = " << u2 - v2 << '\n';
	std::cout << "u2 + v2 = " << u2 + v2 << '\n';
	std::cout << "u2 * v2 = " << u2*v2 << '\n';
	std::cout << "u2 * 3 = " << u2*3 << '\n';
	std::cout << "3 * v2 = " << 3*v2 << '\n';
	std::cout << "u2 / 3 = " << u2/3 << '\n';
	std::cout << "Squared length of u2: " << u2.get_squared_length() << '\n';
	std::cout << "Squared length of v2: " << v2.get_squared_length() << "\n\n";

	return 0;
}


int main()
{
	test_euclidian();
}