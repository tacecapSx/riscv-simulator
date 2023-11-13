// to compile (win): gcc.exe src/instructions.c src/main.c -o main.exe

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "instructions.h"

//defining 32 bit program counter.
int stop = 0;
uint32_t pc = 0;

//zero register
const uint32_t x0 = 0;

//register x1 to x32
uint32_t x[32];

//memory with 1 mb.
uint32_t mem[262144];

void print_binary(uint32_t instruction) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (instruction >> i) & 1);
    }
}

long get_file_size(FILE* file) {
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    return file_size;
}

//Function to read instruction from memory
uint32_t read_instruction() {
    return mem[pc];
}

void ecall() {
    uint32_t opcode = x[17]; // read a7

    printf("Performing ecall %d.\n", opcode);

    switch(opcode) {
        case 0x0a: //exit
            stop = 1;
        break;
    }
}

void print_results() {
    printf("Registers:\nx0 = 0\n");

    for(int i = 1; i < 32; i++) {
        printf("x%d = %d\n", i, x[i]);
    }
}

//Decode instruction
uint32_t decode(uint32_t instruction) {
    int opcode = instruction & 0b1111111; // 7 least significant bits are opcode

    printf("Performing opcode: %d\n", opcode);

    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct7;
    int32_t imm;

    // deciding which format to use

    if(opcode == 0x33) { // R-format
        rd =     (instruction & 0b00000000000000000000111110000000) >> 7;
        funct3 = (instruction & 0b00000000000000000111000000000000) >> 12;
        rs1 =    (instruction & 0b00000000000011111000000000000000) >> 15;
        rs2 =    (instruction & 0b00000001111100000000000000000000) >> 20;
        funct7 = (instruction & 0b11111110000000000000000000000000) >> 25;
    }
    else if(opcode == 0x13) { // I-format
        rd =     (instruction & 0b00000000000000000000111110000000) >> 7;
        funct3 = (instruction & 0b00000000000000000111000000000000) >> 12;
        rs1 =    (instruction & 0b00000000000011111000000000000000) >> 15;
        imm =    (instruction & 0b11111111111100000000000000000000) >> 20;
    }


    switch(opcode) {
        case 0x33:
            ADD(x, rd, funct3, rs1, rs2, funct7);
        break;
        case 0x13:
            LI(x, rd, funct3, rs1, imm);
        break;
        case 0x73:
            ecall();
        break;
        default:
            //nop
        break;
        /*case 0x37:
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
                case 0x1:
                    SLL(instruction);
                case 0x2:
                    SLT(instruction);
                case 0x3:
                    SLTU(instruction);
                case 0x4:
                    XOR(instruction);
                case 0x5:
                    switch (imm_sr) {
                        case 0x0:
                            SRL(instruction);
                        case 0x20:
                            SRA(instruction);
                    }
                case 0x6:
                    OR(instruction);
                case 0x7:
                    AND(instruction);
            }*/
   }
}


void run_program() {
    printf("Running program...\n");

    while(!stop) {
        uint32_t current_instruction = read_instruction();

        decode(current_instruction);

        pc++;
    }
}



//Function to load program
int load(char* fname){
    printf("Opening .bin file...\n");

    FILE* file = fopen(fname, "r");

    int memory_position = 0;
    long file_size = get_file_size(file);

    printf("Collecting binary data into program memory...\n");

    while (ftell(file) < file_size - 4) {
        // collecting chars into one 32-bit instruction
        uint32_t read = 0;
        for(int j = 0; j <= 3; j++) {
            uint32_t byte = fgetc(file);

            read = (byte << (j * 8)) | read;
        }

        printf("%08x ", read);
        print_binary(read);
        printf("\n");

        mem[memory_position] = read;
        memory_position++;
    }

    fclose(file);

    run_program();

    print_results();

    printf("Exiting...");

    return 0;
}

int main(int argc, char* argv[]){
    if(argc != 2) {
        printf("Missing argument");
        return 1;
    }
    load(argv[1]);

}