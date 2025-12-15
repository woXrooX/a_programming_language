#include <iostream>
#include <string>

#include "modules/helpers.hpp"
#include "modules/Token.hpp"
#include "modules/Lexer.hpp"

int main(int argc, char** argv) {
	// Simple argument handling:
	// APL = a programming language
	// APLC = a programming language compiler
	// ./APLC input.a

	if (argc != 2) {
		std::cerr << "Usage: APLC <input file>\n";
		return 1;
	}

	std::string input_path = argv[1];
	std::string input_string = woXrooX::read_file(input_path);

	woXrooX::Lexer lexer(input_string);
	std::vector<woXrooX::Token> tokens = lexer.tokenize();

	return 0;
}
