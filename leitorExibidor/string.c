#include "string.h"

StringList * get_string_list() {
  static StringList string_list;
  return &string_list;
}

String * get_string(uint32_t index) {
  StringList * string_list = get_string_list();
  if (index >= string_list->size) {
    return NULL;
  }
  return string_list->string[index];
}

uint32_t add_string(String * string) {
  StringList * string_list = get_string_list();
  string_list->size++;
  if (string_list->string == NULL) {
    string_list->string = malloc(sizeof(String *) * string_list->size);
  } else {
    string_list->string = realloc(string_list->string, sizeof(String *) * string_list->size);
  }
  string_list->string[string_list->size - 1] = string;
  return string_list->size - 1;
}

void free_string(String * string) {
  free(string->string);
  free(string);
}

void free_string_list(StringList * string_list) {
  for (uint32_t i = 0; i < string_list->size; i++) {
    free_string(string_list->string[i]);
  }
  free(string_list->string);
  free(string_list);
}

int new_string(Frame * frame, Instruction instruction) {
  String * string = malloc(sizeof(String));
  string->size = 0;
  string->string = NULL;
  uint32_t index = add_string(string);

  Object * object = malloc(sizeof(Object));
  object->class = get_string_class_file();
  object->fields = malloc(sizeof(ActiveField *) * 1);
  object->fields[0] = malloc(sizeof(ActiveField));
  object->fields[0]->field = object->class->fields[0];
  object->fields[0]->value = index;

  uint32_t ref = add_object(object);
  add_to_stack(frame, ref);

  return 0;
}

int stringlength(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  Object * object = get_object(index);
  if (object == NULL) {
    add_to_stack(frame, 0);
    return 0;
  }
  String * string = get_string(object->fields[0]->value);
  return 0;
}

ClassFile * get_string_class_file() {
  const Constant class_name = {
    .tag = 1,
    .ConstantUnion = {
      .utf8_info = {
        .length = 16,
        .bytes = "java/lang/String"
      }
    }
  };
  const Constant class_index = {
    .tag = 7,
    .ConstantUnion = {
      .class_info = {
        .name_index = 2,
      }
    }
  };
  const Constant field_name = {
    .tag = 1,
    .ConstantUnion = {
      .utf8_info = {
        .length = 3,
        .bytes = "ref"
      }
    }
  };

  const Constant pool [] = {
    class_index,
    class_name,
    field_name,
  };

  const Field field = {
    .access_flags = 0x0000,
    .name_index = 2,
    .descriptor_index = 0,
    .attributes_count = 0,
    .attributes = NULL,
  };
  const Field fields [] = {field};
  const ClassFile class_file = {
    .magic = 0xCAFEBABE,
    .minor_version = 0,
    .major_version = 0,
    .constant_pool_count = 3,
    .constant_pool = pool,
    .access_flags = 0x0000,
    .this_class = 1,
    .super_class = 0,
    .interfaces_count = 0,
    .interfaces = NULL,
    .fields_count = 1,
    .fields = fields,
    .methods_count = 0,
    .methods = NULL,
    .attributes_count = 0,
    .attributes = NULL,
    .super_class_object = NULL,
    .static_fields_count = 0,
  };
  return &class_file;
}
