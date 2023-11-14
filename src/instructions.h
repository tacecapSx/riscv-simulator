#include "stdint.h"

void ADDI(uint32_t x[32], int rd, int funct3, int rs1, int imm);
void ADD(uint32_t x[32], int rd, int funct3, int rs1, int rs2, int funct7);
void XOR(uint32_t x[32], int rd, int funct3, int rs1, int rs2, int funct7);
void OR(uint32_t x[32], int rd, int funct3, int rs1, int rs2, int funct7);
void AND(uint32_t x[32], int rd, int funct3, int rs1, int rs2, int funct7);
void XORI(uint32_t x[32], int rd, int funct3, int rs1, int imm);
void ORI(uint32_t x[32], int rd, int funct3, int rs1, int imm);
void ANDI(uint32_t x[32], int rd, int funct3, int rs1, int imm);
void LUI(uint32_t x[32], int rd, int imm);