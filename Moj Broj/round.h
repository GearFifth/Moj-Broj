#pragma once
#include <vector>
#include <string>

enum Igrac {A,B};

class Round {
public:
	//Poslednji parametar oznacava ko prvi igra
	Round(std::vector<int> &ponudjeniBrojevi, int &trazeniBroj, Igrac &igrac);
	void calculateBestSolution(); //Program racuna broj

	//Getteri i setteri
	std::vector<int> getPonudjeniBrojevi();
	int getTrazeniBroj();

	void setIzrazA(std::string &iz);
	std::string getIzrazA();
	void setDobijeniBrojA(double &br);
	double getDobijeniBrojA();

	void setIzrazB(std::string &iz);
	std::string getIzrazB();
	void setDobijeniBrojB(double &br);
	double getDobijeniBrojB();

	void setIzrazProg(std::string& iz);
	std::string getIzrazProg();
	void setDobijeniBrojProg(double &br);
	double getDobijeniBrojProg();

private:
	std::vector<int> ponudjeniBrojevi;
	int trazeniBroj;
	Igrac prviIgracNaPotezu;

	std::string izrazA;
	double dobijeniBrojA; //Broj koji je izracunao igrac A
	std::string izrazB;
	double dobijeniBrojB; //Broj koji je izracunao igrac B
	std::string izrazProg;
	double dobijeniBrojProg; //Broj koji je izracunao program

	Igrac pobednik;
};