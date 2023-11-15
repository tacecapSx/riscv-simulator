#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

void ADDI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] + imm;
}

void SLTI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] < imm;
}

void SLTIU(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = (uint32_t)x[rs1] < imm;
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

void SLLI(uint32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] << (imm & 0x1f);
}

void SRAI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    int significant = x[rd] >> 31;
    x[rd] = x[rs1];
    for (int i = 0; i < (imm & 0x1f); i++) {
        x[rd] = x[rd] >> 1;
        x[rd] = x[rd] | (significant << 31);
    }
}

void ADD(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] + x[rs2];
}

void SUB(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] - x[rs2];
}

void SLT(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] < x[rs2];
}

void SLTU(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = (uint32_t)x[rs1] < (uint32_t)x[rs2];
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

void BEQ(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if(x[rs1] == x[rs2]) {
        *pc += (imm - 4);
    }
}

void BNE(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if(x[rs1] != x[rs2]) {
        *pc += (imm - 4);
    }
}

void BLT(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if(x[rs1] < x[rs2]) {
        *pc += (imm - 4);
    }
}

void BGE(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if(x[rs1] >= x[rs2]) {
        *pc += (imm - 4);
    }
}

void BLTU(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if((uint32_t)x[rs1] < (uint32_t)x[rs2]) {
        *pc += (imm - 4);
    }
}

void BGEU(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if((uint32_t)x[rs1] >= (uint32_t)x[rs2]) {
        *pc += (imm - 4);
    }
}

void LUI(int32_t x[32], uint8_t rd, int32_t imm) {
    x[rd] = ((uint32_t)x[rd] & 0xfff) | ((uint32_t)imm << 12);
}

void SLL(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] << x[rs2];
}

void SRL(uint32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] >> x[rs2];
}

void SRA(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    int significant = x[rd] >> 31;
    x[rd] = x[rs1];
    for (int i = 0; i < x[rs2]; i++) {
        x[rd] = x[rd] >> 1;
        x[rd] = x[rd] | (significant << 31);
    }
}

void SRLI(uint32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] >> (imm & 0x1f);
}

