#define PI 3.141592653589793

#include "vector3.h"
#include <iostream>
#include <math.h>

int main()
{
	vector3 a = vector3(1,0,0);
	vector3 b = vector3(1,1,0);
	vector3 c = vector3(7,8,9);
	print_vector3(a);
	print_vector3(b);
	print_vector3(c);
	std::cout << "add:" << std::endl;
	print_vector3(add(a,b));

	std::cout << "mul_scalar:" << std::endl;
	print_vector3(mul_scalar(a,10.0));

	std::cout << "scalar_multiplication_of:" << std::endl;
	std::cout << scalar_multiplication_of(a,b) << std::endl;

	std::cout << "length_of_vector3:" << std::endl;
	std::cout << length_of_vector3(a) << std::endl;

	std::cout << "normalize_vector3:" << std::endl;
	print_vector3(normalize_vector3(a));

	std::cout << "vector3_multiplicaton_of:" << std::endl;
	print_vector3(vector3_multiplication_of(a,b));

	std::cout << "normal_for" << std::endl;
	print_vector3(normal_for(a,b));

	std::cout << "rotate_vector3_to" << std::endl;
	print_vector3(rotate_vector3_to(a,b, -PI/4));

	std::cout << "mixed_multiplication_of()" << std::endl;
	std::cout << (mixed_multiplication_of(a,b,c)) << std::endl;
}
