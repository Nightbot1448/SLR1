#ifndef PARSING_TABLE_H
#define PARSING_TABLE_H

#include "Graph_of_states.h"

class Parsing_table {
	Grammar grammar_;
	Graph_of_states graph_;
	FirstFollow_sets follow_;
public:
	std::map<size_t, std::map<char, Table_cell>> table_;
	Parsing_table() {}
	Parsing_table(const Grammar &g_, const Graph_of_states &graph, const FirstFollow_sets &follow);
	void init_table(std::vector<char> char_base_);
	std::vector<char> V();
	void fill_table();
};

#endif //PARSING_TABLE_H