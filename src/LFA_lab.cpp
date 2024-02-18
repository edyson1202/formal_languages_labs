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
    RegularGrammar grammar(production_rules_24);

    std::vector<std::string> strings;
    for (uint32_t i = 0; i < 5; i++) {
        strings.emplace_back(grammar.GenerateString());
        std::cout << strings.back() << "\n";
    }

    FiniteAutomaton daf(grammar);
    for (std::string& str : strings)
        std::cout << str << "\n" << (daf.IsStringAccepted(str) ? "True\n" : "False\n");

    std::cout << (daf.IsStringAccepted("abc") ? "True\n" : "False\n");

    return 0;
}

