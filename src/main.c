// to compile (win): gcc.exe src/instructions.c src/main.c -o main.exe

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "instructions.h"
#include <string.h>

//defining the instruction formats
uint32_t r_format_instructions[] = {0x33,0xFF};
uint32_t i_format_instructions[] = {0x13,0xFF};
uint32_t s_format_instructions[] = {0xFF};
uint32_t sb_format_instructions[] = {0xFF};
uint32_t u_format_instructions[] = {0x37,0xFF};
uint32_t uj_format_instructions[] = {0xFF};

//defining stop signal 32 bit program counter.
int stop = 0;
uint32_t pc = 0;

//register x1 to x32
int32_t x[32];

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
        printf("x%d = %x\n", i, x[i]);
    }
}

int array_contains_value(int value, uint32_t* array) {
    int i = 0;
    
    while(array[i] != 0xFF) {
        if(value == array[i]) {
            return 1;
        }

        i++;
    }

    return 0;
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

    if(array_contains_value(opcode,r_format_instructions)) { // R-format
        rd =     (instruction & 0b00000000000000000000111110000000) >> 7;
        funct3 = (instruction & 0b00000000000000000111000000000000) >> 12;
        rs1 =    (instruction & 0b00000000000011111000000000000000) >> 15;
        rs2 =    (instruction & 0b00000001111100000000000000000000) >> 20;
        funct7 = instruction >> 25;
    }
    else if(array_contains_value(opcode,i_format_instructions)) { // I-format
        rd =     (instruction & 0b00000000000000000000111110000000) >> 7;
        funct3 = (instruction & 0b00000000000000000111000000000000) >> 12;
        rs1 =    (instruction & 0b00000000000011111000000000000000) >> 15;
        imm =    (int32_t)instruction >> 20;
    }
    else if(array_contains_value(opcode,u_format_instructions)) { // U-format
        rd =     (instruction & 0b00000000000000000000111110000000) >> 7;
        imm =    (int32_t)instruction >> 12;
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
                case 0b010:
                    SLT(x, rd, funct3, rs1, rs2, funct7);
                break;
                case 0b011:
                    SLTU(x, rd, funct3, rs1, rs2, funct7);
                break;
                case 0b100:
                    XOR(x, rd, funct3, rs1, rs2, funct7);
                break;
                case 0b110:
                    OR(x, rd, funct3, rs1, rs2, funct7);
                break;
                case 0b111:
                    AND(x, rd, funct3, rs1, rs2, funct7);
                break;
            }
        break;
        case 0x13:
        printf("%d",funct3);
            switch(funct3) {
                case 0b000:
                    ADDI(x, rd, funct3, rs1, imm);
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
            }
        break;
        case 0x37:
            LUI(x, rd, imm);
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

        x[0] = 0; // make sure x0 is always 0

        pc++;
    }
}

//Function to load program
void load(char* fname){
    printf("Opening .bin file...\n");

    FILE* file = fopen(fname, "r");

    int memory_position = 0;
    long file_size = get_file_size(file);

    printf("Collecting binary data into program memory...\n");

    while (ftell(file) < file_size) {
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
}

void create_result_file(char* file_name) {
    // open the file in binary write mode
    FILE* file = fopen(file_name, "wb");

    if (file != NULL) {
        // write the data to the file
        fwrite(x, sizeof(uint32_t), sizeof(x) / sizeof(uint32_t), file);

        // close the file when done
        fclose(file);
        printf("File written successfully!\n");
    } else {
        // handle error if file couldn't be opened
        printf("Error opening file!\n");
    }
}

void compare_results(char* binary_file, char* generated_result_filename) {
    FILE* file1 = fopen(generated_result_filename, "r");
    
    char* dot_position = strchr(binary_file, '.');
    strcpy(dot_position + 1, "res");

    FILE* file2 = fopen(binary_file, "r");

    char byte1;
    char byte2;
    int i = 0;
    int found_difference = 0;

    printf("Comparing results...\n");

    do {
        byte1 = fgetc(file1);
        byte2 = fgetc(file2);

        if (byte1 != byte2) {
            found_difference = 1;
            printf("Difference at byte %d\n", i);
        }

        i++;
    } while (byte1 != EOF && byte2 != EOF);

    // close the files when done
    fclose(file1);
    fclose(file2);

    if(!found_difference) {
        printf("No differences found!\n");
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

    return 0;
}