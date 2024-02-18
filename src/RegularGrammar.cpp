#include "RegularGrammar.h"

#include <random>
#include <unordered_map>

std::random_device rd;
std::mt19937 e2(rd());
std::uniform_real_distribution<> dist(0, 1);

RegularGrammar::RegularGrammar(const std::vector<std::string> production_rule) 
{
	CreateGrammarDefinition(m_GrammarDef, production_rule);

	m_Rules.resize(m_GrammarDef.production_rules.size());
	m_NT.resize(m_GrammarDef.non_terminals.size());

	std::unordered_map<char, uint32_t> map;
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
		if (m_GrammarDef.production_rules[i].non_terminal == '\0') {
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
void RegularGrammar::CreateGrammarDefinition(RegularGrammarDefinition& grammar_def, 
	const std::vector<std::string>& input)
{
	std::unordered_map<char, uint32_t> map;
	grammar_def.production_rules.resize(input.size());
	for (uint32_t i = 0; i < input.size(); i++) {
		// TERMINALS
		if (map.find(input[i][2]) == map.end()) {
			map[input[i][2]];
			grammar_def.terminals.emplace_back(input[i][2]);
		}
		// NON-TERMINALS
		if (map.find(input[i][0]) == map.end()) {
			map[input[i][0]];
			grammar_def.non_terminals.emplace_back(input[i][0]);
		}
		// PRODUCTION RULES
		grammar_def.production_rules[i].A = input[i][0];
		grammar_def.production_rules[i].terminal = input[i][2];
		grammar_def.production_rules[i].non_terminal = input[i][3];
	}
	// START SYMBOL
	grammar_def.start_symbol = input[0][0];
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
void RegularGrammarDefinition::PrintTerminals()
{
	for (uint32_t i = 0; i < terminals.size(); i++) {
		std::cout << terminals[i] << ", ";
	}
	std::cout << "\n";
}
void RegularGrammarDefinition::PrintProductionRules()
{
	for (uint32_t i = 0; i < production_rules.size(); i++) {
		std::cout << production_rules[i].A << "->"
			<< production_rules[i].terminal
			<< production_rules[i].non_terminal << "\n";
	}
}
const Rule* NonTerminal::GetRandomRule() const
{
	uint32_t random_offset = uint32_t(rules_count * dist(e2));
	return rule_address + random_offset;
}
