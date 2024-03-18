#pragma once

#include <vector>

#include "Token.h"

class Lexer {
public:
	Lexer(const std::string& source)
		: m_Source(source) {}

	void ScanTokens();

	void PrintTokens();
private:
	void ScanToken();
	void AddToken(TokenType type);
	void AddToken(TokenType type, const std::string& lexeme);

	bool IsAtEnd();
	bool IsCurrentChar(char c);
	inline char Peek() { return m_Source[m_CurrentChar]; }
	inline char PeekNext() { return m_Source[m_CurrentChar + 1]; }
	void String();
	void Number();
	void Identifier();
private:
	std::string m_Source;
	std::vector<Token> m_Tokens;

	uint32_t m_StartChar = 0;
	uint32_t m_CurrentChar = 0;
	uint32_t m_Line = 1;
};
