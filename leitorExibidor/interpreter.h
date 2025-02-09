#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "types.h"
#include "instructions.h"
#include "header.h"
#include "bytecode.h"

int run_class_file(ClassFile * class_file);

MethodResponses call_method(Frame * current_frame, ClassFile * class_file, Method * method, Arguments * arguments);

ClassFile * load_class_file(char * class_name);
ClassFile * get_class_file(char * class_name);

#endif