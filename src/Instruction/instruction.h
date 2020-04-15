#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "value.h"
#include "basicBlock.h"
#include "constantPool.h"
#include "methods.h"
#include <vector>
#include <utility>

class Instruction: public Value {
	char opcode;
	string type;
public:
	Instruction(char _opcode, string _type);
	void printInstr();
	string getType();
};


class MoveInstruction: public Instruction {
	Value* op1;
	Value* op2;
public:
	MoveInstruction(char _opcode, Value* _op1, Value* _op2);
	void printAssembly();
};

class BinaryInstruction: public Instruction {
	Value* op1;
	Value* op2;
	Value* op3;
	string operation;
public:
	BinaryInstruction(char _opcode, Value* _op1, Value* _op2, Value* _op3, string _operation);
	void printAssembly();
};

class CmpInstruction: public Instruction {
	Value* cond;
	Value* op1;
	Value* op2;
public:
	CmpInstruction(char _opcode, Value* _cond, Value* _op1, Value* _op2);
	void printAssembly();
};

class CondBranchInstruction: public Instruction {
	Value* cond;
	BasicBlock* targetBB1;
	BasicBlock* targetBB2;
	string predicate;
public:
	CondBranchInstruction(
		char _opcode, Value* _cond, BasicBlock* _targetBB1, 
		BasicBlock* _targetBB2, string _predicate);
	void printAssembly();
};

class UncondBranchInstruction: public Instruction {
	BasicBlock* targetBB;
public:
	UncondBranchInstruction(char _opcode, BasicBlock* _targetBB);
	void printAssembly();
};

class CallInstruction: public Instruction {
	string targetMethod;
public:
	CallInstruction(char _opcode, string _targetMethod);
	void printAssembly();
};

class ReturnInstruction: public Instruction {
	Value* op1;
public:
	ReturnInstruction(char _opcode, Value* _op1);
	void printAssembly();
};

class PhiInstruction: public Instruction {
	vector< pair<BasicBlock*, Value*> > phi;
public:
	PhiInstruction(char _opcode);
	void printAssembly();
};

void makeInstruction(char** buffer, int* stackCt, BasicBlock* b, ConstantPool* cp);

#endif