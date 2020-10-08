#pragma once
#include <algorithm>
#include <sstream>
#include "expression_parser.h"

//This file defines the Evaluator class which is
//used to accept user input and launch the ExpressionParser.

class Evaluator
{
public:
	void launch();
	void evaluate(std::istringstream& expression);
};
