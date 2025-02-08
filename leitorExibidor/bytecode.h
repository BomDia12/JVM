#ifndef BYTECODE_H
#define BYTECODE_H

#include "types.h"
#include "instructions.h"
#include "reader.h"

// Miguel

Instruction read_instruction();
Instruction read_instruction_buffer(Buffer * code_buffer);

#endif