#pragma once
#include <string>
#include <exception>
#include <iostream>
#include <sstream>
//#include <vector>

class Calculator {
public:
	Calculator();
	double calculate(std::string izraz); //Racuna vrednost izraza iz 'ss'

	//---------------- Formalna gramatika ----------------
	double number(); //N -> realan broj
	double primary(); //P -> moze biti N ili (E)
	double term();
	double expression(); //E

	//Errori
	friend void error(std::string error_type);
	friend void error(std::string s, std::string s1);

protected:
	//---------------- Unutrasnje klase ----------------
	//Predstavlja broj ili operaciju
	class Token {
	public:
		Token(char ch, double val);
		Token(char ch);
		Token();
		char kind;
		double value;
	};

	//Niz Tokena
	class TokenStream {
	public:
		TokenStream(Calculator&);
		Token getToken();

		//Vraca procitan token nazad u niz(buffer)
		void putBack(Token token);

	protected:
		Token buffer;
		bool full;

		//Referenca na roditelja
		Calculator& parent;
	};

	//---------------- Atributi ----------------
	TokenStream ts;
	std::istringstream ss; //Ovde smestam izraz koji racunam
	double result;
};