#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

typedef struct Buffer {
  uint8_t * buffer;
  uint64_t position;
} Buffer;

// Constant Pool types
typedef struct CONSTANT_Class_info {
  uint8_t tag;
  uint16_t name_index;
} CONSTANT_Class_info;

typedef union Constant {
  CONSTANT_Class_info class_info;
  // TODO: add other types
} Constant;

// Fields types
typedef struct FIELD_Byte {
  uint8_t tag;
  uint8_t value;
} FIELD_Byte;

typedef union Field {
  FIELD_Byte byte;
  // TODO: add other types
} Field;

// Method types
typedef union Method {
  // TODO: add types
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
  Attribute * attribute_info;
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
// 2 - 
// 3 - 
// 4 - 
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
