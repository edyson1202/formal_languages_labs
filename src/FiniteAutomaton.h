#pragma once

#include "RegularGrammar.h"

struct Transition;
struct State {
	char symbol;
	uint32_t index;
};
class FiniteAutomaton {
public:
	FiniteAutomaton() = default;
	FiniteAutomaton(const RegularGrammar& grammar);

	~FiniteAutomaton();

	void PrintStates();
	void PrintTransitions();

	bool IsStringAccepted(const std::string& str);
private:
	std::vector<State> m_States;
	State** m_Transitions;
};
