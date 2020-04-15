#ifndef BASICBLOCK_H_
#define BASICBLOCK_H_

#include <map>
#include <iostream>
#include <vector>
#include <stack>
#include "byteHelper.h"
#include "value.h"

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

	vector<Value*> instructions;

public:

	int num;

	BasicBlock();
	BasicBlock(int num, char* l, char* e);

	void setNext(BasicBlock* next);
	void setPrev(BasicBlock* prev);
	void addInstruction(Value* instr);
	vector<Value*> getInstructions();

	char* getStart();
	char* getEnd();
	vector<BasicBlock*> getNext();

	void printBlock();

};

#endif