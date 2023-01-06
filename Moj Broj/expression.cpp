#include "expression.h"

Expression::Expression(): expr("") {}

Expression::Expression(std::string &num) : expr(num) {}

Expression::Expression(std::string& num, std::map<std::string, bool> &usedNumbers):
usedNumbers(usedNumbers), expr(num) {}

Expression::Expression(Expression& e): usedNumbers(e.usedNumbers), expr(e.expr) {}

//Expression::Expression(std::string completeExpr, std::string el1, std::string el2):
//	expr(completeExpr)
//{
//	usedNumbers[el1] = true;
//	usedNumbers[el2] = true;
//}
//
//Expression::Expression(std::string completeExpr, Expression el1, std::string el2):
//	expr(completeExpr)
//{
//	usedNumbers.insert(el1.usedNumbers.begin(), el1.usedNumbers.end());
//	usedNumbers[el2] = true;
//}
//
//Expression::Expression(std::string completeExpr, std::string el1, Expression el2):
//	expr(completeExpr)
//{
//	usedNumbers[el1] = true;
//	usedNumbers.insert(el2.usedNumbers.begin(), el2.usedNumbers.end());
//}
//
//Expression::Expression(std::string completeExpr, Expression el1, Expression el2):
//	expr(completeExpr)
//{
//	usedNumbers.insert(el1.usedNumbers.begin(), el1.usedNumbers.end());
//	usedNumbers.insert(el2.usedNumbers.begin(), el2.usedNumbers.end());
//}

bool Expression::isUsed(std::string &num)
{
	try {
		return usedNumbers.at(num);
	}
	catch(std::out_of_range) {
		return false;
	}
	
}

bool Expression::isUsed(Expression &e)
{
	for (std::map<std::string, bool>::iterator iter = e.usedNumbers.begin(); iter != e.usedNumbers.end(); ++iter)
	{
		if (usedNumbers[iter->first] == true) {
			return true;
		}
	}
	return false;
}

std::string Expression::getExpr()
{
	return expr;
}

void Expression::setExpr(std::string& ex)
{
	expr = ex;
}

std::map<std::string, bool> Expression::getUsedNumbers()
{
	return usedNumbers;
}

void Expression::setUsedNumbers(std::map<std::string, bool> &newUsedNumbers)
{
	usedNumbers = newUsedNumbers;
}

Expression mergeExpressions(Expression& e1, Expression& e2, char &op)
{
	std::map<std::string, bool> usedNumbers;
	std::string expr = "(" + e1.getExpr() + op + e2.getExpr() + ")";

	usedNumbers.insert(e1.getUsedNumbers().begin(), e1.getUsedNumbers().end());
	usedNumbers.insert(e2.getUsedNumbers().begin(), e2.getUsedNumbers().end());

	return Expression(expr, usedNumbers);
}
