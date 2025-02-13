#ifndef INVOKE_H
#define INVOKE_H

#include "types.h"
#include "interpreter.h"
#include "instructions.h"
#include "stringBuffer.h"

int invoke_dynamic(Frame * frame, Instruction instruction);
int invoke_interface(Frame * frame, Instruction instruction);
int invoke_special(Frame * frame, Instruction instruction);
int invoke_static(Frame * frame, Instruction instruction);
int invoke_virtual(Frame * frame, Instruction instruction);

int common_invoke(Frame * frame, Instruction instruction, char include_this);
Arguments * get_arguments(Frame * frame, char include_this, char * method_descriptor);

#endif