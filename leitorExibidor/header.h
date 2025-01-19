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
Constant * read_constant_pool(uint16_t constant_pool_count);
Field * read_fields(uint16_t fields_count);
Method * read_methods(uint16_t methods_count);

ClassFile * get_current_class_file();

void free_class_file(ClassFile * class_file);
void free_constant_pool(Constant * constant_pool, uint16_t constant_pool_count);
void free_fields(Field * fields, uint16_t fields_count);
void free_methods(Method * methods, uint16_t methods_count);

#endif