#include <iostream>
#include "byteHelper.h"

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

using namespace std;

const string hexval = "0123456789abcdef";

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