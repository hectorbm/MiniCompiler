#include "check_typos.h"

typedef struct codeGen{
    int destinationRegister;
    int lastLineOfCode;
}CodeGenVM;

CodeGenVM generateCode(SyntaxTree * st,FILE * vm_code,int initialTempReg,int nextLineNo,int lenCheckMode);
void codeGenerator(SyntaxTree * st,char * destFile);



