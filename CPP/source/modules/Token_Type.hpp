#ifndef TOKEN_TYPE_HPP
#define TOKEN_TYPE_HPP

namespace woXrooX {

	enum class Token_Type {
		// Special

		end_of_file,


		// Identifiers & literals

		identifier,
		integer_literal,


		// Keywords

		keyword_int,
		keyword_bool,
		keyword_if,
		keyword_else,
		keyword_while,
		keyword_return,


		// Punctuation / delimiters

		// (
		left_parenthesis,

		// )
		right_parenthesis,

		// {
		left_curly_brace,

		// }
		right_curly_brace,

		// ;
		semicolon,

		// ,
		comma,


		// Operators

		// +
		plus,

		// -
		minus,

		// *
		star,

		// /
		forward_slash,

		// =
		equal,

		// !
		bang,

		// <
		less,

		// >
		greater,

		// ==
		equal_equal,

		// !=
		bang_equal,

		// <=
		less_equal,

		// >=
		greater_equal,

		// &&
		and_and,

		// ||
		or_or
	};

}

#endif
