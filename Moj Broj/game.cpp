#include "game.h"
#include "files.h"

//Konstruktor
Game::Game(std::vector<Round>& rundeInp):
	runde(rundeInp), brojPobedaA(0), brojPobedaB(0) {
	clearOutFile("rezultati.txt");
}


// --------------------- Getteri i setteri ---------------------
void Game::setRunde(std::vector<Round>& runde)
{
	this->runde = runde;
}

std::vector<Round> Game::getRunde() {
	return runde;
}

//Igrac A
void Game::setBrojPobedaA(int br)
{
	brojPobedaA = br;
}

int Game::getBrojPobedaA()
{
	return brojPobedaA;
}

//Igrac B
void Game::setBrojPobedaB(int br)
{
	brojPobedaB = br;
}

int Game::getBrojPobedaB()
{
	return brojPobedaB;
}

// --------------------- Pokretanje igre ---------------------
void Game::start()
{
	std::vector<Round>::iterator iterRunde;
	Calculator<int> calc = Calculator<int>();

	for (iterRunde = runde.begin(); iterRunde != runde.end(); iterRunde++) {

		//Preuzimanje podataka runde
		Round trenutnaRunda = *iterRunde;
		std::vector<std::string> ponudjeniBrojevi = trenutnaRunda.getPonudjeniBrojevi();
		int trazeniBroj = trenutnaRunda.getTrazeniBroj();
		int brojRunde = trenutnaRunda.getBrojRunde();
		Igrac igracNaPotezu = trenutnaRunda.getPrviIgracNaPotezu();

		int pronadjenaVrednost = 0;
		std::string pronadjenIzraz = "";

		// ------------------------- Ispis u konzoli -------------------------
		std::cout << std::string(20, '-') << " MOJ BROJ " << std::string(20, '-') << std::endl;
		std::cout << "Runda: " << brojRunde << std::endl;
		std::cout << "Broj pobeda igraca A: " << brojPobedaA << std::endl;
		std::cout << "Broj pobeda igraca B: " << brojPobedaB << std::endl << std::endl;
		std::cout << "Ponudjeni brojevi: ";
		std::vector<std::string>::iterator it;
		for (it = ponudjeniBrojevi.begin(); it != ponudjeniBrojevi.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl << "Trazeni broj: " << trazeniBroj << std::endl;

		// ------------------------- Igraci na potezu -------------------------
		std::string unosIgraca; //Izraz koji je uneo igrac
		std::string igracStr; //pomocni string koji predstavlja igraca

		for (int i = 0; i < 2; i++) {	
			if (igracNaPotezu == B) {
				igracStr = "B";
			}
			else {
				igracStr = "A";
			}

			int rez;
			while (true) {
				std::cout << "Igrac " << igracStr << " unosi resenje: ";
				std::getline(std::cin, unosIgraca);

				//Proveravam da li je korisnik vise puta uneo broj ili je uneo neki broj koji ne postoji
				if (!trenutnaRunda.validateInput(unosIgraca)) {
					std::cout << "Unos nije dobar, pokusajte ponovo!" << std::endl;
					continue;
				}

				try {
					rez = calc.calculate(unosIgraca + ";q");
					if (igracNaPotezu == A) {
						trenutnaRunda.setDobijeniBrojA(rez);
						trenutnaRunda.setIzrazA(unosIgraca);
					}
					else {
						trenutnaRunda.setDobijeniBrojB(rez);
						trenutnaRunda.setIzrazB(unosIgraca);
					}

					std::cout << "Dobijen broj: " << rez << std::endl;
					if (rez == trazeniBroj) {
						std::cout << "POBEDNIK IGRAC " << igracStr << "!" << std::endl;
						trenutnaRunda.setPobednik(igracStr);
						dodajPobedu(igracNaPotezu);
						i++;
						break;
					}
					else {
						break;
					}
				}
				catch (std::invalid_argument) {
					std::cout << "Unos nije dobar, pokusajte ponovo!" << std::endl;
					continue;
				}
			}

			//Naredni igrac
			if (igracNaPotezu == A) {
				igracNaPotezu = B;
			}
			else {
				igracNaPotezu = A;
			}
		}
		
		// ------------------------- Racunanje programa -------------------------
		std::cout << "Program racuna..." << std::endl;
		//Racunanje vremena trazenja rezultata
		auto start = std::chrono::high_resolution_clock::now();
		trenutnaRunda.findSolution(ponudjeniBrojevi, trazeniBroj, &pronadjenaVrednost, &pronadjenIzraz);
		auto stop = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

		//update u rundi
		trenutnaRunda.setIzrazProg(pronadjenIzraz);
		trenutnaRunda.setDobijeniBrojProg(pronadjenaVrednost);

		//ispis
		std::cout << std::string(10, '*') << std::endl;
		std::cout << "Pronadjen broj: " << pronadjenaVrednost << std::endl;
		std::cout << "Pronadjen izraz: " << pronadjenIzraz << std::endl;
		std::cout << "Vreme trazenja rezultata: " << duration.count() << std::endl;
		std::cout << std::string(10, '*') << std::endl;

		// ------------ U slucaju da ni program ne nadje tacnu vrednost proveravamo ko je blizi od 2 igraca ------------
		if (pronadjenaVrednost != trazeniBroj) {
			//Razlika do tacnog broja
			int progDiff = abs(pronadjenaVrednost - trazeniBroj);
			int igracADiff = abs(trenutnaRunda.getDobijeniBrojA() - trazeniBroj);
			int igracBDiff = abs(trenutnaRunda.getDobijeniBrojB() - trazeniBroj);
			if (trenutnaRunda.getPrviIgracNaPotezu() == A) {
				if (igracADiff == progDiff) {
					std::cout << "POBEDNIK IGRAC A!" << std::endl;
					trenutnaRunda.setPobednik("A");
					dodajPobedu(A);
				}
				else if (igracBDiff == progDiff) {
					std::cout << "POBEDNIK IGRAC B!" << std::endl;
					trenutnaRunda.setPobednik("B");
					dodajPobedu(B);
				}
				else {
					std::cout << "NIJEDAN IGRAC NIJE POBEDIO!" << std::endl;
				}
			}
			else if (trenutnaRunda.getPrviIgracNaPotezu() == B) {
				if (igracBDiff == progDiff) {
					std::cout << "POBEDNIK IGRAC B!" << std::endl;
					trenutnaRunda.setPobednik("B");
					dodajPobedu(B);
				}
				else if (igracADiff == progDiff) {
					std::cout << "POBEDNIK IGRAC A!" << std::endl;
					trenutnaRunda.setPobednik("A");
					dodajPobedu(A);
				}
				else {
					std::cout << "NIJEDAN IGRAC NIJE POBEDIO!" << std::endl;
				}
			}
		}
		

		//Ispis podataka o rundi u output fajl
		writeRoundToFile(trenutnaRunda, "rezultati.txt");
		
		
	}

	//Ispis rezultata u output fajl
	writeResultToFile(brojPobedaA, brojPobedaB, "rezultati.txt"); 


	if (brojPobedaA > brojPobedaB) {
		std::cout << "KONACNI POBEDNIK JE IGRAC A!" << std::endl;
	}
	else if (brojPobedaB > brojPobedaA) {
		std::cout << "KONACNI POBEDNIK JE IGRAC B!" << std::endl;
	}
	else {
		std::cout << "NERESENO!" << std::endl;
	}
	
}

void Game::dodajPobedu(Igrac igrac)
{
	if (igrac == A) {
		brojPobedaA++;
	}
	else {
		brojPobedaB++;
	}
}


