#include "calculator.h"
#include "files.h"
#include "game.h"
#include <iostream>
#include <sstream>
#include <string>
#include <set>

int main(int argc, char* argv[])
{

	//Izvlacenje argumenata komandne linije
	std::string filePath = argv[0];
	std::string inputFile = argv[1];
	std::cout << filePath << std::endl;
	std::cout << inputFile << std::endl;

	//Calc
	Calculator calc = Calculator<int>();

	//Citanje iz fajla i punjenje vektora
	std::vector <Round> runde;
	runde = loadRoundsFromFile(inputFile);

	Game g = Game(runde);
	g.start();

	std::cout << "KRAJ" << std::endl;

	std::cin.get();
	return 0;
}
