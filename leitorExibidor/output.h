#ifndef OUTPUT_H
#define OUTPUT_H

#include "types.h"
#include "reader.h"
#include "bytecode.h"

// Bernardo
    
void print_class_file(ClassFile * class_file);
void print_constant_pool(Constant * constant_pool);
void print_fields(Field * fields);
void print_methods(Method * methods);
void print_attributes(Attribute * attributes);
void print_classfile_access_flags_translation(uint16_t access_flags);
void print_fields_access_flags_translation(uint16_t access_flags);
void print_methods_access_flags_translation(uint16_t access_flags);
void print_inner_classes_access_flags_translation(uint16_t access_flags);

void print_divider();
void print_title(const char * string);

void print_code(CodeAttribute code);
void print_instruction(Instruction instruction);

#endif