#pragma once
#include <vector>
#include <string>
#include <map>
#include "calculator.h"
#include "calculator.cpp"

enum Igrac { A, B };

class Round {
public:
	//3. parametar oznacava ko prvi igra
	Round(std::vector<std::string>& ponudjeniBrojevi, int& trazeniBroj, Igrac& igrac, int& brojRunde);
	Round(std::vector<std::string>& ponudjeniBrojevi, int& trazeniBroj);

	//Funkcija radi tako sto trazenjem azurira pokazivace unutar rekurzije
	//Parametri su sledeci
	// 1 - brojevi pomocu kojih racunamo
	// 2 - broj koji treba da dobijemo
	// 3 - pokazivac na trenutnu najblizu vrednost resenja
	// 4 - pokazivac na izraz trenutne najblize vrednosti
	void findSolution(std::vector<std::string>& ponudjeniBrojevi, int& trazeniBroj,
		int* pronadjenaVrednost, std::string* pronadjenIzraz);

	//Proverava unos korisnika
	//vraca true/false u slucaju dobrog/loseg unosa
	bool validateInput(std::string unos); 

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

	std::string getPobednik();
	void setPobednik(std::string pob);

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

	std::string pobednik; //Inicijalno postavljen na "Nema pobednika"
};