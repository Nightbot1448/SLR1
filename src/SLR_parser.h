#ifndef SLR_PARSER_H 
#define SLR_PARSER_H

#include "Graph_of_states.h"
#include "Parsing_table.h"

class SLR1_parser {
	FirstFollow_sets first;
	FirstFollow_sets follow;
	Grammar grammar;
	Graph_of_states graph;
	Parsing_table table;


	void init_first();
	void init_follow();
	
public:
	SLR1_parser(){}
	SLR1_parser(const Grammar &grammar, bool print_table = false);

	bool parse(std::string input);
	void print_parsing_table();
};

#endif // SLR_PARSER_H 
