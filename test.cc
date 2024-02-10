#include <iostream>
#include "euclidian.h"

int test_euclidian()
{
	Vector<int> u({1,2,2});
	Vector<int> v({2,2,1});

	std::cout << "u = " << u << "\nv = " << v << '\n';
	std::cout << "u - v = " << u - v << '\n';
	std::cout << "u + v = " << u + v << '\n';
	std::cout << "u * v = " << u*v << '\n';
	return 0;
}


int main()
{
	test_euclidian();
}