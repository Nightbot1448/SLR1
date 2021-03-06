﻿#include "SLR_parser.h"
#include "SLR_base.h"

#include <iostream>
#include <fstream>
#ifdef __linux__
#include <getopt.h>
#endif

int main(int argc, char **argv)
{
	bool print_parsing_table = false;
	bool print_tree = false;
	std::string input_string("-n+(n*n--n/n)+n");

	std::string input_file;

	const char* short_options = "pti:f:";
	int res=0;
	int option_index;
#ifdef __linux__
	const struct option long_options[] = {
		{"file",required_argument,NULL,'f'},
		{"input",required_argument,NULL,'i'},
		{"print_tree",no_argument,NULL,'t'},
		{"print_table",no_argument,NULL,'p'},
		{NULL,0,NULL,0}
	};

	while ((res=getopt_long(argc,argv,short_options,
		long_options,&option_index))!=-1){
		switch(res){
			case 'p': {
				print_parsing_table = true;
				break;
			}
			case 't': {
				print_tree = true;
				break;
			}
			case 'i': {
				input_string = optarg;
				break;
			}
			case 'f': {
				input_file = optarg;
				break;
			}
			case '?': default: {
				std::cout << "unknown option" << std::endl;
				break;
			}
		}
	}
#endif
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

	SLR1_parser parser;
	try{
		parser = SLR1_parser(grammar, print_parsing_table);
	}
	catch(std::logic_error &e){
		std::cout << e.what() << std::endl;
	}
	
	if (input_file.empty()) {
		std::cout 	<< "Input string: " << input_string << std::endl 
					<< "Result : "<< (parser.parse(input_string, print_tree) ? "accepted" : "reject") << std::endl;
	}
	else {
		std::ifstream in(input_file, std::ios::in);
		if (in.is_open()) {
			std::string str;
			while (in >> str) {
				std::cout << "Input string: " << str << std::endl
							<< "Result : " << (parser.parse(str, print_tree) ? "accepted" : "reject") 
							<< std::endl << "---" << std::endl;
			}
		}
		else{ 
			std::cout << "file wasn't open; exiting" << std::endl;
			return 0;
		}
	}

	return 0;
}
