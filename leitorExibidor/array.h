#ifndef ARRAY_H
#define ARRAY_H

#include "types.h"
#include <stdlib.h>
#include "instructions.h"

ArrayList * get_array_list();
Array * get_array(uint32_t index);
uint32_t add_array(Array * array);

void free_array(Array * array);
void free_array_list(ArrayList * array_list);

int new_array(Frame * frame, Instruction instruction);
int anewarray(Frame * frame, Instruction instruction);
int arraylength(Frame * frame, Instruction instruction);

int iaload(Frame * frame, Instruction instruction);
int laload(Frame * frame, Instruction instruction);
int faload(Frame * frame, Instruction instruction);
int daload(Frame * frame, Instruction instruction);
int aaload(Frame * frame, Instruction instruction);
int baload(Frame * frame, Instruction instruction);
int caload(Frame * frame, Instruction instruction);
int saload(Frame * frame, Instruction instruction);

int iastore(Frame * frame, Instruction instruction);
int lastore(Frame * frame, Instruction instruction);
int fastore(Frame * frame, Instruction instruction);
int dastore(Frame * frame, Instruction instruction);
int aastore(Frame * frame, Instruction instruction);
int bastore(Frame * frame, Instruction instruction);
int castore(Frame * frame, Instruction instruction);
int sastore(Frame * frame, Instruction instruction);

#endif
