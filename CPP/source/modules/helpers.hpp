#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace woXrooX {

	inline std::string read_file(const std::string& input_path) {
		std::ifstream input_file(input_path);

		if (!input_file) {
			std::cerr << "APLC: error: could not open file '" << input_path << "'\n";
			return "";
		}

		std::ostringstream input_buffer;
		input_buffer << input_file.rdbuf();
		std::string input_string = input_buffer.str();

		std::cout << "APLC: source size = " << input_string.size() << " bytes\n";

		return input_string;
	}

}

#endif
