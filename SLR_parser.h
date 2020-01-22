#ifndef SLR_PARSER_H 
#define SLR_PARSER_H

#include "Graph_of_states.h"
#include "Parsing_table.h"

class SLR1_parser {
	FirstFollow_sets first;
	FirstFollow_sets follow;
	Graph_of_states graph;
	Parsing_table table;


	void init_first();
	void init_follow();
	//void compute_graph();

public:
	SLR1_parser() = delete;
	SLR1_parser(const Grammar &grammar);
};

#endif // !SLR_PARSER_H 
