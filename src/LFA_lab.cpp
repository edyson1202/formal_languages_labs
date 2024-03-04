#include <iostream>

#include "Grammar.h"
#include "RegularGrammar.h"
#include "FiniteAutomaton.h"
#include "InputData.h"


// REQUIRED FORMAT
// 1. Production rules should be grouped by left-hand side non-terminal starting with the 'S' group
// If functionality to transform input into the required format will be implemented later
// these requirements will be droped

// Automaton
// 1. Transition function should have source states in sorted

int main()
{
    // LAB 01
    /*
    {
        RegularGrammar grammar(production_rules_24);
        FiniteAutomaton daf(grammar);

        for (uint32_t i = 0; i < 5; i++) {
            std::string str;
            str = grammar.GenerateString();
            std::cout << str << "\n";
            std::cout << str << "\n" << (daf.IsStringAccepted(str) ? "True\n" : "False\n");
        }
        std::string str = "abc";
        std::cout << str << "\n" << (daf.IsStringAccepted(str) ? "True\n" : "False\n");
    }
    */

    FiniteAutomaton daf(automaton_22);

    daf.PrintStates();
    daf.PrintTransitions();

    RegularGrammar grammar(daf);

    grammar.PrintNonTerminals();
    grammar.GetGrammarDefinition().PrintProductionRules();

    for (uint32_t i = 0; i < 1000; i++) {
        std::string str = grammar.GenerateString();

        if (!daf.IsStringAccepted(str))
            std::cout << "fail!" << "\n";
    }

    //Grammar grammar(production_rules_test);

    //std::cout << "Type: " << grammar.GetGrammarType() << "\n";

    return 0;
}

