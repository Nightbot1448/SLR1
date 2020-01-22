# CMakeList.txt : CMake project for SLR(1), include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("SLR(1)")

set(SRC "SLR1.cpp"
		"SLR_parser.h"
		"SLR_parser.cpp"
		"Graph_of_states.h"
		"Graph_of_states.cpp"
		"Parsing_table.h"
		"Parsing_table.cpp"
		"SLR_base.h"
		"SLR_base.cpp"
		)

# Add source to this project's executable.
add_executable (SLR_parser ${SRC})

# TODO: Add tests and install targets if needed.
