//Program Author: Thomas Robasciotti
//
//This program is an arithmetic expression evaluator built to fulfill
//the requirements outlined by the Plexsys technical interview assignment.
//
//It uses a Recursive Descent Parse Tree to evaluate generated Tokens that 
//represent pieces of a larger expression inputted by a user. The design of 
//the parse tree logic was inspired by Thomas Kim (https://www.youtube.com/channel/UCpQ9kTWohSlFgXIKJmFc4kA)
//and https://unclechromedome.org/c++-tutorials/expression-parser/index.html.
//
//Below is the entry point of the program which creates and launches an Evaluator.

#include "evaluator.h"

int main() {
	Evaluator evaluator;

	evaluator.launch();
}
