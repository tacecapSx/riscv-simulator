#include "stdint.h"

#define MEMORY_CAPACITY 2097152

// 0x13
void ADDI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void SLTI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void SLTIU(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void XORI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void ORI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void ANDI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void SLLI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void SRAI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void SRLI(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);

// 0x3
void LB(int32_t x[32], uint8_t mem[MEMORY_CAPACITY], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void LH(int32_t x[32], uint8_t mem[MEMORY_CAPACITY], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void LW(int32_t x[32], uint8_t mem[MEMORY_CAPACITY], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void LBU(int32_t x[32], uint8_t mem[MEMORY_CAPACITY], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);
void LHU(int32_t x[32], uint8_t mem[MEMORY_CAPACITY], uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);

// 0x23
void SB(int32_t x[32], uint8_t mem[MEMORY_CAPACITY], uint8_t funct3, uint8_t rs1, uint8_t rs2, int32_t imm);
void SH(int32_t x[32], uint8_t mem[MEMORY_CAPACITY], uint8_t funct3, uint8_t rs1, uint8_t rs2, int32_t imm);
void SW(int32_t x[32], uint8_t mem[MEMORY_CAPACITY], uint8_t funct3, uint8_t rs1, uint8_t rs2, int32_t imm);

// 0x33
void ADD(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void SUB(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void SLT(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void SLTU(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void XOR(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void OR(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void AND(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void SLL(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void SRL(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);
void SRA(int32_t x[32], uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7);

void BEQ(int *jump, int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);
void BNE(int *jump, int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);
void BLT(int *jump, int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);
void BGE(int *jump, int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);
void BLTU(int *jump, int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);
void BGEU(int *jump, int32_t x[32], uint32_t *pc, uint8_t rs1, uint8_t rs2, int32_t imm);

// 0x37
void LUI(int32_t x[32], uint8_t rd, int32_t imm);

// 0x17
void AUIPC(int32_t x[32], uint32_t *pc, uint8_t rd, int32_t imm);

// 0x6F
void JAL(int32_t x[32], uint32_t *pc, uint8_t rd, int32_t imm);

// 0x67
void JALR(int32_t x[32], uint32_t *pc, uint8_t rd, uint8_t funct3, uint8_t rs1, int32_t imm);