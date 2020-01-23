#ifndef GRAPH_OF_STATES_H
#define GRAPH_OF_STATES_H

#include "SLR_base.h"

class Graph_of_states {
public:
	std::vector<State> states_;
	std::map<size_t, std::map<char, size_t>> adjency_lst_;
	Grammar grammar;
	
	Graph_of_states() {}
	Graph_of_states(const Grammar &g);
	void closure(Items& state);
	void compute_graph();
	/*void build_table();*/
};

#endif