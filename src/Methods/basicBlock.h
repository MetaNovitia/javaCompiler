#ifndef BASICBLOCK_H_
#define BASICBLOCK_H_

#include <map>
#include <iostream>
#include <vector>
#include <stack>
#include "byteHelper.h"

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

class BasicBlock {

	char* leader;
	char* end;

	vector<BasicBlock*> predecessors;
	vector<BasicBlock*> successors;

public:

	BasicBlock() {};
	BasicBlock(char* l, char* e);

	void setNext(BasicBlock* next);
	void setPrev(BasicBlock* prev);

	char* getStart();
	char* getEnd();

};

#endif