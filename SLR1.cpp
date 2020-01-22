#include "SLR_parser.h"
#include "SLR_base.h"

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

	return 0;
}
