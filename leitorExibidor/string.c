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
  uint32_t size = remove_from_stack(frame);
  String * string = malloc(sizeof(String));
  string->size = size;
  string->string = malloc(sizeof(char) * size);
  uint32_t index = add_string(string);
  add_to_stack(frame, index);

  return 0;
}

int anewstring(Frame * frame, Instruction instruction) {
  uint32_t size = remove_from_stack(frame);
  String * string = malloc(sizeof(String));
  string->size = size;
  string->string = malloc(sizeof(char) * size);
  uint32_t index = add_string(string);
  add_to_stack(frame, index);
  return 0;
}

int stringlength(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  String * string = get_string(index);
  add_to_stack(frame, string->size);
  return 0;
}