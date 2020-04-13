#ifndef INTREPETER_H_
#define INTREPETER_H_

#include <map>
#include <iostream>
#include <vector>
#include <stack>
#include "byteHelper.h"
#include "constantPool.h"
#include "methods.h"

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

class Frame {
	stack<int> frame;
	vector<int> local;
public:
	Frame();
	int pop();
	void push(int value);

	void addLocal(int value, int pos);
	int getLocal(int pos);

	int size();
};

class Interpreter {
	stack<Frame> frames;
	Frame frame;
	ConstantPool cp;
	map<string, Method> methods;
public:
	Interpreter();
	Interpreter(map<string, Method> _methods, ConstantPool _cp);
	void run(string mName);
	bool exec(char** buffer);
	void start();
};
#endif