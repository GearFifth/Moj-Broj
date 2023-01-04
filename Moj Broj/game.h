#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include "round.h"

class Game {
public:
	Game(std::vector<Round> &runde);
	void start(); //Pokrece igru

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
