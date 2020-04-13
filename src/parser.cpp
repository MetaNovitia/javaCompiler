#include <iostream>
#include <fstream>
#include <cstddef>
#include "constantPool.h"
#include "byteHelper.h"
#include "methods.h"

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

string getClassName(ConstantPool cp, char** buffer) {
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

int main() {
    
    char* buffer = readFile("testcases/Test1.class");

    char* start = buffer;

    buffer += 8;        // advance to ConstantPool
    ConstantPool cp = ConstantPool(&buffer);

    buffer += 2;        // skip access flags
    string tcName = getClassName(cp, &buffer);

    buffer += 2;        // skip super class
    buffer += 2;        // skip interface
    buffer += 2;        // skip fields

    MethodTable mt = MethodTable(&buffer);

    // skipInterface(&buffer);
    // skipField(&buffer);  // skip field
    


	return 0;
}