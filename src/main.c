#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

//defining 32 bit program counter.
uint32_t pc = 0;

//zero register
const uint32_t x0 = 0;

//register x1 to x32
uint32_t x[31];

//memory with 1 mb RAM.
uint32_t mem[262144];

long get_file_size(FILE* file) {
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return file_size;
}

//Function to load program
int load(char* fname){
    printf("Opening .bin file...\n");

    FILE* file = fopen(fname, "r");
    int i = 0;

    long file_size = get_file_size(file);

    printf("Collecting binary data into program memory...\n");

    while (ftell(file) < file_size - 4) {
        // collecting chars into one 32-bit instruction
        uint32_t read = 0;
        for(int j = 3; j >= 0; j--) {
            uint32_t byte = fgetc(file);

            read = (byte << (j * 8)) | read;
        }

        printf("%x ", read);
        mem[i] = read;
        i++;
    }

    printf("\nReplicating collected data...\n");

    for (int j = 0; j < i; j++) {
        printf("%x ", mem[j]);
    }
    fclose(file);
    return 0;
}

//Function to read instruction from memory
int read_instruction() {
    uint32_t instruction = mem[pc];
    pc++;
}








int main(int argc, char* argv[]){
    if(argc != 2) {
        printf("Missing argument");
        return 1;
    }
    load(argv[1]);

}