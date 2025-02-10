#include "object.h"

ObjectList * get_object_list() {
  static ObjectList object_list;
  return &object_list;
}

Object * get_object(uint32_t index) {
  ObjectList * object_list = get_object_list();
  if (index >= object_list->size) {
    return NULL;
  }
  return object_list->object[index];
}

uint32_t add_object(Object * object) {
  ObjectList * object_list = get_object_list();
  object_list->size++;
  if (object_list->object == NULL) {
    object_list->object = malloc(sizeof(Object *) * object_list->size);
  } else {
    object_list->object = realloc(object_list->object, sizeof(Object *) * object_list->size);
  }
  object_list->object[object_list->size - 1] = object;
  return object_list->size - 1;
}

void free_object(Object * object) {
  free(object->fields);
  free(object);
}

void free_object_list(ObjectList * object_list) {
  for (uint32_t i = 0; i < object_list->size; i++) {
    free_object(object_list->object[i]);
  }
  free(object_list->object);
  free(object_list);
}

int new_(Frame * frame, Instruction instruction) {
  uint16_t index = (((uint16_t) instruction.operands[0]) << 8) | instruction.operands[1];
  char * class_name = getNestedString(frame->this_class, index);
  if (strcmp(class_name, "java/lang/String") == 0) {
    return 0;
  }

  ClassFile * class_file = get_class_file(class_name);
  if (class_file == NULL) {
    return -3;
  }
  Object * object = malloc(sizeof(Object));
  object->class = class_file;
  object->fields = malloc(sizeof(ActiveField **) * (class_file->fields_count - class_file->static_fields_count));
  for (int i = 0; i < class_file->fields_count; i++) {
    if (class_file->fields[i]->access_flags & 0x8) {
      continue;
    }
    object->fields[i] = malloc(sizeof(ActiveField));
    object->fields[i]->field = class_file->fields[i];
    object->fields[i]->value = 0;
  }

  uint32_t ref = add_object(object);
  add_to_stack(frame, ref);

  return 0;
}

ActiveField * get_static_field(ClassFile * class_file, char * field_name, char * field_descriptor) {
  for (int i = 0; i < class_file->static_fields_count; i++) {
    char * name = getNestedString(class_file, class_file->static_fields[i]->field->name_index);
    if (strcmp(name, field_name) == 0) {
      char * descriptor = getNestedString(class_file, class_file->static_fields[i]->field->descriptor_index);
      if (strcmp(descriptor, field_descriptor) == 0) {
        return class_file->static_fields[i];
      }
    }
  }

  return NULL;
}

int getstatic(Frame * frame, Instruction instruction) {
  uint16_t index = (((uint16_t) instruction.operands[0]) << 8) | instruction.operands[1];
  Constant * fieldref = getFromConstantPool(frame->this_class, index);
  char * class_name = getNestedString(frame->this_class, fieldref->ConstantUnion.fieldref_info.class_index);
  if (strcmp(class_name, "java/lang/System") == 0 || strcmp(class_name, "java/lang/String") == 0) {
    return 0;
  }

  ClassFile * class_file = get_class_file(class_name);

  if (class_file == NULL) {
    return -3;
  }

  fieldref = getFromConstantPool(frame->this_class, fieldref->ConstantUnion.fieldref_info.name_and_type_index);
  char * field_name = getNestedString(frame->this_class, fieldref->ConstantUnion.name_and_type_info.name_index);
  char * field_descriptor = getNestedString(frame->this_class, fieldref->ConstantUnion.name_and_type_info.descriptor_index);

  ActiveField * field = get_static_field(class_file, field_name, field_descriptor);
  if (field == NULL) {
    return -4;
  }

  if (field_descriptor[0] == 'J' || field_descriptor[0] == 'D') {
    add_to_stack(frame, field->extra);
  }
  add_to_stack(frame, field->value);

  return 0;
}

int putstatic(Frame * frame, Instruction instruction) {
  uint16_t index = (((uint16_t) instruction.operands[0]) << 8) | instruction.operands[1];
  Constant * fieldref = getFromConstantPool(frame->this_class, index);
  char * class_name = getNestedString(frame->this_class, fieldref->ConstantUnion.fieldref_info.class_index);
  ClassFile * class_file = get_class_file(class_name);

  if (class_file == NULL) {
    return -3;
  }

  fieldref = getFromConstantPool(frame->this_class, fieldref->ConstantUnion.fieldref_info.name_and_type_index);
  char * field_name = getNestedString(frame->this_class, fieldref->ConstantUnion.name_and_type_info.name_index);
  char * field_descriptor = getNestedString(frame->this_class, fieldref->ConstantUnion.name_and_type_info.descriptor_index);

  ActiveField * field = get_static_field(class_file, field_name, field_descriptor);
  if (field == NULL) {
    return -4;
  }

  field->value = remove_from_stack(frame);
  if (field_descriptor[0] == 'J' || field_descriptor[0] == 'D') {
    field->extra = remove_from_stack(frame);
  }

  return 0;
}

ActiveField * get_field(Object * object, char * field_name, char * field_descriptor) {
  for (int i = 0; i < object->class->fields_count; i++) {
    char * name = getNestedString(object->class, object->fields[i]->field->name_index);
    if (strcmp(name, field_name) == 0) {
      char * descriptor = getNestedString(object->class, object->fields[i]->field->descriptor_index);
      if (strcmp(descriptor, field_descriptor) == 0) {
        return object->fields[i];
      }
    }
  }

  return NULL;
}

int putfield(Frame * frame, Instruction instruction) {
  uint16_t index = (((uint16_t) instruction.operands[0]) << 8) | instruction.operands[1];
  Constant * fieldref = getFromConstantPool(frame->this_class, index);

  fieldref = getFromConstantPool(frame->this_class, fieldref->ConstantUnion.fieldref_info.name_and_type_index);
  char * field_name = getNestedString(frame->this_class, fieldref->ConstantUnion.name_and_type_info.name_index);
  char * field_descriptor = getNestedString(frame->this_class, fieldref->ConstantUnion.name_and_type_info.descriptor_index);
  int high = remove_from_stack(frame);
  int low;
  if (field_descriptor[0] == 'J' || field_descriptor[0] == 'D') {
    low = remove_from_stack(frame);
  }

  Object * object = get_object(remove_from_stack(frame));
  ActiveField * field = get_field(object, field_name, field_descriptor);
  if (field == NULL) {
    return -4;
  }

  if (field_descriptor[0] == 'J' || field_descriptor[0] == 'D') {
    field->extra = low;
  }
  field->value = high;

  return 0;
}

int getfield(Frame * frame, Instruction instruction) {
  uint16_t index = (((uint16_t) instruction.operands[0]) << 8) | instruction.operands[1];
  Constant * fieldref = getFromConstantPool(frame->this_class, index);

  fieldref = getFromConstantPool(frame->this_class, fieldref->ConstantUnion.fieldref_info.name_and_type_index);
  char * field_name = getNestedString(frame->this_class, fieldref->ConstantUnion.name_and_type_info.name_index);
  char * field_descriptor = getNestedString(frame->this_class, fieldref->ConstantUnion.name_and_type_info.descriptor_index);

  Object * object = get_object(remove_from_stack(frame));
  ActiveField * field = get_field(object, field_name, field_descriptor);
  if (field == NULL) {
    return -4;
  }

  if (field_descriptor[0] == 'J' || field_descriptor[0] == 'D') {
    add_to_stack(frame, field->extra);
  }
  add_to_stack(frame, field->value);

  return 0;
}
