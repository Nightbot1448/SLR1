#include <exception>
#include <stdexcept>

#include "Parsing_table.h"

Parsing_table::Parsing_table(const Grammar &g_, const Graph_of_states &graph, const FirstFollow_sets &follow) 
	: grammar_(g_), graph_(graph), follow_(follow) {
	std::vector<char> char_base_ = V();
	init_table(char_base_);
	fill_table();
}

void Parsing_table::init_table(std::vector<char> char_base_) {
	for (size_t i = 0; i < graph_.states_.size(); i++) {
		std::map<char, Table_cell> row;
	
		for (size_t i = 0; i < char_base_.size(); i++) {
			row.try_emplace(char_base_.at(i), Table_cell());
		}
		table_.try_emplace(i, row);
	}
}

std::vector<char> Parsing_table::V() {
	std::set<char> elems;
	for (auto rule : grammar_) {
		elems.insert(rule.first);
		elems.insert(rule.second.begin(), rule.second.end());
	}
	elems.insert('$');
	return std::vector<char>(elems.begin(), elems.end());
}

void Parsing_table::fill_table() {
	Table_cell clear_cell;
	for (size_t i = 0; i < graph_.states_.size(); ++i) {
		auto gones = graph_.adjency_lst_.find(i);
		if (gones != graph_.adjency_lst_.end()) {
			for (auto trans : gones->second) {
				if (std::isalpha(trans.first) && std::isupper(trans.first)) {
					table_.at(i).at(trans.first) = Table_cell(TYPES::GOTO, trans.second);
				}
				else {
					table_.at(i).at(trans.first) = Table_cell(TYPES::SHIFT, trans.second);
				}
			}
		}
		for (size_t j = 0; j < graph_.states_.at(i).items_.size(); j++) {
			Item item = graph_.states_.at(i).items_.at(j);
			if (item.after_point.empty()) {
				if (item.left_part != 'S')
				{
					char left = item.left_part;
					const std::string& bp = item.before_point;
					size_t id = 0;
					for (auto el = grammar_.begin(); el != grammar_.end() && !(el->first == left && el->second == bp); ++el)
						id++;
					for (auto follow_el : follow_.at(left)) {
						if (table_.at(i).at(follow_el) == clear_cell) {
							table_.at(i).at(follow_el) = Table_cell(TYPES::REDUCE, id);
						}
						else {
							throw std::logic_error("conflict in cell(" + i + ',' + follow_el +')');
						}
					}
				}
				else if (table_.at(i).at('$') == clear_cell)
				{
					table_.at(i).at('$') = Table_cell(TYPES::ACCEPT, 0);
				}
				else {
					throw std::logic_error("accept/reduce fail");
				}
			}
		}
	}
}
