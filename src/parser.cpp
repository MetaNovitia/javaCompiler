#include <iostream>
#include <fstream>
#include <cstddef>
#include <vector>
#include <map>
#include "constantPool.h"
#include "byteHelper.h"
#include "methods.h"
#include "interpreter.h"

using namespace std ;

char* readFile(string fname) {
	ifstream inFile(fname);

    // get size //
	size_t size = 0;
	inFile.seekg(0, ios::end); 
	size = inFile.tellg(); 
    char* buffer = new char[size];

    // read file //
	inFile.seekg(0, ios::beg); 
    inFile.read(buffer, size);

    inFile.close();

    return buffer;
}

string getClassName(char** buffer, ConstantPool cp) {
    u2      thisClassIndex = get(buffer, 2);
    int     thisClassNameIndex = cp.getCP(thisClassIndex).getNum();
    string  thisClassName = cp.getCP(thisClassNameIndex).getString();
    return thisClassName;
}

void skipInterface(char** buffer) {
    printHex(**buffer);
    printHex(*(*buffer+1));
    u2 size = get(buffer, 2);
    printHex(**buffer);
    printHex(*(*buffer + 1));
    
    printHex(*(*buffer + 2));
    printHex(*(*buffer + 3));
    (*buffer) += size * 2;
}

map<string, Method> getMethods(char** buffer, ConstantPool cp) {
	map<string, Method> methods;
    u2 methodCount = get(buffer, 2);
    for (int i=0; i<methodCount; i++) {
        Method m = Method(buffer, cp);
		methods[m.getName()] = m;
    }
	return methods;
}

int main() {
    
    char* buffer = readFile("testcases/Test5.class");

    char* start = buffer;

    buffer += 8;        // advance to ConstantPool
    ConstantPool cp = ConstantPool(&buffer);

    buffer += 2;        // skip access flags
    string tcName = getClassName(&buffer, cp);

    buffer += 2;        // skip super class
    buffer += 2;        // skip interface
    buffer += 2;        // skip fields

	map<string, Method> methods = getMethods(&buffer, cp);

	Interpreter interpreter = Interpreter(methods, cp);
	interpreter.start();

	return 0;
}