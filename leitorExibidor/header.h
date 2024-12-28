#ifndef HEADER_H
#define HEADER_H

#include "types.h"
#include "reader.h"
#include "attribute.h"

ClassFile * read_class_file();
Constant * read_constant_pool();
Field * read_fields();
Method * read_methods();

void free_class_file(ClassFile * class_file);
void free_constant_pool(Constant * constant_pool);
void free_fields(Field * fields);
void free_methods(Method * methods);

#endif