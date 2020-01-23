#include "SLR_parser.h"
#include "SLR_base.h"

#include <iostream>
#include <getopt.h>

int main(int argc, char **argv)
{
	const char* short_options = "p::i:";

	const struct option long_options[] = {
		{"input",required_argument,NULL,'i'},
		{"print_table",no_argument,NULL,'p'},
		{NULL,0,NULL,0}
	};

	int rez;
	int option_index;

	bool print_parsing_table = false;
	std::string input_string("-n+(n*n--n/n)+n");
	
	while ((rez=getopt_long(argc,argv,short_options,
		long_options,&option_index))!=-1){

		switch(rez){
			case 'p': {
				print_parsing_table = true;
				break;
			}
			case 'i': {
				input_string = optarg;
				break;
			}
			case '?': default: {
				printf("found unknown option\n");
				break;
			}
		}
	}

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


	SLR1_parser parser(grammar, print_parsing_table);
	
	std::cout 	<< "Input string: " << input_string << std::endl 
				<< "Result : "<< (parser.parse(input_string) ? "accepted" : "reject") << std::endl;
	
	return 0;
}
