#include "attribute.h"

Attribute * read_attribute() {
  // Aqui você tem que ler o attribute info e depois lidar com ele dependendo do tipo
  return NULL;
}

void free_attribute(Attribute * attribute) {
  // TODO tratar quando o atributo é um atributo code
  free(attribute);
  attribute = NULL;
}
