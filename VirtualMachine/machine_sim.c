#include "machine_sim.h"

/*
 * GLOBAL VARIABLES
 * Registers, memory(instructions and data), PC, haltFlag
 */
int reg[REGSIZE];
INSTRUCTION instructionMemory[INSTRUCTION_MEMSIZE];
int dataMemory[DATA_MEMSIZE];
int programCounter;
int haltFlag;
int branchTaken;

/*
 * Clean before running
 */
void cleanStart(){
    int i;
    // Clean Register
    for(i=0; i<REGSIZE;i++){
        reg[i] = 0;
    }
    //Clean instruction memory
    for(i=0;i<INSTRUCTION_MEMSIZE;i++){
        instructionMemory[i].opcode = NOP;
        instructionMemory[i].iarg1 = 0;
        instructionMemory[i].iarg2 = 0;
        instructionMemory[i].iarg3 = 0;
    }
    // Clean data memory
    for(i=0;i<DATA_MEMSIZE;i++){
        dataMemory[i] = 0;
    }
    //Clean Program Counter
    programCounter = 0;
    //Clean branch taken flag
    branchTaken = 0;
    //Clean the halt instruction flag
    haltFlag = 0;
}

InstructionOpcode strToInstruction(char * opcode){
    MapStrToInstructionOpcode opcodeList[29] = {
        {"ADDI", ADDI},
        {"ADD", ADD},
        {"SUB", SUB},
        {"SUBI", SUBI},
        {"MULT", MULT},
        {"MULTI", MULTI},
        {"DIV", DIV},
        {"DIVI", DIVI},
        {"AND", AND},
        {"ANDI", ANDI},
        {"OR", OR},
        {"ORI", ORI},
        {"XOR", XOR},
        {"XORI", XORI},
        {"BEQ", BEQ},
        {"BNE", BNE},
        {"SLT", SLT},
        {"SLTI", SLTI},
        {"BGEZ", BGEZ},
        {"BGTZ", BGTZ},
        {"BLEZ", BLEZ},
        {"BLTZ", BLTZ},
        {"LW", LW},
        {"SW", SW},
        {"READ", READ},
        {"WRITE", WRITE},
        {"JUMP", JUMP},
        {"HALT", HALT},
        {"NOP",NOP}
    };
    int i =0;
    for(i=0;i<29;i++){
        if(strcmp(opcodeList[i].opCode_str, opcode)==0)
            return opcodeList[i].opcode;
    }
    return UNKNOWN;

}

int opcodeNumberOfParams(InstructionOpcode opcode){
    if(opcode==ADDI || opcode==ADD || opcode==SUB || opcode==SUBI || opcode==MULT || opcode==MULTI || opcode==DIV
    || opcode==DIVI || opcode==AND || opcode==ANDI || opcode==OR || opcode==ORI || opcode==XOR || opcode==XORI
    || opcode==BEQ || opcode==BNE || opcode==SLT || opcode==SLTI){
        return 3;
    }
    else if(opcode==BGEZ || opcode==BGTZ || opcode==BLEZ || opcode==BLTZ || opcode==LW || opcode==SW){
        return 2;
    }
    else if(opcode==READ || opcode==WRITE || opcode==JUMP){
        return 1;
    }
    else{
        return 0;
    }
}

int loadLineToMemory(char * line, int lineNo){
    char * opcode = strtok(line,",");
    char * arg1, * arg2, * arg3;
    INSTRUCTION instruction = {NOP,0,0,0};
    if ((instruction.opcode = strToInstruction(opcode))==UNKNOWN){
        return -1;
    }
    int numberOfParams = opcodeNumberOfParams(instruction.opcode);
    if (numberOfParams == 3){
        arg1 = strtok(NULL,",");
        arg2 = strtok(NULL,",");
        arg3 = strtok(NULL,",");

        instruction.iarg1 = atoi(arg1);
        instruction.iarg2 = atoi(arg2);
        instruction.iarg3 = atoi(arg3);
    }
    else if(numberOfParams == 2){
        arg1 = strtok(NULL,",");
        arg2 = strtok(NULL,",");
        instruction.iarg1 = atoi(arg1);
        instruction.iarg2 = atoi(arg2);
    }
    else if(numberOfParams == 1){
        arg1 = strtok(NULL,",");
        instruction.iarg1 = atoi(arg1);
    }

    instructionMemory[lineNo] = instruction;
    return 0;
}

int loadToMemory(FILE *programFile){
    char * line = NULL;
    int lineNo = 0;
    size_t n = 0;

    while(!feof(programFile)){
        //Read line from file
        line = NULL;
        getline(&line,&n,programFile);
        if(loadLineToMemory(line, lineNo)==-1){
            printf("Error on line:%d\t-> %s",lineNo,line);
            return -1;
        }
        lineNo++;
    }
    //Close file
    fclose(programFile);
    return 1;
}

/*
 * Executes an individual instruction
 */
int executeInstruction(INSTRUCTION instruction){
    int aux;
    switch (instruction.opcode) {
        case READ: //Ex:READ,$destReg
            printf("INPUT:");
            scanf("%d",&aux);
            reg[instruction.iarg1] = aux;
            break;
        case WRITE: //Ex:WRITE,$reg1
            printf("%d\n",reg[instruction.iarg1]);
            break;
        case ADDI: //Ex:ADDI,$dest,$reg1,immmediate
            reg[instruction.iarg1] = reg[instruction.iarg2] + instruction.iarg3;
            break;
        case ADD: //Ex:ADD,$dest,$reg1,$reg2
            reg[instruction.iarg1] = reg[instruction.iarg2] + reg[instruction.iarg3];
            break;
        case SUB: //Ex:SUB,$dest,$reg1,$reg2
            reg[instruction.iarg1] = reg[instruction.iarg2] - reg[instruction.iarg3];
            break;
        case SUBI: //Ex:SUBI,$dest,$reg1,immediate
            reg[instruction.iarg1] = reg[instruction.iarg2] - instruction.iarg3;
            break;
        case MULT: //Ex:MULT,$dest,$reg1,$reg2
            reg[instruction.iarg1] = reg[instruction.iarg2] * reg[instruction.iarg3];
            break;
        case MULTI: //Ex:MULTI,$dest,$reg1,immediate
            reg[instruction.iarg1] = reg[instruction.iarg2] * instruction.iarg3;
            break;
        case DIVI: //Ex:DIVI,$dest,$reg1,immediate
            reg[instruction.iarg1] = reg[instruction.iarg2] / instruction.iarg3;
            break;
        case DIV: //Ex:DIV,$dest,$reg1,$reg2
            reg[instruction.iarg1] = reg[instruction.iarg2] / reg[instruction.iarg3];
            break;
        case AND: //Ex:AND,$dest,$reg1,$reg2
            reg[instruction.iarg1] = reg[instruction.iarg2] & reg[instruction.iarg3];
            break;
        case ANDI: //Ex:ANDI,$dest,$reg1,immediate
            reg[instruction.iarg1] = reg[instruction.iarg2] & instruction.iarg3;
            break;
        case ORI: //Ex:ORI,$dest,$reg1,immediate
            reg[instruction.iarg1] = reg[instruction.iarg2] | instruction.iarg3;
            break;
        case OR: //Ex:OR,$dest,$reg1,$reg2
            reg[instruction.iarg1] = reg[instruction.iarg2] | reg[instruction.iarg3];
            break;
        case XOR: //Ex:XOR,$dest,$reg1,$reg2
            reg[instruction.iarg1] = reg[instruction.iarg2] ^ reg[instruction.iarg3];
            break;
        case XORI: //Ex:XORI,$dest,$reg1,immediate
            reg[instruction.iarg1] = reg[instruction.iarg2] ^ instruction.iarg3;
            break;
        case JUMP: //Ex:JUMP,destPC
            programCounter = instruction.iarg1;
            branchTaken = 1;
            break;
        case BEQ: //Ex:BEQ,$reg1,$reg2,destPC
            if(reg[instruction.iarg1]==reg[instruction.iarg2]){
                programCounter = instruction.iarg3;
                branchTaken = 1;
            }
            break;
        case BGEZ: //Ex:BGEZ,$reg1,destPC
            if(reg[instruction.iarg1]>=0){
                programCounter = instruction.iarg2;
                branchTaken = 1;
            }
            break;
        case BGTZ: //Ex:BGTZ,$reg1,destPC
            if(reg[instruction.iarg1]>0){
                programCounter = instruction.iarg2;
                branchTaken = 1;
            }
            break;
        case BLEZ: //Ex:BLEZ,$reg1,destPC
            if(reg[instruction.iarg1]<=0){
                programCounter = instruction.iarg2;
                branchTaken = 1;
            }
            break;
        case BLTZ: //Ex:BLTZ,$reg1,destPC
            if(reg[instruction.iarg1]<0){
                programCounter = instruction.iarg2;
                branchTaken = 1;
            }
            break;
        case BNE: //Ex:BNE,$reg1,$reg2,destPC
            if(reg[instruction.iarg1]!=reg[instruction.iarg2]){
                programCounter = instruction.iarg3;
                branchTaken = 1;
            }
            break;
        case LW: //Ex:LW,$dest,memPos
            reg[instruction.iarg1] = dataMemory[instruction.iarg2];
            break;
        case SW: //Ex:SW,$reg1, destMemPos
            dataMemory[instruction.iarg2] = reg[instruction.iarg1];
            break;
        case SLT: //Ex:SLT,$dest,$reg1,$reg2
            if(reg[instruction.iarg2]<reg[instruction.iarg3]){
                reg[instruction.iarg1] = reg[instruction.iarg2];
            }
            break;
        case SLTI: //Ex:SLTI,$dest,$reg,immediate
            if(reg[instruction.iarg2]<instruction.iarg3){
                reg[instruction.iarg1] = reg[instruction.iarg2];
            }
            break;
        case NOP: //Ex:NOP
            break;
        case HALT: //Ex:HALT
            haltFlag = 1;
            break;
        default: //
            printf("Opcode not recognized");
            return -1;
    }
    return 0;
}

/*
 * Execute program
 */
void runProgram(){
    while(!haltFlag && programCounter<INSTRUCTION_MEMSIZE){
        if(executeInstruction(instructionMemory[programCounter])==-1){
            exit(EXIT_FAILURE);
        }
        if(branchTaken == 0){
            programCounter++;
        }
        else{
            branchTaken = 0;
        }
    }
}

/*
 * VM main
 */
int main(int argc, char *argv[]){
    FILE *programFile = NULL;

    if(argc !=2){
        printf("Check args!\n");
        exit(EXIT_FAILURE);
    }
    if((programFile=fopen(argv[1],"r"))==NULL){
        printf("Unable to open file");
        exit(EXIT_FAILURE);
    }

    cleanStart();

    if(loadToMemory(programFile)==-1){
        exit(EXIT_FAILURE);
    }

    printf("Program is ready!, press [y] to run it: ");
    char run = 'n';
    scanf("%c",&run);

    if(run=='y'){
        runProgram();
        printf("\nProgram Ended, Bye!\n");
    }
    return 0;
}
