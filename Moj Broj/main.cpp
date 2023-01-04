#include "calculator.h"
#include "files.h"
#include "game.h"
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
	//Izvlacenje patha
	std::string filePath = argv[0];


	//Calc
	Calculator calc = Calculator();
	try {
		double res = calc.calculate("5/7;q");
		//std::cout << res << std::endl;
	}
	catch (std::invalid_argument error) {
		std::cerr << error.what() << std::endl;
	}
	
	//Citanje iz fajla i punjenje vektora
	std::vector <Round> runde;
	runde = loadRoundsFromFile("input.txt");

	Game g = Game(runde);
	g.start();
	

	std::cin.get();
	return 0;
}
