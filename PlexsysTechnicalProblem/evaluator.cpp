#include <algorithm>
#include "evaluator.h"
#include "expression_parser.h"

//The main user interface loop that drives the program.
//
//Handles the user input and checks for obviously invalid 
//expressions (i.e. alphabetic characters, empty string) and 
//exit command. If input is valid, it copies the input to a 
//std::istringstream for evaluation by the ExpressionParser.
void Evaluator::launch()
{
	std::cout << "Welcome to the arithmetic expression evaluator!" << std::endl;
	std::cout << "\nThis evaluator supports the following operations: '+', '-', '*', '/', '^' as well as negative & floating point numbers." << std::endl;
	std::cout << "\nPlease wrap individual expressions in parentheses for accurate results (ex. '3+2-5*3^2' --> '(3+2)-(5*(3^2))')" << std::endl;
	std::cout << "\nHere are a few expample expressions to try:" << std::endl;
	std::cout << "1 + 1\n(3 + 4) * 6\n(1 * 4) + (5 * 2)" << std::endl;
	std::cout << "\nType EXIT to quit" << std::endl;

	while (true)
	{
		//Placing input into a std::string object instead of evaluating
		//expresisons directly from std::cin makes validating user input 
		//easier and minimizes parsing errors. It also allows the program
		//to handle the EXIT case cleanly without creating an ExpressionParser object.
		std::string user_input;
		std::cout << "\nPlease enter an expression to evaluate: ";
		std::getline(std::cin, user_input);

		if (user_input.empty())
		{
			std::cout << "The expression cannot be blank." << std::endl;
		}

		else if (user_input.compare("exit") == 0 || user_input.compare("EXIT") == 0)
		{
			std::cout << "\nThank you! Shutting down..." << std::endl;
			return;
		}
		//Check for any alphabetic characters in user input, alert user
		else if (std::any_of(std::begin(user_input), std::end(user_input), ::isalpha))
		{
			std::cout << "Please enter only numeric or operational (+, -, *, /, ^, (, )) characters." << std::endl;
		}
		else
		{
			//good input, continue
			std::istringstream sstream(user_input);
			evaluate(sstream);
		}
	}
}

//Creates and starts an ExpressionParser
void Evaluator::evaluate(std::istringstream& expression)
{
	expression_parser::ExpressionParser parser(expression);
	parser.parse();
}
