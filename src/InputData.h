#pragma once

#include <vector>
#include <string>

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
