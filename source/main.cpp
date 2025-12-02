#include <iostream>
#include <string>

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

	std::cout << "APLC: compiling " << input_path << "\n";

	return 0;
}
