#pragma once

#include "RegularGrammar.h"

struct Transition {
	std::string src_state;
	std::string dst_state;
	char transition_symbol;
};
struct FiniteAutomatonDefinition {
	std::vector<std::string> Q;
	std::vector<char> sigma;
	std::vector<std::string> F;
	std::vector<Transition> delta;
};

struct State {
	std::string symbol;
	uint32_t index;
};
class FiniteAutomaton {
public:
	FiniteAutomaton() = default;
	FiniteAutomaton(const RegularGrammar& grammar);
	~FiniteAutomaton();

	void CreateFADefFromRegularGrammar(FiniteAutomatonDefinition& fa_def, 
		const RegularGrammarDefinition& grammar);

	void PrintStates();
	void PrintTransitions();

	void CreateTransition(const std::string& st_state, const std::string& nd_state, char symbol);
	const State& TransitionFunction(const State& state, char symbol) const;
	bool IsStringAccepted(const std::string& str);
private:
	std::vector<State> m_States;
	State** m_Transitions;

	FiniteAutomatonDefinition m_FADefinition;

	uint32_t m_FinalState_id;
};
