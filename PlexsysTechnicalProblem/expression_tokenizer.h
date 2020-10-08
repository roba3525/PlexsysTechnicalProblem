#pragma once
#include <iostream>
#include <string>
#include <sstream>

//This file defines the Tokenizer class, the Token struct, 
//and the TokenType enum. Each of these structures are used
//in the translation of user input into Tokens that are then
//passed into the ExpressionParser for evaluation.

namespace tokenizer
{
	//Defines the types of Tokens the parser understands.
	//
	//Any input besides a real number or an arithmetic operation 
	//(+, -, *, /, (, ), ^) is not accepted.
	enum class TokenType : char
	{
		num, add = '+', subt = '-', mult = '*', div = '/',
		open = '(', close = ')', exp = '^', done
	};

	struct Token
	{
		TokenType type;
		double number;
	};

	class Tokenizer
	{
	private:
		//Data Members
		std::istringstream* m_input_stream;
		Token m_current_token;

	public:
		//Constructors
		Tokenizer() : m_input_stream{ nullptr }, m_current_token{ Token() } {}
		Tokenizer(std::istringstream& sstream) : m_input_stream{ &sstream }, m_current_token{ Token() } {}

		//Member Functions
		Token& getCurrentToken();
		Token& getNextToken();
		std::istringstream& getNextChar(char& character);
	};
}
