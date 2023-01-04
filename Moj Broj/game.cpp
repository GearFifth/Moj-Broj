#include "game.h"
#include "files.h"

//Konstruktor
Game::Game(std::vector<Round>& rundeInp):
	runde(rundeInp), brojPobedaA(0), brojPobedaB(0) {}


// --------------------- Getteri i setteri ---------------------
void Game::setRunde(std::vector<Round>& runde)
{
	this->runde = runde;
}

std::vector<Round> Game::getRunde() {
	return runde;
}

//Igrac A
void Game::setBrojPobedaA(int br)
{
	brojPobedaA = br;
}

int Game::getBrojPobedaA()
{
	return brojPobedaA;
}

//Igrac B
void Game::setBrojPobedaB(int br)
{
	brojPobedaB = br;
}

int Game::getBrojPobedaB()
{
	return brojPobedaB;
}


// --------------------- Pokretanje igre ---------------------
void Game::start()
{
	std::vector<Round>::iterator iterRunde;

	for (iterRunde = runde.begin(); iterRunde != runde.end(); iterRunde++) {
		Round trenutnaRunda = *iterRunde;
		int brojRunde = iterRunde - runde.begin() + 1;

		std::cout << std::string(20, '-') << " MOJ BROJ " << std::string(20, '-') << std::endl;
		std::cout << "Runda: " << brojRunde << std::endl;

		std::vector<int> ponudjeniBrojevi = trenutnaRunda.getPonudjeniBrojevi();
		int trazeniBroj = trenutnaRunda.getTrazeniBroj();

		std::cout << "Ponudjeni brojevi: ";
		std::vector<int>::iterator it;
		for (it = ponudjeniBrojevi.begin(); it != ponudjeniBrojevi.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl << "Trazeni broj: " << trazeniBroj << std::endl;
	}

}


