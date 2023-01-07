#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "game.h"
//Ovde su funkcije za rad sa fajlovima

//Funkcija koja cita vrednosti za svaku rundu iz file-a
//Ulazni parametar - naziv ulaznog fajla
//Povratna vrednost - vektor rundi koje su ucitane
std::vector<Round> loadRoundsFromFile(std::string &fileLocation);

//Upisuje podatke prikupljene u toku runde u fajl
//Ulazni parametri - runda, naziv fajla u koji upisujemo
void writeRoundToFile(Round &runda,std::string fileLocation);

//Upisuje rezultate igre u fajl
void writeResultToFile(int &brojPobedaA, int &brojPobedaB, std::string fileName);

//cisti fajl - poziva se nakon poziva igre, tj u konstruktoru
//Ulazni parametar - fajl koji se cisti
void clearOutFile(std::string fileLocation);