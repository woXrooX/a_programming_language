#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <iostream>

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

			while (!this->is_at_end()) {
				this->skip_whitespace_and_comments();

				if (this->is_at_end()) break;

				std::size_t start_line = this->line;
				std::size_t start_column = this->column;

				char c = this->advance();

				// Identifiers & keywords
				if (
					(c >= 'a' && c <= 'z') ||
					(c >= 'A' && c <= 'Z') ||
					c == '_'
				) {
					Token token = this->identifier_or_keyword(
						start_line,
						start_column,
						c
					);

					tokens.push_back(token);
					continue;
				}

				// Integer literal
				if (
					c >= '0' &&
					c <= '9'
				) {
					Token token = this->integer_literal(
						start_line,
						start_column,
						c
					);

					tokens.push_back(token);
					continue;
				}


				// Punctuation tokens

				if (c == '(') {
					tokens.emplace_back(
						Token_Type::left_parenthesis,
						"(",
						start_line,
						start_column
					);
					continue;
				}

				if (c == ')') {
					tokens.emplace_back(
						Token_Type::right_parenthesis,
						")",
						start_line,
						start_column
					);
					continue;
				}

				if (c == '{') {
					tokens.emplace_back(
						Token_Type::left_curly_brace,
						"{",
						start_line,
						start_column
					);
					continue;
				}

				if (c == '}') {
					tokens.emplace_back(
						Token_Type::right_curly_brace,
						"}",
						start_line,
						start_column
					);
					continue;
				}

				if (c == ';') {
					tokens.emplace_back(
						Token_Type::semicolon,
						";",
						start_line,
						start_column
					);
					continue;
				}

				if (c == ',') {
					tokens.emplace_back(
						Token_Type::comma,
						",",
						start_line,
						start_column
					);
					continue;
				}

				// For now, everything else is an error until we implement more cases
				std::cerr
					<< "APLC: lexer: unexpected character '"
					<< c
					<< "' @ "
					<< start_line
					<< ':'
					<< start_column
					<< '\n';

				break;
			}

			// Always add EOF token at the end
			tokens.emplace_back(
				Token_Type::end_of_file,
				"",
				this->line,
				this->column
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

		Token identifier_or_keyword(
			std::size_t start_line,
			std::size_t start_column,
			char first_character
		) {
			std::string lexeme;
			lexeme.push_back(first_character);

			// Consume [a-zA-Z0-9_]* after the first character
			while (!this->is_at_end()) {
				char c = this->peek();

				if (
					(c >= 'a' && c <= 'z') ||
					(c >= 'A' && c <= 'Z') ||
					(c >= '0' && c <= '9') ||
					c == '_'
				) lexeme.push_back(this->advance());

				else break;
			}

			// Decide if this lexeme is a keyword or identifier
			Token_Type token_type = Token_Type::identifier;

			if (lexeme == "int") token_type = Token_Type::keyword_int;
			else if (lexeme == "bool") token_type = Token_Type::keyword_bool;
			else if (lexeme == "if") token_type = Token_Type::keyword_if;
			else if (lexeme == "else") token_type = Token_Type::keyword_else;
			else if (lexeme == "while") token_type = Token_Type::keyword_while;
			else if (lexeme == "return") token_type = Token_Type::keyword_return;

			return Token(
				token_type,
				lexeme,
				start_line,
				start_column
			);
		}

		Token integer_literal(
			std::size_t start_line,
			std::size_t start_column,
			char first_character
		) {
			std::string lexeme;
			lexeme.push_back(first_character);

			while (!this->is_at_end()) {
				char c = this->peek();

				if (
					c >= '0' &&
					c <= '9'
				) lexeme.push_back(this->advance());

				else break;
			}

			return Token(
				Token_Type::integer_literal,
				lexeme,
				start_line,
				start_column
			);
		}
	};
}

#endif
