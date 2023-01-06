#pragma once
//Ovde su funkcije za rad sa fajlovima
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "round.h"

//Funkcija koja cita vrednosti za svaku rundu iz file-a
std::vector<Round> loadRoundsFromFile(std::string fileLocation);

//Upisuje podatke prikupljene u toku runde u fajl
void writeRoundToFile(Round &runda,std::string fileLocation);

//cisti fajl - poziva se nakon poziva igre, tj u konstruktoru
void clearOutFile(std::string fileLocation);