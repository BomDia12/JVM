#include "attribute.h"

Attribute * read_attribute() {
  Attribute * attribute = malloc(sizeof(Attribute));
  attribute->attribute_name_index = read_u16();
  attribute->attribute_length = read_u32();
  ClassFile * class_file = get_current_class_file();

  Constant * constant = &class_file->constant_pool[attribute->attribute_name_index];

  
  return NULL;
}

void free_attribute(Attribute * attribute) {
  // TODO tratar quando o atributo é um atributo code
  free(attribute);
  attribute = NULL;
}
