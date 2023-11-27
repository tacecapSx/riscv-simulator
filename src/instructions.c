#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#define MEMORY_CAPACITY 1048576
#define REGISTER_AMOUNT 32

void ADDI(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] + imm;
}

void SLTI(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] < imm;
}

void SLTIU(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = (uint32_t)x[rs1] < imm;
}

void XORI(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] ^ imm;
}

void ORI(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] | imm;
}

void ANDI(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] & imm;
}

void SLLI(uint32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] << (imm & 0x1f);
}

void SRAI(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    int significant = x[rd] >> 31;
    x[rd] = x[rs1];
    for (int i = 0; i < (imm & 0x1f); i++) {
        x[rd] = x[rd] >> 1;
        x[rd] = x[rd] | (significant << 31);
    }
}

void LB(int32_t x[REGISTER_AMOUNT], uint8_t mem[MEMORY_CAPACITY], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = (int32_t)((int8_t)mem[imm + x[rs1]]);
}

void LH(int32_t x[REGISTER_AMOUNT], uint8_t mem[MEMORY_CAPACITY], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = (int32_t)(*(int16_t*)&mem[imm + x[rs1]]);
}

void LW(int32_t x[REGISTER_AMOUNT], uint8_t mem[MEMORY_CAPACITY], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = *(int32_t*)&mem[imm + x[rs1]];
}

void LBU(int32_t x[REGISTER_AMOUNT], uint8_t mem[MEMORY_CAPACITY], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = (int32_t)((uint8_t)mem[imm + x[rs1]]);
}

void LHU(int32_t x[REGISTER_AMOUNT], uint8_t mem[MEMORY_CAPACITY], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = (int32_t)(*(uint16_t*)&mem[imm + x[rs1]]);
}

void SB(int32_t x[REGISTER_AMOUNT], uint8_t mem[MEMORY_CAPACITY], uint8_t funct3, uint8_t rs1, uint8_t rs2, int32_t imm) {
    mem[imm + x[rs1]] = x[rs2] & 0xFF;
}

void SH(int32_t x[REGISTER_AMOUNT], uint8_t mem[MEMORY_CAPACITY], uint8_t funct3, uint8_t rs1, uint8_t rs2, int32_t imm) {
    mem[imm + x[rs1]] = x[rs2] & 0xFF;
    mem[imm + x[rs1] + 1] = (x[rs2] & 0xFF00) >> 8;
}

void SW(int32_t x[REGISTER_AMOUNT], uint8_t mem[MEMORY_CAPACITY], uint8_t funct3, uint8_t rs1, uint8_t rs2, int32_t imm) {
    mem[imm + x[rs1]] = x[rs2] & 0xFF;
    mem[imm + x[rs1] + 1] = (x[rs2] & 0xFF00) >> 8;
    mem[imm + x[rs1] + 2] = (x[rs2] & 0xFF0000) >> 16;
    mem[imm + x[rs1] + 3] = (x[rs2] & 0xFF000000) >> 24;
}

void ADD(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] + x[rs2];
}

void SUB(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] - x[rs2];
}

void SLT(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] < x[rs2];
}

void SLTU(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = (uint32_t)x[rs1] < (uint32_t)x[rs2];
}

void XOR(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] ^ x[rs2];
}

void OR(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] | x[rs2];
}

void AND(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] & x[rs2];
}

void BEQ(int *jump, int32_t x[REGISTER_AMOUNT], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if(x[rs1] == x[rs2]) {
        *jump = 1;
        *pc += imm;
    }
}

void BNE(int *jump, int32_t x[REGISTER_AMOUNT], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if(x[rs1] != x[rs2]) {
        *jump = 1;
        *pc += imm;
    }
}

void BLT(int *jump, int32_t x[REGISTER_AMOUNT], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if(x[rs1] < x[rs2]) {
        *jump = 1;
        *pc += imm;
    }
}

void BGE(int *jump, int32_t x[REGISTER_AMOUNT], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if(x[rs1] >= x[rs2]) {
        *jump = 1;
        *pc += imm;
    }
}

void BLTU(int *jump, int32_t x[REGISTER_AMOUNT], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if((uint32_t)x[rs1] < (uint32_t)x[rs2]) {
        *jump = 1;
        *pc += imm;
    }
}

void BGEU(int *jump, int32_t x[REGISTER_AMOUNT], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm) {
    if((uint32_t)x[rs1] >= (uint32_t)x[rs2]) {
        *jump = 1;
        *pc += imm;
    }
}

void LUI(int32_t x[REGISTER_AMOUNT], uint8_t rd, int32_t imm) {
    x[rd] = ((uint32_t)x[rd] & 0xfff) | ((uint32_t)imm << 12);
}

void AUIPC(int32_t x[REGISTER_AMOUNT], uint32_t *pc, uint8_t rd, int32_t imm) {
    x[rd] = (*pc + imm) << 12;
}

void SLL(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] << x[rs2];
}

void SRL(uint32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] >> x[rs2];
}

void SRA(int32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    int significant = x[rd] >> 31;
    x[rd] = x[rs1];
    for (int i = 0; i < x[rs2]; i++) {
        x[rd] = x[rd] >> 1;
        x[rd] = x[rd] | (significant << 31);
    }
}

void SRLI(uint32_t x[REGISTER_AMOUNT], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] >> (imm & 0x1f);
}

void JAL(int32_t x[REGISTER_AMOUNT], uint32_t *pc, uint8_t rd, int32_t imm) {
    x[rd] = *pc + 4;
    *pc += imm;
}

void JALR(int32_t x[REGISTER_AMOUNT], uint32_t *pc, uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = *pc + 4;
    *pc = x[rs1] + imm;
}