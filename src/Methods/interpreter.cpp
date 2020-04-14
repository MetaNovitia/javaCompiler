#include <map>
#include <iostream>
#include "interpreter.h"
#include "byteHelper.h"
#include "constantPool.h"

// FRAME //
Frame::Frame() {}
int Frame::size() { return frame.size(); }

int Frame::pop() { int top = frame.top(); frame.pop(); return top; }
void Frame::push(int value) { frame.push(value); }

int Frame::getLocal(int pos) { return local[pos]; }
void Frame::addLocal(int value, int pos) { 
	while (local.size() < pos+1) local.push_back(0);
	local[pos] = value;
}
// FRAME //

bool Interpreter::exec(char** buffer) {
	string opcode = opStr[get(buffer, 1)].first;

	// cout << opcode << " " << endl;
	if 		(opcode == "iconst_m1") 	{	frame.push(-1);							}
	else if (opcode == "iconst_0") 		{	frame.push(0);							}
	else if (opcode == "iconst_1") 		{	frame.push(1);							}
	else if (opcode == "iconst_2") 		{	frame.push(2);							}
	else if (opcode == "iconst_3") 		{	frame.push(3);							}
	else if (opcode == "iconst_4") 		{	frame.push(4);							}
	else if (opcode == "iconst_5") 		{	frame.push(5);							}
	else if (opcode == "iload_0") 		{	frame.push(frame.getLocal(0));			}
	else if (opcode == "iload_1") 		{	frame.push(frame.getLocal(1));			}
	else if (opcode == "iload_2") 		{	frame.push(frame.getLocal(2));			}
	else if (opcode == "iload_3") 		{	frame.push(frame.getLocal(3));			}
	else if (opcode == "istore_0") 		{	frame.addLocal(frame.pop(), 0);			}
	else if (opcode == "istore_1") 		{	frame.addLocal(frame.pop(), 1);			}
	else if (opcode == "istore_2") 		{	frame.addLocal(frame.pop(), 2);			}
	else if (opcode == "istore_3") 		{	frame.addLocal(frame.pop(), 3);			}
	else if (opcode == "iadd") 			{	frame.push(frame.pop()+frame.pop());	}
	else if (opcode == "iinc") 			{	int pos = get(buffer, 1);
											int val = frame.getLocal(pos);
											val += get(buffer, 1);
											frame.addLocal(val, pos);				}
	else if (opcode == "isub") 			{	frame.push(-frame.pop()+frame.pop());	}
	else if (opcode == "imul") 			{	frame.push(frame.pop()*frame.pop());	}
	else if (opcode == "ishl") 			{	int amt = frame.pop();
											frame.push(frame.pop() << amt);			}
	else if (opcode == "ishr") 			{	int amt = frame.pop();
											frame.push(frame.pop() >> amt);			}
	else if (opcode == "if_icmpne") 	{	int16_t offset = getSigned2(buffer);
											if(frame.pop() != frame.pop()) 
												(*buffer) += offset - 3;			}
	else if (opcode == "if_icmpeq") 	{	int16_t offset = getSigned2(buffer);
											if(frame.pop() == frame.pop()) 
												(*buffer) += offset - 3;			}
	else if (opcode == "if_icmpge") 	{	int16_t offset = getSigned2(buffer);
											if(frame.pop() <= frame.pop()) 
												(*buffer) += offset - 3;			}
	else if (opcode == "if_icmpgt") 	{	int16_t offset = getSigned2(buffer);
											if(frame.pop() < frame.pop()) 
												(*buffer) += offset - 3;			}
	else if (opcode == "if_icmple") 	{	int16_t offset = getSigned2(buffer);
											if(frame.pop() >= frame.pop()) 
												(*buffer) += offset - 3;			}
	else if (opcode == "if_icmplt") 	{	int16_t offset = getSigned2(buffer);
											if(frame.pop() > frame.pop()) 
												(*buffer) += offset - 3;			}
	else if (opcode == "ifeq") 			{	int16_t offset = getSigned2(buffer);
											if(frame.pop() == 0) 
												(*buffer) += offset - 3;			}
	else if (opcode == "ifne") 			{	int16_t offset = getSigned2(buffer);
											if(frame.pop() != 0) 
												(*buffer) += offset - 3;			}
	else if (opcode == "ifge") 			{	int16_t offset = getSigned2(buffer);
											if(frame.pop() > 0) 
												(*buffer) += offset - 3;			}
	else if (opcode == "ifgt") 			{	int16_t offset = getSigned2(buffer);
											if(frame.pop() >= 0) 
												(*buffer) += offset - 3;			}
	else if (opcode == "ifle") 			{	int16_t offset = getSigned2(buffer);
											if(frame.pop() <= 0) 
												(*buffer) += offset - 3;			}
	else if (opcode == "iflt") 			{	int16_t offset = getSigned2(buffer);
											if(frame.pop() < 0) 
												(*buffer) += offset - 3;			}
	else if (opcode == "goto") 			{	(*buffer) += getSigned2(buffer) - 3;	}
	else if (opcode == "bipush") 		{	frame.push(get(buffer, 1)); 			}
	else if (opcode == "invokestatic") 	{	u2 i = cp.getCP(get(buffer,2)).getNum();
											u2 ind = cp.getCP(i).getNum() >> 16;
											string nm = cp.getCP(ind).getString();
											run(nm);
																					}
	else if (opcode == "invokevirtual") {	u2 i = cp.getCP(get(buffer,2)).getNum();
											u2 ind = cp.getCP(i).getNum() >> 16;
											string nm = cp.getCP(ind).getString();
											if (nm=="println") 
												cout << "println: " << frame.pop() << endl;	}
	else if (opcode == "return") 		{	return false;}
	else if (opcode == "ireturn") 		{	return false;}
	else if (opcode == "getstatic") 	{	get(buffer,2);							}
	return true;
}

void Interpreter::run(string mName) {

	Method m = methods[mName];
	Frame newF = Frame();
	vector<string> params = m.getParams();

	for (int i=0; i<params.size(); i++) {
		if (params[i][0] != '[') {
			newF.addLocal(frame.pop(), 0);
		}
	}

	frames.push(newF);
	frame = frames.top();

	int debug=0;
	char* temp = m.getStart();
	bool cont = true;
	while ((temp) < m.getEnd() && cont) {
		cont = exec(&temp);
		debug++;
	}

	// if ()
	// int ret = frame.pop();
	frames.pop();
	frame = frames.top();
	// frame.push(ret);
}

void Interpreter::start() {
	frames.push(Frame());
	run("main");
}

Interpreter::Interpreter() {}
Interpreter::Interpreter(map<string, Method> _methods, ConstantPool _cp) {
	methods = _methods;
	cp = _cp;
}