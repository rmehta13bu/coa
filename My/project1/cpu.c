
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include "cpu.h"

#define REG_COUNT 128
#define ARRAY_LENGTH 128
#define INSTRUCTION_LENGTH 128
#define SET 0
#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4
#define LD 5
#define RET 6
char *myLines[100][5];
// int *memoryMapValues[16384];
int valueRegister[REG_COUNT] = {0};
int booleanRegister = 0;
int memoryMapValues[16384];
int totalStalling = 0;
int totalCycles = 0;
int totalInstructions = 0;

 
CPU*
CPU_init(const char *filename)
{
    CPU* cpu = malloc(sizeof(*cpu));
    if (!cpu) {
        return NULL;
    }
    if (!filename) {
        return NULL;
    }

    /* Create register files */
    cpu->regs= create_registers(REG_COUNT);
    cpu->filename= filename;

    return cpu;
}

/*
 * This function de-allocates CPU cpu.
 */
void
CPU_stop(CPU* cpu)
{
    free(cpu);
}

/*
 * This function prints the content of the registers.
 */
void print_registers(CPU *cpu){
    FILE *pipeline = fopen("program_pipeline.txt", "w");
    fprintf(pipeline, "");
    fclose(pipeline);
    FILE *registerstatus = fopen("program_registerstatus.txt", "w");
    fprintf(registerstatus, "");
    fclose(registerstatus);
    FILE *result = fopen("program_result.txt", "w");
    fprintf(result, "");
    fclose(result);
    FILE *stats = fopen("program_stats.txt", "w");
    fprintf(stats, "");
    fclose(stats);
}


// MY CODEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE


bool getIsRegister(char *number){
    if (number[0]=='#'){
        return false;
    }
    return true;
}

int characterToInt(char *number) {
    int i = 0;
    int finalNumber = 0;
    int temp;
    
    for( i = 0 ; i<strlen(number) ; ++i){
        if (i==0 && number[i]=='#'){
            booleanRegister = 0;
            continue;
        }
        if (i==0 && number[i]=='R'){
            booleanRegister = 1;
            continue;
        }
        else{
            temp = number[i] - '0';
            finalNumber = finalNumber * 10 + temp;
        }
    }
    return finalNumber;
}

int setInstruction(int number1){
    return number1;
}

int addInstruction(int number1, int number2){
    return number1 + number2;
}

int subInstruction(int number1, int number2){
    return number1 - number2;
}

int mulInstruction(int number1, int number2){
    return number1 * number2;
}

int divInstruction(int number1, int number2){
    return number1 / number2;
}

int ldInstruction(int number1){
    return memoryMapValues[number1/4];
}

int retInstruction(){
    return 0;
}


int getFinalValue(int totalInstructions, int index){
    int instructionValue;
    if (getIsRegister(myLines[totalInstructions][index])){
        instructionValue = valueRegister[characterToInt(myLines[totalInstructions][index])];
    } else{
        instructionValue = characterToInt(myLines[totalInstructions][index]);
    }
    return instructionValue;
}


void getInstructions(char *instruction, int totalInstructions){
    if((strcmp(instruction ,"set")) == 0){
        int firstInstruction = getFinalValue(totalInstructions, 3);
        valueRegister[characterToInt(myLines[totalInstructions][2])] = setInstruction(firstInstruction);
    }
    else if((strcmp(instruction ,"add")) == 0){
        int firstInstruction = getFinalValue(totalInstructions, 3);
        int secondInstruction = getFinalValue(totalInstructions, 4);
        valueRegister[characterToInt(myLines[totalInstructions][2])] = addInstruction(firstInstruction, secondInstruction);
    }
    else if((strcmp(instruction ,"sub")) == 0){
        int firstInstruction = getFinalValue(totalInstructions, 3);
        int secondInstruction = getFinalValue(totalInstructions, 4);
        valueRegister[characterToInt(myLines[totalInstructions][2])] = subInstruction(firstInstruction, secondInstruction);
    }
    else if((strcmp(instruction ,"mul")) == 0){
        int firstInstruction = getFinalValue(totalInstructions, 3);
        int secondInstruction = getFinalValue(totalInstructions, 4);
        valueRegister[characterToInt(myLines[totalInstructions][2])] = mulInstruction(firstInstruction, secondInstruction);
    }
    else if((strcmp(instruction ,"div")) == 0){
        int firstInstruction = getFinalValue(totalInstructions, 3);
        int secondInstruction = getFinalValue(totalInstructions, 4);
        valueRegister[characterToInt(myLines[totalInstructions][2])] = divInstruction(firstInstruction, secondInstruction);
    }
    else if((strcmp(instruction ,"ld")) == 0){
        ldInstruction(characterToInt(myLines[totalInstructions][3]));
        int firstInstruction = getFinalValue(totalInstructions, 3);
        valueRegister[characterToInt(myLines[totalInstructions][2])] = ldInstruction(firstInstruction);
    }
    else if((strcmp(instruction ,"ret")) == 0){
        retInstruction();
    }
}


// WRITING HERREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE


void writeStats(){
    // FILE *f = fopen("program_stats.txt", "a+");
    // if (f == NULL)
    // {
    //     printf("Error opening file!\n");
    //     exit(1);
    // }
    // fprintf(f, "Stalled cycles due to structural hazard: %d\n", totalStalling);
    // fprintf(f, "Total execution cycles: %d\n", totalCycles);
    // fprintf(f, "Total instruction simulated: %d\n", totalInstructions);
    // fprintf(f, "IPC: %f\n", (float)totalInstructions / (float)totalCycles);

    // fclose(f);

    printf("Stalled cycles due to structural hazard: %d\n", totalStalling);
    printf("Total execution cycles: %d\n", totalCycles);
    printf("Total instruction simulated: %d\n", totalInstructions);
    printf("IPC: %f\n", (float)totalInstructions / (float)totalCycles);
}

void writeRegisterStatus(){
    // FILE *f = fopen("program_registerstatus.txt", "a+");
    // if (f == NULL)
    // {
    //     printf("Error opening file!\n");
    //     exit(1);
    // }
    // fprintf(f, "================================\n");
    // fprintf(f, "--------------------------------\n");
    // for (int reg=0; reg<REG_COUNT; reg++) {
    //     fprintf(f, "REG[%2d]   |   Value=%d  \n",reg,valueRegister[reg]);
    //     fprintf(f, "--------------------------------\n");
    // }
    // fprintf(f, "================================\n\n");
    // fclose(f);

    printf("================================\n");
    printf("--------------------------------\n");
    for (int reg=0; reg<REG_COUNT; reg++) {
        printf("REG[%2d]   |   Value=%d  \n",reg,valueRegister[reg]);
        printf("--------------------------------\n");
    }
    printf("================================\n\n");
}

void writeHashDash(int index){
    FILE *f = fopen("program_pipeline.txt", "a+");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    if (index == 0){
        fprintf(f, "================================\n");
    } else{
        fprintf(f, "--------------------------------\n");
    }
    fclose(f);
}

void writeClockCycle(int cycleNumber){
    FILE *f = fopen("program_pipeline.txt", "a+");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "Clock Cycle #: %d\n", cycleNumber);
    fclose(f);
}

void writeToFilePipeline(int number, char *functionName){

    FILE *f = fopen("program_pipeline.txt", "a+");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "%s", functionName);
    for (int i=0; i<= 15-strlen(functionName)-1; i++){
        fprintf(f, " ");
    }
    fprintf(f, ": ");

    for (int i = 0; i < 5; i++){
        if(myLines[number-1][i] != '\0'){
            fprintf(f, "%s ", myLines[number-1][i]);
        }
    }
    fprintf(f, "\n");
    fclose(f);
}


int IFFunction(int executionCycle[11],int stalling){
    int myIndex = 0;
    if (executionCycle[myIndex] != 0){
        writeToFilePipeline(executionCycle[myIndex], "IF");
    }
    return stalling;
}

int IDFunction(int executionCycle[11],int stalling){
    int myIndex = 1;
    if (executionCycle[myIndex] != 0){
        writeToFilePipeline(executionCycle[myIndex], "ID");
    }
    stalling = IFFunction(executionCycle, stalling);
    return stalling;
}

int IAFunction(int executionCycle[11],int stalling){
    int myIndex = 2;
    if (executionCycle[myIndex] != 0){
        writeToFilePipeline(executionCycle[myIndex], "IA");
    }
    stalling = IDFunction(executionCycle, stalling);
    return stalling;
}

int RRFunction(int executionCycle[11],int stalling){
    int myIndex = 3;
    if (executionCycle[myIndex] != 0){
        writeToFilePipeline(executionCycle[myIndex], "RR");
    }
    stalling = IAFunction(executionCycle, stalling);
    return stalling;
}

int ADDFunction(int executionCycle[11],int stalling){
    int myIndex = 4;
    if (executionCycle[myIndex] != 0){
        writeToFilePipeline(executionCycle[myIndex], "ADD");
    }
    stalling = RRFunction(executionCycle, stalling);
    return stalling;
}

int MULFunction(int executionCycle[11],int stalling){
    int myIndex = 5;
    if (executionCycle[myIndex] != 0){
        writeToFilePipeline(executionCycle[myIndex], "MUL");
    }
    stalling = ADDFunction(executionCycle, stalling);
    return stalling;
}

int DIVFunction(int executionCycle[11],int stalling){
    int myIndex = 6;
    if (executionCycle[myIndex] != 0){
        writeToFilePipeline(executionCycle[myIndex], "DIV");
    }
    stalling = MULFunction(executionCycle, stalling);
    return stalling;
}

int BRFunction(int executionCycle[11],int stalling){
    int myIndex = 7;
    if (executionCycle[myIndex] != 0){
        writeToFilePipeline(executionCycle[myIndex], "BR");
    }
    stalling = DIVFunction(executionCycle, stalling);
    return stalling;
}

int Mem1Function(int executionCycle[11],int stalling){
    int myIndex = 8;
    if (myLines[executionCycle[myIndex]-1][1] != '\0'){
        if (strcmp(myLines[executionCycle[myIndex]-1][1], "ld") == 0){
            stalling = 1;
            totalStalling += 1;
        } 
    }
    if (executionCycle[myIndex] != 0){
        writeToFilePipeline(executionCycle[myIndex], "Mem1");
    }
    stalling = BRFunction(executionCycle, stalling);
    return stalling;
}

int Mem2Function(int executionCycle[11],int stalling){
    int myIndex = 9;
    if(executionCycle[myIndex] != 0){
        writeToFilePipeline(executionCycle[myIndex], "Mem2");
    }
    stalling = Mem1Function(executionCycle, stalling);
    return stalling;
}

int WBFunction(int executionCycle[11],int stalling){
    int myIndex = 10;
    if (executionCycle[myIndex] != 0){
        getInstructions(myLines[executionCycle[myIndex]-1][1], executionCycle[myIndex]-1);
        writeToFilePipeline(executionCycle[myIndex], "WB");
    }
    stalling = Mem2Function(executionCycle, stalling);
    return stalling;
}

void pipelining(int totalInstructions){
    char tempString[5];
    int executionCycle[11] = {0};
    int counter = 0;
    int temp = 0;
    int stalling = 0;
    while(executionCycle[10] != totalInstructions){
        for(int j=10; j>=0; j=j-1){
            executionCycle[j] = executionCycle[j-1];
            if (j==0){
                if(stalling==0){
                    if (temp == totalInstructions+1){
                        executionCycle[j] = 0;
                    } else{
                        executionCycle[j] = temp;
                        temp += 1;
                    }
                } else{
                    stalling = 0;
                    executionCycle[j] = 0;
                }
            }
        }
        if (counter >= 1){
            writeHashDash(0);
            writeClockCycle(counter);
            writeHashDash(1);
            stalling = WBFunction(executionCycle, stalling);
        }
        counter += 1;
    }
    writeHashDash(0);
    totalCycles = counter-1;
}

void splitWords(int startPoint,int endPoint,int currentMainIndex,int currentTempIndex, char *buff){
    char *temp = calloc(10, 1);
    for(int i = startPoint; i <= endPoint; i++){
        temp[i-startPoint] = buff[i];
    }
    myLines[currentMainIndex][currentTempIndex] = temp;
}

int readFileInstructions(const char *filename){
    FILE *textfile;
    char line[INSTRUCTION_LENGTH];
    int lineIndex = 0;

    textfile = fopen(filename, "r");
    if(textfile == NULL)
        return 1;
    while(fgets(line, INSTRUCTION_LENGTH, textfile)){
        int start = 0;
        int tempCounter = 0;
        int last;
        for(int i = 0; line[i] != '\0'; i++){
            if (line[i] == ' '){
                splitWords(start, i-1, lineIndex, tempCounter, line);
                start = i+1;
                tempCounter += 1;
            }
            else{
                last = i;
            }
        }
        splitWords(start, last-1, lineIndex, tempCounter, line);
        lineIndex = lineIndex + 1;
    }
    return lineIndex;
}

int splitMemory(int startPoint,int endPoint,int currentMainIndex,int currentTempIndex, char *buff){
    char *temp = calloc(10, 1);
    for(int i = startPoint; i <= endPoint; i++){
        temp[i-startPoint] = buff[i];
    }
    return characterToInt(temp);
}

int readMemoryMap(){
    FILE *textfile;
    char line[65535];
    int lineIndex = 0;
    int index = 0;

    textfile = fopen("../programs/memory_map.txt", "r");
    if(textfile == NULL)
        return 1;
    while(fgets(line, INSTRUCTION_LENGTH, textfile)){
        int start = 0;
        int tempCounter = 0;
        int last;
        for(int i = 0; line[i] != '\0'; i++){
            if (line[i] == ' '){
                char *temp = calloc(10, 1);
                for(int m = start; m <= i-1; m++){
                    temp[m-start] = line[m];
                }
                memoryMapValues[lineIndex] = characterToInt(temp);
                start = i+1;
                tempCounter += 1;
                lineIndex += 1;
            }
            else{
                last = i;
            }
        }
    }
    return 0;
}


/*
 *  CPU CPU simulation loop
 */
int
CPU_run(CPU* cpu)
{

    readMemoryMap();
    
    print_registers(cpu);

    totalInstructions = readFileInstructions(cpu->filename);
    pipelining(totalInstructions);
    writeRegisterStatus();
    writeStats();
    
}



Register*
create_registers(int size){
    Register* regs = malloc(sizeof(*regs) * size);
    if (!regs) {
        return NULL;
    }
    for (int i=0; i<size; i++){
        regs[i].value = 0;
        regs[i].is_writing = false;
    }
    return regs;
}

