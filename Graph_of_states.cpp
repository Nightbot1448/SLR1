#include "Graph_of_states.h"

#include <cctype>
#include <iostream>
#include <queue>
#include <set>


Graph_of_states::Graph_of_states(const Grammar& g) {
	grammar = g;
	compute_graph();
	std::cout << "computed" << std::endl;
}

void Graph_of_states::closure(Items& state) {
	for (size_t i = 0; i < state.size(); ++i) {
		std::string& to_go = state.at(i).after_point;
		if (!(to_go.empty()) && std::isupper(to_go.at(0)))
		{
			auto range = grammar.equal_range(to_go.at(0));
			for (auto el = range.first; el != range.second; ++el) {
				Item item = Item(el->first, "", el->second);
				if (std::find(state.begin(), state.end(), item) == state.end())
					state.push_back(item);
			}
		}
	}
}

void Graph_of_states::compute_graph() {
	auto base_rule = grammar.find('S');
	Item first_rule(base_rule->first, "", base_rule->second);
	Items start_state({ first_rule });
	closure(start_state);
	states_.push_back(State(start_state));
	for (size_t state_i = 0; state_i < states_.size(); ++state_i) {
		std::set<size_t> goto_completed_rules;
		while (goto_completed_rules.size() != states_.at(state_i).items_.size()) {
			size_t id = 0;
			for (id; id < states_.at(state_i).items_.size() &&
				goto_completed_rules.size() &&
				goto_completed_rules.find(id) != goto_completed_rules.end(); id++);
			std::string& ap = states_.at(state_i).items_.at(id).after_point;
			if (!ap.empty())
			{
				char goto_symb = ap.at(0);
				Items possible_state;
				for (size_t i = 0; i < states_.at(state_i).items_.size(); ++i) {
					if (!(states_.at(state_i).items_.at(i).after_point.empty()) &&
						states_.at(state_i).items_.at(i).after_point.at(0) == goto_symb)
					{
						goto_completed_rules.insert(i);
						possible_state.push_back({ states_.at(state_i).items_.at(i).left_part,
													states_.at(state_i).items_.at(i).before_point +
														states_.at(state_i).items_.at(i).after_point.at(0),
													std::string(states_.at(state_i).items_.at(i).after_point.begin() + 1,
														states_.at(state_i).items_.at(i).after_point.end()) });
					}

				}
				closure(possible_state);
				State st(possible_state);
				auto it = states_.begin();
				for (it; it != states_.end() && it->hash_ != st.hash_; ++it);
				size_t to_id = 0;
				if (it == states_.end()) {
					to_id = states_.size();
					states_.push_back(st);
				}
				else {
					to_id = it - states_.begin();
				}
				auto el = adjency_lst_.find(state_i);
				if (el == adjency_lst_.end())
				{
					std::map<char, size_t> gones;
					gones.try_emplace(goto_symb, to_id);
					adjency_lst_.try_emplace(state_i, gones);
				}
				else {
					el->second.try_emplace(goto_symb, to_id);
				}
			}
			else {
				goto_completed_rules.insert(id);
			}
		}
	}
}
