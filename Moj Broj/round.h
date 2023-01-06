#pragma once
#include <vector>
#include <string>
#include <map>
#include "calculator.h"

enum Igrac { A, B };

class Round {
public:
	//Poslednji parametar oznacava ko prvi igra
	Round(std::vector<std::string>& ponudjeniBrojevi, int& trazeniBroj, Igrac& igrac, int& brojRunde);
	//Funkcija radi tako sto trazenjem azurira pokazivace unutar rekurzije
	void findSolution(std::vector<std::string>& ponudjeniBrojevi, int& trazeniBroj,
		int* pronadjenaVrednost, std::string* pronadjenIzraz);

	bool validateInput(std::string unos); //Proverava unos korisnika

	// ------------------ Getteri i setteri ------------------
	int getBrojRunde();
	void setBrojRunde(int br);

	Igrac getPrviIgracNaPotezu();

	std::vector<std::string> getPonudjeniBrojevi();
	int getTrazeniBroj();

	void setIzrazA(std::string& iz);
	std::string getIzrazA();
	void setDobijeniBrojA(int& br);
	int getDobijeniBrojA();

	void setIzrazB(std::string& iz);
	std::string getIzrazB();
	void setDobijeniBrojB(int& br);
	int getDobijeniBrojB();

	void setIzrazProg(std::string& iz);
	std::string getIzrazProg();
	void setDobijeniBrojProg(int& br);
	int getDobijeniBrojProg();

	Igrac getPobednik();
	void setPobednik(Igrac pob);

private:
	int brojRunde;
	std::vector<std::string> ponudjeniBrojevi;
	int trazeniBroj;
	Igrac prviIgracNaPotezu;

	std::string izrazA;
	int dobijeniBrojA; //Broj koji je izracunao igrac A
	std::string izrazB;
	int dobijeniBrojB; //Broj koji je izracunao igrac B
	std::string izrazProg;
	int dobijeniBrojProg; //Broj koji je izracunao program

	Igrac pobednik;
};