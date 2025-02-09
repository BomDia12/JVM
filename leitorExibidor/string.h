#ifndef STRING_H
#define STRING_H

#include "types.h"

StringList * get_string_list();
String * get_string(uint32_t index);
uint32_t add_string(String * string);

void free_string(String * string);
void free_string_list(StringList * string_list);

int new_string(Frame * frame, Instruction instruction);
int anewstring(Frame * frame, Instruction instruction);
int stringlength(Frame * frame, Instruction instruction);

#endif