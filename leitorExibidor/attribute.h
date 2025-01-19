#ifndef METHOD_H
#define METHOD_H

#include "types.h"
#include "reader.h"
#include "header.h"

// Nícolas

Attribute * read_attribute();
Attribute * read_attributes(u2 attributes_count);

void free_attribute(Attribute * attribute);

#endif