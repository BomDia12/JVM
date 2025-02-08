#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "types.h"
#include "array.h"

InstructionType * get_instruction_type(uint8_t opcode);

void nop(Frame * frame);

void add_to_stack(Frame * frame, uint32_t value);
uint32_t remove_from_stack(Frame * frame);

void load_constant(Frame * frame, Instruction instruction);

#endif
