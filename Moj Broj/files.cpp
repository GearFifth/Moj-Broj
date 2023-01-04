#include "files.h"

std::vector<Round> loadRoundsFromFile(std::string fileName)
{
	std::vector<Round> runde;
	std::vector<int> brojevi;
	int trazeniBroj;

	std::string broj;
	std::ifstream myfile(fileName);

	int cnt = 1; //Pomocna promenljiva na osnovu koje racunamo redosled runde

	if (myfile.is_open()) {
#		//Iterira do kraja fajla
		while (myfile.good()) {
			brojevi.clear();

			for (int i = 0; i < 6; i++) {
				myfile >> broj;
				brojevi.push_back(stoi(broj));
			}
			myfile >> broj;
			trazeniBroj = stoi(broj);

			//Odabir koji igrac igra prvi
			Igrac prviIgrac = A;
			if (cnt % 2 == 0) { prviIgrac = B; }

			runde.push_back(Round(brojevi,trazeniBroj,prviIgrac));
			
			cnt++;
		}
	}
	return runde;
}
