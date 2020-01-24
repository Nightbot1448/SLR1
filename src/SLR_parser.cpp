#include "SLR_parser.h"

#include <iostream>
#include <stack>

SLR1_parser::SLR1_parser(const Grammar &g, bool print_table) : grammar(g), graph(Graph_of_states(grammar)) {
	//init_first();
	init_follow();
	table = Parsing_table(grammar, graph, follow);
	if (print_table)
		print_parsing_table();
}

void SLR1_parser::print_parsing_table() {
	std::cout << '\t';
	for (auto it : table.table_.begin()->second) {
		std::cout << it.first << '\t';
	}
	std::cout << std::endl;

	std::map<TYPES, char> translate;
	translate.try_emplace(TYPES::ACCEPT, 'A');
	translate.try_emplace(TYPES::FAIL, 'F');
	translate.try_emplace(TYPES::SHIFT, 'S');
	translate.try_emplace(TYPES::REDUCE, 'R');
	translate.try_emplace(TYPES::GOTO, 'G');

	for (auto it_r : table.table_) {
		std::cout << it_r.first << '\t';
		for (auto it_y : it_r.second) {
			std::cout << translate.at(it_y.second.type) << it_y.second.id << '\t';
		}
		std::cout << std::endl;
	}
}

void SLR1_parser::init_first() {
	// TODO: compute first

	first.emplace('E', std::set<char>({'-', '(', 'n'}));
	first.emplace('T', std::set<char>({ '-', '(', 'n' }));
	first.emplace('F', std::set<char>({ '-', '(', 'n' }));
}

void SLR1_parser::init_follow() {
	// TODO: compute follow

	follow.emplace('E', std::set<char>({ '+', '-',')', '$' }));
	follow.emplace('T', std::set<char>({ '+', '-',')', '*', '/', '$' }));
	follow.emplace('F', std::set<char>({ '+', '-',')', '*', '/', '$' }));
}

bool SLR1_parser::parse(std::string input) {
	std::stack<Stack_elem> st;
	if (*(input.end() - 1) != '$')
		input.push_back('$');
	size_t input_pointer = 0;
	st.push(Stack_elem('$', 0));
	while (st.size()) {
		Stack_elem current = st.top();
		Table_cell action;
		try{
			action = table.table_.at(current.state).at(input.at(input_pointer));
		}
		catch(std::out_of_range &e){
			std::cout << "Symbol \'" << input.at(input_pointer) << "\' at position " << input_pointer << " isn't part of grammar" << std::endl;
			return false;
		}
		if (action.type == TYPES::SHIFT) {
			st.push(Stack_elem(input.at(input_pointer), action.id));
			++input_pointer;
		}
		else if (action.type == TYPES::REDUCE) {
			auto grammar_rule = grammar.begin();
			for (size_t i = 0; i < grammar.size() && i<action.id; grammar_rule++, ++i);
			for (size_t i = 0; i < grammar_rule->second.size(); ++i) {
				st.pop();
			}
			Table_cell goto_cell = table.table_.at(st.top().state).at(grammar_rule->first);
			if (goto_cell.type != TYPES::GOTO) {
				return false;
			}
			else{
				st.push(Stack_elem(grammar_rule->first, goto_cell.id));
			}
		}
		else if (action.type == TYPES::ACCEPT) {
			return true;
		}
		else {
			return false;
		}
	}
}