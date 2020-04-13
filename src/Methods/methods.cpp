#include <iostream>
#include "methods.h"
#include "byteHelper.h"
#include <vector>
#include "constantPool.h"

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

void Attribute::skip(char** buffer) {
	while ((*buffer) != end) get(buffer, 1);
}

CodeAttribute::CodeAttribute() {}

CodeAttribute::CodeAttribute(char** buffer) {
	max_stack = get(buffer, 2);
	max_locals = get(buffer, 2);
	u4 code_length = get(buffer, 4);

	start = (*buffer);
	end = (*buffer) + code_length;
}
char* CodeAttribute::getStart() { return start; }
char* CodeAttribute::getEnd() { return end; }

Method::Method(char** buffer, ConstantPool _cp) {
    u2 access_flags = get(buffer, 2);
    u2 name_index = get(buffer, 2);
    u2 descriptor_index = get(buffer, 2);

	name = _cp.getCP(name_index).getString();
	string type = _cp.getCP(descriptor_index).getString();
	int pos = 1;
	while (type[pos] != ')') {
		string s = "";
		s += type[pos];
		if (s == "[") {
			while (type[pos] != ';') {
				pos++;
				s += type[pos];
			}
		}
		params.push_back(s);
		pos++;
	} pos++;
	while (pos < type.size()) {
		returnType += type[pos];
		pos++;
	}

    int attCount = get(buffer, 2);

    for (int i=0; i<attCount; i++) {
		Attribute att = Attribute(buffer, _cp);
		if (att.getName() == "Code") 
			code = CodeAttribute(buffer);
		att.skip(buffer);
	}
}
Method::Method() {}
string Method::getName() { return name; }
char* Method::getStart() {return code.getStart(); }
char* Method::getEnd() {return code.getEnd(); }
vector<string> Method::getParams() {return params;}