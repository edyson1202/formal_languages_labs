#pragma once

#include "RegularGrammar.h"

struct Transition {
	std::string src_state;
	std::string dst_state;
	char transition_symbol;
};
struct FiniteAutomatonDefinition {
	std::vector<std::string> Q;
	std::vector<std::string> sigma;
	std::vector<std::string> F;
	std::vector<Transition> delta;
};

struct State {
	std::string symbol;
	uint32_t index;
	bool is_final;
};
class FiniteAutomaton {
public:
	FiniteAutomaton(const std::vector<std::vector<std::string>>& fa_input);
	FiniteAutomaton(const RegularGrammar& grammar);
	~FiniteAutomaton();

	void InitAutomaton();

	void CreateFADefinition(const std::vector<std::vector<std::string>>& fa_input);
	void CreateFADefFromRegularGrammar(const RegularGrammarDefinition& grammar);
	bool IsNFA();
	void ConvertNFAtoDFA();
	// helper functions
	void GetDstStateSet(std::vector<std::string>& src_state_set, std::string transition_symbol,
		std::vector<std::string>& dst_state_set);
	std::string GetStringFromStateVector(std::vector<std::string>& state_vector);


	void PrintStates();
	void PrintTransitions();

	bool IsStateFinal(const std::string& state_name);

	void CreateTransition(const std::string& st_state, const std::string& nd_state, char symbol);
	const State& TransitionFunction(const State& state, char symbol) const;
	bool IsStringAccepted(const std::string& str);

	const FiniteAutomatonDefinition& GetFiniteAutomatonDefinition() const { return m_FADefinition; }
private:
	std::vector<State> m_States;
	State** m_Transitions;

	FiniteAutomatonDefinition m_FADefinition;
};
