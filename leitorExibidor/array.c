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
  uint32_t value = array->array[index].uint32;
  add_to_stack(frame, value);
}

void laload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint64_t value = array->array[index].long_;
  uint32_t low = (uint32_t) value;
  uint32_t high = (uint32_t) (value >> 32);
  add_to_stack(frame, high);
  add_to_stack(frame, low);
}

void faload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].uint32;
  add_to_stack(frame, value);
}

void daload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  double value = array->array[index].double_;
  uint32_t hi, lo;
  double_to_ints(value, &hi, &lo);
  add_to_stack(frame, hi);
  add_to_stack(frame, lo);
}

void aaload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].reference;
  add_to_stack(frame, value);
}

void baload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].boolean;
  add_to_stack(frame, value);
}

void caload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].char_;
  add_to_stack(frame, value);
}

void saload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].short_;
  add_to_stack(frame, value);
}

void iastore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].integer = value;
}

void lastore(Frame * frame, Instruction instruction) {
  uint32_t value_hi = remove_from_stack(frame);
  uint32_t value_low = remove_from_stack(frame);
  uint64_t value = value_hi << 32 | value_low;
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].long_ = value;
}

void fastore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].uint32 = value;
}

void dastore(Frame * frame, Instruction instruction) {
  uint32_t value_hi = remove_from_stack(frame);
  uint32_t value_low = remove_from_stack(frame);
  double value = uint64_to_double(value_hi << 32 | value_low);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].double_ = value;
}

void aastore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].reference = value;
}

void bastore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].boolean = value;
}

void castore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].char_ = value;
}

void sastore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].short_ = value;
}
