#ifndef METHOD_H
#define METHOD_H

#include "types.h"
#include "reader.h"

Attribute * read_attribute();

void free_attribute(Attribute * attribute);

#endif