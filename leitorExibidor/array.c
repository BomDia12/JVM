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

void free_array(Array * array) {
  free(array->array);
  free(array);
}

void free_array_list(ArrayList * array_list) {
  for (uint32_t i = 0; i < array_list->size; i++) {
    free_array(array_list->array[i]);
  }
  free(array_list->array);
  free(array_list);
}

uint32_t add_array(Array * array) {
  ArrayList * array_list = get_array_list();
  array_list->size++;
  array_list->array = realloc(array_list->array, sizeof(Array *) * array_list->size);
  array_list->array[array_list->size - 1] = array;
  return array_list->size - 1;
}

int new_array(Frame * frame, Instruction instruction) {
  uint32_t size = remove_from_stack(frame);
  Array * array = malloc(sizeof(Array));
  if (instruction.operands[0] == 7 || instruction.operands[0] == 11) {
    array->size = size * 2;
  } else {
    array->size = size;
  }
  array->array = malloc(sizeof(ArrayTypes) * size);
  uint32_t index = add_array(array);
  add_to_stack(frame, index);

  return 0;
}

int anewarray(Frame * frame, Instruction instruction) {
  uint32_t size = remove_from_stack(frame);
  Array * array = malloc(sizeof(Array));
  array->size = size;
  array->array = malloc(sizeof(ArrayTypes) * size);
  uint32_t index = add_array(array);
  add_to_stack(frame, index);
  return 0;
}

int multinewarray(Frame * frame, Instruction instruction) {
  uint8_t dimensions = instruction.operands[2];
  ArrayDimensions array_dimensions = {
    .dimensions = dimensions,
    .sizes = malloc(sizeof(uint32_t) * dimensions)
  };
  for (int i = 0; i >= dimensions; i++) {
    array_dimensions.sizes[i] = remove_from_stack(frame);
  }

  uint32_t index = recursive_new_array(dimensions, &array_dimensions);
  add_to_stack(frame, index);

  return 0;
}

uint32_t recursive_new_array(uint8_t dimensions, ArrayDimensions * array_dimensions) {
  uint32_t size = array_dimensions->sizes[dimensions - 1];

  Array * array = malloc(sizeof(Array));
  array->size = size;
  array->array = malloc(sizeof(ArrayTypes) * size);
  uint32_t index = add_array(array);

  if (dimensions > 1) {
    for (int i = 0; i < size; i++) {
      array->array[i].reference = recursive_new_array(dimensions - 1, array_dimensions);
    }
  }

  return index;
}

int arraylength(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  Array * array = get_array(index);
  add_to_stack(frame, array->size);
  return 0;
}

int iaload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].uint32;
  add_to_stack(frame, value);
  return 0;
}

int laload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint64_t value = array->array[index].long_;
  uint32_t low = (uint32_t) value;
  uint32_t high = (uint32_t) (value >> 32);
  add_to_stack(frame, high);
  add_to_stack(frame, low);
  return 0;
}

int faload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].uint32;
  add_to_stack(frame, value);
  return 0;
}

int daload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  double value = array->array[index].double_;
  uint32_t hi, lo;
  double_to_ints(value, &hi, &lo);
  add_to_stack(frame, hi);
  add_to_stack(frame, lo);
  return 0;
}

int aaload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].reference;
  add_to_stack(frame, value);
  return 0;
}

int baload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].boolean;
  add_to_stack(frame, value);

  return 0;
}

int caload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].char_;
  add_to_stack(frame, value);

  return 0;
}

int saload(Frame * frame, Instruction instruction) {
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  uint32_t value = array->array[index].short_;
  add_to_stack(frame, value);

  return 0;
}

int iastore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].integer = value;

  return 0;
}

int lastore(Frame * frame, Instruction instruction) {
  uint64_t value_hi = remove_from_stack(frame);
  uint64_t value_low = remove_from_stack(frame);
  uint64_t value = value_hi << 32 | value_low;
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].long_ = value;

  return 0;
}

int fastore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].uint32 = value;

  return 0;
}

int dastore(Frame * frame, Instruction instruction) {
  uint64_t value_hi = remove_from_stack(frame);
  uint64_t value_low = remove_from_stack(frame);
  double value = uint64_to_double(value_hi << 32 | value_low);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].double_ = value;

  return 0;
}

int aastore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].reference = value;

  return 0;
}

int bastore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].boolean = value;

  return 0;
}

int castore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].char_ = value;

  return 0;
}

int sastore(Frame * frame, Instruction instruction) {
  uint32_t value = remove_from_stack(frame);
  uint32_t index = remove_from_stack(frame);
  uint32_t arrayref = remove_from_stack(frame);
  Array * array = get_array(arrayref);
  array->array[index].short_ = value;

  return 0;
}
