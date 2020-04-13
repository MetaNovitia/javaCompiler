#ifndef CONSTANTPOOL_H_
#define CONSTANTPOOL_H_

#include <map>
#include <iostream>
#include <vector>
#include "byteHelper.h"

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

class ConstantPoolInfo {
    u1 tag;
    vector<u1> info;

public:

    ConstantPoolInfo(u1 tag, char** buffer, u2 size);

    void printInfoHex();
    string getString();
    u8 getNum();
};

class ConstantPool {
    vector<ConstantPoolInfo> cpinfos;

public:

    ConstantPool(char** buffer);

    void add(char** buffer);
    ConstantPoolInfo getCP(int i);
};

#endif