#include "value.h"
#include <iostream>

using namespace std;

Value::Value( string _name, int _val ) {
	name = _name;
	val = _val;
}

StackVar::StackVar(int _index)
: Value("Stack", _index) { }

LocalVar::LocalVar(int _index)
: Value("Local", _index) { }

Constant::Constant(int _val)		// TODO: assuming only ints
: Value("Const", _val) { }

TempVar::TempVar(int _index)
: Value("Tmp", _index) { }

// MethodName::MethodName(int _index)
// : Value("MethodName", _index) { }

ostream& operator<<(ostream& os, const Value& v)
{
    os << v.name << v.val;
    return os;
}