#include "stdint.h"

// 0x13
void ADDI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void SLTI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void SLTIU(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void XORI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void ORI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void ANDI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void SLLI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void SRAI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);


void ADD(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void SUB(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void SLT(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void SLTU(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void XOR(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void OR(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void AND(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);

void BEQ(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);
void BNE(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);
void BLT(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);
void BGE(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);
void BLTU(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);
void BGEU(int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);

void LUI(int32_t x[32], uint8_t rd, int32_t imm);