#ifndef METHODS_H_
#define METHODS_H_

#include <map>
#include <iostream>
#include <vector>
#include "byteHelper.h"
// #include "attributes.h"

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

class Method {
    u2 access_flags;
    u2 name;
    u2 descriptor_index;
    // vector<Attribute> attributes;

public:

    Method(char** buffer);

};

class MethodTable {
    vector<Method> methods;

public:

    MethodTable(char** buffer);
    Method getMethod(int i);
};

#endif