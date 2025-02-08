#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "types.h"
#include "arithmetic.h"
#include <math.h>
#include "array.h"

InstructionType * get_instruction_type(uint8_t opcode);

void nop(Frame * frame);

void add_to_stack(Frame * frame, uint32_t value);
uint32_t remove_from_stack(Frame * frame);
int32_t uint32_to_int(uint32_t value);
uint32_t int_to_uint32(int32_t value);
int64_t uint64_to_long(uint64_t value);
uint64_t long_to_uint64(int64_t value);
float uint32_to_float(uint32_t value);
uint32_t float_to_uint32(float value);
double uint64_to_double(uint64_t value);
uint64_t double_to_uint64(double value);

void load_constant(Frame * frame, Instruction instruction);

#endif
