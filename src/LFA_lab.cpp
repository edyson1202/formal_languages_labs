#include <iostream>
#include <string>
#include <vector>

#include "RegularGrammar.h"

std::vector<std::string> production_rules = {
    "S,aP",
    "S,bQ",
    "P,bP",
    "P,cP",
    "P,dQ",
    "P,e",
    "Q,eQ",
    "Q,fQ",
    "Q,a"
};
std::vector<std::string> production_rules_24 = {
    "S,aA",
    "A,bS",
    "A,dD",
    "D,bC",
    "D,aD",
    "C,bA",
    "C,a"  
};

int main()
{
    RegularGrammar grammar(production_rules_24);

    for (uint32_t i = 0; i < 5; i++) {
        std::string word;
        word = grammar.GenerateString();

        std::cout << word << std::endl;
    }

    return 0;
}

