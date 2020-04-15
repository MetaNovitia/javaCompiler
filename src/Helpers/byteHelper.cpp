#include <iostream>
#include <utility>
#include <map>
#include "byteHelper.h"

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

using namespace std;

const string hexval = "0123456789abcdef";

map<char, instr> opStr {
	{0x02, {"iconst_m1", 0}}, 		{0x03, {"iconst_0", 0}}, 
	{0x04, {"iconst_1", 0}}, 		{0x05, {"iconst_2", 0}}, 
	{0x06, {"iconst_3", 0}}, 		{0x07, {"iconst_4", 0}}, 
	{0x08, {"iconst_5", 0}}, 		{0x1a, {"iload_0", 0}},
	{0x1b, {"iload_1", 0}}, 		{0x1c, {"iload_2", 0}}, 
	{0x1d, {"iload_3", 0}}, 		{0x3b, {"istore_0", 0}},
	{0x3c, {"istore_1", 0}}, 		{0x3d, {"istore_2", 0}}, 
	{0x3e, {"istore_3", 0}}, 		{0x60, {"iadd", 0}},
	{0x84, {"iinc", 1}}, 			{0x64, {"isub", 0}}, 
	{0x68, {"imul", 0}}, 			{0x78, {"ishl", 0}}, 
	{0x7a, {"ishr", 0}}, 			{0xa0, {"if_icmpne", 2}}, 
	{0x9f, {"if_icmpeq", 2}}, 		{0xa3, {"if_icmpgt", 2}},
	{0xa2, {"if_icmpge", 2}}, 		{0xa1, {"if_icmplt", 2}}, 
	{0xa4, {"if_icmple", 2}}, 		{0x99, {"ifeq", 2}}, 
	{0x9a, {"ifne", 2}}, 			{0x9d, {"ifgt", 2}}, 
	{0x9c, {"ifge", 2}}, 			{0x9b, {"iflt", 2}}, 
	{0x9e, {"ifle", 2}}, 			{0xa7, {"goto", 2}}, 
	{0x10, {"bipush", 1}}, 		{0xb8, {"invokestatic", 2}}, 
	{0xb6, {"invokevirtual", 2}}, 	{0xb1, {"return", 0}}, 
	{0xad, {"ireturn", 0}}, 		{0xb2, {"getstatic", 2}}
};

/*  returns bytes as integer 
    from pos to pos+numBytes-1 */
u4 get(char** buffer, int numBytes) {
    u4 result = 0;
    for (int i=0; i <numBytes; i++) {
        result = result << 8;
        result += *((*buffer)++);
    }
    return result;
}

int16_t getSigned2(char** buffer) {
    return (*((*buffer)++) << 8) | *((*buffer)++);
}

int8_t getSigned1(char** buffer) {
    return *((*buffer)++);
}

void printHex(char byte) {
    cout    << hexval[(byte >> 4) & 0xF] 
            << hexval[(byte) & 0x0F] << " ";
}