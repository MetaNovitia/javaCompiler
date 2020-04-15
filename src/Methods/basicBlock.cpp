#include <map>
#include <iostream>
#include <vector>
#include <stack>
#include "byteHelper.h"
#include "basicBlock.h"
#include "value.h"

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

BasicBlock::BasicBlock() { }
BasicBlock::BasicBlock(int n,char* l, char* e) { 
	num=n; leader=l; end=e;
}

void BasicBlock::setNext(BasicBlock* next) { successors.push_back(next); }
vector<BasicBlock*> BasicBlock::getNext() { return successors; }
void BasicBlock::setPrev(BasicBlock* prev) { predecessors.push_back(prev); }
char* BasicBlock::getStart() { return leader; }
char* BasicBlock::getEnd() { return end; }
void BasicBlock::addInstruction(Value* instr) { instructions.push_back(instr); }
vector<Value*> BasicBlock::getInstructions() { return instructions; }

void BasicBlock::printBlock() {
	char* s = leader;
	cout << "leader: " << opStr[get(&s, 1)].name << endl;

	cout << "successors: " << endl;
	for (int i=0; i<successors.size(); i++) {
		if (successors[i] != nullptr) {
			s = successors[i]->getStart();
			cout << opStr[get(&s, 1)].name << endl;
		}
	}

	cout << "predecessors: " << endl;
	for (int i=0; i<predecessors.size(); i++) {
		s = predecessors[i]->getStart();
		cout << opStr[get(&s, 1)].name << endl;
	}

	cout << endl;
}