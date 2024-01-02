#include "instruction.h"

int reg_to_num(string s, int pos) {
	string ss = s.substr(pos);
	return stoi(ss);
}

int reg_to_num(string s, int pos, int cnt) {
	string ss = s.substr(pos, cnt);
	return stoi(ss);
}