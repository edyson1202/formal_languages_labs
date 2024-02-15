#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

#include "FiniteAutomaton.h"


struct Rule;
struct NonTerminal {
	char symbol = '\0';
	uint32_t rules_count = 0;
	Rule* rule_address = nullptr;
};
struct Rule {
	char terminal;
	NonTerminal* NT_address = nullptr;
};
class RegularGrammar {
public:
	RegularGrammar(const std::vector<std::string> production_rules);

	std::string GenerateString();
	FiniteAutomaton* ToFiniteAutomaton();

	void PrintNonTerminals();
	void PrintRules();

private:
	void Derive(NonTerminal* NT, std::string& word);
private:
	NonTerminal* m_NT;
	Rule* m_Rules;

	uint32_t m_NT_count = 0;
	uint32_t m_Rules_count = 0;
};
