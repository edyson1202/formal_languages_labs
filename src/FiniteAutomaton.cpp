#include "FiniteAutomaton.h"

#include <string>

FiniteAutomaton::FiniteAutomaton(const RegularGrammar& grammar)
{
	CreateFADefFromRegularGrammar(m_FADefinition, grammar.GetGrammarDefinition());

	m_States.resize(m_FADefinition.Q.size());
	m_Transitions = (State**)calloc(m_States.size() * 26, sizeof(State*));
	for (uint32_t i = 0; i < m_FADefinition.Q.size(); i++) {
		m_States[i].symbol = m_FADefinition.Q[i];
		m_States[i].index = i;
	}
	m_FinalState_id = m_FADefinition.Q.size() - 1;

	for (uint32_t i = 0; i < m_FADefinition.delta.size(); i++) {
		CreateTransition(m_FADefinition.delta[i].src_state, m_FADefinition.delta[i].dst_state,
			m_FADefinition.delta[i].transition_symbol);
	}
}
void FiniteAutomaton::CreateFADefFromRegularGrammar(FiniteAutomatonDefinition& fa_def, 
	const RegularGrammarDefinition& grammar)
{
	// Q
	const std::vector<char>& non_terminals = grammar.GetNonTerminals();
	fa_def.Q.resize(non_terminals.size() + 1);
	for (uint32_t i = 0; i < non_terminals.size(); i++) {
		fa_def.Q[i] = non_terminals[i];
	}
	fa_def.Q.back() = "*";
	// F
	fa_def.F.emplace_back("*");
	// SIGMA
	const std::vector<char>& terminals = grammar.GetTerminals();
	fa_def.sigma.resize(terminals.size());
	for (uint32_t i = 0; i < terminals.size(); i++) {
		fa_def.sigma[i] = terminals[i];
	}
	// TRANSITION FUNCTION
	const std::vector<ProductionRule>& production_rules = grammar.GetProductionRules();
	fa_def.delta.resize(production_rules.size());
	for (uint32_t i = 0; i < production_rules.size(); i++) {
		fa_def.delta[i].src_state = production_rules[i].A;
		fa_def.delta[i].transition_symbol = production_rules[i].terminal;

		if (production_rules[i].non_terminal == '\0') {
			fa_def.delta[i].dst_state = fa_def.F[0];
		}
		else
			fa_def.delta[i].dst_state = production_rules[i].non_terminal;
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
void FiniteAutomaton::CreateTransition(const std::string& st_state, const std::string& nd_state, char symbol)
{
	uint32_t src_state_id, dst_state_id;
	for (uint32_t i = 0; i < m_States.size(); i++) {
		if (m_States[i].symbol == st_state) {
			src_state_id = i;
			break;
		}
	}
	for (uint32_t i = 0; i < m_States.size(); i++) {
		if (m_States[i].symbol == nd_state) {
			dst_state_id = i;
			break;
		}
	}
	m_Transitions[src_state_id * 26 + symbol - 'a'] = &m_States[dst_state_id];
}
const State& FiniteAutomaton::TransitionFunction(const State& state, char symbol) const
{
	return *m_Transitions[state.index * 26 + symbol - 'a'];
}
bool FiniteAutomaton::IsStringAccepted(const std::string& str) {
	State* current_state = &m_States[0];
	for (uint32_t i = 0; i < str.length(); i++) {
		const State& next_state = TransitionFunction(*current_state, str[i]);
		if (&next_state == nullptr)
			return false;
		current_state = (State*)&next_state;
	}
	return (current_state->index == m_FinalState_id);
}
