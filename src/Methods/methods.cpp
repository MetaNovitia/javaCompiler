#include <iostream>
#include "methods.h"
#include "byteHelper.h"
#include <vector>
#include <utility>
#include <map>
#include "constantPool.h"
#include "basicBlock.h"
#include <set>
#include <algorithm>

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

Attribute::Attribute(char** buffer, ConstantPool cp) {
	u2 attribute_name_index = get(buffer, 2);
	u4 attribute_length = get(buffer, 4);
	end = (*buffer) + attribute_length;

	name = cp.getCP(attribute_name_index).getString();
}

string Attribute::getName() { return name; }

void Attribute::skip(char** buffer) { (*buffer) = end; }

void Method::setLeaders() {
	char* temp = start;
	set<char*> lSet;
	lSet.insert(start);

	while ((temp) < end) {
		char op = get(&temp, 1);
		string name = opStr[op].first;
		int operands = opStr[op].second;

		if ( name.find("if") == 0 ) {
			int16_t offset = getSigned2(&temp);
			lSet.insert(temp);
			lSet.insert(temp - 3 + offset);
		} else if ( name == "goto" ) {
			int16_t offset = getSigned2(&temp);
			lSet.insert(temp);
		} else temp += operands;
	}

	leaders = vector<char*>(lSet.begin(), lSet.end());
}

void Method::setBlocks() {

	map<char*, BasicBlock*> bMap;
	int last = leaders.size()-1;

	for (int i=0; i<last; i++) {
		BasicBlock b = BasicBlock(leaders[i], leaders[i+1]-3);
		blocks.push_back(b);
		bMap[leaders[i]] = &blocks[i];
	}
	BasicBlock b = BasicBlock(leaders[last], end-1);
	blocks.push_back(b);
	bMap[leaders[last]] = &blocks[last];

	for (int i=0; i<blocks.size()-1; i++) {
		char* e = blocks[i].getEnd();
		char op = get(&temp, 1);
		string name = opStr[op].first;
		int operands = opStr[op].second;
	}

	top = bList[0];
}

void Method::setCode(char** buffer) {
	u2 max_stack = get(buffer, 2);
	u2 max_locals = get(buffer, 2);
	u4 code_length = get(buffer, 4);

	start = (*buffer);
	end = (*buffer) + code_length;
}

Method::Method(char** buffer, ConstantPool _cp) {
    u2 access_flags = get(buffer, 2);
    u2 name_index = get(buffer, 2);
    u2 descriptor_index = get(buffer, 2);

	name = _cp.getCP(name_index).getString();
	string type = _cp.getCP(descriptor_index).getString();

	// Type Parsing Begin //
	int pos = 1;
	while (type[pos] != ')') {
		string s = "";
		s += type[pos];
		if (s == "[") 
			while (type[pos] != ';') {
				pos++;
				s += type[pos];
			}
		params.push_back(s);
		pos++;
	} pos++;

	while (pos < type.size()) {
		returnType += type[pos];
		pos++;
	}
	//  Type Parsing End  //

    int attCount = get(buffer, 2);

    for (int i=0; i<attCount; i++) {
		Attribute att = Attribute(buffer, _cp);
		if (att.getName() == "Code") {
			setCode(buffer);
			setLeaders();
		} att.skip(buffer);
	}
}

Method::Method() {}
string Method::getName() { return name; }
char* Method::getStart() { return start; }
char* Method::getEnd() { return end; }
vector<string> Method::getParams() { return params; }