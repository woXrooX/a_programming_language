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

		// Past the end of the source?
		bool is_at_end() const {
			return index >= source.size();
		}

		// Look at the current character without moving
		char peek() const {
			// sentinel: "no more characters"
			if (is_at_end()) return '\0';

			return source[index];
		}

		// Look at the current character without moving.
		char peek_next() const {
			if (index + 1 >= source.size()) return '\0';

			return source[index + 1];
		}

		// Consume the current character, move index, update line/column, and return that character
		char advance() {
			if (is_at_end()) return '\0';

			char c = source[index++];

			if (c == '\n') {
				++line;
				column = 1;
			}

			else ++column;

			return c;
		}
	};
}

#endif
