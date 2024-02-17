#include <iostream>

#include "RegularGrammar.h"
#include "FiniteAutomaton.h"
#include "InputData.h"


// REQUIRED FORMAT
// 1. Production rules should be grouped by left-hand side non-terminal starting with the 'S' group
// If functionality to transform input into the required format will be implemented later
// these requirements will be droped

int main()
{
    RegularGrammar grammar(production_rules_08);
    grammar.PrintNonTerminals();
    grammar.PrintRules();

    std::vector<std::string> strings;
    for (uint32_t i = 0; i < 5; i++) {
        std::string word;
        word = grammar.GenerateString();

        //std::cout << word << std::endl;
        strings.emplace_back(word);
    }

    FiniteAutomaton daf(grammar);
    daf.PrintStates();
    daf.PrintTransitions();
    for (std::string& str : strings) {
        std::cout << str << "\n";
        if (daf.IsStringAccepted(str)) {
            std::cout << "True\n";
        }
        else
            std::cout << "False\n";
    }

    return 0;
}

