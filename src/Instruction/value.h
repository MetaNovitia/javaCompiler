#ifndef VALUE_H_
#define VALUE_H_

#include <iostream>

using namespace std;

class Value {
	string name;
	int val;
public:
	Value(string _name, int _val);
	friend ostream& operator<<(ostream& os, const Value& dt);
};

class StackVar: public Value {
	int index;
public:
	StackVar(int _index);
};

class LocalVar: public Value {
	int index;
public:
	LocalVar(int _index);
};

class Constant: public Value {
	int val;
public:
	Constant(int _val);
};

class TempVar: public Value {
	int index;
public:
	TempVar(int _index);
};

// class MethodName: public Value {
// 	int index;
// public:
// 	MethodName(int _index);
// };

#endif