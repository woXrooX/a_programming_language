#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>

#include "Token.hpp"

namespace woXrooX {

	class Lexer {
	public:
		Lexer(
			const std::string& source
		) :
			source(source),
			index(0),
			line(1),
			column(1)
		{}

		std::vector<Token> tokenize() {
			std::vector<Token> tokens;

			// Temporary stub: just emit an EOF token so things compile & run.
			tokens.emplace_back(
				Token_Type::end_of_file,
				"",
				line,
				column
			);

			return tokens;
		}

	private:
		const std::string& source;
		std::size_t index;
		std::size_t line;
		std::size_t column;
	};

}

#endif
