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

			this->skip_whitespace_and_comments();

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
			return this->index >= this->source.size();
		}

		// Look at the current character without moving
		char peek() const {
			// sentinel: "no more characters"
			if (this->is_at_end()) return '\0';

			return this->source[this->index];
		}

		// Look at the current character without moving.
		char peek_next() const {
			if (this->index + 1 >= this->source.size()) return '\0';

			return this->source[this->index + 1];
		}

		// Consume the current character, move index, update line/column, and return that character
		char advance() {
			if (this->is_at_end()) return '\0';

			char c = this->source[this->index++];

			if (c == '\n') {
				++this->line;
				this->column = 1;
			}

			else ++this->column;

			return c;
		}

		void skip_whitespace_and_comments() {
			for (;;) {
				if (this->is_at_end()) return;

				char c = this->peek();

				// Whitespace
				if (
					c == ' ' ||
					c == '\t' ||
					c == '\r' ||
					c == '\n'
				) {
					this->advance();
					continue;
				}

				// Single-line comment: // ...
				if (
					c == '/' &&
					this->peek_next() == '/'
				) {
					//// Consume the two slashes

					// first '/'
					this->advance();

					// second '/'
					this->advance();

					// Skip until newline or end of file
					while (
						!this->is_at_end() &&
						this->peek() != '\n'
					) this->advance();

					// If we hit a newline, advance once more to consume it
					if (
						!this->is_at_end() &&
						this->peek() == '\n'
					) this->advance();

					continue;
				}

				// If it's not whitespace or comment start, we're done
				return;
			}
		}
	};
}

#endif
