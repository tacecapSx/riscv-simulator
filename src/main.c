// to compile (linux/mac): gcc src/instructions.c src/main.c -o main.out -std=c99
// to run (linux/mac):     ./main.out <binary_file_path>

// to compile (win): gcc src/instructions.c src/main.c -o main.exe -std=c99
// to run (win):     ./main.exe <binary_file_path>

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "instructions.h"
#include <string.h>

// defining jump and stop signals (booleans)
int jump = 0;
int stop = 0;

// 32-bit program counter
uint32_t pc = 0;

// registers
int32_t x[32];

// memory with 1 mb.
uint8_t mem[MEMORY_CAPACITY];

void print_binary(uint32_t instruction) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (instruction >> i) & 1);
    }
}

uint32_t read_instruction() {
    return *(uint32_t*)&mem[pc];
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
    printf("\nRegister contents:\n");

    for(int i = 0; i < 32; i+=4) {
        for(int j = 0; j < 4; j++) {
            printf("x%d = 0x%08x,\t", i+j, x[i+j]);
        }
        printf("\n");
    }
}

//Decode instruction
uint32_t decode(uint32_t instruction) {
    int opcode = instruction & 0x7F; // 7 least significant bits are opcode

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
        funct7 = instruction >> 25;
    }
    else if(opcode == 0x13 || opcode == 0x3 || opcode == 0x67) { // I-format
        rd =     (instruction & 0b00000000000000000000111110000000) >> 7;
        funct3 = (instruction & 0b00000000000000000111000000000000) >> 12;
        rs1 =    (instruction & 0b00000000000011111000000000000000) >> 15;
        imm =    (int32_t)instruction >> 20;
        funct7 = instruction >> 25;
    }
    else if(opcode == 0x23) { // S-format
        funct3 = (instruction & 0b00000000000000000111000000000000) >> 12;
        rs1 =    (instruction & 0b00000000000011111000000000000000) >> 15;
        rs2 =    (instruction & 0b00000001111100000000000000000000) >> 20;
        imm =    ((int32_t)(((instruction & 0b11111110000000000000000000000000) >> 20) | ((instruction & 0b00000000000000000000111110000000) >> 7)) << 20) >> 20;
    }
    else if(opcode == 0x63) { // SB-format
        funct3 = (instruction & 0b00000000000000000111000000000000) >> 12;
        rs1 =    (instruction & 0b00000000000011111000000000000000) >> 15;
        rs2 =    (instruction & 0b00000001111100000000000000000000) >> 20;
        imm =    (int32_t)((((((instruction & 0x7E000000) >> 21) | ((instruction & 0xF00) >> 8)) | ((instruction & 0x80000000) >> 20)) | ((instruction & 0x80) << 3)) << 20) >> 19;
    }
    else if(opcode == 0x37 || opcode == 0x17) { // U-format
        rd =     (instruction & 0b00000000000000000000111110000000) >> 7;
        imm =    (int32_t)instruction >> 12;
    }
    else if(opcode == 0x6F) { // UJ-format
        rd =    (instruction & 0b00000000000000000000111110000000) >> 7;
        imm =   (int32_t)((instruction & 0x80000000) | ((instruction & 0xFF000) << 11) | ((instruction & 0x100000) << 2) | ((instruction & 0x7FE00000) >> 9)) >> 11;
    }

    switch(opcode) {
        case 0x33:
            switch(funct3)
            {
                case 0b000:
                    if(funct7 == 0) {
                        ADD(x, rd, funct3, rs1, rs2, funct7);
                    }
                    else {
                        SUB(x, rd, funct3, rs1, rs2, funct7);
                    }
                    break;
                case 0b001:
                    SLL(x, rd, funct3, rs1, rs2, funct7);
                    break;
                case 0b010:
                    SLT(x, rd, funct3, rs1, rs2, funct7);
                    break;
                case 0b011:
                    SLTU(x, rd, funct3, rs1, rs2, funct7);
                    break;
                case 0b100:
                    XOR(x, rd, funct3, rs1, rs2, funct7);
                    break;
                case 0b101:
                    if(funct7 == 0) {
                        SRL(x, rd, funct3, rs1, rs2, funct7);
                    } else {
                        SRA(x, rd, funct3, rs1, rs2, funct7);
                    }
                    break;
                case 0b110:
                    OR(x, rd, funct3, rs1, rs2, funct7);
                    break;
                case 0b111:
                    AND(x, rd, funct3, rs1, rs2, funct7);
                    break;
            }
        break;
        case 0x3:
            switch(funct3) {
                case 0b000:
                    LB(x, mem, rd, funct3, rs1, imm);
                    break;
                case 0b001:
                    LH(x, mem, rd, funct3, rs1, imm);
                    break;
                case 0b010:
                    LW(x, mem, rd, funct3, rs1, imm);
                    break;
                case 0b100:
                    LBU(x, mem, rd, funct3, rs1, imm);
                    break;
                case 0b101:
                    LHU(x, mem, rd, funct3, rs1, imm);
                    break;
            }
        break;
        case 0x23:
            switch(funct3) {
                case 0b000:
                    SB(x, mem, funct3, rs1, rs2, imm);
                    break;
                case 0b001:
                    SH(x, mem, funct3, rs1, rs2, imm);
                    break;
                case 0b010:
                    SW(x, mem, funct3, rs1, rs2, imm);
                    break;
            }
        break;
        case 0x13:
            switch(funct3) {
                case 0b000:
                    ADDI(x, rd, funct3, rs1, imm);
                    break;
                case 0b001:
                    SLLI(x, rd, funct3, rs1, imm);
                    break;
                case 0b010:
                    SLTI(x, rd, funct3, rs1, imm);
                    break;
                case 0b011:
                    SLTIU(x, rd, funct3, rs1, imm);
                    break;
                case 0b100:
                    XORI(x, rd, funct3, rs1, imm);
                break;
                case 0b110:
                    ORI(x, rd, funct3, rs1, imm);
                    break;
                case 0b111:
                    ANDI(x, rd, funct3, rs1, imm);
                    break;
                case 0b101:
                    if(funct7 == 0) {
                        SRLI(x, rd, funct3, rs1, imm);
                    } else {
                        SRAI(x, rd, funct3, rs1, imm);
                    }
                    break;
            }
        break;
        case 0x37:
            LUI(x, rd, imm);
            break;
        case 0x17:
            AUIPC(x, &pc, rd, imm);
            break;
        case 0x63:
            switch(funct3) {
                case 0b000:
                    BEQ(&jump, x, &pc, rs1, rs2, imm);
                    break;
                case 0b001:
                    BNE(&jump, x, &pc, rs1, rs2, imm);
                    break;
                case 0b100:
                    BLT(&jump, x, &pc, rs1, rs2, imm);
                    break;
                case 0b101:
                    BGE(&jump, x, &pc, rs1, rs2, imm);
                    break;
                case 0b110:
                    BLTU(&jump, x, &pc, rs1, rs2, imm);
                    break;
                case 0b111:
                    BGEU(&jump, x, &pc, rs1, rs2, imm);
                    break;
            }
        break;
        case 0x73:
            ecall();
            break;
        case 0x6F:
            jump = 1;
            JAL(x, &pc, rd, imm);
            break;
        case 0x67:
            jump = 1;
            JALR(x, &pc, rd, funct3, rs1, imm);
            break;
        default:
            //nop
        break;
   }
    //return 0 if opp code not found
    return 0;
}

void run_program() {
    printf("Running program...\n");

    while(!stop) {
        uint32_t current_instruction = read_instruction();
        printf("Performing instruction: 0x%08x\n",current_instruction);

        decode(current_instruction);

        x[0] = 0; // make sure x0 is always 0

        if(!jump) {
            pc += 4;
        }
        else {
            jump = 0;
        }
    }
}

//Function to load program
void load(char* fname){
    printf("Opening .bin file...\n");

    FILE* file = fopen(fname, "r");

    int memory_position = 0;

    printf("Collecting binary data into program memory...\n");

    do {
        mem[memory_position] = fgetc(file);
        memory_position++;
    }
    while (!feof(file));

    fclose(file);
}

void create_result_file(char* file_name) {
    // open the file in binary write mode
    FILE* file = fopen(file_name, "wb");

    if (file != NULL) {
        // write the data to the file
        fwrite(x, sizeof(uint32_t), sizeof(x) / sizeof(uint32_t), file);

        // close the file when done
        fclose(file);
        printf("\nFile written successfully!\n");
    } else {
        printf("\nFailed to write result file!\n");
    }
}

void compare_results(char* binary_file, char* generated_result_filename) {
    printf("\nComparing file \"%s\"", generated_result_filename);
    FILE* file1 = fopen(generated_result_filename, "r");
    
    char* dot_position = strchr(binary_file, '.');
    strcpy(dot_position + 1, "res");

    printf(" to \"%s\"...\n", binary_file);

    FILE* file2 = fopen(binary_file, "r");

    uint8_t byte1;
    uint8_t byte2;
    int i = 0;
    int found_difference = 0;

    do {
        byte1 = fgetc(file1);
        byte2 = fgetc(file2);

        if (byte1 != byte2) {
            found_difference = 1;
            printf("Difference at byte %d\n", i);
        }

        i++;
    } while (!feof(file1) && !feof(file2));

    // close the files when done
    fclose(file1);
    fclose(file2);

    if(!found_difference) {
        printf("\nNo differences found!\n");
    }
}

int main(int argc, char* argv[]){
    if(argc != 2) {
        printf("Missing argument");
        return 1;
    }

    load(argv[1]);

    run_program();

    print_results();

    char* file_name_to_save = argv[1];
    sprintf(file_name_to_save, "%s.res", argv[1]);

    create_result_file(file_name_to_save);

    compare_results(argv[1], file_name_to_save);

    printf("\nExiting...\n");

    return 0;
}