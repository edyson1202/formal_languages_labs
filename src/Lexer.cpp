#include "Lexer.h"

#include <iostream>

void Lexer::ScanTokens()
{
	while (!IsAtEnd())
	{
		m_StartChar = m_CurrentChar;
		ScanToken();
	}
}

void Lexer::PrintTokens()
{
	for (Token& token : m_Tokens)
	{
		token.PrintToken();
	}
}

void Lexer::ScanToken()
{
	char c = m_Source[m_CurrentChar];
	m_CurrentChar++;
	switch (c)
	{
	case '{': AddToken(LEFT_BRACE); break;
	case '}': AddToken(RIGHT_BRACE); break;
	case '(': AddToken(LEFT_PAREN); break;
	case ')': AddToken(RIGHT_PAREN); break;
	case ',': AddToken(COMMA); break;
	case '.': AddToken(DOT); break;
	case '-': AddToken(MINUS); break;
	case '+': AddToken(PLUS); break;
	case ';': AddToken(SEMICOLON); break;
	case '*': AddToken(STAR); break;
	case '!':
		AddToken(IsCurrentChar('=') ? NOT_EQUAL : NOT);
		break;
	case '=':
		AddToken(IsCurrentChar('=') ? EQUAL_EQUAL : EQUAL);
		break;
	case '<':
		AddToken(IsCurrentChar('=') ? LESS_EQUAL : LESS);
		break;
	case '>':
		AddToken(IsCurrentChar('=') ? GREATER_EQUAL : GREATER);
		break;
	case '/':
		if (IsCurrentChar('/')) {
			// advace the current char pointer until a new line (ignore the comment)
			while (m_Source[m_CurrentChar] != '\n' && !IsAtEnd())
				m_CurrentChar++;
		}
		else {
			AddToken(SLASH);
		}
		break;
	case ' ':
	case '\r':
	case '\t':
		// Ignore whitespace.
		break;
	case '\n':
		m_Line++;
		break;
	case '"': String(); break;
	default:
		if (isdigit(c))
			Number();
		else if (isalpha(c))
			Identifier();
		else
			std::cout << "Unexpected character '" << c << "' at line : " << m_Line << "\n";
		break;
	}
}

void Lexer::AddToken(TokenType type)
{
	m_Tokens.emplace_back(Token(type, m_Line));
}

void Lexer::AddToken(TokenType type, const std::string& lexeme)
{
	m_Tokens.emplace_back(Token(type, m_Line, lexeme));
}
bool Lexer::IsCurrentChar(char c)
{
	if (m_CurrentChar >= m_Source.length())
		return false;
	if (m_Source[m_CurrentChar] != c)
		return false;

	m_CurrentChar++;
	return true;
}

void Lexer::String()
{
	while (Peek() != '"' && !IsAtEnd())
	{
		if (Peek() == '\n')
			m_Line++;
		m_CurrentChar++;
	}
	if (IsAtEnd()) {
		std::cout << "Unterminated string!\n";
		return;
	}
	// Closing "
	m_CurrentChar++;

	std::string lexeme = m_Source.substr(m_StartChar + 1, m_CurrentChar - m_StartChar - 2);
	AddToken(STRING, lexeme);
}

void Lexer::Number()
{
	while (isdigit(Peek()))
		m_CurrentChar++;
	if (Peek() == '.' && isdigit(PeekNext())) {
		m_CurrentChar++;
		while (isdigit(Peek()))
			m_CurrentChar++;
	}

	std::string lexeme = m_Source.substr(m_StartChar, m_CurrentChar - m_StartChar);
	AddToken(NUMBER, lexeme);
}

void Lexer::Identifier()
{
	while (isalpha(Peek()) || isdigit(Peek()) || Peek() == '_')
		m_CurrentChar++;
	
	std::string identifier = m_Source.substr(m_StartChar, m_CurrentChar - m_StartChar);
	TokenType type = TokenType::IDENTIFIER;
	if (Token::IsKeyWord(identifier))
		type = Token::GetKeywordTokenType(identifier);

	AddToken(type, identifier);
}
