# CMakeList.txt : CMake project for SLR(1), include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("SLR(1)")

set(CMAKE_CXX_STANDARD 17)

set(SRC "src/SLR_parser.h"
		"src/SLR_parser.cpp"
		"src/Graph_of_states.h"
		"src/Graph_of_states.cpp"
		"src/Parsing_table.h"
		"src/Parsing_table.cpp"
		"src/SLR_base.h"
		"src/SLR_base.cpp"
		)

include_directories(src)

add_library(SLR ${SRC})

add_executable (SLR_parser src/SLR1.cpp)
target_link_libraries(SLR_parser SLR)

find_package(GTest)
if (GTest_FOUND)
	include_directories(${GTEST_INCLUDE_DIRS})

	enable_testing()

	add_executable(run_tests test/main_tests.cpp test/arithmetic.cpp test/ab_grammar.cpp)
	target_link_libraries(run_tests SLR gtest pthread)

	add_test(run_tests run_tests)
endif()
