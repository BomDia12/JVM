#include "header.h"

ClassFile * read_class_file() {
  ClassFile * classFile = malloc(sizeof(ClassFile));
  ClassFile * singleton = get_current_class_file();
  singleton = classFile;

  classFile->magic = read_u32();
  if (classFile->magic != 0xCAFEBABE) {
    fprintf(stderr, "Magic number não bateu: %x\n", classFile->magic);
    free(classFile);
    return NULL;
  }

  classFile->minor_version = read_u16();
  classFile->major_version = read_u16();

  classFile->constant_pool_count = read_u16();
  classFile->constant_pool = read_constant_pool(classFile->constant_pool_count);

  classFile->access_flags = read_u16();
  classFile->this_class = read_u16();
  classFile->super_class = read_u16();

  classFile->interfaces_count = read_u16();
  classFile->interfaces = malloc(classFile->interfaces_count * sizeof(uint16_t));
  for (uint16_t i = 0; i < classFile->interfaces_count; i++) {
      classFile->interfaces[i] = read_u16();
  }

  classFile->fields_count = read_u16();
  classFile->fields = read_fields(classFile->fields_count);

  classFile->methods_count = read_u16();
  classFile->methods = read_methods(classFile->methods_count);

  classFile->attributes_count = read_u16();
  classFile->attributes = malloc(classFile->attributes_count * sizeof(Attribute));
  for (int i = 0; i < classFile->attributes_count; i++) {
    classFile->attributes[i] = read_attribute();
  }

  return classFile;
}

Constant * read_constant_pool(uint16_t constant_pool_count) {
  Constant * constant_pool = malloc(constant_pool_count * sizeof(Constant));

  for (uint16_t i = 1; i < constant_pool_count; i++) {
    constant_pool[i].tag = read_u8();
    switch (constant_pool[i].tag) {
      case 7: // class
        constant_pool[i].ConstantUnion.class_info.name_index = read_u16();
        break;
      case 9: // fieldRef
        constant_pool[i].ConstantUnion.fieldref_info.class_index = read_u16();
        constant_pool[i].ConstantUnion.fieldref_info.name_and_type_index = read_u16();
        break;
      case 10: // MethodRef
        constant_pool[i].ConstantUnion.methodref_info.class_index = read_u16();
        constant_pool[i].ConstantUnion.methodref_info.name_and_type_index = read_u16();
        break;
      case 11: // InterfaceMethod
        constant_pool[i].ConstantUnion.interface_methodref_info.class_index = read_u16();
        constant_pool[i].ConstantUnion.interface_methodref_info.name_and_type_index = read_u16();
        break;
      case 8: // String
        constant_pool[i].ConstantUnion.string_info.string_index = read_u16();
        break;
      case 3: // Integer
        constant_pool[i].ConstantUnion.integer_info.bytes = read_u32();
        break;
      case 4: // Float
        constant_pool[i].ConstantUnion.float_info.bytes = read_u32();
        break;
      case 5: // Long
        constant_pool[i].ConstantUnion.long_info.high_bytes = read_u32();
        constant_pool[i].ConstantUnion.long_info.low_bytes = read_u32();
        break;
      case 6: // Double
        constant_pool[i].ConstantUnion.double_info.high_bytes = read_u32();
        constant_pool[i].ConstantUnion.double_info.low_bytes = read_u32();
        break;
      case 12: // NameAndType
        constant_pool[i].ConstantUnion.name_and_type_info.name_index = read_u16();
        constant_pool[i].ConstantUnion.name_and_type_info.descriptor_index = read_u16();
        break;
      case 1: // utf8
        constant_pool[i].ConstantUnion.utf8_info.length = read_u16();
        constant_pool[i].ConstantUnion.utf8_info.bytes = malloc(sizeof(uint8_t) * constant_pool[i].ConstantUnion.utf8_info.length);
        for (int i = 0; i < constant_pool[i].ConstantUnion.utf8_info.length; i++) {
          constant_pool[i].ConstantUnion.utf8_info.bytes[i] = read_u8();
        }
        break;
      case 15: // MethodHandle
        constant_pool[i].ConstantUnion.method_handle.reference_kind = read_u8();
        constant_pool[i].ConstantUnion.method_handle.reference_index = read_u16();
        break;
      case 16: // MethodType
        constant_pool[i].ConstantUnion.method_type.descriptor_index = read_u16();
        break;
      case 18: // InvokeDynamic
        constant_pool[i].ConstantUnion.invoke_dynamic.bootstrap_method_attr_index = read_u16();
        constant_pool[i].ConstantUnion.invoke_dynamic.name_and_type_index = read_u16();
        break;
      default:
        fprintf(stderr, "Tag desconhecida: %d\n", constant_pool[i].tag);
        exit(1);
    }
  }
  return constant_pool;
}

Field * read_fields(uint16_t fields_count) {
  Field * fields = malloc(fields_count * sizeof(Field));
  for (uint16_t i = 0; i < fields_count; i++) {
    fields[i].access_flags = read_u16();
    fields[i].name_index = read_u16();
    fields[i].descriptor_index = read_u16();
    fields[i].attributes_count = read_u16();

    fields[i].attributes = malloc(fields[i].attributes_count * sizeof(Attribute *));
    for (int j = 0; j < fields[i].attributes_count; j++) {
      fields[i].attributes[j] = read_attribute();
    }
  }
  return fields;
}

Method * read_methods(uint16_t methods_count) {
  Method * methods = malloc(methods_count * sizeof(Method));
  for (uint16_t i = 0; i < methods_count; i++) {
    methods[i].access_flags = read_u16();
    methods[i].name_index = read_u16();
    methods[i].descriptor_index = read_u16();
    methods[i].attributes_count = read_u16();

    methods[i].attributes = malloc(methods[i].attributes_count * sizeof(Attribute));
    for (int j = 0; j < methods[i].attributes_count; j++) {
      methods[i].attributes[j] = read_attribute();
    }
  }
  return methods;
}

void free_class_file(ClassFile *class_file) {
  if (!class_file) return;

  free_constant_pool(class_file->constant_pool, class_file->constant_pool_count);
  free_fields(class_file->fields, class_file->fields_count);
  free_methods(class_file->methods, class_file->methods_count);
  for (int i = 0; i < class_file->attributes_count; i++) {
    free_attribute(class_file->attributes[i]);
  }

  free(class_file->interfaces);

  free(class_file);
}

void free_constant_pool(Constant * constant_pool, uint16_t constant_pool_count) {
  if (!constant_pool) return;
  for (int i = 0; i < constant_pool_count; i++) {
    if (constant_pool[i].tag == 1) {
      free(constant_pool[i].ConstantUnion.utf8_info.bytes);
    }
  }

  free(constant_pool);
}

void free_fields(Field *fields, uint16_t fields_count) {
  if (!fields) return;
  for (int i = 0; i < fields_count; i++) {
    free_attributes(fields[i].attributes);
  }

  free(fields);
}

void free_methods(Method *methods, uint16_t methods_count) {
  if (!methods) return;
  for (int i = 0; i < methods_count; i++) {
    free_attributes(methods[i].attributes);
  }
  free(methods);
}

ClassFile * get_current_class_file() {
  static ClassFile class_file;
  return &class_file;
}