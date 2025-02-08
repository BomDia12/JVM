#ifndef ARRAY_H
#define ARRAY_H

#include "types.h"
#include "instructions.h"

ArrayList * get_array_list();

Array * get_array(uint32_t index);

uint32_t add_array(Array * array);

void new_array(Frame * frame, Instruction instruction);
void anewarray(Frame * frame, Instruction instruction);
void arraylength(Frame * frame, Instruction instruction);

void iaload(Frame * frame, Instruction instruction);
void laload(Frame * frame, Instruction instruction);
void faload(Frame * frame, Instruction instruction);
void daload(Frame * frame, Instruction instruction);
void aaload(Frame * frame, Instruction instruction);
void baload(Frame * frame, Instruction instruction);
void caload(Frame * frame, Instruction instruction);
void saload(Frame * frame, Instruction instruction);

#endif
