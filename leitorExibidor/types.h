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

typedef struct CONSTANT_Fieldref_info {
  uint8_t tag;
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct CONSTANT_Methodref_info {
  uint8_t tag;
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct CONSTANT_InterfaceMethodref_info {
  uint8_t tag;
  uint16_t class_index;
  uint16_t name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct CONSTANT_NameAndType_info {
  uint8_t tag;
  uint16_t name_index;
  uint16_t descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct CONSTANT_Utf8_info {
  uint8_t tag;
  uint16_t length;
  uint8_t bytes[];
} CONSTANT_Utf8_info;

typedef struct CONSTANT_Integer_info {
  uint8_t tag;
  uint32_t bytes;
} CONSTANT_Integer_info;

typedef struct CONSTANT_String_info {
  uint8_t tag;
  uint16_t string_index;
} CONSTANT_String_info;

typedef struct CONSTANT_Float_info {
  uint8_t tag;
  uint32_t bytes;
} CONSTANT_Float_info;

typedef struct CONSTANT_Long_info {
  uint8_t tag;
  uint32_t high_bytes;
  uint32_t low_bytes;
} CONSTANT_Long_info;

typedef struct CONSTANT_Double_info {
  uint8_t tag;
  uint32_t high_bytes;
  uint32_t low_bytes;
} CONSTANT_Double_info;

typedef union Constant {
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
} Constant;

// Fields types
typedef struct FIELD_Byte {
  uint8_t tag;
  uint8_t value;
} FIELD_Byte;

typedef struct FIELD_Info {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  Attribute * attribute_info;
}

typedef union Field {
  FIELD_Byte byte;
} Field;

// Method types
typedef union Method {
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  Attribute * attribute_info;
} Method;

typedef struct ExceptionTable {
  uint16_t start_pc;
  uint16_t end_pc;
  uint16_t handler_pc;
  uint16_t catch_type;
} ExceptionTable;

typedef struct CodeAttribute {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint16_t max_stack;
  uint16_t max_locals;
  uint32_t code_length;
  uint8_t * code;
  uint16_t exception_table_lenght;
  ExceptionTable * exception_table;
  uint16_t attributes_count;
  Attribute * attribute_info;
} CodeAttribute;

// Attributes types
typedef union Attribute {
  CodeAttribute code_attribute;
  // TODO: add types
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
