#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

struct ProductionRule {
	char A;
	char terminal;
	char non_terminal;
};
struct RegularGrammarDefinition {
	std::vector<char> non_terminals;
	std::vector<char> terminals;
	std::string start_symbol;
	std::vector<ProductionRule> production_rules;

	const std::vector<char>& GetNonTerminals() const { return non_terminals; }
	const std::vector<char>& GetTerminals() const { return terminals; }
	const std::vector<ProductionRule>& GetProductionRules() const { return production_rules; }

	void PrintTerminals();
	void PrintProductionRules();
};
class FiniteAutomaton;
struct Rule;
struct NonTerminal {
	char symbol = '\0';
	uint32_t rules_count = 0;
	Rule* rule_address = nullptr;

	const Rule* GetRandomRule() const;
};
struct Rule {
	char terminal;
	NonTerminal* NT_address = nullptr;
};
class RegularGrammar {
public:
	RegularGrammar(const std::vector<std::string> production_rules);
	~RegularGrammar() = default;

	void CreateGrammarDefinition(RegularGrammarDefinition& grammar_def, 
		const std::vector<std::string>& input);

	std::string GenerateString();

	const RegularGrammarDefinition& GetGrammarDefinition() const { return m_GrammarDef; }

	void PrintNonTerminals();
	void PrintRules();
private:
	void Derive(const NonTerminal* NT, std::string& word);
private:
	std::vector<NonTerminal> m_NT;
	std::vector<Rule> m_Rules;
	
	RegularGrammarDefinition m_GrammarDef;
};
