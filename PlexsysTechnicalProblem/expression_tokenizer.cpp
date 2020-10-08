#pragma once
#include "expression_tokenizer.h"

namespace tokenizer {

	Token& Tokenizer::getCurrentToken()
	{
		return this->m_current_token;
	}

	//Generates tokens based on user input. The tokens
	//contain a number (double) and a type (TokenType)
	//
	//e.x. the input "1+1" becomes three tokens:
	//Token 1. {type: TokenType::num , number: 1.0}
	//Token 2. {type: TokenType::add , number: 0}
	//Token 3. {type: TokenType::num , number: 1.0}
	//
	//When no input remains in the stream or an unrecognized 
	//value is detected, returns TokenType::done to stop expression
	//evaluation
	Token& Tokenizer::getNextToken()
	{
		char next_character = 0;
		this->getNextChar(next_character);
		switch (next_character)
		{
		case 0: //no input remains, trigger stop
			this->m_current_token = { TokenType::done };
			return this->m_current_token;
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '(':
		case ')':

			this->m_current_token = { (TokenType)next_character };
			return this->m_current_token;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
			//next_character is a number, put it back into the 
			//std::istringstream and place in Token.number
			(*this->m_input_stream).putback(next_character);
			(*this->m_input_stream) >> this->m_current_token.number;
			this->m_current_token.type = TokenType::num;
			return this->m_current_token;
		default:
			this->m_current_token.type = TokenType::done;
			return this->m_current_token;
		}
	}

	std::istringstream& Tokenizer::getNextChar(char& character)
	{
		//read through std::istringstream for next non-blank character
		while ((*this->m_input_stream).get(character) && std::isblank(character));

		return *this->m_input_stream;
	}
}
