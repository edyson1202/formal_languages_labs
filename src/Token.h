#pragma once

#include <string>
#include <cstdint>
#include <iostream>
#include <map>

enum TokenType {
	// Punctuation
	LEFT_BRACE, RIGHT_BRACE, LEFT_PAREN, RIGHT_PAREN,
	COMMA, DOT, SEMICOLON,

	// Operators
	PLUS, MINUS, SLASH, STAR, NOT, NOT_EQUAL,
	EQUAL, EQUAL_EQUAL, LESS, LESS_EQUAL,
	GREATER, GREATER_EQUAL,

	// Literals
	IDENTIFIER, STRING, NUMBER,

	// Keywords
	IF, ELSE, FOR, WHILE, TRUE, FALSE, INT, FLOAT, RETURN, THIS
};


class Token {
public:
	Token(TokenType type, uint32_t line, const std::string& lexeme = "\0")
		: m_Type(type), m_Line(line), m_Lexeme(lexeme) {}

	void PrintToken() { std::cout << "Type: " << TokenTypeToString[m_Type] << " Lexeme: " << m_Lexeme 
		<< " Line: " << m_Line << "\n"; }
	inline static bool IsKeyWord(std::string str) { return (Keywords.find(str) != Keywords.end()); }
	static TokenType GetKeywordTokenType(std::string& keyword) { return Keywords[keyword]; }
private:
private:
	TokenType m_Type;
	std::string m_Lexeme;
	uint32_t m_Line;

	static std::map<TokenType, std::string> TokenTypeToString;
	static std::map<std::string, TokenType> Keywords;
};
