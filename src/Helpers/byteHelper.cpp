#include <iostream>
#include <utility>
#include <map>
#include "byteHelper.h"

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

using namespace std;

const string hexval = "0123456789abcdef";


map<char, pair<string, int> > opStr {
	{0x02, make_pair("iconst_m1", 0)}, 		{0x03, make_pair("iconst_0", 0)}, 
	{0x04, make_pair("iconst_1", 0)}, 		{0x05, make_pair("iconst_2", 0)}, 
	{0x06, make_pair("iconst_3", 0)}, 		{0x07, make_pair("iconst_4", 0)}, 
	{0x08, make_pair("iconst_5", 0)}, 		{0x1a, make_pair("iload_0", 0)},
	{0x1b, make_pair("iload_1", 0)}, 		{0x1c, make_pair("iload_2", 0)}, 
	{0x1d, make_pair("iload_3", 0)}, 		{0x3b, make_pair("istore_0", 0)},
	{0x3c, make_pair("istore_1", 0)}, 		{0x3d, make_pair("istore_2", 0)}, 
	{0x3e, make_pair("istore_3", 0)}, 		{0x60, make_pair("iadd", 0)},
	{0x84, make_pair("iinc", 1)}, 			{0x64, make_pair("isub", 0)}, 
	{0x68, make_pair("imul", 0)}, 			{0x78, make_pair("ishl", 0)}, 
	{0x7a, make_pair("ishr", 0)}, 			{0xa0, make_pair("if_icmpne", 2)}, 
	{0x9f, make_pair("if_icmpeq", 2)}, 		{0xa3, make_pair("if_icmpgt", 2)},
	{0xa2, make_pair("if_icmpge", 2)}, 		{0xa1, make_pair("if_icmplt", 2)}, 
	{0xa4, make_pair("if_icmple", 2)}, 		{0x99, make_pair("ifeq", 2)}, 
	{0x9a, make_pair("ifne", 2)}, 			{0x9d, make_pair("ifgt", 2)}, 
	{0x9c, make_pair("ifge", 2)}, 			{0x9b, make_pair("iflt", 2)}, 
	{0x9e, make_pair("ifle", 2)}, 			{0xa7, make_pair("goto", 2)}, 
	{0x10, make_pair("bipush", 1)}, 		{0xb8, make_pair("invokestatic", 2)}, 
	{0xb6, make_pair("invokevirtual", 2)}, 	{0xb1, make_pair("return", 0)}, 
	{0xad, make_pair("ireturn", 0)}, 		{0xb2, make_pair("getstatic", 2)}
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

/*  returns bytes as integer 
    from pos to pos+numBytes-1 */
int16_t getSigned2(char** buffer) {
    return (*((*buffer)++) << 8) | *((*buffer)++);
}

void printHex(char byte) {
    cout    << hexval[(byte >> 4) & 0xF] 
            << hexval[(byte) & 0x0F] << " ";
}