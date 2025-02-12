#include "stringBuffer.h"

StringBufferList * get_string_buffer_list() {
  static StringBufferList string_buffer_list;
  return &string_buffer_list;
}

StringBuffer * get_string_buffer(uint32_t index) {
  StringBufferList * string_buffer_list = get_string_buffer_list();
  if (index >= string_buffer_list->size) {
    return NULL;
  }
  return string_buffer_list->buffer[index];
}

void free_string_buffer(StringBuffer * string_buffer) {
  if (string_buffer->string != NULL) {
    free(string_buffer->string);
  }
  if (string_buffer != NULL) {
    free(string_buffer);
  }
}

void free_string_buffer_list(StringBufferList * string_buffer_list) {
  for (uint32_t i = 0; i < string_buffer_list->size; i++) {
    if (string_buffer_list->buffer[i] != NULL) {
      free_string_buffer(string_buffer_list->buffer[i]);
    }
  }
  if (string_buffer_list->buffer != NULL) {
    free(string_buffer_list->buffer);
  }
}

uint32_t add_string_buffer(StringBuffer * string_buffer) {
  StringBufferList * string_buffer_list = get_string_buffer_list();
  string_buffer_list->size++;
  if (string_buffer_list->buffer == NULL) {
    string_buffer_list->buffer = malloc(sizeof(StringBuffer *) * string_buffer_list->size);
  } else {
    string_buffer_list->buffer = realloc(string_buffer_list->buffer, sizeof(StringBuffer *) * string_buffer_list->size);
  }
  string_buffer_list->buffer[string_buffer_list->size - 1] = string_buffer;
  return string_buffer_list->size - 1;
}

int new_string_buffer(Frame * frame, Instruction instruction) {
  StringBuffer * string_buffer = malloc(sizeof(StringBuffer));
  string_buffer->curr_size = 0;
  string_buffer->string = malloc(sizeof(char) * 100);
  uint32_t index = add_string_buffer(string_buffer);
  add_to_stack(frame, index);
  return 0;
}

int append(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  StringBuffer * string_buffer = get_string_buffer(index);
  Object * object = get_object(value);
  String * value_string = get_string(object->fields[0]->value);
  uint32_t old_size = string_buffer->curr_size;
  string_buffer->curr_size += value_string->size;
  for (int i = 0; i < string_buffer->curr_size - old_size; i++) {
    if (value_string->string[i] == '\0') {
      string_buffer->curr_size--;
      i--;
      break;
    }
    string_buffer->string[old_size + i] = value_string->string[i];
  }
  add_to_stack(frame, index);
  return 0;
}

int toString(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  StringBuffer * string_buffer = get_string_buffer(index);
  String * string = malloc(sizeof(String));
  string->size = string_buffer->curr_size;
  string->string = string_buffer->string;

  Object * object = malloc(sizeof(Object));
  object->class = get_string_class_file();
  object->fields = malloc(sizeof(ActiveField *) * 1);
  object->fields[0] = malloc(sizeof(ActiveField));
  object->fields[0]->field = object->class->fields[0];
  object->fields[0]->value = index;

  uint32_t ref = add_object(object);
  add_to_stack(frame, ref);

  return 0;
}
