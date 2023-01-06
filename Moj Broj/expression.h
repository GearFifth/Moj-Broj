#pragma once
#include <string>
#include <map>
#include <stdexcept>


class Expression {
public:
	Expression();
	Expression(std::string &num);
	Expression(std::string& num, std::map<std::string, bool> &usedNumbers);
	Expression(Expression &e);
	/*Expression(std::string &completeExpr, std::string el1, std::string el2);
	Expression(std::string &completeExpr, Expression el1, std::string el2);
	Expression(std::string &completeExpr, std::string el1, Expression el2);
	Expression(std::string &completeExpr, Expression el1, Expression el2);*/
	
	bool isUsed(std::string &num); //Proverava da li se dati broj koristi
	bool isUsed(Expression &e); //Proverava da li se neki broj iz izraza koristi

	std::string getExpr();
	void setExpr(std::string &ex);
	std::map<std::string, bool> getUsedNumbers();
	void setUsedNumbers(std::map<std::string, bool> &newUsedNumbers);
private:
	//Ovde cuvam koji brojevi se nalaze unutar izraza
	std::map<std::string, bool> usedNumbers;

	//Ceo izraz
	std::string expr; 
};

Expression mergeExpressions(Expression &e1, Expression& e2, char &op);