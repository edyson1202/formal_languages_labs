#include "Token.h"

std::map<TokenType, std::string> Token::TokenTypeToString{
	{ LEFT_BRACE, "{" }, { RIGHT_BRACE, "}" }, { LEFT_PAREN, "(" }, { RIGHT_PAREN, ")" },
	{ PLUS, "+" }, { MINUS, "-" }, { SLASH, "/" }, { STAR, "*" },
	{ NOT, "!" }, { NOT_EQUAL, "!=" }, { EQUAL, "=" }, { EQUAL_EQUAL, "==" },
	{ LESS, "<" }, { LESS_EQUAL, "<=" }, { GREATER, ">" }, { GREATER_EQUAL, ">=" },

	{ IDENTIFIER, "identifier" }, { STRING, "string" }, { NUMBER, "number" },

	{ IF, "if" }, { ELSE, "else" }, { FOR, "for" }, { WHILE, "while" },
	{ TRUE, "true" }, { FALSE, "false" }, { INT, "int" }, { FLOAT, "float" },
	{ RETURN, "return" }, { THIS, "this" }
};
std::map<std::string, TokenType> Token::Keywords{
	{"if", IF},
	{"else",   ELSE},
	{"true", TRUE},
	{"false",  FALSE},
	{"for",    FOR},
	{"while", WHILE},
	{"return", RETURN},
	{"this",   THIS}
};