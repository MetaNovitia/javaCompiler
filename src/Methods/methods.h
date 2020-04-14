#ifndef METHODS_H_
#define METHODS_H_

#include <map>
#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include "byteHelper.h"
#include "constantPool.h"
#include "basicBlock.h"

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

class Method {
    string name;
	vector<string> params;
	vector<char*> leaders;
	vector<BasicBlock> blocks;
	string returnType;
	char* start;
	char* end;
public:
	Method();
    Method(char** buffer, ConstantPool _cp);
	void setCode(char** buffer);
	void setLeaders();
	void setBlocks();
	string getName();
	char* getStart();
	char* getEnd();
	vector<string> getParams();
};

#endif