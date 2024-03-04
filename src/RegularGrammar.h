#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

struct FiniteAutomatonDefinition;
struct ProductionRule {
	std::string A;
	char terminal;
	std::string non_terminal;
};
struct RegularGrammarDefinition {
	std::vector<std::string> non_terminals;
	std::vector<char> terminals;
	std::string start_symbol;
	std::vector<ProductionRule> production_rules;

	const std::vector<std::string>& GetNonTerminals() const { return non_terminals; }
	const std::vector<char>& GetTerminals() const { return terminals; }
	const std::vector<ProductionRule>& GetProductionRules() const { return production_rules; }

	void PrintTerminals() const;
	void PrintProductionRules() const;
};
class FiniteAutomaton;
struct Rule;
struct NonTerminal {
	std::string symbol;
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
	RegularGrammar(const FiniteAutomaton& automaton);
	~RegularGrammar() = default;

	void InitRegularGrammar();

	void CreateGrammarDefinition(const std::vector<std::string>& input);
	void CreateGrammarDefinitionFromFA(const FiniteAutomatonDefinition& fa_def);

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
