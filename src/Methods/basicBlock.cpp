#include <map>
#include <iostream>
#include <vector>
#include <stack>
#include "byteHelper.h"
#include "basicBlock.h"

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

BasicBlock::BasicBlock() { }
BasicBlock::BasicBlock(char* l, char* e) { leader=l; end=e;}
void BasicBlock::setNext(BasicBlock* next) { successors.push_back(next); }
void BasicBlock::setPrev(BasicBlock* prev) { predecessors.push_back(prev); }
char* BasicBlock::getStart() { return leader; }
char* BasicBlock::getEnd() { return end; }