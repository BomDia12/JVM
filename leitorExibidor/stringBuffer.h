#ifndef STRING_BUFFER_H
#define STRING_BUFFER_H

#include <stdint.h>
#include <stdlib.h>
#include "types.h"
#include "string.h"
#include "object.h"

StringBufferList * get_string_buffer_list();
StringBuffer * get_string_buffer(uint32_t index);
void free_string_buffer(StringBuffer * string_buffer);
void free_string_buffer_list(StringBufferList * string_buffer_list);
uint32_t add_string_buffer(StringBuffer * string_buffer);
int new_string_buffer(Frame * frame, Instruction instruction);
int append(Frame * frame, Instruction instruction);
int toString(Frame * frame, Instruction instruction);

#endif
