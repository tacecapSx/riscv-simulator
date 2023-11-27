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

//Read a word from byte memory
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
            printf("x%02d = 0x%08x, ", i+j, x[i+j]);
        }
        printf("\n");
    }
}

//Decode and execute instruction
void execute(uint32_t instruction) {
    int opcode = instruction & 0x7F; // 7 least significant bits are opcode

    uint8_t rd;
    uint8_t funct3;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct7;
    int32_t imm;

    // universal data positions
    rd =     (instruction & 0b00000000000000000000111110000000) >> 7;
    funct3 = (instruction & 0b00000000000000000111000000000000) >> 12;
    rs1 =    (instruction & 0b00000000000011111000000000000000) >> 15;
    rs2 =    (instruction & 0b00000001111100000000000000000000) >> 20;

    // deciding which format to use

    if(opcode == 0x33) { // R-format
        funct7 = instruction >> 25;
    }
    else if(opcode == 0x13 || opcode == 0x3 || opcode == 0x67) { // I-format
        imm =    (int32_t)instruction >> 20;
        funct7 = instruction >> 25;
    }
    else if(opcode == 0x23) { // S-format
        imm = ((int32_t)(((instruction & 0b11111110000000000000000000000000) >> 20) | ((instruction & 0b00000000000000000000111110000000) >> 7)) << 20) >> 20;
    }
    else if(opcode == 0x63) { // SB-format
        imm = (int32_t)((((((instruction & 0x7E000000) >> 21) | ((instruction & 0xF00) >> 8)) | ((instruction & 0x80000000) >> 20)) | ((instruction & 0x80) << 3)) << 20) >> 19;
    }
    else if(opcode == 0x37 || opcode == 0x17) { // U-format
        imm = (int32_t)instruction >> 12;
    }
    else if(opcode == 0x6F) { // UJ-format
        imm = (int32_t)((instruction & 0x80000000) | ((instruction & 0xFF000) << 11) | ((instruction & 0x100000) << 2) | ((instruction & 0x7FE00000) >> 9)) >> 11;
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
}

//Main program loop
void run_program() {
    printf("Running program...\n");

    while(!stop) {
        uint32_t current_instruction = read_instruction();
        printf("Performing instruction: 0x%08x\n",current_instruction);

        execute(current_instruction);

        x[0] = 0; // make sure x0 is always 0

        if(!jump) {
            pc += 4; // go to next instruction (4 bytes ahead)
        }
        else {
            jump = 0;
        }
    }
}

//Function to load program from binary file
int load(char* fname){
    printf("Opening .bin file...\n");

    FILE* file = fopen(fname, "r");

    if(file != NULL) {
        int memory_position = 0;
        
        printf("Collecting binary data into program memory...\n");

        do {
            mem[memory_position] = fgetc(file);
            memory_position++;
        }
        while (!feof(file));

        fclose(file);

        return 0;
    }

    printf("ERROR: .bin file not found!");
    return 1;
}

//Dumping register contents to a binary .res file
int create_result_file(char* file_name) {
    FILE* file = fopen(file_name, "wb");

    if (file != NULL) {
        // write the entire register array to the file
        fwrite(x, sizeof(uint32_t), sizeof(x) / sizeof(uint32_t), file);

        fclose(file);
        printf("\n.res file written successfully!\n");

        return 0;
    }
    
    printf("\nERROR: Failed to write .res file!\n");
    return 1;
}

int compare_results(char* binary_file, char* generated_result_filename) {
    printf("\nComparing file \"%s\"", generated_result_filename);
    FILE* file1 = fopen(generated_result_filename, "r");
    
    char* dot_position = strchr(binary_file, '.');
    strcpy(dot_position + 1, "res");

    printf(" to \"%s\"...\n", binary_file);

    FILE* file2 = fopen(binary_file, "r");

    if(file1 != NULL && file2 != NULL) {
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

        return 0;
    }

    printf("ERROR: One or both .res files not found!");
    return 1;
}

int main(int argc, char* argv[]){
    if(argc != 2) {
        printf("Missing argument");
        return 1;
    }

    if(load(argv[1])) {
        return 1; // return error, as file is not found
    }

    run_program();

    print_results();

    // create file name to save by adding the .res file extension to the input file
    char* file_name_to_save = argv[1];
    sprintf(file_name_to_save, "%s.res", argv[1]);

    if(create_result_file(file_name_to_save)) {
        return 1; // return error, as .res file failed to be written
    }

    if(compare_results(argv[1], file_name_to_save)){
        return 1; // return error, as one or both .res files cannot be found
    }

    printf("\nExiting...\n");

    return 0;
}