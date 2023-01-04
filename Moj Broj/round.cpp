#include "round.h"

//Konstruktor
Round::Round(std::vector<int>& ponudjeniBrojevi, int &trazeniBroj, Igrac &igrac):
	ponudjeniBrojevi(ponudjeniBrojevi), trazeniBroj(trazeniBroj), prviIgracNaPotezu(igrac),
	dobijeniBrojA(0), dobijeniBrojB(0), dobijeniBrojProg(0), pobednik() {}



// --------------------- Getteri i setteri ---------------------
//Brojevi
std::vector<int> Round::getPonudjeniBrojevi()
{
	return ponudjeniBrojevi;
}

int Round::getTrazeniBroj()
{
	return trazeniBroj;
}

//Igrac A
void Round::setIzrazA(std::string &iz)
{
	izrazA = iz;
}

std::string Round::getIzrazA()
{
	return izrazA;
}

void Round::setDobijeniBrojA(double &br) {
	dobijeniBrojA = br;
}

double Round::getDobijeniBrojA() {
	return dobijeniBrojA;
}

//Igrac B
void Round::setIzrazB(std::string &iz)
{
	izrazB = iz;
}

std::string Round::getIzrazB()
{
	return izrazB;
}

void Round::setDobijeniBrojB(double &br) {
	dobijeniBrojB = br;
}

double Round::getDobijeniBrojB() {
	return dobijeniBrojB;
}

//Program
void Round::setIzrazProg(std::string& iz)
{
	izrazProg = iz;
}

std::string Round::getIzrazProg()
{
	return izrazProg;
}

void Round::setDobijeniBrojProg(double &br) {
	dobijeniBrojProg = br;
}

double Round::getDobijeniBrojProg() {
	return dobijeniBrojProg;
}