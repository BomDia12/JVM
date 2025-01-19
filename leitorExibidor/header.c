#include "header.h"

ClassFile * read_class_file() {
  // Aqui é só você ler os cabeçalhos do arquivo .class, na ordem dos slides
  ClassFile * class_file = get_current_class_file();
  class_file = malloc(sizeof(ClassFile));
  return class_file;
}

Constant * read_constant_pool() {
  // Aqui é só você ler o pool de constantes, lembrando que cada constante pode ser um tipo diferente, com tamanhos diferentes
  return NULL;
}

Field * read_fields() {
  // Aqui é só você ler os campos da classe, sendo que cada um tem tamanhos diferentes
  return NULL;
}

Method * read_methods() {
  // Aqui é só você ler as métodos, o método tem dentro de si 
  return NULL;
}

void free_class_file(ClassFile * class_file) {
  free_constant_pool(class_file->constant_pool);
  free_fields(class_file->fields);
  free_methods(class_file->methods);
  free_attribute(class_file->attributes);

  free(class_file);
  class_file = NULL;
}

void free_constant_pool(Constant * constant_pool) {
  free(constant_pool);
  constant_pool = NULL;
}

void free_fields(Field * fields) {
  // TODO free atributes of fields
  free(fields);
  fields = NULL;
}

void free_methods(Method * methods) {
  // TODO free atributes of methods
  free(methods);
  methods = NULL;
}

ClassFile * get_current_class_file() {
  static ClassFile class_file;
  return &class_file;
}