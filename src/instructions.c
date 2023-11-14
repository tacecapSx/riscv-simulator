#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

void ADDI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] + imm;
}

void XORI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] ^ imm;
}

void ORI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] | imm;
}

void ANDI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] & imm;
}

void ADD(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] + x[rs2];
}

void XOR(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] ^ x[rs2];
}

void OR(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] | x[rs2];
}

void AND(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] & x[rs2];
}

void LUI(int32_t x[32], uint8_t rd, int32_t imm) {
    x[rd] = imm << 12;
}