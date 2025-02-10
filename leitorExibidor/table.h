#ifndef TABLE_H
#define TABLE_H

#include "types.h"
#include "instructions.h"
#include "array.h"

int lookupswitch(Frame * frame, Instruction instruction);
int tableswitch(Frame * frame, Instruction instruction);

#endif