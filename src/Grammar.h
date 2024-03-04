#pragma once

#include <string>
#include <vector>
#include <cstdint>

struct GrammarProductionRule {
	std::vector<std::string> left_side;
	std::vector<std::string> right_side;
};
struct GrammarDefinition {
	std::vector<std::string> non_terminals;
	std::vector<std::string> terminals;
	std::string start;
	std::vector<GrammarProductionRule> production_rules;

};

class Grammar {
public:
	Grammar(std::vector<std::string>& production_rules);

	void CreateGrammarDefinition(std::vector<std::string>& production_rules);

	uint32_t GetGrammarType();

private:
	GrammarDefinition m_GrammarDef;
	uint32_t m_GrammarType;
};
