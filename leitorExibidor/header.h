#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attribute.h"
#include "reader.h"
#include "types.h"

// Vanessa

ClassFile * read_class_file();
Constant * read_constant();
Field * read_field();
Method * read_method();
Constant * getFromConstantPool(ClassFile * class_file, uint16_t index);

ClassFileBuffer * get_current_class_file();
void pushToClassFileBuffer(ClassFile * class_file);

void free_class_file(ClassFile * class_file);
void free_constant(Constant * constant);
void free_field(Field * fields);
void free_method(Method * methods);

#endif