#include "SLR_parser.h"

#include <iostream>

SLR1_parser::SLR1_parser(const Grammar &g, bool print_table) : grammar(g), graph(Graph_of_states(grammar)) {
	init_first();
	init_follow();
	table = Parsing_table(grammar, graph, follow_);
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
			if (it_y.second.type != TYPES::FAIL) {
				std::cout << translate.at(it_y.second.type) << it_y.second.id << '\t';
			}
			else {
				std::cout << "--\t";
			}
		}
		std::cout << std::endl;
	}
}

void SLR1_parser::insert_ff_sets(FirstFollow_sets &set_, char symb, std::set<char> s) {
	auto it = set_.find(symb);
	if (it != set_.end()) {
		set_.at(symb).insert(s.begin(), s.end());
	}
	else {
		set_.insert(std::pair<char, std::set<char>>(symb, s));
	}
}

std::set<char> SLR1_parser::first(std::string form) {

	if (std::isupper(form.at(0)))
	{
		std::set<char> first_for_nt;
		auto range = grammar.equal_range(form.at(0));
		for (auto rule = range.first; rule != range.second; rule++) {
			if (rule->first != rule->second.at(0)) {
				std::set<char> part_of_first_for_nt = first(rule->second);
				first_for_nt.insert(part_of_first_for_nt.begin(), part_of_first_for_nt.end());
			}
		}
		insert_ff_sets(first_, form.at(0), first_for_nt);
		return first_for_nt;
	}
	else {
		std::set<char> res;
		res.emplace(form.at(0));
		return res;
	}
}

void SLR1_parser::init_first() {
	for (auto rule_it = grammar.begin(); rule_it != grammar.end(); ++rule_it) {
		insert_ff_sets(first_, rule_it->first, first(rule_it->second));
	}
}

std::set<char> SLR1_parser::firstFollow(char symb) {
	return std::isupper(symb) ? first_.at(symb) : std::set<char>{symb};
}

void SLR1_parser::init_follow() {
	FirstFollow_sets previous_state = follow_;
	follow_.emplace('S', std::set<char>{'$'});
	while (previous_state != follow_) {
		previous_state = follow_;
		for (auto rule_it = grammar.begin(); rule_it != grammar.end(); ++rule_it) {
			for (auto symb_it = rule_it->second.begin(); symb_it != rule_it->second.end(); ++symb_it) {
				if (std::isupper(*symb_it)) {
					if (symb_it + 1 != rule_it->second.end()) {
						insert_ff_sets(follow_, *symb_it, firstFollow(*(symb_it + 1)));
					}
					else {
						auto it = follow_.find(rule_it->first);
						if (it != follow_.end()) {
							insert_ff_sets(follow_, *symb_it, it->second);
						}
					}
				}
			}
		}
	}
}

bool SLR1_parser::parse(std::string input, bool print_tree) {
	std::stack<Stack_elem> st;
	std::stack<TreeNode> tree;
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
			tree.push(TreeNode(input.at(input_pointer)));
			st.push(Stack_elem(input.at(input_pointer), action.id));
			++input_pointer;
		}
		else if (action.type == TYPES::REDUCE) {
			auto grammar_rule = grammar.begin();
			for (size_t i = 0; i < grammar.size() && i<action.id; grammar_rule++, ++i);
			size_t pop_count = grammar_rule->second.size();
			TreeNode parent(grammar_rule->first);
			for (size_t i = 0; i < pop_count; ++i) {
				TreeNode child = tree.top();
				parent.children.push_back(child);
				tree.pop();
				st.pop();
			}
			tree.push(parent);
			Table_cell goto_cell = table.table_.at(st.top().state).at(grammar_rule->first);
			if (goto_cell.type != TYPES::GOTO) {
				return false;
			}
			else{
				st.push(Stack_elem(grammar_rule->first, goto_cell.id));
			}
		}
		else if (action.type == TYPES::ACCEPT) {
			if (print_tree) {
				complete_tree_(tree);
				print_tree_(tree.top());
				std::cout << std::endl;
			}
			return true;
		}
		else {
			std::cout << "Fail at position " << input_pointer << std::endl;
			return false;
		}
	}
}

void SLR1_parser::print_tree_(const TreeNode& node) const {
	std::cout << "[." << node.symb << ' ';
	for (auto child_it = node.children.rbegin(); child_it != node.children.rend(); ++child_it) {
		if (child_it->children.empty())
		{
			std::cout << child_it->symb << ' ';
		}
		else {
			print_tree_(*child_it);
		}
	}
	std::cout << "] ";
}

void SLR1_parser::complete_tree_(std::stack<TreeNode> &tree) {
	if (tree.size() && tree.top().symb != 'S') {
		std::stack<TreeNode> copy = tree;
		std::string result_rule;
		while (copy.size()) {
			result_rule.push_back(copy.top().symb);
			copy.pop();
		}
		std::reverse(result_rule.begin(), result_rule.end());
		auto range = grammar.equal_range('S');
		for (auto it = range.first; it != range.second; ++it) {
			if (it->second == result_rule ) {
				TreeNode parent('S');
				while (tree.size()) {
					parent.children.push_back(tree.top());
					tree.pop();
				}
				tree.push(parent);
			}
		}
	}
}