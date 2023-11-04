#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

//defining 32 bit program counter.
uint32_t PC = 0;

//zero register
const uint32_t x0 = 0;

//register x1 to x32
uint32_t x[31];

//memory with 2³² Gb RAM.
uint8_t *mem;










int main(){
    mem = malloc(4294967295*sizeof(uint8_t));
}