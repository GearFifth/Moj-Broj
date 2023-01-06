#include "calculator.h"

//---------------------- ERRORS ----------------------
void error(std::string error_type) {
	std::cout << error_type << "\n";
}

void error(std::string s, std::string s1) {
	std::cout << s + s1 << "\n";
}

//-------------------- TOKEN --------------------
Calculator::Token::Token(char ch, double val) : kind(ch), value(val) {}
Calculator::Token::Token(char ch) : kind(ch), value(0) {}
Calculator::Token::Token() : kind('x'), value(0) {}



//-------------------- TOKEN STREAM --------------------
Calculator::TokenStream::TokenStream(Calculator& cal) : buffer(), full(false), parent(cal) {}

Calculator::Token Calculator::TokenStream::getToken()
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

		double val;
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

void Calculator::TokenStream::putBack(Token token)
{
	buffer = token;
	full = true;
}



//-------------------- KALKULATOR --------------------
Calculator::Calculator() :result(NULL), ss(), ts(*this) {} //konstruktor

// ----- Formalna gramatika -----
double Calculator::number()
{
	Token token = ts.getToken();
	if (token.kind != '8')
		throw std::invalid_argument("Expected a number");
	return token.value;
}

double Calculator::primary()
{
	Token token = ts.getToken();
	switch (token.kind) {
	case '(': {
		//u ovom slucaju rekurzivno ponovo ucitava izraz pozivom funkcije expression
		double lval = expression();
		token = ts.getToken();

		//Obavezna provera da li se zagrada zatvorila
		if (token.kind != ')')
			error("Unmatched '('");
		return lval;
	}
	default:
		ts.putBack(token);
		return number(); //Ucitava realan broj N
	}
}

double Calculator::term()
{
	double lval = primary();

	while (true) {
		Token token = ts.getToken();

		switch (token.kind) {
		case '*':
			lval *= primary();
			break;
		case '/':
			lval /= primary();
			break;
		default:
			ts.putBack(token);
			return lval;
		}
	}
}

double Calculator::expression()
{
	double lval = term();

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

double Calculator::calculate(std::string izraz)
{
	ss = std::istringstream(izraz);

	try {
		while (true) {

			double lval = 0;
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
}

