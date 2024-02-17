#include "FiniteAutomaton.h"

#include <string>

FiniteAutomaton::FiniteAutomaton(const RegularGrammar& grammar)
{
	NonTerminal* non_terminals = grammar.GetNonTerminals();
	Rule* rules = grammar.GetRules();
	m_States.resize(grammar.GetNonTerminalsCount() + 1);

	m_Transitions = (State**)calloc(m_States.size() * 26, sizeof(State*));

	for (uint32_t i = 0; i < m_States.size() - 1; i++) {
		m_States[i].symbol = non_terminals[i].symbol;
		m_States[i].index = i;
	}
	m_States[m_States.size() - 1].symbol = '*';
	m_States[m_States.size() - 1].index = m_States.size() - 1;
	for (uint32_t i = 0; i < m_States.size() - 1; i++) {
		for (uint32_t j = 0; j < non_terminals[i].rules_count; j++) {
			Rule* rule = non_terminals[i].rule_address + j;
			if (rule->NT_address == nullptr) {
				m_Transitions[m_States[i].index * 26 + rule->terminal - 'a'] = &m_States[m_States.size() - 1];
				continue;
			}
			for (uint32_t k = 0; k < m_States.size(); k++) {
				if (rule->NT_address->symbol != m_States[k].symbol)
					continue;
				m_Transitions[m_States[i].index * 26 + rule->terminal - 'a'] = &m_States[k];
				break;
			}
		}
	}
}
FiniteAutomaton::~FiniteAutomaton()
{
	free(m_Transitions);
}
void FiniteAutomaton::PrintStates()
{
	for (uint32_t i = 0; i < m_States.size(); i++) {
		std::cout << m_States[i].index << ": State: " << m_States[i].symbol
			<< "\n";
	}
	std::cout << "\n";
}
void FiniteAutomaton::PrintTransitions()
{
	for (uint32_t i = 0; i < m_States.size() * 26; i++) {
		if (m_Transitions[i] == nullptr)
			continue;
		std::cout << "Transition: " << (char)((i % 26) + 'a') << " -> "
			<< m_Transitions[i]->symbol << '\n';
	}
	std::cout << "\n";
}
bool FiniteAutomaton::IsStringAccepted(const std::string& str)
{
	State* current_state = &m_States[0];
	for (uint32_t i = 0; i < str.length(); i++) {
		State* next_state = m_Transitions[current_state->index * 26 + str[i] - 'a'];
		if (next_state == nullptr) {
			if (current_state->index == m_States.size() - 1 && i == str.length() - 1)
				return true;
			else
				return false;
		}
		current_state = next_state;
	}
}
