g++-9 -o a.exe \
    -I src/ConstantPool/ \
    -I src/Helpers/ \
    -I src/Methods/ \
    -I src/Instruction/ \
    src/parser.cpp \
    src/ConstantPool/constantPool.cpp \
    src/Helpers/byteHelper.cpp \
    src/Methods/methods.cpp \
    src/Methods/interpreter.cpp \
    src/Methods/basicBlock.cpp \
    src/Instruction/value.cpp \
    src/Instruction/instruction.cpp