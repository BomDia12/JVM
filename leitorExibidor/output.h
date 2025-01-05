#ifndef OUTPUT_H
#define OUTPUT_H

#include "types.h"

// Bernardo

void print_class_file(ClassFile * class_file);
void print_constant_pool(Constant * constant_pool);
void print_fields(Field * fields);
void print_methods(Method * methods);
void print_attributes(Attribute * attributes);

#endif