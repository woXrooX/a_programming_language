#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <cstddef>

#include "Token_Type.hpp"

namespace woXrooX {

	class Token {
	public:
		const Token_Type type;
		const std::string lexeme;
		const std::size_t line;
		const std::size_t column;

		Token(
			Token_Type type,
			const std::string& lexeme,
			std::size_t line,
			std::size_t column
		) :
			type(type),
			lexeme(lexeme),
			line(line),
			column(column)
		{}
	};

}

#endif
