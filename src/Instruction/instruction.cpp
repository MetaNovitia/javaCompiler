#include "instruction.h"
#include "basicBlock.h"
#include "byteHelper.h"
#include "constantPool.h"
#include <vector>
#include <utility>
#include <iostream>

typedef uint16_t u2;

Instruction::Instruction(char _opcode, string _type)
: Value("Instr", _opcode) { opcode = _opcode; type = _type; }

void Instruction::printInstr() { 
	std::cout << type << std::endl; 
}

string Instruction::getType() { return type; }

MoveInstruction::MoveInstruction(char _opcode, Value* _op1, Value* _op2)
: Instruction(_opcode, "MOV") {
	op1=_op1; op2=_op2;
}

void MoveInstruction::printAssembly(){
	std::cout << "MOV " << (*op1) << ", " << (*op2) << std::endl; 
}

BinaryInstruction::BinaryInstruction(char _opcode, Value* _op1, Value* _op2, Value* _op3, string _operation) 
: Instruction(_opcode, "BIN") {
	op1=_op1; op2=_op2; op3=_op3; operation=_operation;
}

void BinaryInstruction::printAssembly(){
	std::cout << operation << " " << (*op1) << ", " << (*op2) << ", " << (*op3) << std::endl; 
}

CmpInstruction::CmpInstruction(char _opcode, Value* _cond, Value* _op1, Value* _op2) 
: Instruction(_opcode, "CMP") {
	cond=_cond; op1=_op1; op2=_op2;
}

void CmpInstruction::printAssembly(){
	std::cout <<  "CMP " << (*cond) << ", " << (*op1) << ", " << (*op2) << std::endl; 
}

CondBranchInstruction::CondBranchInstruction(
	char _opcode, Value* _cond, BasicBlock* _targetBB1, BasicBlock* _targetBB2, string _predicate)
: Instruction(_opcode, "BRCond") {
	cond=_cond; targetBB1=_targetBB1; targetBB2=_targetBB2; predicate=_predicate;
}

void CondBranchInstruction::printAssembly(){
	std::cout 
		<< predicate << " " << (*cond) << ", #" 
		<< (*targetBB1).num << ", #" << (*targetBB2).num 
	<< std::endl; 
}

UncondBranchInstruction::UncondBranchInstruction(char _opcode, BasicBlock* _targetBB) 
: Instruction(_opcode, "JMP") {
	targetBB=_targetBB;
}

void UncondBranchInstruction::printAssembly(){
	std::cout 
		<< "JMP #" << (*targetBB).num 
	<< std::endl; 
}

CallInstruction::CallInstruction(char _opcode, string _targetMethod) 
: Instruction(_opcode, "CALL") {
	targetMethod=_targetMethod;
}

void CallInstruction::printAssembly(){
	std::cout 
		<< "CALL " << targetMethod
	<< std::endl; 
}

ReturnInstruction::ReturnInstruction(char _opcode, Value* _op1) 
: Instruction(_opcode, "RET") {
	op1=_op1;
}

void ReturnInstruction::printAssembly(){
	std::cout << "RET ";
	if (op1 != nullptr) std::cout << op1 << std::endl; 
}

PhiInstruction::PhiInstruction(char _opcode) 
: Instruction(_opcode, "PHI") { }

void PhiInstruction::printAssembly(){
	
}

void makeInstruction(char** buffer, int* stackCt, BasicBlock* b, ConstantPool* cp) {
	char op = get(buffer, 1);
	string opcode = opStr[op].name;
	vector<Instruction*> i;

	if 		  (opcode == "iconst_m1") {	
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new Constant(-1);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "iconst_0") {
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new Constant(0);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "iconst_1") {	
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new Constant(1);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "iconst_2") {
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new Constant(2);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "iconst_3") {
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new Constant(3);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "iconst_4") {
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new Constant(4);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "iconst_5") {
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new Constant(5);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "iload_0") {	
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new LocalVar(0);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "iload_1") {
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new LocalVar(1);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "iload_2") {
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new LocalVar(2);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "iload_3") {
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new LocalVar(3);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "istore_0") {
		Value* op1 = new LocalVar(0);
		Value* op2 = new StackVar((*stackCt)-1);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)--;
	} else if (opcode == "istore_1") {
		Value* op1 = new LocalVar(1);
		Value* op2 = new StackVar((*stackCt)-1);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)--;
	} else if (opcode == "istore_2") {
		Value* op1 = new LocalVar(2);
		Value* op2 = new StackVar((*stackCt)-1);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)--;
	} else if (opcode == "istore_3") {
		Value* op1 = new LocalVar(3);
		Value* op2 = new StackVar((*stackCt)-1);
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)--;
	} else if (opcode == "iadd") {
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		Value* op3 = new StackVar((*stackCt)-2);
		b->addInstruction(new BinaryInstruction(op, op1, op2, op3, "ADD"));
		(*stackCt)--;
	} else if (opcode == "iinc") {
		int locIndex = get(buffer, 1);
		Value* op1 = new LocalVar(locIndex);
		Value* op2 = new LocalVar(locIndex);
		Value* op3 = new Constant(getSigned1(buffer));
		b->addInstruction(new BinaryInstruction(op, op1, op2, op3, "INC"));
	} else if (opcode == "isub") {
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		Value* op3 = new StackVar((*stackCt)-2);
		b->addInstruction(new BinaryInstruction(op, op1, op2, op3, "SUB"));
		(*stackCt)--;
	} else if (opcode == "imul") {
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		Value* op3 = new StackVar((*stackCt)-2);
		b->addInstruction(new BinaryInstruction(op, op1, op2, op3, "MUL"));
		(*stackCt)--;
	} else if (opcode == "ishl") {
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		Value* op3 = new StackVar((*stackCt)-2);
		b->addInstruction(new BinaryInstruction(op, op1, op2, op3, "SHL"));
		(*stackCt)--;
	} else if (opcode == "ishr") {
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		Value* op3 = new StackVar((*stackCt)-2);
		b->addInstruction(new BinaryInstruction(op, op1, op2, op3, "SHR"));
		(*stackCt)--;
	} else if (opcode == "if_icmpne"){
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JNE"));
	} else if (opcode == "if_icmpeq"){
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JE"));
	} else if (opcode == "if_icmpge"){
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JGE"));
	} else if (opcode == "if_icmpgt"){
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JG"));
	} else if (opcode == "if_icmple"){
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JLE"));
	} else if (opcode == "if_icmplt"){
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-2);
		Value* op2 = new StackVar((*stackCt)-1);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JL"));
	} else if (opcode == "ifeq") {
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-1);
		Value* op2 = new Constant(0);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JE"));
	} else if (opcode == "ifne") {
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-1);
		Value* op2 = new Constant(0);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JNE"));
	} else if (opcode == "ifge") {
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-1);
		Value* op2 = new Constant(0);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JGE"));
	} else if (opcode == "ifgt") {
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-1);
		Value* op2 = new Constant(0);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JG"));
	} else if (opcode == "ifle") {
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-1);
		Value* op2 = new Constant(0);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JLE"));
	} else if (opcode == "iflt") {
		Value* cond = new TempVar(0);
		Value* op1 = new StackVar((*stackCt)-1);
		Value* op2 = new Constant(0);
		b->addInstruction(new CmpInstruction(op, cond, op1, op2));
		(*stackCt)-=2;

		vector<BasicBlock*> next = b->getNext();
		b->addInstruction(
			new CondBranchInstruction(
				op, cond, next[1], next[0], "JL"));
	} else if (opcode == "goto") {
		Value* cond = new TempVar(0);
		b->addInstruction(
			new UncondBranchInstruction(op, b->getNext()[0]));
	} else if (opcode == "bipush") {
		Value* op1 = new StackVar((*stackCt));
		Value* op2 = new Constant(getSigned1(buffer));
		b->addInstruction(new MoveInstruction(op, op1, op2));
		(*stackCt)++;
	} else if (opcode == "invokestatic"){
		u2 i = cp->getCP(get(buffer,2)).getNum();
		u2 ind = cp->getCP(i).getNum() >> 16;
		string nm = cp->getCP(ind).getString();
		b->addInstruction(new CallInstruction(op, nm));
	} else if (opcode == "invokevirtual") {	
		u2 i = cp->getCP(get(buffer,2)).getNum();
		u2 ind = cp->getCP(i).getNum() >> 16;
		string nm = cp->getCP(ind).getString();
		b->addInstruction(new CallInstruction(op, nm));
	} else if (opcode == "return") {
		b->addInstruction(new ReturnInstruction(op, nullptr));
	} else if (opcode == "ireturn") {
		Value* op1 = new StackVar((*stackCt)-1);
		b->addInstruction(new ReturnInstruction(op, op1));
		(*stackCt)--;
	} else if (opcode == "getstatic"){	
		b->addInstruction(new Instruction(op, opcode));
		get(buffer,2);
	} else { 
		b->addInstruction(new Instruction(op, "None"));
		get(buffer, opStr[op].opNum); 
	}
}