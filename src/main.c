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
int load(char* file_name){
    printf("Opening .bin file...\n");

    FILE* file = fopen(file_name, "r");
    int i = 0;

    long file_size = get_file_size(file);

    printf("Collecting binary data into program memory...\n");

    while (ftell(file) < file_size - 4) {
        // collecting chars into one 32-bit instruction and bitshift to simulate risc-v memory layout
        uint32_t read = 0;
        for(int j = 0; j <= 3; j++) {
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
uint32_t read_instruction() {
    uint32_t instruction = mem[pc];
    pc++;
    return instruction;
}

//Decode instruction
uint32_t decode(uint32_t instruction) {
    uint8_t opcode = instruction & 0x7F; //7F represents the mask for opcode
    uint8_t func3 = (instruction >> 12) & 0x7;
    switch(opcode) {
        case 0x37:
            LUI(instruction);
        case 0x17:
            AUIPC(instruction);
        case 0x6F:
            JAL(instruction);
        case 0x67:
            JALR(instruction);
        case 0x63:
            switch(func3_branch) {
                case 0x0:
                    BEQ(instruction);
                case 0x1:
                    BNE(instruction);
                case 0x4:
                    BLT(instruction);
                case 0x5:
                    BGE(instruction);
                case 0x6:
                    BLTU(instruction);
                case 0x7:
                    BGEU(instruction);
            }
        case 0x3:
            switch (func3_load) {
                case 0x0:
                    LB(instruction);
                case 0x1:
                    LH(instruction);
                case 0x2:
                    LW(instruction);
                case 0x4:
                    LBU(instruction);
                case 0x5:
                    LHU(instruction);
            }
        case 0x23:
            switch (func3_store) {
                case 0x0:
                    SB(instruction);
                case 0x1:
                    SH(instruction);
                case 0x2:
                    SW(instruction);
            }
        case 0x13:
            switch (func3_two_op) {
                case 0x0:
                    ADDI(instruction);
                case 0x2:
                    SLTI(instruction);
                case 0x3:
                    SLTIU(instruction);
                case 0x4:
                    XORI(instruction);
                case 0x6:
                    ORI(instruction);
                case 0x7:
                    ANDI(instruction);
                case 0x1:
                    SLLI(instruction);
                case 0x5:
                    switch (imm) {
                        case 0x0:
                            SRLI(instruction);
                        case 0x20:
                            SRAI(instruction);                        
                    }
            }
        case 0x33:
            switch (func3_logic) {
                case 0x0:
                    switch (imm_add_sub) {
                        case 0x0:
                            ADD(instruction);
                        case 0x20:
                            SUB(instruction);
                    }
                case expression:

            }
            



   }
}







int main(int argc, char* argv[]){
    if(argc != 2) {
        printf("Missing argument\n");
        return 1;
    }
    load(argv[1]);

    while (1){
        uint32_t instruction = read_instruction();

    }

}