#include "expression_parser.h"

namespace expression_parser
{
	//The following series of functions implement a Recursive Descent Parse Tree for Token evaluation. 
	//
	//Design & implementation inspired by Thomas Kim (https://www.youtube.com/channel/UCpQ9kTWohSlFgXIKJmFc4kA)
	//and https://unclechromedome.org/c++-tutorials/expression-parser/index.html
	//
	//
	//b_next_token tells the parser if it should process the
	//next Token as part of the evaluation (true) or not (false).
	//
	//The first Token is always passed with a false value. 
	//
	//If the first Token is valid (i.e. TokenType::num, TokenType::subt (negative number),
	//or TokenType::open), the ExpressionParser::primary() function will read the next Token
	//and subsequent Tokens will be passed with a true value.
	//
	//If the first Token is not valid, an error message is displayed and processing stops.
	//In this case, the program will return a result of 0 or the result of valid expressions
	//found prior to the error. These results are not guaranteed to be accurate and should
	//be ignored.

	using namespace tokenizer;

	//handles addition and subtraction
	double ExpressionParser::add_expression(bool b_next_token)
	{
		double result = this->mult_expression(b_next_token);

		switch (this->mcTokenizer.getCurrentToken().type)
		{
			//'+'
			case TokenType::add:
				result += this->add_expression(true);
				return result;
			//'-'
			case TokenType::subt:
				result -= this->add_expression(true);
				return result;
			default:
				return result;
		}
	}

	//handles multiplication, division, and exponents
	double ExpressionParser::mult_expression(bool b_next_token)
	{
		double result = primary(b_next_token);

		switch (this->mcTokenizer.getCurrentToken().type)
		{
			//'*'
			case TokenType::mult:
				result *= this->primary(true);
				return result;
			//'/'
			case TokenType::div:
				result /= this->primary(true);
				return result;
			//'^'
			case TokenType::exp:
				result = pow(result, this->primary(true));
				return result;
			default:
				return result;
		}
	}

	//handles digits, unary minus (negative), and parentheses
	double ExpressionParser::primary(bool b_next_token)
	{
		if (b_next_token)
		{
			this->mcTokenizer.getNextToken();
		}

		switch (this->mcTokenizer.getCurrentToken().type)
		{
			//digit or '.'
			case TokenType::num:
			{
				double result = this->mcTokenizer.getCurrentToken().number;

				this->mcTokenizer.getNextToken();

				return result;
			}
			//unary '-'
			case TokenType::subt:
				return -this->primary(true);
			//'('
			case TokenType::open:
			{
				double result = this->add_expression(true);

				//no matching closing parentheses ')' found
				if (this->mcTokenizer.getCurrentToken().type != TokenType::close)
				{
					std::cerr << "Syntax error: Missing one or more \')\'" << std::endl;
				}

				this->mcTokenizer.getNextToken();

				return result;
			}

			default:
			{
				//If we get here without a valid TokenType, there is a syntax error
				std::cerr << "Syntax Error" << std::endl;
				return 0;
			}
		}
	}

	void ExpressionParser::parse()
	{
		//This loop triggers the first Token read and continues until TokenType::done is found. 
		//First token is pased with false value as explained above. 
		for (this->mcTokenizer.getNextToken(); this->mcTokenizer.getCurrentToken().type != TokenType::done; this->mcTokenizer.getNextToken())
		{
			std::cout << "Result: " << this->add_expression(false) << std::endl;
			return;
		}
	}
}
