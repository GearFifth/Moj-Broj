#include "calculator.h"
#include <iostream>
#include <sstream>
#include <string>

int main()
{
	Calculator calc = Calculator();
	double res = calc.calculate("2+3;q");
	std::cout << res;

	std::cin.get();
	return 0;
}
