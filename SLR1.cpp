#include "SLR_parser.h"
#include "SLR_base.h"

#include <iostream>

int main()
{
	Grammar grammar;
	grammar.emplace('S', "E");
	grammar.emplace('E', "T");
	grammar.emplace('E', "E+T");
	grammar.emplace('E', "E-T");
	grammar.emplace('T', "F");
	grammar.emplace('T', "T*F");
	grammar.emplace('T', "T/F");
	grammar.emplace('F', "(E)");
	grammar.emplace('F', "-F");
	grammar.emplace('F', "n");


	SLR1_parser parser(grammar);
	std::string in("n");
	std::cout << parser.parse(in) << ' ' << in << std::endl;
	in = "-n";
	std::cout << parser.parse(in) << ' ' << in << std::endl;
	in = "n+n";
	std::cout << parser.parse(in) << ' ' << in << std::endl;
	in = "-n+(n*n--n/n)+n";
	std::cout << parser.parse(in) << ' ' << in << std::endl;
	in = "n*-n";
	std::cout << parser.parse(in) << ' ' << in << std::endl;
	in = "n*/n";
	std::cout << parser.parse(in) << ' ' << in << std::endl;
	in = "n*(n";
	std::cout << parser.parse(in) << ' ' << in << std::endl;
	in = "n*-n)";
	std::cout << parser.parse(in) << ' ' << in << std::endl;
	in = "n*-nn";
	std::cout << parser.parse(in) << ' ' << in << std::endl;

	return 0;
}
