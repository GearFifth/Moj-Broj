#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <chrono>
#include "round.h"
#include "files.h"

class Game {
public:
	Game(std::vector<Round> &runde); //Konstruktor
	void start(); //Pokrece igru
	void dodajPobedu(Igrac igrac); //Dodaje pobedu igracu

	//Getteri i setteri
	void setRunde(std::vector<Round>& runde);
	std::vector<Round> getRunde();

	void setBrojPobedaA(int br);
	int getBrojPobedaA();

	void setBrojPobedaB(int br);
	int getBrojPobedaB();

private:
	std::vector<Round> runde;

	int brojPobedaA;
	int brojPobedaB;
};
