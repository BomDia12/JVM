#include "arithmetic.h"

int iadd(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) + uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int isub(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) - uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int imul(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) * uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int idiv(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) / uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int irem(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) % uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int ineg(Frame * frame, Instruction Instruction) {
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = - uint32_to_int(value1);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int ishl(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) << (uint32_to_int(value2) & 0x1f);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int ishr(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) >> (uint32_to_int(value2) & 0x1f);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int iushr(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  uint32_t result = value1 >> (uint32_to_int(value2) & 0x1f);
  add_to_stack(frame, result);

  return 0;
}

int iand(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) & uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int ior(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) | uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int ixor(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) ^ uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));

  return 0;
}

int iinc(Frame * frame, Instruction Instruction) {
  uint8_t index = Instruction.operands[0];
  uint8_t consti = Instruction.operands[1];
  frame->local_variables[index] += consti;

  return 0;
}

int ladd(Frame * frame, Instruction Instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = uint64_to_long(value1) + uint64_to_long(value2);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lsub(Frame * frame, Instruction Instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = uint64_to_long(value1) - uint64_to_long(value2);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lmul(Frame * frame, Instruction Instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = uint64_to_long(value1) * uint64_to_long(value2);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int ldiv_(Frame * frame, Instruction Instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = uint64_to_long(value1) / uint64_to_long(value2);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lrem(Frame * frame, Instruction Instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = uint64_to_long(value1) % uint64_to_long(value2);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lneg(Frame * frame, Instruction Instruction) {
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = - uint64_to_long(value1);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lshl(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = uint64_to_long(value1) << (uint32_to_int(value2) & 0x3f);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lshr(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = uint64_to_long(value1) >> (uint32_to_int(value2) & 0x3f);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lushr(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  uint64_t result = value1 >> (uint32_to_int(value2) & 0x3f);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int land(Frame * frame, Instruction Instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = uint64_to_long(value1) & uint64_to_long(value2);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lor(Frame * frame, Instruction Instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = uint64_to_long(value1) | uint64_to_long(value2);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int lxor(Frame * frame, Instruction Instruction) {
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  int64_t resultl = uint64_to_long(value1) ^ uint64_to_long(value2);
  uint64_t result = long_to_uint64(resultl);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int fadd(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  float result = uint32_to_float(value1) + uint32_to_float(value2);
  add_to_stack(frame, float_to_uint32(result));

  return 0;
}

int fsub(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  float result = uint32_to_float(value1) - uint32_to_float(value2);
  add_to_stack(frame, float_to_uint32(result));

  return 0;
}

int fmul(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  float result = uint32_to_float(value1) * uint32_to_float(value2);
  add_to_stack(frame, float_to_uint32(result));

  return 0;
}

int fdiv(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  float result = uint32_to_float(value1) / uint32_to_float(value2);
  add_to_stack(frame, float_to_uint32(result));

  return 0;
}

int frem(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  if (uint32_to_float(value2) == 0.0f) {
    add_to_stack(frame, value1);
    return 0;
  }
  float result = fmodf(uint32_to_float(value1), uint32_to_float(value2));
  add_to_stack(frame, float_to_uint32(result));

  return 0;
}

int fneg(Frame * frame, Instruction Instruction) {
  uint32_t value1 = remove_from_stack(frame);
  float result = - uint32_to_float(value1);
  add_to_stack(frame, float_to_uint32(result));

  return 0;
}

int dadd(Frame * frame, Instruction Instruction){
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  double resultd = uint64_to_double(value1) + uint64_to_double(value2);
  uint64_t result = double_to_uint64(resultd);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int dsub(Frame * frame, Instruction Instruction){
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  double resultd = uint64_to_double(value1) - uint64_to_double(value2);
  uint64_t result = double_to_uint64(resultd);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int dmul(Frame * frame, Instruction Instruction){
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  double resultd = uint64_to_double(value1) * uint64_to_double(value2);
  uint64_t result = double_to_uint64(resultd);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int ddiv(Frame * frame, Instruction Instruction){
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  double resultd = uint64_to_double(value1) / uint64_to_double(value2);
  uint64_t result = double_to_uint64(resultd);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int drem_(Frame * frame, Instruction Instruction){
  uint64_t value2_low = (uint64_t) remove_from_stack(frame);
  uint64_t value2_high = (uint64_t) remove_from_stack(frame);
  uint64_t value2 = value2_high << 32;
  value2 |= value2_low;
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  if (uint64_to_double(value2) == 0.0) {
    uint32_t result_low = (uint32_t) (value1 & 0xFFFFFFFF);
    uint32_t result_high = (uint32_t) (value1 >> 32);
    add_to_stack(frame, result_high);
    add_to_stack(frame, result_low);
    return 0;
  }
  double resultd = fmod(uint64_to_double(value1), uint64_to_double(value2));
  uint64_t result = double_to_uint64(resultd);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}

int dneg(Frame * frame, Instruction Instruction){
  uint64_t value1_low = (uint64_t) remove_from_stack(frame);
  uint64_t value1_high = (uint64_t) remove_from_stack(frame);
  uint64_t value1 = value1_high << 32;
  value1 |= value1_low;
  double resultd = - uint64_to_double(value1);
  uint64_t result = double_to_uint64(resultd);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);

  return 0;
}