#include <iostream>
#include <string>

#include "modules/helpers.hpp"

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

	return 0;
}
