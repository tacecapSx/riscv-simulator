#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

void ADDI(uint32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int imm) {
    x[rd] = x[rs1] + imm;
}

void LI(uint32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int imm) {
    ADDI(x, rd, funct3, 0, imm);
}

void ADD(uint32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] + x[rs2];
}