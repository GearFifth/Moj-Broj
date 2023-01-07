#include "round.h"

//Konstruktori
Round::Round(std::vector<std::string>& ponudjeniBrojevi, int &trazeniBroj, Igrac &igrac, int &br):
	ponudjeniBrojevi(ponudjeniBrojevi), trazeniBroj(trazeniBroj), prviIgracNaPotezu(igrac),
	brojRunde(br), dobijeniBrojA(0), dobijeniBrojB(0), dobijeniBrojProg(0), pobednik("Nema pobednika") {}

Round::Round(std::vector<std::string>& ponudjeniBrojevi, int& trazeniBroj) :
	ponudjeniBrojevi(ponudjeniBrojevi), trazeniBroj(trazeniBroj), prviIgracNaPotezu(A),
	brojRunde(1), dobijeniBrojA(0), dobijeniBrojB(0), dobijeniBrojProg(0), pobednik("Nema pobednika") {}


// --------------------- Getteri i setteri ---------------------

int Round::getBrojRunde()
{
	return brojRunde;
}

void Round::setBrojRunde(int br)
{
	brojRunde = br;
}

Igrac Round::getPrviIgracNaPotezu()
{
	return prviIgracNaPotezu;
}

//Brojevi
std::vector<std::string> Round::getPonudjeniBrojevi()
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

void Round::setDobijeniBrojA(int &br) {
	dobijeniBrojA = br;
}

int Round::getDobijeniBrojA() {
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

void Round::setDobijeniBrojB(int &br) {
	dobijeniBrojB = br;
}

int Round::getDobijeniBrojB() {
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

void Round::setDobijeniBrojProg(int &br) {
	dobijeniBrojProg = br;
}

int Round::getDobijeniBrojProg() {
	return dobijeniBrojProg;
}

//Pobednik
std::string Round::getPobednik()
{
	return pobednik;
}

void Round::setPobednik(std::string pob)
{
	pobednik = pob;
}

// ---------------------- RACUNANJE BROJA -----------------------
//Parametri su sledeci
// 1 - brojevi pomocu kojih racunamo
// 2 - broj koji treba da dobijemo
// 3 - pokazivac na trenutnu najblizu vrednost resenja
// 4 - pokazivac na izraz trenutne najblize vrednosti

//Funkcija radi tako sto trazenjem azurira pokazivace unutar rekurzije
void Round::findSolution(std::vector<std::string>& ponudjeniBrojevi, int& trazeniBroj, int* pronadjenaVrednost, std::string* pronadjenIzraz) {

	Calculator<double> calc = Calculator<double>();
	int velicina = ponudjeniBrojevi.size();

	//Pravim kombinacije i pozivam dok ne dodjem do nekog od navedenih slucajeva
	//Uslovi za izlaz iz rekurzije
	if (pronadjenIzraz->size() != 0) {
		//Ukoliko je pronadjen izraz izlazimo iz rekurzije
		if (*pronadjenaVrednost == trazeniBroj) {
			return;
		}
	}
	if (velicina == 1) {
		//Ukoliko smo iskoristili sve brojeve
		return;
	}

	std::vector<std::string> noviNiz;
	std::vector<std::string>::iterator iter1, iter2, iter3;
	std::string e1, e2, temp;
	double num;
	bool swap; //Oznacava da li se swap dogodio

	//Iteriram kroz sve parove ucitanih brojeva (e1,e2)

	for (iter1 = ponudjeniBrojevi.begin(); iter1 != ponudjeniBrojevi.end() - 1; iter1++) {
		for (iter2 = iter1 + 1; iter2 != ponudjeniBrojevi.end(); iter2++) {
			swap = false;
			e1 = *iter1;
			e2 = *iter2;

			//Primenjujem svaku operaciju {'+', '-', '*', '/'} :
			for (char op : { '+', '-', '*', '/'}) {
			PETLJA:

				std::string newExpr = e1 + op + e2;

				num = calc.calculate(newExpr + ";q");

				

				//Da bi izbegli (9/4) itd.
				if (op == '/') {
					if ((trunc(num) != num)) {
						if (!swap) {
							goto SWAP;
						}
						continue;
					}
					//Jer se dobije isti broj
					else if (e2 == "1") {
						continue;
					}
				}
				//kada je broj negativan ne racunamo ga
				else if (op == '-') {
					if (num < 0) {
						if(!swap) {
							goto SWAP;
						}
						continue;
					}
				}
				//Jer se dobije isti broj
				else if (op == '*') {
					if (e1 == "1" || e2 == "1") {
						continue;
					}
				}

				//Da bi izbegli deljenje nulom
				if (num == 0) {
					continue;
				}
				
				else if (num == trazeniBroj) {
					//Postavljam resenje
					*pronadjenaVrednost = num;
					*pronadjenIzraz = newExpr;
					return;
				}
				//Trazimo najpriblizniji broj
				else if (abs(num - trazeniBroj) < abs(*pronadjenaVrednost - trazeniBroj)) {
					*pronadjenaVrednost = num;
					*pronadjenIzraz = newExpr;
				}

				// ---------------- Ako nije pronadjen trazimo dublje (pozivamo rekurziju) ----------------
				//1. formiramo novi niz sa novim izrazom, bez koriscenih brojeva
				//primer: ako smo koristili (2 + 3), iz originalnog niza brojeva brisemo 2 i 3

				// ------------------- V1 --------------------
				noviNiz = ponudjeniBrojevi; //kopiram
				noviNiz.push_back("(" + newExpr + ")"); //Smestam novi izraz obgrljen zagradama na kraju
				noviNiz.erase(noviNiz.begin() + (iter1-ponudjeniBrojevi.begin())); //Brisem e1
				noviNiz.erase(noviNiz.begin() + (iter2 - ponudjeniBrojevi.begin()) -1); //Brisem e2 (ide -1 posto je sad prvi obrisan)

				//2. trazimo resenje pomocu izmenjenog niza brojeva
				findSolution(noviNiz, trazeniBroj, pronadjenaVrednost, pronadjenIzraz);

				//Radim swap elemenata ako su u pitanju '/' i '-'
				SWAP:
				if (op == '/' || op == '-') {
					if (!swap) {
						swap = true;
						temp = e1;
						e1 = e2;
						e2 = temp;
						goto PETLJA;
					}
				}

			}
		}
	}
}

bool Round::validateInput(std::string unos)
{
	//Mapa brojeva gde inicijalno sve postavljam na false
	//true znaci da je broj iskoristen
	std::map<std::string, int> mapaBrojeva;
	for (std::string broj : ponudjeniBrojevi) {
		if (mapaBrojeva.find(broj) != mapaBrojeva.end()) {
			mapaBrojeva[broj]++;
		}
		else {
			mapaBrojeva[broj] = 1;
		}
		
	}
	std::string broj;

	for (int i = 0; i < unos.size(); i++) {
		if (isdigit(unos[i])) {
			broj += unos[i];
		}
		else {
			if (broj != "") {
				//Unet broj koji nije ponudjen
				if (mapaBrojeva.find(broj) == mapaBrojeva.end()) {
					return false;
				}
				//broj unet vise puta nego sto sme
				else if (mapaBrojeva[broj] == 0) {
					return false;
				}
				mapaBrojeva[broj]--;
				broj = "";//clear
			}	
		}

		if (i == unos.size()-1) {
			if (isdigit(unos[i])) {
				if (broj != "") {
					//Unet broj koji nije ponudjen
					if (mapaBrojeva.find(broj) == mapaBrojeva.end()) {
						return false;
					}
					//Isti broj unet vise puta
					else if (mapaBrojeva[broj] == 0) {
						return false;
					}
				}
			}
		}	
	}
	return true;
}


