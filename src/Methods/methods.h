#ifndef METHODS_H_
#define METHODS_H_

#include <map>
#include <iostream>
#include <vector>
#include <stack>
#include "byteHelper.h"
#include "constantPool.h"

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

class Attribute {
	string name;
	char* end;
public:
	Attribute(char** buffer, ConstantPool cp);
	string getName();
	void skip(char** buffer);
};

class CodeAttribute {
	u2 max_stack;
	u2 max_locals;
	char* start;
	char* end;

public:
	CodeAttribute();
	CodeAttribute(char** buffer);
	char* getStart();
	char* getEnd();
};

class Method {
    string name;
	vector<string> params;
	string returnType;
	CodeAttribute code;
public:
	Method();
    Method(char** buffer, ConstantPool _cp);
	string getName();
	char* getStart();
	char* getEnd();
	vector<string> getParams();
};

#endif