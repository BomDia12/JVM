#ifndef HEADER_H
#define HEADER_H

#include "types.h"
#include "reader.h"

ClassFile * read_class_file();
Constant * read_constant_pool();
Field * read_fields();
Method * read_methods();

#endif