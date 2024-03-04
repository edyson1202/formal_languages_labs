#include "Grammar.h"

#include <sstream>
#include <iostream>
#include <unordered_map>

std::vector<std::string> SplitBySymbol(std::string input, char symbol) {
	std::vector<std::string> split;
	std::stringstream stream(input);
	std::string segment;

	while (std::getline(stream, segment, ','))
	{
		split.push_back(segment);
	}
	return split;
}
Grammar::Grammar(std::vector<std::string>& production_rules)
{
	CreateGrammarDefinition(production_rules);
	m_GrammarType = GetGrammarType();
}

void Grammar::CreateGrammarDefinition(std::vector<std::string>& production_rules)
{
	std::unordered_map<std::string, uint32_t> map;

	// Production rules
	m_GrammarDef.production_rules.resize(production_rules.size());
	for (uint32_t i = 0; i < production_rules.size(); i++) {
		uint32_t middle_index = production_rules[i].find("-");

		std::string left_side = production_rules[i].substr(0, middle_index);
		std::string right_side = production_rules[i].substr(middle_index + 1);

		std::vector<std::string> left_list = SplitBySymbol(left_side, ',');
		std::vector<std::string> right_list = SplitBySymbol(right_side, ',');
		for (uint32_t j = 0; j < left_list.size(); j++)
			m_GrammarDef.production_rules[i].left_side.push_back(left_list[j]);
		for (uint32_t j = 0; j < right_list.size(); j++)
			m_GrammarDef.production_rules[i].right_side.push_back(right_list[j]);

		// Terminals , Non-terminals
		std::string combined = left_side + "," + right_side;
		std::vector<std::string> combined_list = SplitBySymbol(combined, ',');
		for (uint32_t j = 0; j < combined_list.size(); j++) {
			if (map.find(combined_list[j]) == map.end()) {
				map[combined_list[j]];
				if (combined_list[j][0] < 91)
					m_GrammarDef.non_terminals.push_back(combined_list[j]);
				else
					m_GrammarDef.terminals.push_back(combined_list[j]);
			}
		}
	}
	// Start 
	m_GrammarDef.start = m_GrammarDef.non_terminals[0];
}

uint32_t Grammar::GetGrammarType()
{
	uint32_t type = 3;
	for (uint32_t i = 0; i < m_GrammarDef.production_rules.size(); i++) {
		if (m_GrammarDef.production_rules[i].left_side.size() > 1) {
			type = 1;
			break;
		}
		uint32_t rs_terminal_count = 0;
		uint32_t rs_nonterminal_count = 0;
		for (uint32_t j = 0; j < m_GrammarDef.production_rules[i].right_side.size(); j++) {
			if (m_GrammarDef.production_rules[i].right_side[j][0] > 91)
				rs_terminal_count++;
			else
				rs_nonterminal_count++;
		}
		if (rs_nonterminal_count > 1 || rs_terminal_count > 1)
			type = 2;
	}
	for (uint32_t i = 0; i < m_GrammarDef.production_rules.size(); i++) {
		if (m_GrammarDef.production_rules[i].left_side.size() >
			m_GrammarDef.production_rules[i].right_side.size()) {
			type = 0;
			break;
		}
	}
	return type;
}
