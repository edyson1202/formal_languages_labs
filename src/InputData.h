#pragma once

#include <vector>
#include <string>

std::vector<std::string> Q_22 = { "q0", "q1", "q2" };
std::vector<std::string> sigma_22{ "a", "b" };
std::vector<std::string> F_22 = { "q2" };
std::vector<std::string> transition_function_22 = {
    "q0,a,q0",
    "q0,b,q1",
    "q1,b,q1",
    "q1,b,q2",
    "q1,a,q0",
    "q2,b,q1"
};
std::vector<std::vector<std::string>> automaton_22 = { Q_22, sigma_22, F_22, transition_function_22 };

std::vector<std::string> Q = { "q0", "q1", "q2" };
std::vector<std::string> sigma{ "a", "b" };
std::vector<std::string> F = { "q2" };
std::vector<std::string> transition_function = {
    "q0,a,q0",
    "q0,b,q0",
    "q0,b,q1",
    "q1,a,q1",
    "q1,b,q2",
    "q2,a,q2"
};
std::vector<std::vector<std::string>> automaton_24 = { Q, sigma, F, transition_function };

std::vector<std::string> production_rules_test = {
    "S-a,P",
    "S-b,Q",
    "P-b,P",
    "P-c,P",
    "P-d,Q",
    "P-e",
    "Q-e,Q",
    "Q-f,Q",
    "Q-a"
};
std::vector<std::string> production_rules_01 = {
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
std::vector<std::string> production_rules_02 = {
    "S,aS",
    "S,bS",
    "S,cR",
    "S,dL",
    "R,dL",
    "R,e",
    "L,fL",
    "L,eL",
    "L,d"
};
std::vector<std::string> production_rules_05 = {
    "S,bS",
    "S,aF",
    "S,d",
    "F,cF",
    "F,dF",
    "F,aL",
    "F,b",
    "L,aL",
    "L,c" 
};
std::vector<std::string> production_rules_08 = {
    "S,aD",
    "D,dE",
    "D,bJ",
    "D,aE",
    "J,cS",
    "E,e",
    "E,aE"
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
