#include "files.h"

std::vector<Round> loadRoundsFromFile(std::string &fileName)
{
	std::vector<Round> runde;
	std::vector<std::string> brojevi;
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
				brojevi.push_back(broj);
			}
			myfile >> broj;
			trazeniBroj = stoi(broj);

			//Odabir koji igrac igra prvi
			Igrac prviIgrac = A;
			if (cnt % 2 == 0) { prviIgrac = B; }

			runde.push_back(Round(brojevi, trazeniBroj, prviIgrac, cnt));

			cnt++;
		}
	}
	myfile.close();
	return runde;
}

void writeRoundToFile(Round& runda, std::string fileName)
{
	//Број рунде.

	/*бројеве који су били на располагању за рачунање и тражени троцифрени број;
	троцифрени број који је добио сваки од играча у тој рунди,
	колико он одступа од траженог,
	као и израз који је дово до тих бројева;
	информацију који играч је добио рунду;
	и на послетку – решење које сам програм пронашао;*/

	/*На крају датоеке,
	исписује број освојених рунди оба играча и закључује који играч је укупни победник*/
	//Ovo ce biti posebna funkcija

	std::ofstream myfile(fileName, std::ios_base::app); //appendujem rundu

	//Preuzimanje podataka iz runde
	std::vector<std::string> ponudjeniBrojevi = runda.getPonudjeniBrojevi();
	int trazeniBroj = runda.getTrazeniBroj();
	int brojRunde = runda.getBrojRunde();
	Igrac prviIgracNaPotezu = runda.getPrviIgracNaPotezu();
	std::string izrazA = runda.getIzrazA();
	std::string izrazB = runda.getIzrazB();
	std::string izrazProg = runda.getIzrazProg();
	double dobijeniBrojA = runda.getDobijeniBrojA();
	double dobijeniBrojB = runda.getDobijeniBrojB();
	double dobijeniBrojProg = runda.getDobijeniBrojProg();
	std::string pobednik = runda.getPobednik();

	if (myfile.is_open()) {
#		//Iterira do kraja fajla
		myfile << "---------- RUNDA " << brojRunde << " ----------" << std::endl;
		myfile << "Ponudjeni brojevi: ";
		for (std::string broj: ponudjeniBrojevi) {
			myfile << broj << " ";
		}
		myfile << std::endl << "Trazeni broj: " << trazeniBroj << std::endl;
		myfile << "Izraz igraca A: " << izrazA << std::endl;
		myfile << "Dobijeni broj igraca A: " << dobijeniBrojA << std::endl;
		myfile << "Razlika u odnosu na trazeni broj: " << abs(trazeniBroj - dobijeniBrojA) << std::endl;
		myfile << "Izraz igraca B: " << izrazB << std::endl;
		myfile << "Dobijeni broj igraca B: " << dobijeniBrojB << std::endl;
		myfile << "Razlika u odnosu na trazeni broj: " << abs(trazeniBroj - dobijeniBrojB) << std::endl;
		myfile << "Pobednik: " << pobednik << std::endl;
		myfile << "Izraz koji je pronasao racunar: " << izrazProg << std::endl;
		myfile << "Dobijeni broj racunara: " << dobijeniBrojProg << std::endl << std::endl;

	}
	myfile.close();
}

void writeResultToFile(int& brojPobedaA, int& brojPobedaB, std::string fileName)
{
	std::ofstream myfile(fileName, std::ios_base::app); //appendujem rezultat na kraju
	
	if (myfile.is_open()) {
		myfile << "---------- REZULTAT  ----------" << std::endl;
		myfile << "Broj pobeda igraca A: " << brojPobedaA << std::endl;
		myfile << "Broj pobeda igraca B: " << brojPobedaB << std::endl;
	
		if (brojPobedaA > brojPobedaB) {
			myfile << "Konacni pobednik je igrac A!" << std::endl;
		}
		else if (brojPobedaB > brojPobedaA) {
			myfile << "Konacni pobednik je igrac B!" << std::endl;
		}
		else {
			myfile << "NERESENO!" << std::endl;
		}
	}
	
	myfile.close();
}

void clearOutFile(std::string fileName)
{
	std::ofstream myfile(fileName, std::ofstream::out | std::ofstream::trunc); //cistim fajl
	myfile.close();
}
