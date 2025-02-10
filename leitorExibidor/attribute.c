#include "attribute.h"

Attribute * read_attribute() {
  Attribute * attribute = malloc(sizeof(Attribute));
  attribute->attribute_name_index = read_u16();
  attribute->attribute_length = read_u32();
  ClassFileList * class_file = get_class_file_list();

  Constant * constant = class_file->buffer[class_file->size - 1]->constant_pool[attribute->attribute_name_index - 1];

  if (constant->tag == 1) {
    const char * string = constant->ConstantUnion.utf8_info.bytes;
    if (strcmp(string, "ConstantValue") == 0){
      attribute->attribute_union.constantvalue_attribute.constantvalue_index = read_u16();
      attribute->attribute_type = 1;
      return attribute;
    }
    else if (strcmp(string, "Code") == 0){
      attribute->attribute_union.code_attribute.max_stack = read_u16();
      attribute->attribute_union.code_attribute.max_locals = read_u16();
      attribute->attribute_union.code_attribute.code_length = read_u32();
      attribute->attribute_union.code_attribute.code = malloc(attribute->attribute_union.code_attribute.code_length * sizeof(uint8_t));

      for (int i = 0; i < attribute->attribute_union.code_attribute.code_length; i++){
        attribute->attribute_union.code_attribute.code[i] = read_u8();
      }

      attribute->attribute_union.code_attribute.exception_table_length = read_u16();
      attribute->attribute_union.code_attribute.exception_table = malloc(attribute->attribute_union.code_attribute.exception_table_length * sizeof(ExceptionTable));
      for (int j = 0; j < attribute->attribute_union.code_attribute.exception_table_length; j++){
        attribute->attribute_union.code_attribute.exception_table[j].start_pc = read_u16();
        attribute->attribute_union.code_attribute.exception_table[j].end_pc = read_u16();
        attribute->attribute_union.code_attribute.exception_table[j].handler_pc = read_u16();
        attribute->attribute_union.code_attribute.exception_table[j].catch_type = read_u16();
      }

      attribute->attribute_union.code_attribute.attributes_count = read_u16();
      attribute->attribute_union.code_attribute.attribute_info = malloc(attribute->attribute_union.code_attribute.attributes_count * sizeof(Attribute *));
      for (int k = 0; k < attribute->attribute_union.code_attribute.attributes_count; k++){
        attribute->attribute_union.code_attribute.attribute_info[k] = read_attribute();
      }
      attribute->attribute_type = 2;
      return attribute;
    }
    else if (strcmp(string, "Exceptions") == 0){
      attribute->attribute_union.exceptions_attribute.number_of_exceptions = read_u16();
      attribute->attribute_union.exceptions_attribute.exception_index_table = malloc(attribute->attribute_union.exceptions_attribute.number_of_exceptions * sizeof(uint16_t));
      for (int i = 0; i < attribute->attribute_union.exceptions_attribute.number_of_exceptions; i++){
        attribute->attribute_union.exceptions_attribute.exception_index_table[i] = read_u16();
      }
      attribute->attribute_type = 3;
      return attribute;
    }
    else if (strcmp(string, "InnerClasses") == 0){
      attribute->attribute_union.innerclasses_attribute.number_of_classes = read_u16();
      attribute->attribute_union.innerclasses_attribute.classes = malloc(attribute->attribute_union.innerclasses_attribute.number_of_classes * sizeof(Classes));
      for (int i = 0; i < attribute->attribute_union.exceptions_attribute.number_of_exceptions; i++){
        attribute->attribute_union.innerclasses_attribute.classes[i].inner_class_info_index = read_u16();
        attribute->attribute_union.innerclasses_attribute.classes[i].outer_class_info_index = read_u16();
        attribute->attribute_union.innerclasses_attribute.classes[i].inner_name_index = read_u16();
        attribute->attribute_union.innerclasses_attribute.classes[i].inner_class_access_flags = read_u16();
      }
      attribute->attribute_type = 4;
      return attribute;
    }
  }

  for (int i = 0; i < attribute->attribute_length; i++){
    read_u8();
  }
  attribute->attribute_type = 0;
  return attribute;
}

void free_attribute(Attribute * attribute) {
  switch (attribute->attribute_type){
    case 1:
      break;
    case 2:
      if (attribute->attribute_union.code_attribute.code != NULL){
        free(attribute->attribute_union.code_attribute.code);
        attribute->attribute_union.code_attribute.code = NULL;
      }
      if (attribute->attribute_union.code_attribute.exception_table != NULL){
        free(attribute->attribute_union.code_attribute.exception_table);
        attribute->attribute_union.code_attribute.exception_table = NULL;
      }
      if (attribute->attribute_union.code_attribute.attribute_info != NULL){
        for (int i = 0; i < attribute->attribute_union.code_attribute.attributes_count; i++){
          free_attribute(attribute->attribute_union.code_attribute.attribute_info[i]);
        }
        free(attribute->attribute_union.code_attribute.attribute_info);
        attribute->attribute_union.code_attribute.attribute_info = NULL;
      }
      break;
    case 3:
      if (attribute->attribute_union.exceptions_attribute.exception_index_table != NULL){
        free(attribute->attribute_union.exceptions_attribute.exception_index_table);
        attribute->attribute_union.exceptions_attribute.exception_index_table = NULL;
      }
      break;
    case 4:
      if (attribute->attribute_union.innerclasses_attribute.classes != NULL){
        free(attribute->attribute_union.innerclasses_attribute.classes);
        attribute->attribute_union.innerclasses_attribute.classes = NULL;
      }
      break;
  }
  free(attribute);
  attribute = NULL;
}
