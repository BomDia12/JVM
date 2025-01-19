#ifndef HEADER_H
#define HEADER_H

#include "types.h"
#include "reader.h"
#include "attribute.h"

// Vanessa

ClassFile * read_class_file(char path[]);
Constant * read_constant_pool(FILE *fp, uint16_t constant_pool_count);
Field * read_fields(FILE *fp, uint16_t fields_count);
Method * read_methods(FILE *fp, uint16_t methods_count);

ClassFile * get_current_class_file();

void free_class_file(ClassFile * class_file);
void free_constant_pool(Constant * constant_pool);
void free_fields(Field * fields);
void free_methods(Method * methods);

#endif