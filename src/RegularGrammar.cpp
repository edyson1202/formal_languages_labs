#include "RegularGrammar.h"

#include <random>
#include <unordered_map>
#include <sstream>

#include "FiniteAutomaton.h"

std::random_device rd;
std::mt19937 e2(rd());
std::uniform_real_distribution<> dist(0, 1);

RegularGrammar::RegularGrammar(const std::vector<std::string> production_rule) 
{
	CreateGrammarDefinition(production_rule);

	InitRegularGrammar();
}
RegularGrammar::RegularGrammar(const FiniteAutomaton& automaton)
{
	CreateGrammarDefinitionFromFA(automaton.GetFiniteAutomatonDefinition());

	InitRegularGrammar();
}
void RegularGrammar::InitRegularGrammar()
{
	m_Rules.resize(m_GrammarDef.production_rules.size());
	m_NT.resize(m_GrammarDef.non_terminals.size());

	std::unordered_map<std::string, uint32_t> map;
	for (uint32_t i = 0; i < m_GrammarDef.production_rules.size(); i++) {
		map[m_GrammarDef.production_rules[i].A]++;
	}
	uint32_t pointer = 0;
	for (uint32_t i = 0; i < m_NT.size(); i++) {
		m_NT[i].symbol = m_GrammarDef.non_terminals[i];
		m_NT[i].rules_count = map[m_NT[i].symbol];
		m_NT[i].rule_address = &m_Rules[pointer];

		pointer += m_NT[i].rules_count;
	}
	for (uint32_t i = 0; i < m_Rules.size(); i++) {
		m_Rules[i].terminal = m_GrammarDef.production_rules[i].terminal;
		if (m_GrammarDef.production_rules[i].non_terminal[0] == '\0') {
			m_Rules[i].NT_address = nullptr;
			continue;
		}
		for (uint32_t j = 0; j < m_NT.size(); j++)
			if (m_GrammarDef.production_rules[i].non_terminal == m_NT[j].symbol) {
				m_Rules[i].NT_address = &m_NT[j];
				break;
			}
	}
}
void RegularGrammar::CreateGrammarDefinition(const std::vector<std::string>& input)
{
	std::unordered_map<char, uint32_t> map;
	m_GrammarDef.production_rules.resize(input.size());
	for (uint32_t i = 0; i < input.size(); i++) {
		// TERMINALS
		if (map.find(input[i][2]) == map.end()) {
			map[input[i][2]];
			m_GrammarDef.terminals.emplace_back(input[i][2]);
		}
		// NON-TERMINALS
		if (map.find(input[i][0]) == map.end()) {
			map[input[i][0]];
			std::string str = "";
			str += input[i][0];
			m_GrammarDef.non_terminals.emplace_back(str);
		}
		// PRODUCTION RULES
		m_GrammarDef.production_rules[i].A = input[i][0];
		m_GrammarDef.production_rules[i].terminal = input[i][2];
		m_GrammarDef.production_rules[i].non_terminal = input[i][3];
	}
	// START SYMBOL
	m_GrammarDef.start_symbol = input[0][0];
}
void RegularGrammar::CreateGrammarDefinitionFromFA(const FiniteAutomatonDefinition& fa_def)
{
	// Terminals
	m_GrammarDef.terminals.resize(fa_def.sigma.size());
	for (uint32_t i = 0; i < m_GrammarDef.terminals.size(); i++) {
		m_GrammarDef.terminals[i] = fa_def.sigma[i][0];
	}
	// Non-terminals
	m_GrammarDef.non_terminals.resize(fa_def.Q.size());
	for (uint32_t i = 0; i < m_GrammarDef.non_terminals.size(); i++) {
		m_GrammarDef.non_terminals[i] = fa_def.Q[i];
	}
	// Production rules
	//m_GrammarDef.production_rules.resize(fa_def.delta.size());
	for (uint32_t i = 0; i < fa_def.delta.size(); i++) {
		ProductionRule rule;
		rule.A = fa_def.delta[i].src_state;
		rule.non_terminal = fa_def.delta[i].dst_state;
		rule.terminal = fa_def.delta[i].transition_symbol;

		m_GrammarDef.production_rules.push_back(rule);
		// if transition leads to a final state create an additional rule without a non-terminal on the right side
		for (uint32_t j = 0; j < fa_def.F.size(); j++)
			if (fa_def.delta[i].dst_state == fa_def.F[j]) {
				rule.non_terminal = "\0";
				m_GrammarDef.production_rules.push_back(rule);
				break;
			}
	}
	// Start symbol
	m_GrammarDef.start_symbol = m_GrammarDef.non_terminals[0];
}
std::string RegularGrammar::GenerateString() {
	std::string word;
	do {
		word = "";
		Derive(&m_NT[0], word);
	} while (word.length() < 5);

	return word;
}
void RegularGrammar::PrintNonTerminals()
{
	std::cout << "Grammar non-terminals: \n";
	for (uint32_t i = 0; i < m_NT.size(); i++) {
		std::cout << m_NT[i].symbol << " Rules count: " << m_NT[i].rules_count << "\n";
	}
	std::cout << "\n";
}
void RegularGrammar::PrintRules()
{
	std::cout << "Rules count: " << m_Rules.size() << "\n";
	for (uint32_t i = 0; i < m_Rules.size(); i++) {
		std::cout << "Terminal: " << m_Rules[i].terminal << " NonTerminal: ";
		if (m_Rules[i].NT_address != nullptr)
			std::cout << m_Rules[i].NT_address->symbol << '\n';
		else
			std::cout << "nullptr\n";
	}
	std::cout << "\n";
}
void RegularGrammar::Derive(const NonTerminal* NT, std::string& word) {
	const Rule* rule = NT->GetRandomRule();
	const NonTerminal* next_NT = rule->NT_address;

	word += rule->terminal;
	if (next_NT != nullptr)
		Derive(next_NT, word);
}
void RegularGrammarDefinition::PrintTerminals() const
{
	for (uint32_t i = 0; i < terminals.size(); i++) {
		std::cout << terminals[i] << ", ";
	}
	std::cout << "\n";
}
void RegularGrammarDefinition::PrintProductionRules() const
{
	std::cout << "Grammar production rules: \n";
	for (uint32_t i = 0; i < production_rules.size(); i++) {
		std::cout << production_rules[i].A << "->"
			<< production_rules[i].terminal
			<< production_rules[i].non_terminal << "\n";
	}
	std::cout << "\n";
}
const Rule* NonTerminal::GetRandomRule() const
{
	uint32_t random_offset = uint32_t(rules_count * dist(e2));
	return rule_address + random_offset;
}
