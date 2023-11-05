#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

//defining 32 bit program counter.
uint32_t pc = 0;

//zero register
const uint32_t x0 = 0;

//register x1 to x32
uint32_t x[31];

//memory with 2³² Gb RAM.
uint32_t mem[4294967295];

//Function to load program
int load(char* fname){
    FILE* openF = fopen(fname, "r");
    int i = 0;
    while (1) {
        int read = fgetc(openF);
        if (feof(openF)) {
            break;
        }
        printf("%x", read);
        mem[i] = read;
        i++;
    }
    printf("\n");
    for (int j = 0; j < i; j++) {
        printf("%x", mem[j]);
    }
    fclose(openF);
    return 0;
}

//Function to read instruction from memory
int readInstr() {
    uint32_t instr = mem[pc];
    pc ++;
}








int main(int argc, char* argv[]){
    if(argc != 2) {
        printf("Missing argument");
        return 1;
    }
    load(argv[1]);

}