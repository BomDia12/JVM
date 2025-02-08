#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "types.h"
#include "arithmetic.h"
#include "conversions.h"
#include "stackops.h"
#include <math.h>
#include "array.h"

InstructionType * get_instruction_type(uint8_t opcode);

int nop(Frame * frame, Instruction instruction);

void add_to_stack(Frame * frame, uint32_t value);
uint32_t remove_from_stack(Frame * frame);

void load_constant(Frame * frame, Instruction instruction);

#endif
