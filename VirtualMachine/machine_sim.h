#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * REGISTERS MAP: reg[0] <- $zero (Constant)
 */

// Machine Register and memory params
#define REGSIZE 32
#define INSTRUCTION_MEMSIZE 4096
#define DATA_MEMSIZE 4096
#define MAXLENOPCODE 6
/*
 * Instruction Set
 */
typedef enum{
    READ,
    WRITE,
    ADDI,
    ADD,
    SUB,
    SUBI,
    MULT,
    MULTI,
    DIVI,
    DIV,
    AND,
    ANDI,
    ORI,
    OR,
    XOR,
    XORI,
    JUMP,
    BEQ,
    BGEZ,
    BGTZ,
    BLEZ,
    BLTZ,
    BNE,
    LW,
    SW,
    SLT,
    SLTI,
    NOP,
    HALT,
    UNKNOWN
}InstructionOpcode;

/*
 * INSTRUCTION STRUCT
 */
typedef struct {
    InstructionOpcode opcode;
    int iarg1;
    int iarg2;
    int iarg3;
} INSTRUCTION;

typedef struct {
    char opCode_str [6];
    InstructionOpcode opcode;
} MapStrToInstructionOpcode;

void cleanStart();
InstructionOpcode strToInstruction(char * opcode);
int opcodeNumberOfParams(InstructionOpcode opcode);
int loadLineToMemory(char * line, int lineNo);
int loadToMemory(FILE *programFile);
int executeInstruction(INSTRUCTION instruction);
void runProgram();