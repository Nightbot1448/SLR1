#include "SLR_base.h"

Item::Item(char l, const std::string& bp, const std::string& ap) : left_part(l), before_point(bp), after_point(ap) {
	static std::hash<char> hash_c;
	static std::hash<std::string> hash_s;
	hash_ = hash_c(l) ^ (hash_s(bp) << 1) ^ (hash_s(ap) << 2);
}

bool operator==(Item f, Item s) {
	if (f.left_part == s.left_part &&
		f.before_point == s.before_point &&
		f.after_point == s.after_point)
		return true;
	return false;
}

bool operator!=(Item f, Item s) {
	return !(f == s);
}

bool operator==(Table_cell f, Table_cell s) {
	return (f.type == s.type && f.id == s.id);
}

bool operator!=(Table_cell f, Table_cell s) {
	return !(f == s);
}


State::State(const std::vector<Item> items) :items_(items) {
	hash_ = 0;
	for (size_t i = 0; i < items.size(); ++i) {
		hash_ ^= items.at(i).hash_<< i;
	}
}

Stack_elem::Stack_elem(char sy, size_t st) : symbol(sy), state(st) {}

Table_cell::Table_cell() : type(TYPES::FAIL), id(0) {}

Table_cell::Table_cell(TYPES t, size_t i) : type(t), id(i) {}

TreeNode::TreeNode(char s, std::vector<TreeNode> ch) : symb(s), children(ch) {}