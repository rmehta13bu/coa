
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cpu.h"

#define REG_COUNT 16
#define ARRAY_LENGTH 128
#define INSTRUCTION_LENGTH 128
#define MAX_LINES 1000
#define MAX_LINE_LENGTH 100
#define MAX_WORDS 80
 
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
void
print_registers(CPU *cpu){
    
    
    printf("================================\n\n");

    printf("=============== STATE OF ARCHITECTURAL REGISTER FILE ==========\n\n");

    printf("--------------------------------\n");
    for (int reg=0; reg<REG_COUNT; reg++) {
        printf("REG[%2d]   |   Value=%d  \n",reg,cpu->regs[reg].value);
        printf("--------------------------------\n");
    }
    printf("================================\n\n");
}

void print_display(CPU *cpu, int cycle){
    printf("================================\n");
    printf("Clock Cycle #: %d\n", cycle);
    printf("--------------------------------\n");

   for (int reg=0; reg<REG_COUNT; reg++) {
       
        printf("REG[%2d]   |   Value=%d  \n",reg,cpu->regs[reg].value);
        printf("--------------------------------\n");
    }
    printf("================================\n");
    printf("\n");

}
// --------------------------------


int wB(char** lines,int currentindex){
    printf("writeback\t");
   if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
    }
    // printf("%s\n", s);
}

int mem2(char** lines,int currentindex){
    printf("mem2\t");
     if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
    }
    wB(lines,currentindex-1);
}

int mem1(char** lines,int currentindex){
    printf("mem1\t");
     if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
    }
    mem2(lines,currentindex-1);
}

int br(char** lines,int currentindex){
    printf("br\t");
     if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
    }
    mem1(lines,currentindex-1);
}

int divstage(char** lines,int currentindex){
    printf("div\t");
    if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
    }
    br(lines,currentindex-1);
}

int multi(char** lines,int currentindex){
    printf("multi\t");
    if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
    }
    divstage(lines,currentindex-1);
}

int add(char** lines,int currentindex){
    printf("add\t");
     if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
    }
    multi(lines,currentindex-1);
}

int readReg(char** lines,int currentindex){
    printf("readReg\t");
    if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
    }
    add(lines,currentindex-1);
}

int iaStage(char **lines,int currentindex){
    printf("iastage\t");
    
    if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
    }
    readReg(lines,currentindex-1);
}

int decode(char **lines,int currentindex){
    printf("decode\t");
    char* address;
    char* inst;
    char* opcode;
    char* oprend1;
    char* operand2;
    

    if(currentindex-1 ==-1){

        return 1;
    }else{
     printf("%s\n", lines[currentindex-1]);
     char *words[MAX_WORDS];
     int word_count = 0;
     int i;
     char *word = strtok(lines[currentindex-1], " ");
    while (word != NULL && word_count < MAX_WORDS) {
        // Store the word in the array
        words[word_count] = word;
        word_count++;

        // Get the next word
        word = strtok(NULL, " ");
    }

    if (word_count == 2){
        address = words[0];
        inst = words[1];
        // wB(line);
    }else if(word_count==4){
        address = words[0];
        inst = words[1];
        opcode = words[2];
        oprend1=words[3];
        int i = iaStage(lines,currentindex-1);
        if(i ==1){
        return 1;
    }
    }else if(word_count == 5){
        address = words[0];
        inst = words[1];
        opcode = words[2];
        oprend1=words[3];
        operand2=words[4];
         int i = iaStage(lines,currentindex-1);
        if(i ==1){
        return 1;
    }
    }

    }
    

    
//     printf("%s\n",address);
//    printf("%s\n",inst);
//    printf("%s\n",opcode);
//    printf("%s\n",oprend1);
}


void fetch(const char *filename){
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    char *lines[MAX_LINES];
    char arr[MAX_LINES];
    int line_count = 0;
    int count=0;
    char c;


    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening the file.\n");
        
    }

    // Read each line from the file and store it in the lines array
    while (fgets(line, sizeof(line), fp)) {
        // Remove the newline character at the end of the line
        line[strcspn(line, "\n")] = 0;

        // Allocate memory for the line and copy it to the lines array
        lines[line_count] = malloc(strlen(line) + 1);
        strcpy(lines[line_count], line);

        // Increment the line count
        line_count++;

        // If we've reached the maximum number of lines, break out of the loop
        if (line_count == MAX_LINES) {
            break;
        }
    }

    fclose(fp);

    // Print the lines stored in the lines array
    for (int i = 0; i < line_count+10; i++) {
        
        printf("fetchstage %i\n",i);
        printf("%s\n", lines[i]);
        int r = decode(lines,i);
        if(r==1){
            printf("1 is return\n");
            continue;
        }
    }
}





/*
 *  CPU CPU simulation loop
 */
int
CPU_run(CPU* cpu)
{

    fetch(cpu->filename);
    // print_display(cpu,0);
    
    // printf("Stalled cycles due to data hazard: \n");
    // printf("Total execution cycles: \n");
    // printf("Total instruction simulated:\n" );
    // printf("IPC: \n");

   
    return 0;
}

Register*
create_registers(int size){
    Register* regs = malloc(sizeof(*regs) * size);
    if (!regs) {
        return NULL;
    }
    for (int i=0; i<size; i++){
        regs[i].value = 0;
    }
    return regs;
}



