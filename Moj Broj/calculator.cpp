#include "calculator.h"

//-------------------- TOKEN --------------------

template <typename T> Calculator<T>::Token::Token(char ch, T val) : kind(ch), value(val) {}
template <typename T> Calculator<T>::Token::Token(char ch) : kind(ch), value(0) {}
template <typename T> Calculator<T>::Token::Token() : kind('x'), value(0) {}



//-------------------- TOKEN STREAM --------------------
template <typename T> Calculator<T>::TokenStream::TokenStream(Calculator& cal) : buffer(), full(false), parent(cal) {}

template <typename T> typename Calculator<T>::Token Calculator<T>::TokenStream::getToken()
{
	if (full) {
		full = false;
		return buffer;
	}

	char tmp;
	parent.ss >> tmp;

	switch (tmp) {
	case '0': case '1': case '2': case '3':
	case '4': case '5': case '6': case '7':
	case '8': case '9': case '.': {
		parent.ss.putback(tmp);

		T val;
		parent.ss >> val;
		return Token('8', val);
	}
	case '(':
	case ')':
	case ';':
	case 'q':
	case '+':
	case '*':
	case '-':
	case '/':
		return Token(tmp);
	default:
		throw std::invalid_argument("Bad token");
		return Token();
	}
}

template <typename T> void Calculator<T>::TokenStream::putBack(Token token)
{
	buffer = token;
	full = true;
}



//-------------------- KALKULATOR --------------------
template <typename T> Calculator<T>::Calculator() :result(NULL), ss(), ts(*this) {} //konstruktor

// ----- Formalna gramatika -----
template <typename T> T Calculator<T>::number()
{
	Token token = ts.getToken();
	if (token.kind != '8')
		throw std::invalid_argument("Expected a number");
	return token.value;
}

template <typename T> T Calculator<T>::primary()
{
	Token token = ts.getToken();
	switch (token.kind) {
	case '(': {
		//u ovom slucaju rekurzivno ponovo ucitava izraz pozivom funkcije expression
		T lval = expression();
		token = ts.getToken();

		//Obavezna provera da li se zagrada zatvorila
		if (token.kind != ')')
			throw std::invalid_argument("Unmatched '('");
		return lval;
	}
	default:
		ts.putBack(token);
		return number(); //Ucitava realan broj N
	}
}
template <typename T> T Calculator<T>::term()
{
	T lval = primary();

	while (true) {
		Token token = ts.getToken();

		switch (token.kind) {
		case '*':
			lval *= primary();
			break;
		case '/':
			if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
				lval /= primary();
			}
			else if(std::is_same<T, short>::value || std::is_same<T, int>::value || std::is_same<T, long long>::value) {
				T rval = primary();

				//Ukoliko radimo sa celobrojnim vrednostima i dobijemo ostatak to je greska
				if ((static_cast<long long>(lval) % static_cast<long long>(rval)) != 0) {
					throw std::invalid_argument("Nedozvoljeno deljenje");
				}
				lval /= rval;
			}
			break;
		default:
			ts.putBack(token);
			return lval;
		}
	}
}

template <typename T> T Calculator<T>::expression()
{
	T lval = term();

	while (true) {
		Token token = ts.getToken();

		switch (token.kind) {
		case '+':
			lval += term();
			break;
		case '-':
			lval -= term();
			break;
		default:
			ts.putBack(token);
			return lval;
		}
	}
}

template <typename T> T Calculator<T>::calculate(std::string izraz)
{
	ss = std::istringstream(izraz);

	try {
		while (true) {

			T lval = 0;
			//std::cout << ">";
			Token token = ts.getToken();
			if (token.kind == 'q')
				break;
			ts.putBack(token);

			lval = expression();

			token = ts.getToken();
			if (token.kind != ';')
				throw std::invalid_argument("Badly terminated expression");
			return lval;
		}
	}
	catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 1;
}

