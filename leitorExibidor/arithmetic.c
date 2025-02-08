#include "arithmetic.h"

void iadd(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) + uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));
}

void isub(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) - uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));
}

void imul(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) * uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));
}

void idiv(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) / uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));
}

void irem(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) % uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));
}

void ineg(Frame * frame, Instruction Instruction) {
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = - uint32_to_int(value1);
  add_to_stack(frame, int_to_uint32(result));
}

void ishl(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) << (uint32_to_int(value2) & 0x1f);
  add_to_stack(frame, int_to_uint32(result));
}

void ishr(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) >> (uint32_to_int(value2) & 0x1f);
  add_to_stack(frame, int_to_uint32(result));
}

void iushr(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  uint32_t result = value1 >> (uint32_to_int(value2) & 0x1f);
  add_to_stack(frame, result);
}

void iand(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) & uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));
}

void ior(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) | uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));
}

void ixor(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  int32_t result = uint32_to_int(value1) ^ uint32_to_int(value2);
  add_to_stack(frame, int_to_uint32(result));
}

void iinc(Frame * frame, Instruction Instruction) {
  uint8_t index = Instruction.operands[0];
  uint8_t consti = Instruction.operands[1];
  frame->local_variables->variables[index] += consti;
}

void ladd(Frame * frame, Instruction Instruction) {
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
}

void lsub(Frame * frame, Instruction Instruction) {
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
}

void lmul(Frame * frame, Instruction Instruction) {
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
}

void ldiv(Frame * frame, Instruction Instruction) {
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
}

void lrem(Frame * frame, Instruction Instruction) {
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
}

void lneg(Frame * frame, Instruction Instruction) {
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
}

void lshl(Frame * frame, Instruction Instruction) {
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
}

void lshr(Frame * frame, Instruction Instruction) {
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
}

void lushr(Frame * frame, Instruction Instruction) {
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
}

void land(Frame * frame, Instruction Instruction) {
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
}

void lor(Frame * frame, Instruction Instruction) {
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
}

void lxor(Frame * frame, Instruction Instruction) {
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
}

void fadd(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  float result = uint32_to_float(value1) + uint32_to_float(value2);
  add_to_stack(frame, float_to_uint32(result));
}

void fsub(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  float result = uint32_to_float(value1) - uint32_to_float(value2);
  add_to_stack(frame, float_to_uint32(result));
}

void fmul(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  float result = uint32_to_float(value1) * uint32_to_float(value2);
  add_to_stack(frame, float_to_uint32(result));
}

void fdiv(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  float result = uint32_to_float(value1) / uint32_to_float(value2);
  add_to_stack(frame, float_to_uint32(result));
}

void frem(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  if (uint32_to_float(value2) == 0.0f) {
    add_to_stack(frame, value1);
    return;
  }
  float result = fmodf(uint32_to_float(value1), uint32_to_float(value2));
  add_to_stack(frame, float_to_uint32(result));
}

void fneg(Frame * frame, Instruction Instruction) {
  uint32_t value1 = remove_from_stack(frame);
  float result = - uint32_to_float(value1);
  add_to_stack(frame, float_to_uint32(result));
}

void dadd(Frame * frame, Instruction Instruction){
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
}

void dsub(Frame * frame, Instruction Instruction){
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
}

void dmul(Frame * frame, Instruction Instruction){
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
}

void ddiv(Frame * frame, Instruction Instruction){
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
}

void drem(Frame * frame, Instruction Instruction){
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
    return;
  }
  double resultd = fmod(uint64_to_double(value1), uint64_to_double(value2));
  uint64_t result = double_to_uint64(resultd);
  uint32_t result_low = (uint32_t) (result & 0xFFFFFFFF);
  uint32_t result_high = (uint32_t) (result >> 32);
  add_to_stack(frame, result_high);
  add_to_stack(frame, result_low);
}

void dneg(Frame * frame, Instruction Instruction){
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
}