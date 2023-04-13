
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
#define MAX_SIZE 60000

char * arrvalue1[100][12];
 
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
    cpu->regs = create_registers(REG_COUNT);
    cpu->filename= filename;
    cpu->clock = 1;
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


int wB(char** lines,int currentindex,char* isret,CPU *cpu,int temp){
     char *str = "ret";
    char*str1 = "noret";
    printf("writeback");
    if(strcmp(isret,str)==0){
            printf("ret WB %s\n",lines[currentindex]);
            // divstage(lines,currentindex-1,str);
            
    }else{
   if(currentindex-1 ==-1){

        return 1;
    }else{

        // cpu->regs[atoi(arrvalue1[currentindex-1][5])].value = temp;
        // printf("Writbackkk %s\n",atoi(arrvalue1[currentindex-1][5]));
        printf("Writbackkk %d\n",temp);
        printf("%s\n", lines[currentindex-1]);
    }
    }
    // printf("%s\n", s);
}

int mem2(char** lines,int currentindex,char* isret,CPU *cpu,int temp){
    char *str = "ret";
    char*str1 = "noret";
    int a;
    int b;

    FILE *fp;
    int myArray[MAX_SIZE];
    int i=0;

    if(strcmp(isret,str)==0){
            printf("ret mem2 %s\n",lines[currentindex]);
            wB(lines,currentindex-1,str,cpu,temp);
            
    }else{
    printf("mem2\t");
     if(currentindex-1 ==-1){

        return 1;
    }else{

        fp=fopen("memory_map.txt","r");
        if(fp==NULL){
            printf("Error");
        }

        while(fscanf(fp,"%d",&myArray[i]) != EOF){
            i++;
        }

        fclose(fp);

        

        printf("%s\n", lines[currentindex-1]);
        if(strcmp(arrvalue1[currentindex-1][1],"ld")==0){
            if(strchr(arrvalue1[currentindex-1][3],'#')){
            // type number
            char new_str[sizeof(arrvalue1[currentindex-1][3])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][3][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][3][i] != '#') {
                new_str[j++] = arrvalue1[currentindex-1][3][i];
            }
        }
        new_str[j] = '\0';
         

        a = atoi(new_str);
        }else if(strchr(arrvalue1[currentindex-1][3],'R')){
            // type reg
            
           a = atoi(arrvalue1[currentindex-1][6]);
        }

        // b
        if(arrvalue1[currentindex-1][4]!=NULL)
        if(strchr(arrvalue1[currentindex-1][4],'#')){
            // type number
            char new_str[sizeof(arrvalue1[currentindex-1][4])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][4][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][4][i] != '#') {
                new_str[j++] = arrvalue1[currentindex-1][4][i];
            }
        }
        new_str[j] = '\0';
         

        b = atoi(new_str);
        }else if(strchr(arrvalue1[currentindex-1][4],'R')){
            // type reg
            
           b = atoi(arrvalue1[currentindex-1][8]);
        }

        printf("mem22 %d\n",a);

        temp = cpu->regs[a/4].value;

        }else if(strcmp(arrvalue1[currentindex-1][1],"st")==0){
            printf("hii");
        }
    }
    wB(lines,currentindex-1,str1,cpu,temp);
    }
}

int mem1(char** lines,int currentindex,char* isret,CPU *cpu,int temp){
     char *str = "ret";
    char*str1 = "noret";
  

    if(strcmp(isret,str)==0){
            printf("ret mem1 %s\n",lines[currentindex]);
            mem2(lines,currentindex-1,str,cpu,temp);
            
    }else{
    printf("mem1\t");
     if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
       
    }
    mem2(lines,currentindex-1,str1,cpu,temp);
    }
}

int br(char** lines,int currentindex,char* isret,CPU *cpu,int temp){
     char *str = "ret";
    char*str1 = "noret";
    if(strcmp(isret,str)==0){
            printf("ret br %s\n",lines[currentindex]);
            mem1(lines,currentindex-1,str,cpu,temp);
            
    }else{
    printf("br\t");
     if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
    }
    mem1(lines,currentindex-1,str1,cpu,temp);
    }
}

int divstage(char** lines,int currentindex,char* isret,CPU *cpu,int temp){
     char *str = "ret";
    char*str1 = "noret";
    int a;
    int b;

    
    if(strcmp(isret,str)==0){
            printf("ret div %s\n",lines[currentindex]);
            br(lines,currentindex-1,str,cpu,temp);
            
    }else{
    printf("div\t");
    if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("%s\n", lines[currentindex-1]);
        if(strchr(arrvalue1[currentindex-1][3],'#')){
            // type number
            char new_str[sizeof(arrvalue1[currentindex-1][3])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][3][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][3][i] != '#') {
                new_str[j++] = arrvalue1[currentindex-1][3][i];
            }
        }
        new_str[j] = '\0';
         

        a = atoi(new_str);
        }else if(strchr(arrvalue1[currentindex-1][3],'R')){
            // type reg
            
           a = atoi(arrvalue1[currentindex-1][6]);
        }

        // b
        if(arrvalue1[currentindex-1][4]!=NULL)
        if(strchr(arrvalue1[currentindex-1][4],'#')){
            // type number
            char new_str[sizeof(arrvalue1[currentindex-1][4])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][4][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][4][i] != '#') {
                new_str[j++] = arrvalue1[currentindex-1][4][i];
            }
        }
        new_str[j] = '\0';
         

        b = atoi(new_str);
        }else if(strchr(arrvalue1[currentindex-1][4],'R')){
            // type reg
            
           b = atoi(arrvalue1[currentindex-1][8]);
        }
        if(strcmp(arrvalue1[currentindex-1][1],"mul")==0){
            temp = a/b;
        }

    }
    br(lines,currentindex-1,str1,cpu,temp);
    }
}

int multi(char** lines,int currentindex,char* isret,CPU *cpu, int temp){
     char *str = "ret";
    char*str1 = "noret";
    int a;
    int b;

    
    if(strcmp(isret,str)==0){
            printf("ret multi %s\n",lines[currentindex]);
            divstage(lines,currentindex-1,str,cpu,temp);
            
    }else{
    printf("multi\t");
    if(currentindex-1 ==-1){

        return 1;
    }else{
        if(strchr(arrvalue1[currentindex-1][3],'#')){
            // type number
            char new_str[sizeof(arrvalue1[currentindex-1][3])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][3][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][3][i] != '#') {
                new_str[j++] = arrvalue1[currentindex-1][3][i];
            }
        }
        new_str[j] = '\0';
         

        a = atoi(new_str);
        }else if(strchr(arrvalue1[currentindex-1][3],'R')){
            // type reg
            
           a = atoi(arrvalue1[currentindex-1][6]);
        }

        // b
        if(arrvalue1[currentindex-1][4]!=NULL)
        if(strchr(arrvalue1[currentindex-1][4],'#')){
            // type number
            char new_str[sizeof(arrvalue1[currentindex-1][4])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][4][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][4][i] != '#') {
                new_str[j++] = arrvalue1[currentindex-1][4][i];
            }
        }
        new_str[j] = '\0';
         

        b = atoi(new_str);
        }else if(strchr(arrvalue1[currentindex-1][4],'R')){
            // type reg
            
           b = atoi(arrvalue1[currentindex-1][8]);
        }

        printf("%s\n", lines[currentindex-1]);
         if(strcmp(arrvalue1[currentindex-1][1],"mul")==0){
            temp = a*b;
        }
    }
    divstage(lines,currentindex-1,str1,cpu,temp);
    }
}

int add(char** lines,int currentindex,char* isret,CPU *cpu){
     char *str = "ret";
    char*str1 = "noret";
    int a;
    int b;
    int temp;

    
    if(strcmp(isret,str)==0){
            printf("ret add %s\n",lines[currentindex]);
            multi(lines,currentindex-1,str,cpu,temp);
            
    }else{
    printf("add\t");

     if(currentindex-1 ==-1){

        return 1;
    }else{
        if(strchr(arrvalue1[currentindex-1][3],'#')){
            // type number
            char new_str[sizeof(arrvalue1[currentindex-1][3])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][3][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][3][i] != '#') {
                new_str[j++] = arrvalue1[currentindex-1][3][i];
            }
        }
        new_str[j] = '\0';
         

        a = atoi(new_str);
        }else if(strchr(arrvalue1[currentindex-1][3],'R')){
            // type reg
            
           a = atoi(arrvalue1[currentindex-1][6]);
        }

        // b
        if(arrvalue1[currentindex-1][4]!=NULL)
        if(strchr(arrvalue1[currentindex-1][4],'#')){
            // type number
            char new_str[sizeof(arrvalue1[currentindex-1][4])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][4][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][4][i] != '#') {
                new_str[j++] = arrvalue1[currentindex-1][4][i];
            }
        }
        new_str[j] = '\0';
         

        b = atoi(new_str);
        }else if(strchr(arrvalue1[currentindex-1][4],'R')){
            // type reg
            
           b = atoi(arrvalue1[currentindex-1][8]);
        }

        if(strcmp(arrvalue1[currentindex-1][1],"set")==0){
            temp = a;
        }else if(strcmp(arrvalue1[currentindex-1][1],"add")==0){
            temp = a+b;
        }else if(strcmp(arrvalue1[currentindex-1][1],"sub")==0){
            temp = a-b;
        }

        printf("%s\n", lines[currentindex-1]);
    }
    multi(lines,currentindex-1,str1,cpu,temp);
    }
}

int readReg(char** lines,int currentindex,char* isret,CPU *cpu){
     char *str = "ret";
    char*str1 = "noret";
    char regvaluestr[10];
    int regvalue;


    if(strcmp(isret,str)==0){
            printf("ret readreg %s\n",lines[currentindex]);
            add(lines,currentindex-1,str,cpu);
            
    }else{
    // printf("readReg\t");
    if(currentindex-1 ==-1){

        return 1;
    }else{
         
        // read first opcode
        if(arrvalue1[currentindex-1][2]!=NULL)
        if(strchr(arrvalue1[currentindex-1][2],'R')){
        
        char new_str[sizeof(arrvalue1[currentindex-1][2])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][2][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][2][i] != 'R') {
                new_str[j++] = arrvalue1[currentindex-1][2][i];
            }
        }
        new_str[j] = '\0';

    
        regvalue = cpu->regs[atoi(new_str)].value;
        
        sprintf(regvaluestr,"%d",regvalue);
        arrvalue1[currentindex-1][5] = new_str;
        arrvalue1[currentindex-1][6] = regvaluestr;

        }else if(strchr(arrvalue1[currentindex-1][4],'#')){
        char new_str[sizeof(arrvalue1[currentindex-1][4])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][4][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][4][i] != '#') {
                new_str[j++] = arrvalue1[currentindex-1][4][i];
            }
        }
        new_str[j] = '\0';
        arrvalue1[currentindex-1][6] = new_str;
        }
        // read operand1
        if(arrvalue1[currentindex-1][3]!=NULL)
        if(strchr(arrvalue1[currentindex-1][3],'R')){
           char new_str[sizeof(arrvalue1[currentindex-1][3])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][3][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][3][i] != 'R') {
                new_str[j++] = arrvalue1[currentindex-1][3][i];
            }
        }
        new_str[j] = '\0';

    
        regvalue = cpu->regs[atoi(new_str)].value;
        
        sprintf(regvaluestr,"%d",regvalue);
        arrvalue1[currentindex-1][7] = new_str;
        arrvalue1[currentindex-1][8] = regvaluestr;


        }
        // else if(strchr(arrvalue1[currentindex-1][3],'#')){
        // char new_str[sizeof(arrvalue1[currentindex-1][3])];
        // int j = 0;

        // for (int i = 0; arrvalue1[currentindex-1][3][i] != '\0'; i++) {
        //     if (arrvalue1[currentindex-1][3][i] != '#') {
        //         new_str[j++] = arrvalue1[currentindex-1][3][i];
        //     }
        // }
        // new_str[j] = '\0';
        // arrvalue1[currentindex-1][8] = new_str;
        // printf("arrrrr%s\n",arrvalue1[currentindex-1][8]);
        // }

        // read operand2


        if(arrvalue1[currentindex-1][4]!=NULL)
        if(strchr(arrvalue1[currentindex-1][4],'R')){
            char new_str[sizeof(arrvalue1[currentindex-1][4])];
        int j = 0;

        for (int i = 0; arrvalue1[currentindex-1][4][i] != '\0'; i++) {
            if (arrvalue1[currentindex-1][4][i] != 'R') {
                new_str[j++] = arrvalue1[currentindex-1][4][i];
            }
        }
        new_str[j] = '\0';

    
        regvalue = cpu->regs[atoi(new_str)].value;
        
        sprintf(regvaluestr,"%d",regvalue);
        arrvalue1[currentindex-1][9] = new_str;
        arrvalue1[currentindex-1][10] = regvaluestr;
        }
        // else if(strchr(arrvalue1[currentindex-1][4],'#')){
        // char new_str[sizeof(arrvalue1[currentindex-1][4])];
        // int j = 0;

        // for (int i = 0; arrvalue1[currentindex-1][4][i] != '\0'; i++) {
        //     if (arrvalue1[currentindex-1][4][i] != '#') {
        //         new_str[j++] = arrvalue1[currentindex-1][4][i];
        //     }
        // }
        // new_str[j] = '\0';
        // arrvalue1[currentindex-1][10] = new_str;
        // }
        
        printf("%s\n", lines[currentindex-1]);
    }
    add(lines,currentindex-1,str1,cpu);
    }
}

int iaStage(char **lines,int currentindex,char* isret,CPU *cpu){
     char *str = "ret";
    char*str1 = "noret";

         
   
    if(strcmp(isret,str)==0){
            printf("ret iastage %s\n",lines[currentindex]);
            readReg(lines,currentindex-1,str,cpu);
            
    }else{
    
    // printf("iastage\t");
    
    if(currentindex-1 ==-1){

        return 1;
    }else{
        printf("iastage %s\n", lines[currentindex-1]);
    }
    readReg(lines,currentindex-1,str1,cpu);
    }
}

int decode(char **lines,int currentindex,char* isret,int line_count,CPU *cpu){
    
    char* address=NULL;
    char* inst=NULL;
    char* opcode=NULL;
    char* oprend1=NULL;
    char* operand2=NULL;
    char *str = "ret";
    char*str1 = "noret";



 if(strcmp(isret,str)==0){
            printf("ret decode %s\n",lines[currentindex]);
            iaStage(lines,currentindex-1,str,cpu);
            
    }else{
    // printf("decode\t");
    if(currentindex-1 ==-1){

        return 1;
    }else{
     printf("decode %s\n", lines[currentindex-1]);
     char *words[MAX_WORDS];
     int word_count = 0;
     int i;
     char *word = strtok(lines[currentindex-1], " ");
    while (word != NULL && word_count < MAX_WORDS) {
       
        words[word_count] = word;
        word_count++;
        word = strtok(NULL, " ");
    }


    if (word_count == 2){
       arrvalue1[currentindex-1][0] = words[0];
       arrvalue1[currentindex-1][1] = words[1];
       
        // wB(line);
    }else if(word_count==4){
       arrvalue1[currentindex-1][0] = words[0];
       arrvalue1[currentindex-1][1] = words[1];
        arrvalue1[currentindex-1][2] = words[2];
         arrvalue1[currentindex-1][3]=words[3];
        
        int i = iaStage(lines,currentindex-1,str1,cpu);
        if(i ==1){
        return 1;
    }
    }else if(word_count == 5){
        arrvalue1[currentindex-1][0] = words[0];
       arrvalue1[currentindex-1][1] = words[1];
         arrvalue1[currentindex-1][2] = words[2];
         arrvalue1[currentindex-1][3]=words[3];
         arrvalue1[currentindex-1][4]=words[4];

         
         int i = iaStage(lines,currentindex-1,str1,cpu);
        if(i ==1){
        return 1;
    }
    }

    }
    
        }
    
//     printf("%s\n",address);
//    printf("%s\n",inst);
//    printf("%s\n",opcode);
//    printf("%s\n",oprend1);
}


void fetch(const char *filename, CPU *cpu){

    // printf("kya h%d\n",cpu->regs[1].value);

    FILE *fp;
    char line[MAX_LINE_LENGTH];
    char *lines[MAX_LINES];
    char *lines1[MAX_LINES];
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
        lines1[line_count] = malloc(strlen(line) + 1);
        strcpy(lines[line_count], line);
        strcpy(lines1[line_count], line);

        // Increment the line count
        line_count++;

        // If we've reached the maximum number of lines, break out of the loop
        if (line_count == MAX_LINES) {
            break;
        }
    }

    fclose(fp);


    // Print the lines stored in the lines array
    for (int i = 0; i < line_count; i++) {
        
        char *str = "ret";
        char*str1 = "noret";


        if(lines[i]==NULL){
            printf("ret fetch %s\n",lines1[i]);
            decode(lines1,i-1,str,line_count,cpu);
        }else{
        char* val = strtok(lines[i]," ");
        char* val1 = strtok(NULL," ");
         if(strcmp(val1,str)==0){
            printf("ret fetch %s\n",lines1[i]);
            decode(lines1,i-1,str,line_count,cpu);
            
        }else{
        printf("Clock Cycle # %2d\n",cpu->clock);
        printf("=======================\n");
        cpu->clock++;
        printf("fetch %s\n",lines1[i]);
        int r = decode(lines1,i,str1,line_count,cpu);
        if(r==1){
            // printf("1 is return\n");
            continue;
        }
        }
        
        }
        printf("--------------------------------------------\n");
    }
}





/*
 *  CPU CPU simulation loop
 */
int
CPU_run(CPU* cpu)
{

    fetch(cpu->filename,cpu);
    // print_registers(cpu);
    print_display(cpu,0);
    
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



