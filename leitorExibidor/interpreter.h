#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "types.h"
#include "instructions.h"
#include "header.h"
#include "bytecode.h"

void run_class_file(ClassFile * class_file);

uint32_t call_method(Frame * current_frame, ClassFile * class_file, char * method_name);

#endif