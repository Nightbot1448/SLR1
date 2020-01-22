#ifndef SLR_BASE
#define SLR_BASE

#include <string>
#include <map>
#include <utility>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>

enum TYPES {
	ACCEPT,
	SHIFT,
	GOTO,
	REDUCE,
	FAIL
};

class Item {
public:
	char left_part;
	std::string before_point;
	std::string after_point;
	size_t hash_;
	Item(char l, const std::string& bp, const std::string& ap);
};

class State {
public:
	std::vector<Item> items_;
	size_t hash_;
	State(const std::vector<Item>);
};

class Table_cell {
public:
	TYPES type;
	size_t id;

	Table_cell();
	Table_cell(TYPES t, size_t id);
};

bool operator==(Item f, Item s);
bool operator!=(Item f, Item s);

bool operator==(Table_cell f, Table_cell s);
bool operator!=(Table_cell f, Table_cell s);

typedef std::multimap<char, std::string> Grammar;
typedef std::vector<Item> Items;
typedef std::map<char, std::set<char>> FirstFollow_sets;


#endif