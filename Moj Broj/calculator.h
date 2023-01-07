#pragma once
#include <string>
#include <exception>
#include <iostream>
#include <sstream>
#include <type_traits>

template <typename T>
class Calculator {
public:
	Calculator();

	//Racuna vrednost izraza iz 'ss'
	//Baca exception invalid_argument u slucaju lose unetog izraza
	T calculate(std::string izraz); 

	//---------------- Formalna gramatika ----------------
	T number(); //N -> realan broj
	T primary(); //P -> moze biti N ili (E)
	T term(); //množi,deli
	T expression(); //E

protected:
	//---------------- Unutrasnje klase ----------------
	//Predstavlja broj ili operaciju
	class Token {
	public:
		Token(char ch, T val);
		Token(char ch);
		Token();
		char kind;
		T value;
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
};