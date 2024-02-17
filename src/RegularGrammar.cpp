#include "RegularGrammar.h"

#include <random>

std::random_device rd;
std::mt19937 e2(rd());
std::uniform_real_distribution<> dist(0, 1);

RegularGrammar::RegularGrammar(const std::vector<std::string> production_rule) {
	m_Rules_count = production_rule.size();
	m_Rules = (Rule*)malloc(production_rule.size() * sizeof(Rule));

	char non_terminal = ' ';
	for (uint32_t i = 0; i < production_rule.size(); i++) {
		if (production_rule[i][0] != non_terminal)
		{
			non_terminal = production_rule[i][0];
			m_NT_count++;
		}
	}
	m_NT = (NonTerminal*)malloc(m_NT_count * sizeof(NonTerminal));

	int current_NT = -1;
	char temp = ' ';
	for (uint32_t i = 0; i < production_rule.size(); i++) {
		if (production_rule[i][0] != temp) {
			current_NT++;
			m_NT[current_NT].symbol = production_rule[i][0];
			m_NT[current_NT].rules_count = 1;
			m_NT[current_NT].rule_address = m_Rules + i;

			temp = m_NT[current_NT].symbol;
		}
		else 
			m_NT[current_NT].rules_count++;
	}
	for (uint32_t i = 0; i < production_rule.size(); i++) {
		m_Rules[i].terminal = production_rule[i][2];
		if (production_rule[i].size() < 4)
			m_Rules[i].NT_address = nullptr;
		else {
			for (uint32_t j = 0; j < m_NT_count; j++)
				if (production_rule[i][3] == m_NT[j].symbol) {
					m_Rules[i].NT_address = m_NT + j;
					break;
				}
		}
	}
}
std::string RegularGrammar::GenerateString() {
	std::string word;
	do {
		word = "";
		Derive(m_NT, word);
	} while (word.length() < 5);

	return word;
}
void RegularGrammar::PrintNonTerminals()
{
	for (uint32_t i = 0; i < m_NT_count; i++) {
		std::cout << m_NT[i].symbol << " Rules count: " << m_NT[i].rules_count << "\n";
	}
	std::cout << "\n";
}
void RegularGrammar::PrintRules()
{
	std::cout << "Rules count: " << m_Rules_count << "\n";
	for (uint32_t i = 0; i < m_Rules_count; i++) {
		std::cout << "Terminal: " << m_Rules[i].terminal << " NonTerminal: ";
		if (m_Rules[i].NT_address != nullptr)
			std::cout << m_Rules[i].NT_address->symbol << '\n';
		else
			std::cout << "nullptr\n";
	}
	std::cout << "\n";
}
void RegularGrammar::Derive(NonTerminal* NT, std::string& word) {
	uint32_t random_offset = uint32_t(NT->rules_count * dist(e2));

	Rule* rule = (NT->rule_address + random_offset);
	NonTerminal* next_NT = rule->NT_address;

	word += rule->terminal;
	if (next_NT != nullptr)
		Derive(next_NT, word);
}