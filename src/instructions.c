#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

void ADDI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm) {
    x[rd] = x[rs1] + imm;
}

void ADD(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7) {
    x[rd] = x[rs1] + x[rs2];
}