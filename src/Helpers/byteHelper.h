#ifndef BYTEHELPER_H_
#define BYTEHELPER_H_

#include <iostream>
#include <utility>
#include <map>

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

extern map< char, pair<string, int> > opStr;

u4 get(char** buffer, int numBytes);
int16_t getSigned2(char** buffer);

void printHex(char byte);


#endif