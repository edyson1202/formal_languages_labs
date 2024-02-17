#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

class FiniteAutomaton;

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

	NonTerminal* GetNonTerminals() const { return m_NT; }
	uint32_t GetNonTerminalsCount() const { return m_NT_count; }
	Rule* GetRules() const { return m_Rules; }
	uint32_t GetRulesCount() const { return m_Rules_count; }
	Rule* GetRules() { return m_Rules; }

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
