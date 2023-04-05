//
//  main.c
//  Pipeline
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

int binary_flag;

void run_cpu_fun(){

    CPU *cpu = CPU_init();
    CPU_run(cpu);
    CPU_stop(cpu);
}

int main(int argc, const char * argv[]) {
    if (argc<=1) {
        fprintf(stderr, "Error : missing required args\n");
        return -1;
    }
    char* filename = (char*)argv[1];
    
    run_cpu_fun();
    
    return 0;
}
