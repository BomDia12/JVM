#include "array.h"

ArrayList * get_array_list() {
  static ArrayList array_list;
  return &array_list;
}

Array * get_array(uint32_t index) {
  ArrayList * array_list = get_array_list();
  if (index >= array_list->size) {
    return NULL;
  }
  return array_list->array[index];
}

uint32_t add_array(Array * array) {
  ArrayList * array_list = get_array_list();
  array_list->size++;
  array_list->array = realloc(array_list->array, sizeof(Array *) * array_list->size);
  array_list->array[array_list->size - 1] = array;
  return array_list->size - 1;
}

void new_array(Frame * frame, Instruction instruction) {
  uint32_t size = remove_from_stack(frame);
  Array * array = malloc(sizeof(Array));
  array->size = size;
  array->array = malloc(sizeof(ArrayTypes) * size);
  uint32_t index = add_array(array);
  add_to_stack(frame, index);
}

void anewarray(Frame * frame, Instruction instruction) {
  uint32_t size = remove_from_stack(frame);
  Array * array = malloc(sizeof(Array));
  array->size = size;
  array->array = malloc(sizeof(ArrayTypes) * size);
  uint32_t index = add_array(array);
  add_to_stack(frame, index);
}

void arraylength(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  Array * array = get_array(index);
  add_to_stack(frame, array->size);
}

void iaload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  int value = array->array[index].integer;
  add_to_stack(frame, value);
}
