#include "stackops.h"

int pop(Frame * frame, Instruction Instruction) {
  remove_from_stack(frame);
  return 0;
}

int pop2(Frame * frame, Instruction Instruction) {
  remove_from_stack(frame);
  remove_from_stack(frame);
  return 0;
}

int dup(Frame * frame, Instruction Instruction) {
  uint32_t value = remove_from_stack(frame);
  add_to_stack(frame, value);
  add_to_stack(frame, value);
  return 0;
}

int dup_x1(Frame * frame, Instruction Instruction) {
  uint32_t value1 = remove_from_stack(frame);
  uint32_t value2 = remove_from_stack(frame);
  add_to_stack(frame, value1);
  add_to_stack(frame, value2);
  add_to_stack(frame, value1);
  return 0;
}

int dup_x2(Frame * frame, Instruction Instruction) {
  uint32_t value1 = remove_from_stack(frame);
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value3 = remove_from_stack(frame);
  add_to_stack(frame, value1);
  add_to_stack(frame, value3);
  add_to_stack(frame, value2);
  add_to_stack(frame, value1);
  return 0;
}

int dup2(Frame * frame, Instruction Instruction) {
  uint32_t value1 = remove_from_stack(frame);
  uint32_t value2 = remove_from_stack(frame);
  add_to_stack(frame, value2);
  add_to_stack(frame, value1);
  add_to_stack(frame, value2);
  add_to_stack(frame, value1);
  return 0;
}

int dup2_x1(Frame * frame, Instruction Instruction) {
  uint32_t value1 = remove_from_stack(frame);
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value3 = remove_from_stack(frame);
  add_to_stack(frame, value2);
  add_to_stack(frame, value1);
  add_to_stack(frame, value3);
  add_to_stack(frame, value2);
  add_to_stack(frame, value1);
  return 0;
}

int dup2_x2(Frame * frame, Instruction Instruction) {
  uint32_t value1 = remove_from_stack(frame);
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value3 = remove_from_stack(frame);
  uint32_t value4 = remove_from_stack(frame);
  add_to_stack(frame, value2);
  add_to_stack(frame, value1);
  add_to_stack(frame, value4);
  add_to_stack(frame, value3);
  add_to_stack(frame, value2);
  add_to_stack(frame, value1);
  return 0;
}

int swap(Frame * frame, Instruction Instruction) {
  uint32_t value1 = remove_from_stack(frame);
  uint32_t value2 = remove_from_stack(frame);
  add_to_stack(frame, value2);
  add_to_stack(frame, value1);
  return 0;
}

int lcmp(Frame * frame, Instruction Instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  if (uint64_to_long(value1) > uint64_to_long(value2)) {
    add_to_stack(frame, int_to_uint32(1));
  }
  else if (uint64_to_long(value1) == uint64_to_long(value2)) {
    add_to_stack(frame, int_to_uint32(0));
  }
  else if (uint64_to_long(value1) < uint64_to_long(value2)) {
    add_to_stack(frame, int_to_uint32(-1));
  }
  return 0;
}

int fcmp(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  if (uint32_to_float(value1) > uint32_to_float(value2)) {
    add_to_stack(frame, int_to_uint32(1));
  }
  else if (uint32_to_float(value1) == uint32_to_float(value2)) {
    add_to_stack(frame, int_to_uint32(0));
  }
  else if (uint32_to_float(value1) < uint32_to_float(value2)) {
    add_to_stack(frame, int_to_uint32(-1));
  }
  return 0;
}

int dcmp(Frame * frame, Instruction Instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  if (uint64_to_double(value1) > uint64_to_double(value2)) {
    add_to_stack(frame, int_to_uint32(1));
  }
  else if (uint64_to_double(value1) == uint64_to_double(value2)) {
    add_to_stack(frame, int_to_uint32(0));
  }
  else if (uint64_to_double(value1) < uint64_to_double(value2)) {
    add_to_stack(frame, int_to_uint32(-1));
  }
  return 0;
}

int bipush(Frame * frame, Instruction Instruction) {
  uint8_t byte = Instruction.operands[0];
  int8_t bytei = uint8_to_byte(byte);
  int32_t result = (int32_t) bytei;
  add_to_stack(frame, int_to_uint32(result));
  return 0;
}

int sipush(Frame * frame, Instruction Instruction) {
  uint16_t byte1 = Instruction.operands[0];
  uint16_t byte2 = Instruction.operands[1];
  uint16_t bytes = byte1 << 8;
  bytes |= byte2;
  int16_t bytes16 = uint16_to_short(bytes);
  int32_t result = (int32_t) bytes16;
  add_to_stack(frame, int_to_uint32(result));
  return 0;
}