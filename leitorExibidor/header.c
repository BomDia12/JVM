#include "header.h"

ClassFile * read_class_file() {
  ClassFile * classFile = malloc(sizeof(ClassFile));
  pushToClassFileList(classFile);

  classFile->magic = read_u32();
  if (classFile->magic != 0xCAFEBABE) {
    fprintf(stderr, "Magic number não bateu: %x\n", classFile->magic);
    free(classFile);
    return NULL;
  }

  classFile->minor_version = read_u16();
  classFile->major_version = read_u16();

  classFile->constant_pool_count = read_u16();
  classFile->constant_pool = malloc(classFile->constant_pool_count * sizeof(Constant *));
  for (uint16_t i = 0; i < (classFile->constant_pool_count - 1); i++) {
    Constant * constant = read_constant();
    classFile->constant_pool[i] = constant;

    if (constant->tag == 5 || constant->tag == 6) {
      i++;
    }
  }

  classFile->access_flags = read_u16();
  classFile->this_class = read_u16();
  classFile->super_class = read_u16();

  classFile->interfaces_count = read_u16();
  classFile->interfaces = malloc(classFile->interfaces_count * sizeof(uint16_t));
  for (uint16_t i = 0; i < classFile->interfaces_count; i++) {
      classFile->interfaces[i] = read_u16();
  }

  classFile->fields_count = read_u16();
  classFile->fields = malloc(classFile->fields_count * sizeof(Field *));
  for (uint16_t i = 0; i < classFile->fields_count; i++) {
    classFile->fields[i] = read_field();
  }

  classFile->methods_count = read_u16();
  classFile->methods = malloc(classFile->methods_count * sizeof(Method *));
  for (uint16_t i = 0; i < classFile->methods_count; i++) {
    classFile->methods[i] = read_method();
  }

  classFile->attributes_count = read_u16();
  classFile->attributes = malloc(classFile->attributes_count * sizeof(Attribute));
  for (int i = 0; i < classFile->attributes_count; i++) {
    classFile->attributes[i] = read_attribute();
  }

  setup_static_fields(classFile);

  return classFile;
}

Constant * read_constant() {
  Constant * constant = malloc(sizeof(Constant));

  constant->tag = read_u8();
  switch (constant->tag) {
    case 7: // class
      constant->ConstantUnion.class_info.name_index = read_u16();
      break;
    case 9: // fieldRef
      constant->ConstantUnion.fieldref_info.class_index = read_u16();
      constant->ConstantUnion.fieldref_info.name_and_type_index = read_u16();
      break;
    case 10: // MethodRef
      constant->ConstantUnion.methodref_info.class_index = read_u16();
      constant->ConstantUnion.methodref_info.name_and_type_index = read_u16();
      break;
    case 11: // InterfaceMethod
      constant->ConstantUnion.interface_methodref_info.class_index = read_u16();
      constant->ConstantUnion.interface_methodref_info.name_and_type_index = read_u16();
      break;
    case 8: // String
      constant->ConstantUnion.string_info.string_index = read_u16();
      break;
    case 3: // Integer
      constant->ConstantUnion.integer_info.bytes = read_u32();
      break;
    case 4: // Float
      constant->ConstantUnion.float_info.bytes = read_u32();
      break;
    case 5: // Long
      constant->ConstantUnion.long_info.high_bytes = read_u32();
      constant->ConstantUnion.long_info.low_bytes = read_u32();
      break;
    case 6: // Double
      constant->ConstantUnion.double_info.high_bytes = read_u32();
      constant->ConstantUnion.double_info.low_bytes = read_u32();
      break;
    case 12: // NameAndType
      constant->ConstantUnion.name_and_type_info.name_index = read_u16();
      constant->ConstantUnion.name_and_type_info.descriptor_index = read_u16();
      break;
    case 1: // utf8
      constant->ConstantUnion.utf8_info.length = read_u16();
      constant->ConstantUnion.utf8_info.bytes = malloc(sizeof(uint8_t) * (constant->ConstantUnion.utf8_info.length + 1));
      for (int j = 0; j < constant->ConstantUnion.utf8_info.length; j++) {
        constant->ConstantUnion.utf8_info.bytes[j] = read_u8();
      }
      constant->ConstantUnion.utf8_info.bytes[constant->ConstantUnion.utf8_info.length] = '\0';
      break;
    case 15: // MethodHandle
      constant->ConstantUnion.method_handle.reference_kind = read_u8();
      constant->ConstantUnion.method_handle.reference_index = read_u16();
      break;
    case 16: // MethodType
      constant->ConstantUnion.method_type.descriptor_index = read_u16();
      break;
    case 18: // InvokeDynamic
      constant->ConstantUnion.invoke_dynamic.bootstrap_method_attr_index = read_u16();
      constant->ConstantUnion.invoke_dynamic.name_and_type_index = read_u16();
      break;
    default:
      fprintf(stderr, "Tag desconhecida: %d\n", constant->tag);
      exit(1);
  }

  return constant;
}

Field * read_field() {
  Field * field = malloc(sizeof(Field));
    field->access_flags = read_u16();
    field->name_index = read_u16();
    field->descriptor_index = read_u16();
    field->attributes_count = read_u16();

    field->attributes = malloc(field->attributes_count * sizeof(Attribute *));
    for (int j = 0; j < field->attributes_count; j++) {
      field->attributes[j] = read_attribute();
    }
  return field;
}

Method * read_method() {
  Method * method = malloc(sizeof(Method));
  method->access_flags = read_u16();
  method->name_index = read_u16();
  method->descriptor_index = read_u16();
  method->attributes_count = read_u16();

  method->attributes = malloc(sizeof(Attribute *) * method->attributes_count);
  for (int j = 0; j < method->attributes_count; j++) {
    method->attributes[j] = read_attribute();
  }

  return method;
}

void free_class_file(ClassFile *class_file) {
  if (!class_file) return;

  for (int i = 0; i < (class_file->constant_pool_count - 1); i++) {
    free_constant(class_file->constant_pool[i]);
  }


  for (int i = 0; i < class_file->fields_count; i++) {
    free_field(class_file->fields[i]);
  }

  for (int i = 0; i < class_file->methods_count; i++) {
    free_method(class_file->methods[i]);
  }

  for (int i = 0; i < class_file->attributes_count; i++) {
    free_attribute(class_file->attributes[i]);
  }

  free(class_file->interfaces);

  free(class_file);
}

void free_constant(Constant * constant) {
  if (!constant) return;

  if (constant->tag == 1) {
    free(constant->ConstantUnion.utf8_info.bytes);
  }

  free(constant);
}

void free_field(Field *fields) {
  if (!fields) return;
  for (int i = 0; i < fields->attributes_count; i++) {
    free_attribute(fields->attributes[i]);
  }

  free(fields);
}

void free_method(Method *method) {
  if (!method) return;
  for (int i = 0; i < method->attributes_count; i++) {
    free_attribute(method->attributes[i]);
  }
  free(method);
}

ClassFileList * get_class_file_list() {
  static ClassFileList class_file = {
    .buffer = NULL,
    .size = 0
  };
  return &class_file;
}

void pushToClassFileList(ClassFile * class_file) {
  ClassFileList * class_file_list = get_class_file_list();
  class_file_list->size++;
  if (class_file_list->buffer == NULL) {
    class_file_list->buffer = malloc(sizeof(ClassFile *) * class_file_list->size);
  } else {
    class_file_list->buffer = realloc(class_file_list->buffer, sizeof(ClassFile *) * class_file_list->size);
  }
  class_file_list->buffer[class_file_list->size - 1] = class_file;
}

Constant * getFromConstantPool(ClassFile * class_file, uint16_t index) {
  return class_file->constant_pool[index - 1];
};

char * getNestedString(ClassFile * class_file, uint16_t index) {
  Constant * info = getFromConstantPool(class_file, index);
  if (info->tag == 1) {
    return info->ConstantUnion.utf8_info.bytes;
  }
  return getNestedString(class_file, info->ConstantUnion.class_info.name_index);
}

Method * get_method(ClassFile * class_file, char * method_name, char * method_descriptor) {
  for (int i = 0; i < class_file->methods_count; i++) {
    Method * method = class_file->methods[i];
    char * name = getNestedString(class_file, method->name_index);
    if (strcmp(method_name, name) == 0) {
      char * descriptor = getNestedString(class_file, method->descriptor_index);
      if (strcmp(method_descriptor, descriptor) == 0) {
        return method;
      }
    }
  }
  return NULL;
}

uint16_t get_argument_amount(char * method_identifier) {
  int amount = 0;
  for (int i = 0; method_identifier[i] != '\0'; i++) {
    if (method_identifier[i] == ')') {
      return amount;
    }
    if (method_identifier[i] == '(') {
      amount = 0;
    }
    if (method_identifier[i] == 'L') {
      while (method_identifier[i] != ';') {
        i++;
      }
    }
    if (method_identifier[i] == '[') {
      while(method_identifier[i] == '[') {
        i++;
      }
      continue;
    }
    if (method_identifier[i] == 'J' || method_identifier[i] == 'D') {
      amount++;
    }
    amount++;
  }
  return amount;
}

void setup_static_fields(ClassFile * class_file) {
  for (int i = 0; i < class_file->fields_count; i++) {
    if (class_file->fields[i]->access_flags & 0x8) {
      class_file->static_fields_count++;
      if (class_file->static_fields == NULL) {
        class_file->static_fields = malloc(sizeof(ActiveField *) * class_file->static_fields_count);
      } else {
        class_file->static_fields = realloc(class_file->static_fields, sizeof(ActiveField *) * class_file->static_fields_count);
      }
      class_file->static_fields[class_file->static_fields_count - 1] = malloc(sizeof(ActiveField));
      class_file->static_fields[class_file->static_fields_count - 1]->field = class_file->fields[i];
      class_file->static_fields[class_file->static_fields_count - 1]->value = 0;
    }
  }
}
