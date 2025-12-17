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

			while (this->is_at_end() == false) {
				this->skip_whitespace_and_comments();

				if (this->is_at_end()) break;

				if (this->try_identifier_or_keyword(tokens) == true) continue;
				if (this->try_integer_literal(tokens) == true) continue;
				if (this->try_operator(tokens) == true) continue;
				if (this->try_punctuation(tokens) == true) continue;

				std::cerr
					<< "APLC: lexer: unexpected character '"
					<< this->peek()
					<< "' @ "
					<< this->line
					<< ':'
					<< this->column
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

			this->dump_tokens(tokens);

			return tokens;
		}

	private:
		const std::string& source;
		std::size_t index;
		std::size_t line;
		std::size_t column;


		/////////// Helpers

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

			char current_character = this->source[this->index++];

			if (current_character == '\n') {
				++this->line;
				this->column = 1;
			}

			else ++this->column;

			return current_character;
		}

		// Helper for 2-char operators
		bool match_next_character(char expected) {
			if (this->is_at_end()) return false;
			if (this->peek() != expected) return false;

			this->advance();
			return true;
		}

		void skip_whitespace_and_comments() {
			for (;;) {
				if (this->is_at_end()) return;

				char current_character = this->peek();

				// Whitespace
				if (
					current_character == ' ' ||
					current_character == '\t' ||
					current_character == '\r' ||
					current_character == '\n'
				) {
					this->advance();
					continue;
				}

				// Single-line comment: // ...
				if (
					current_character == '/' &&
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

		/////////// Handlers

		bool try_identifier_or_keyword(std::vector<Token>& tokens) {
			char current_character = this->peek();

			// First character must be [a-zA-Z_]
			if (
				(current_character >= 'a' && current_character <= 'z') == false &&
				(current_character >= 'A' && current_character <= 'Z') == false &&
				current_character != '_'
			) return false;

			std::size_t start_line = this->line;
			std::size_t start_column = this->column;

			std::string lexeme;

			// Consume first character
			lexeme.push_back(this->advance());

			// Consume the rest: [a-zA-Z0-9_]*
			while (this->is_at_end() == false) {
				char next_character = this->peek();

				if (
					(next_character >= 'a' && next_character <= 'z') ||
					(next_character >= 'A' && next_character <= 'Z') ||
					(next_character >= '0' && next_character <= '9') ||
					next_character == '_'
				) {
					lexeme.push_back(this->advance());
					continue;
				}

				break;
			}

			// Keywords vs identifier
			Token_Type token_type = Token_Type::identifier;

			if (lexeme == "int") token_type = Token_Type::keyword_int;
			else if (lexeme == "bool") token_type = Token_Type::keyword_bool;
			else if (lexeme == "if") token_type = Token_Type::keyword_if;
			else if (lexeme == "else") token_type = Token_Type::keyword_else;
			else if (lexeme == "while") token_type = Token_Type::keyword_while;
			else if (lexeme == "return") token_type = Token_Type::keyword_return;

			tokens.emplace_back(token_type, lexeme, start_line, start_column);

			return true;
		}

		bool try_integer_literal(std::vector<Token>& tokens) {
			char current_character = this->peek();

			// First character must be [0-9]
			if (
				current_character >= '0' &&
				current_character <= '9'
			) {
				std::size_t start_line = this->line;
				std::size_t start_column = this->column;

				std::string lexeme;

				// Consume first digit
				lexeme.push_back(this->advance());

				// Consume remaining digits
				while (this->is_at_end() == false) {
					char next_character = this->peek();

					if (
						next_character >= '0' &&
						next_character <= '9'
					) {
						lexeme.push_back(this->advance());
						continue;
					}

					break;
				}

				tokens.emplace_back(Token_Type::integer_literal, lexeme, start_line, start_column);

				return true;
			}

			return false;
		}

		bool try_operator(std::vector<Token>& tokens) {
			char current_character = this->peek();

			std::size_t start_line = this->line;
			std::size_t start_column = this->column;

			// Single-character operators

			if (current_character == '+') {
				this->advance();
				tokens.emplace_back(Token_Type::plus, "+", start_line, start_column);
				return true;
			}

			if (current_character == '-') {
				this->advance();
				tokens.emplace_back(Token_Type::minus, "-", start_line, start_column);
				return true;
			}

			if (current_character == '*') {
				this->advance();
				tokens.emplace_back(Token_Type::star, "*", start_line, start_column);
				return true;
			}

			if (current_character == '/') {
				this->advance();
				tokens.emplace_back(Token_Type::forward_slash, "/", start_line, start_column);
				return true;
			}


			// One-or-two-character operators (longest match wins)

			if (current_character == '=') {
				this->advance();
				if (this->match_next_character('=') == true) tokens.emplace_back(Token_Type::equal_equal, "==", start_line, start_column);
				else tokens.emplace_back(Token_Type::equal, "=", start_line, start_column);
				return true;
			}

			if (current_character == '!') {
				this->advance();
				if (this->match_next_character('=') == true) tokens.emplace_back(Token_Type::bang_equal, "!=", start_line, start_column);
				else tokens.emplace_back(Token_Type::bang, "!", start_line, start_column);
				return true;
			}

			if (current_character == '<') {
				this->advance();
				if (this->match_next_character('=') == true) tokens.emplace_back(Token_Type::less_equal, "<=", start_line, start_column);
				else tokens.emplace_back(Token_Type::less, "<", start_line, start_column);
				return true;
			}

			if (current_character == '>') {
				this->advance();
				if (this->match_next_character('=') == true) tokens.emplace_back(Token_Type::greater_equal, ">=", start_line, start_column);
				else tokens.emplace_back(Token_Type::greater, ">", start_line, start_column);
				return true;
			}



			// Two-character-only operators (do NOT consume unless we are sure)

			if (
				current_character == '&' &&
				this->peek_next() == '&'
			) {
				this->advance();
				this->advance();
				tokens.emplace_back(Token_Type::and_and, "&&", start_line, start_column);
				return true;
			}

			if (
				current_character == '|' &&
				this->peek_next() == '|'
			) {
				this->advance();
				this->advance();
				tokens.emplace_back(Token_Type::or_or, "||", start_line, start_column);
				return true;
			}

			return false;
		}

		bool try_punctuation(std::vector<Token>& tokens) {
			char current_character = this->peek();
			std::size_t start_line = this->line;
			std::size_t start_column = this->column;

			if (current_character == '(') {
				this->advance();
				tokens.emplace_back(Token_Type::left_parenthesis, "(", start_line, start_column);

				return true;
			}

			if (current_character == ')') {
				this->advance();
				tokens.emplace_back(Token_Type::right_parenthesis, ")", start_line, start_column);

				return true;
			}

			if (current_character == '{') {
				this->advance();
				tokens.emplace_back(Token_Type::left_curly_brace, "{", start_line, start_column);
				return true;
			}

			if (current_character == '}') {
				this->advance();
				tokens.emplace_back(Token_Type::right_curly_brace, "}", start_line, start_column);
				return true;
			}

			if (current_character == ';') {
				this->advance();
				tokens.emplace_back(Token_Type::semicolon, ";", start_line, start_column);
				return true;
			}

			if (current_character == ',') {
				this->advance();
				tokens.emplace_back(Token_Type::comma, ",", start_line, start_column);
				return true;
			}

			return false;
		}


		/////////// TMP

		const char* token_type_to_string(Token_Type token_type) const {
			switch (token_type) {
				case Token_Type::end_of_file: return "end_of_file";

				case Token_Type::identifier: return "identifier";
				case Token_Type::integer_literal: return "integer_literal";

				case Token_Type::keyword_int: return "keyword_int";
				case Token_Type::keyword_bool: return "keyword_bool";
				case Token_Type::keyword_if: return "keyword_if";
				case Token_Type::keyword_else: return "keyword_else";
				case Token_Type::keyword_while: return "keyword_while";
				case Token_Type::keyword_return: return "keyword_return";

				case Token_Type::left_parenthesis: return "left_parenthesis";
				case Token_Type::right_parenthesis: return "right_parenthesis";
				case Token_Type::left_curly_brace: return "left_curly_brace";
				case Token_Type::right_curly_brace: return "right_curly_brace";
				case Token_Type::semicolon: return "semicolon";
				case Token_Type::comma: return "comma";

				case Token_Type::plus: return "plus";
				case Token_Type::minus: return "minus";
				case Token_Type::star: return "star";
				case Token_Type::forward_slash: return "forward_slash";
				case Token_Type::equal: return "equal";
				case Token_Type::bang: return "bang";
				case Token_Type::less: return "less";
				case Token_Type::greater: return "greater";

				case Token_Type::equal_equal: return "equal_equal";
				case Token_Type::bang_equal: return "bang_equal";
				case Token_Type::less_equal: return "less_equal";
				case Token_Type::greater_equal: return "greater_equal";
				case Token_Type::and_and: return "and_and";
				case Token_Type::or_or: return "or_or";
			}

			return "unknown_token_type";
		}

		void dump_tokens(const std::vector<Token>& tokens) const {
			std::cout << "---- TOKEN DUMP ----\n";

			for (const Token& token : tokens) {
				std::cout
					<< token.line
					<< ':'
					<< token.column
					<< "  "
					<< this->token_type_to_string(token.type)
					<< "  \""
					<< token.lexeme
					<< "\"\n";
			}

			std::cout << "--------------------\n";
		}
	};
}

#endif

