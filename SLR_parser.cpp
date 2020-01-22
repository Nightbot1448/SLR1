#include "SLR_parser.h"



SLR1_parser::SLR1_parser(const Grammar &grammar) : graph(Graph_of_states(grammar)) {
	//init_first();
	init_follow();
	table = Parsing_table(grammar, graph, follow);
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

//void SLR1_parser::compute_graph() {
//
//}