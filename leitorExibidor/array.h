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

void iastore(Frame * frame, Instruction instruction);
void lastore(Frame * frame, Instruction instruction);
void fastore(Frame * frame, Instruction instruction);
void dastore(Frame * frame, Instruction instruction);
void aastore(Frame * frame, Instruction instruction);
void bastore(Frame * frame, Instruction instruction);
void castore(Frame * frame, Instruction instruction);
void sastore(Frame * frame, Instruction instruction);

#endif
