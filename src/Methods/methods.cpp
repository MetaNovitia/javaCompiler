#include <map>
#include <iostream>
#include "methods.h"
#include "byteHelper.h"
#include <vector>

using namespace std;

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

Method::Method(char** buffer) {
    access_flags = get(buffer, 2);
    u2 name_index = get(buffer, 2);
    descriptor_index = get(buffer, 2);

    int attCount = get(buffer, 2);

    for (int i=0; i<attCount; i++) {
        get(buffer, 2);
        u4 len = get(buffer, 4);
        for(int j=0; j<len; j++) {
            get(buffer, 1);
        }
    }
}

MethodTable::MethodTable(char** buffer) {
    u2 methodCount = get(buffer, 2);
    for (int i=0; i<methodCount; i++) {
        cout << "Method #" << i+1 << ": ";
        methods.push_back( Method(buffer) );
        cout << endl;
    }
}

Method MethodTable::getMethod(int i) {
    return methods[i];
}