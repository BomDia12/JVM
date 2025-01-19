#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef struct Buffer {
  uint8_t * buffer;
  uint64_t position;
} Buffer;

// Constant Pool types
typedef struct CONSTANT_Class_info {
  uint16_t name_index;
} CONSTANT_Class_info;

typedef struct CONSTANT_Fieldref_info {
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct CONSTANT_Methodref_info {
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct CONSTANT_InterfaceMethodref_info {
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct CONSTANT_NameAndType_info {
  uint16_t name_index;
  uint16_t descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct CONSTANT_Utf8_info {
  uint16_t length;
  uint8_t bytes[];
} CONSTANT_Utf8_info;

typedef struct CONSTANT_Integer_info {
  uint32_t bytes;
} CONSTANT_Integer_info;

typedef struct CONSTANT_String_info {
  uint16_t string_index;
} CONSTANT_String_info;

typedef struct CONSTANT_Float_info {
  uint32_t bytes;
} CONSTANT_Float_info;

typedef struct CONSTANT_Long_info {
  uint32_t high_bytes;
  uint32_t low_bytes;
} CONSTANT_Long_info;

typedef struct CONSTANT_Double_info {
  uint32_t high_bytes;
  uint32_t low_bytes;
} CONSTANT_Double_info;

typedef union ConstantUnion {
  CONSTANT_Class_info class_info;
  CONSTANT_Fieldref_info fieldref_info;
  CONSTANT_Methodref_info methodref_info;
  CONSTANT_InterfaceMethodref_info interface_methodref_info;
  CONSTANT_NameAndType_info name_and_type_info;
  CONSTANT_Utf8_info utf8_info;
  CONSTANT_Integer_info integer_info;
  CONSTANT_String_info string_info;
  CONSTANT_Float_info float_info;
  CONSTANT_Long_info long_info;
  CONSTANT_Double_info double_info;
} ConstantUnion;

typedef struct Constant {
  uint8_t tag;
  ConstantUnion ConstantUnion;
} Constant;

// Fields types
typedef struct FIELD_Byte {
  uint8_t value;
} FIELD_Byte;

typedef struct FIELD_Info {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  // Attribute * attribute_info;
} FIELD_Info;

typedef union FieldUnion {
  FIELD_Byte byte;
  FIELD_Info info;
} FieldUnion;

typedef struct Field {
  uint8_t tag;
  FieldUnion FieldUnion;
} Field;

// Method types
typedef union Method {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  // Attribute * attribute_info;
} Method;

typedef struct ExceptionTable {
  uint16_t start_pc;
  uint16_t end_pc;
  uint16_t handler_pc;
  uint16_t catch_type;
} ExceptionTable;

typedef struct CodeAttribute {
  uint16_t max_stack;
  uint16_t max_locals;
  uint32_t code_length;
  uint8_t * code;
  uint16_t exception_table_lenght;
  ExceptionTable * exception_table;
  uint16_t attributes_count;
  // list of all the attributes;
  Attribute * * attribute_info;
} CodeAttribute;

typedef struct ConstantValueAttribute {
  uint16_t constantvalue_index;
} ConstantValueAttribute;

typedef struct ExceptionsAttribute {
  uint16_t number_of_exceptions;
  uint16_t * exception_index_table;
} ExceptionsAttribute;

typedef struct Classes {
  uint16_t inner_class_info_index;
  uint16_t outer_class_info_index;
  uint16_t inner_name_index;
  uint16_t inner_class_access_flags;
} Classes;

typedef struct InnerClassesAttribute {
  uint16_t number_of_classes;
  Classes * classes;
} InnerClassesAttribute;

// Attributes types
typedef union AttributeUnion {
  CodeAttribute code_attribute;
  ConstantValueAttribute constantvalue_attribute;
  ExceptionsAttribute exceptions_attribute;
  InnerClassesAttribute innerclasses_attribute;
} AttributeUnion;

// 1 - ConstantValue
// 2 - Code
// 3 - Exceptions
// 4 - InnerClasses
// 0 - Não implementado
typedef struct Attribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint8_t attribute_type;
  AttributeUnion attribute_union;
} Attribute;

// ClassFile types
typedef struct ClassFile {
  uint32_t magic;
  uint16_t minor_version;
  uint16_t major_version;
  uint16_t constant_pool_count;
  Constant * constant_pool;
  uint16_t access_flags;
  uint16_t this_class;
  uint16_t super_class;
  uint16_t interfaces_count;
  uint16_t * interfaces;
  uint16_t fields_count;
  Field * fields;
  uint16_t methods_count;
  Method * methods;
  uint16_t attributes_count;
  Attribute * attributes;
} ClassFile;

// Bytecode types
typedef struct InstructionType {
  uint8_t opcode;
  uint8_t operand_count;
  char * mnemonic;
} InstructionType;

typedef struct Instruction {
  uint8_t opcode;
  uint8_t operand_count;
  uint32_t * operands;
  char * mnemonic;
} Instruction;

#endif
