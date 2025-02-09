#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"
#include "instructions.h"
#include "array.h"
#include <stdlib.h>

ObjectList * get_object_list();
Object * get_object(uint32_t index);
uint32_t add_object(Object * object);
ClassFile * get_class_file(char * class_name);

void free_object(Object * object);
void free_object_list(ObjectList * object_list);

int new_(Frame * frame, Instruction instruction);
int getfield(Frame * frame, Instruction instruction);
int putfield(Frame * frame, Instruction instruction);
int getstatic(Frame * frame, Instruction instruction);
int putstatic(Frame * frame, Instruction instruction);

ActiveField * get_static_field(ClassFile * class_file, char * field_name, char * field_descriptor);
ActiveField * get_field(Object * object, char * field_name, char * field_descriptor);

#endif
