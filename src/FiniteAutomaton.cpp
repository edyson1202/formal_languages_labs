#include "FiniteAutomaton.h"

#include <string>
#include <sstream>
#include <unordered_map>

FiniteAutomaton::FiniteAutomaton(const std::vector<std::vector<std::string>>& FA_input)
{
	CreateFADefinition(FA_input);

	InitAutomaton();
}

FiniteAutomaton::FiniteAutomaton(const RegularGrammar& grammar)
{
	CreateFADefFromRegularGrammar(grammar.GetGrammarDefinition());

	InitAutomaton();
}
void FiniteAutomaton::InitAutomaton()
{
	if (IsNFA())
		ConvertNFAtoDFA();

	m_States.resize(m_FADefinition.Q.size());
	m_Transitions = (State**)calloc(m_States.size() * 26, sizeof(State*));
	for (uint32_t i = 0; i < m_FADefinition.Q.size(); i++) {
		m_States[i].symbol = m_FADefinition.Q[i];
		m_States[i].index = i;
		m_States[i].is_final = IsStateFinal(m_FADefinition.Q[i]);
	}

	for (uint32_t i = 0; i < m_FADefinition.delta.size(); i++) {
		CreateTransition(m_FADefinition.delta[i].src_state, m_FADefinition.delta[i].dst_state,
			m_FADefinition.delta[i].transition_symbol);
	}
}
void FiniteAutomaton::CreateFADefinition(const std::vector<std::vector<std::string>>& fa_input)
{
	// Q 
	m_FADefinition.Q.resize(fa_input[0].size());
	for (uint32_t i = 0; i < m_FADefinition.Q.size(); i++) {
		m_FADefinition.Q[i] = fa_input[0][i];
	}
	// F
	m_FADefinition.F.resize(fa_input[2].size());
	for (uint32_t i = 0; i < m_FADefinition.F.size(); i++) {
		m_FADefinition.F[i] = fa_input[2][i];
	}
	// Sigma
	m_FADefinition.sigma.resize(fa_input[1].size());
	for (uint32_t i = 0; i < m_FADefinition.sigma.size(); i++) {
		m_FADefinition.sigma[i] = fa_input[1][i];
	}
	// Transition Function
	m_FADefinition.delta.resize(fa_input[3].size());
	for (uint32_t i = 0; i < m_FADefinition.delta.size(); i++) {
		std::stringstream transition(fa_input[3][i]);
		std::string segment;
		std::vector<std::string> list;

		while (std::getline(transition, segment, ','))
		{
			list.push_back(segment);
		}
		m_FADefinition.delta[i].src_state = list[0];
		m_FADefinition.delta[i].dst_state = list[2];
		m_FADefinition.delta[i].transition_symbol = list[1][0];
	}
}
void FiniteAutomaton::CreateFADefFromRegularGrammar(const RegularGrammarDefinition& grammar)
{
	// Q
	const std::vector<std::string>& non_terminals = grammar.GetNonTerminals();
	m_FADefinition.Q.resize(non_terminals.size() + 1);
	for (uint32_t i = 0; i < non_terminals.size(); i++) {
		m_FADefinition.Q[i] = non_terminals[i];
	}
	m_FADefinition.Q.back() = "*";
	// F
	m_FADefinition.F.emplace_back("*");
	// SIGMA
	const std::vector<char>& terminals = grammar.GetTerminals();
	m_FADefinition.sigma.resize(terminals.size());
	for (uint32_t i = 0; i < terminals.size(); i++) {
		m_FADefinition.sigma[i] = terminals[i];
	}
	// TRANSITION FUNCTION
	const std::vector<ProductionRule>& production_rules = grammar.GetProductionRules();
	m_FADefinition.delta.resize(production_rules.size());
	for (uint32_t i = 0; i < production_rules.size(); i++) {
		m_FADefinition.delta[i].src_state = production_rules[i].A;
		m_FADefinition.delta[i].transition_symbol = production_rules[i].terminal;

		if (production_rules[i].non_terminal[0] == '\0') {
			m_FADefinition.delta[i].dst_state = m_FADefinition.F[0];
		}
		else
			m_FADefinition.delta[i].dst_state = production_rules[i].non_terminal;
	}
}
bool FiniteAutomaton::IsNFA()
{
	std::unordered_map<std::string, uint32_t> map;
	for (uint32_t i = 0; i < m_FADefinition.delta.size(); i++) {
		std::string key = m_FADefinition.delta[i].src_state + m_FADefinition.delta[i].transition_symbol;
		if (map.find(key) != map.end())
			return true;
		map[key];
	}
	return false;
}
void FiniteAutomaton::ConvertNFAtoDFA()
{
	std::vector<std::vector<std::string>> new_Q;
	new_Q.resize(m_FADefinition.Q.size());
	std::unordered_map<std::string, uint32_t> map;
	for (uint32_t i = 0; i < m_FADefinition.Q.size(); i++) {
		map[m_FADefinition.Q[i]];
		std::vector<std::string> entry = { m_FADefinition.Q[i] };
		new_Q[i] = entry;
	}
	std::vector<Transition> new_delta;

	for (uint32_t i = 0; i < new_Q.size(); i++) {
		for (uint32_t j = 0; j < m_FADefinition.sigma.size(); j++) {
			std::vector<std::string> dst_set;

			GetDstStateSet(new_Q[i], m_FADefinition.sigma[j], dst_set);

			if (dst_set.size() == 0)
				continue;
			std::string src_set_name = GetStringFromStateVector(new_Q[i]);
			std::string dst_set_name = GetStringFromStateVector(dst_set);

			if (map.find(dst_set_name) == map.end()) {
				map[dst_set_name];
				new_Q.emplace_back(dst_set);
				m_FADefinition.Q.push_back(dst_set_name);

				for (uint32_t k = 0; k < dst_set.size(); k++)
					if (IsStateFinal(dst_set[k])) {
						m_FADefinition.F.push_back(dst_set_name);
						break;
					}
			}
			// Creating the transition
			Transition transition;
			transition.src_state = src_set_name;
			transition.dst_state = dst_set_name;
			transition.transition_symbol = m_FADefinition.sigma[j][0];

			new_delta.push_back(transition);
		}
	}
	m_FADefinition.delta.clear();
	for (uint32_t i = 0; i < new_delta.size(); i++)
		m_FADefinition.delta.push_back(new_delta[i]);
}
void FiniteAutomaton::GetDstStateSet(std::vector<std::string>& src_state_set, std::string transition_symbol, 
	std::vector<std::string>& dst_state_set)
{
	std::unordered_map<std::string, uint32_t> occurrence;
	for (uint32_t k = 0; k < src_state_set.size(); k++) {
		for (uint32_t i = 0; i < m_FADefinition.delta.size(); i++) {
			if (m_FADefinition.delta[i].src_state == src_state_set[k]
				&& m_FADefinition.delta[i].transition_symbol == transition_symbol[0]) {
				std::string dst_state = m_FADefinition.delta[i].dst_state;
				if (occurrence.find(dst_state) == occurrence.end()) {
					occurrence[dst_state];
					dst_state_set.emplace_back(m_FADefinition.delta[i].dst_state);
				}
			}
		}
	}
}
std::string FiniteAutomaton::GetStringFromStateVector(std::vector<std::string>& state_vector)
{
	if (state_vector.size() == 0)
		std::cout << "vector is empty!" << "\n";

	std::string name = "";
	for (uint32_t i = 0; i < state_vector.size(); i++) {
		name += state_vector[i];
	}
	return name;
}
FiniteAutomaton::~FiniteAutomaton()
{
	free(m_Transitions);
}
void FiniteAutomaton::PrintStates()
{
	std::cout << "Automaton states: \n";
	for (uint32_t i = 0; i < m_States.size(); i++) {
		std::cout << m_States[i].index << ": State: " << m_States[i].symbol;
		if (m_States[i].is_final)
			std::cout << " final";
		std::cout << "\n";
	}
	std::cout << "\n";
}
void FiniteAutomaton::PrintTransitions()
{
	//for (uint32_t i = 0; i < m_States.size() * 26; i++) {
	//	if (m_Transitions[i] == nullptr)
	//		continue;
	//	std::cout << "Transition: " << (char)((i % 26) + 'a') << " -> "
	//		<< m_Transitions[i]->symbol << '\n';
	//}
	//std::cout << "\n";
	std::cout << "Automaton transitions: \n";
	for (uint32_t i = 0; i < m_FADefinition.delta.size(); i++) {
		std::cout << "Src: " << m_FADefinition.delta[i].src_state << 
			" transition: " << m_FADefinition.delta[i].transition_symbol
			<< " dst: " << m_FADefinition.delta[i].dst_state << "\n";
	}
	std::cout << "\n";
}
bool FiniteAutomaton::IsStateFinal(const std::string& state_name)
{
	for (uint32_t i = 0; i < m_FADefinition.F.size(); i++) {
		if (state_name == m_FADefinition.F[i])
			return true;
	}
	return false;
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
	return current_state->is_final;
}
