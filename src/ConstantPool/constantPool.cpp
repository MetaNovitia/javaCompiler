#include <map>
#include <iostream>
#include "constantPool.h"
#include "byteHelper.h"
#include <vector>

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

map<u1, u2> additionalBytes = {
    {3, 4}, {4, 4}, {5, 8}, {6, 8}, {7, 2},
    {8, 2}, {9, 4}, {10, 4}, {11, 4}, {12, 4},
    {15, 3}, {16, 2}, {17, 4}, {18, 4}, {19, 2},
    {20, 2}
};

ConstantPoolInfo::ConstantPoolInfo(u1 newtag, char** buffer, u2 size) {
    tag = newtag;
    for(int i=0; i<size; i++) {
        info.push_back( get(buffer, 1) );
        printHex(info[i]);
    }
}

void ConstantPoolInfo::printInfoHex() {
    for (int i=0; i<info.size(); i++) printHex(info[i]);
}

u8 ConstantPoolInfo::getNum() {
    u8 num = 0;
    u2 size = info.size();

    if (tag == 1)   cout << "Invoked getNum on String type" << endl;
    else            for (int i=0; i<size; i++) num += ((u8) info[i] << (4*(size-1-i)));

    return num;
}

string ConstantPoolInfo::getString() {
    string s = "";
    u2 size = info.size();

    if (tag != 1)   cout << "Invoked getString on non-String type" << endl;
    else            for (int i=0; i<size; i++) s += info[i];

    return s;
}

ConstantPool::ConstantPool(char** buffer) {
    u2 constantPoolCount = get(buffer, 2) - 1;
    for (int i=0; i<constantPoolCount; i++) {
        cout << "CP#" << i+1 << ": ";
        add(buffer);
        cout << endl;
    }
}

void ConstantPool::add(char** buffer) {
    u1 tag = get(buffer, 1);
    u2 size = 0;

    if (tag == 1)   size = get(buffer, 2);
    else            size = additionalBytes[tag];

    cpinfos.push_back( ConstantPoolInfo(tag, buffer, size) );
}

ConstantPoolInfo ConstantPool::getCP(int i) {
    return cpinfos[i-1];
}