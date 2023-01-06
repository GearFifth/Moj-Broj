#include "calculator.h"
#include "files.h"
#include "game.h"
#include <iostream>
#include <sstream>
#include <string>
#include <set>




int main(int argc, char* argv[])
{


	//Izvlacenje patha
	std::string filePath = argv[0];

	//Calc
	Calculator calc = Calculator<int>();

	//Test kalkulatora
	/*try {
		int res = calc.calculate("6/3;q");
		std::cout << res << std::endl;
	}
	catch (std::invalid_argument error) {
		std::cerr << error.what() << std::endl;
	}*/

	//Citanje iz fajla i punjenje vektora
	std::vector <Round> runde;
	runde = loadRoundsFromFile("input.txt");

	Game g = Game(runde);
	g.start();

	std::cout << "KRAJ" << std::endl;


	
	
	//Trazenje test
	//std::vector<std::string> ponudjeniBrojevi = {"4","8","9"};
	//int trazeniBroj = 18;
	//int pronadjenaVrednost = 0;
	//std::string pronadjenIzraz = "";

	//findSolution(ponudjeniBrojevi, trazeniBroj, &pronadjenaVrednost, &pronadjenIzraz);

	//std::cout << "Pronadjen izraz: " << pronadjenIzraz << std::endl;
	//std::cout << "Pronadjen broj: " << calc.calculate(pronadjenIzraz + ";q") << std::endl;

	//Test expression
	/*Expression expr1 = Expression("2+5*3", "2", Expression("5*3", "5", "3"));
	std::cout << expr1.isUsed("2") << std::endl;
	std::cout << expr1.isUsed(Expression("8/2", "8", "2")) << std::endl;*/

	//std::string expr = findSolution();
	//std::cout << std::endl << expr << std::endl;
	//std::cout << calc.calculate(expr + ";q") << std::endl;

	

	std::cin.get();
	return 0;
}
