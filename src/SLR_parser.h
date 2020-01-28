#ifndef SLR_PARSER_H 
#define SLR_PARSER_H

#include "Graph_of_states.h"
#include "Parsing_table.h"

#include <stack>


class SLR1_parser {
	FirstFollow_sets first_;
	FirstFollow_sets follow_;
	Grammar grammar;
	Graph_of_states graph;
	Parsing_table table;

	std::set<char> first(std::string form);
	//std::set<char> follow(char form, FirstFollow_sets& previous_state);
	std::set<char> firstFollow(char symb);
	void insert_ff_sets(FirstFollow_sets &set_, char symb, std::set<char> s);

	void init_first();
	void init_follow();
	void print_tree_(const TreeNode& tree) const;
	void complete_tree_(std::stack<TreeNode>& tree);
	
public:
	SLR1_parser(){}
	SLR1_parser(const Grammar &grammar, bool print_table = false);

	bool parse(std::string input, bool print_tree = false);
	void print_parsing_table();
};

#endif // SLR_PARSER_H 
