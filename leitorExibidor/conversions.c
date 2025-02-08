#include "conversions.h"

void i2l(Frame * frame, Instruction Instruction) {
  uint32_t number = remove_from_stack(frame);
  if (number > 0x7fffffff) {
    add_to_stack(frame, 0xffffffff);
  } else {
    add_to_stack(frame, 0);
  }
  add_to_stack(frame, number);
}

void i2f(Frame * frame, Instruction Instruction) {
  float number = (float) remove_from_stack(frame);
  uint32_t converted_number = float_to_uint32(number);
  add_to_stack(frame, converted_number);
}

void i2d(Frame * frame, Instruction Instruction) {
  uint32_t number = remove_from_stack(frame);
  double converted_number = (double) number;
  int hi;
  int lo;
  double_to_ints(converted_number, &hi, &lo);
  add_to_stack(frame, hi);
  add_to_stack(frame, lo);
}

void l2i(Frame * frame, Instruction Instruction) {
  uint32_t low = remove_from_stack(frame);
  uint32_t high = remove_from_stack(frame);
  // uint64_t number = high << 32 | low;
  add_to_stack(frame, low);
}

void l2f(Frame * frame, Instruction Instruction) {
  float low = (float) remove_from_stack(frame);
  uint32_t high = remove_from_stack(frame);
  uint32_t converted_number = float_to_uint32(low);
  add_to_stack(frame, converted_number);
}

void l2d(Frame * frame, Instruction Instruction) {
  uint64_t low = (uint64_t) remove_from_stack(frame);
  uint64_t high = (uint64_t) remove_from_stack(frame);
  uint64_t number = high << 32 | low;
  double converted_number = (double) number;
  uint32_t hi;
  uint32_t lo;
  double_to_ints(converted_number, &hi, &lo);
  add_to_stack(frame, hi);
  add_to_stack(frame, lo);
}

void f2i(Frame * frame, Instruction Instruction) {
  float number = uint32_to_float(remove_from_stack(frame));
  uint32_t converted_number = (uint32_t) number;
  add_to_stack(frame, converted_number);
}

void f2l(Frame * frame, Instruction Instruction) {
  float number = uint32_to_float(remove_from_stack(frame));
  uint64_t converted_number = (uint64_t) number;
  uint32_t low = (uint32_t) converted_number;
  uint32_t high = (uint32_t) (converted_number >> 32);
  add_to_stack(frame, high);
  add_to_stack(frame, low);
}

void f2d(Frame * frame, Instruction Instruction) {
  float number = uint32_to_float(remove_from_stack(frame));
  double converted_number = (double) number;
  uint32_t hi;
  uint32_t lo;
  double_to_ints(converted_number, &hi, &lo);
  add_to_stack(frame, hi);
  add_to_stack(frame, lo);
}

void d2i(Frame * frame, Instruction Instruction) {
  uint64_t low = (uint64_t) remove_from_stack(frame);
  uint64_t high = (uint64_t) remove_from_stack(frame);
  uint64_t number = high << 32 | low;
  double converted_number = uint64_to_double(number);
  uint32_t final_number = (uint32_t) converted_number;
  add_to_stack(frame, final_number);
}

void d2l(Frame * frame, Instruction Instruction) {
  uint64_t low = (uint64_t) remove_from_stack(frame);
  uint64_t high = (uint64_t) remove_from_stack(frame);
  uint64_t number = high << 32 | low;
  double converted_number = uint64_to_double(number);
  uint64_t final_long_number = (uint64_t) converted_number; 
  uint32_t final_low = (uint32_t) final_long_number;
  uint32_t final_high = (uint32_t) (final_long_number >> 32);
  add_to_stack(frame, final_low);
  add_to_stack(frame, final_high);
}

void d2f(Frame * frame, Instruction Instruction) {
  uint64_t low = (uint64_t) remove_from_stack(frame);
  uint64_t high = (uint64_t) remove_from_stack(frame);
  uint64_t number = high << 32 | low;
  double converted_number = uint64_to_double(number);
  float final_float_number = (float) converted_number;
  uint32_t final_number = float_to_uint32(final_float_number);
  add_to_stack(frame, final_number);
}

void i2b(Frame * frame, Instruction Instruction) {
  uint8_t number = (uint8_t) remove_from_stack(frame);
  uint32_t converted_number = (uint32_t) number;
  add_to_stack(frame, converted_number);
}

void i2s(Frame * frame, Instruction Instruction) {
  uint16_t number = (uint16_t) remove_from_stack(frame);
  uint32_t converted_number = (uint32_t) number;
  add_to_stack(frame, converted_number);
}

void i2c(Frame * frame, Instruction Instruction) {
  char number = (char) remove_from_stack(frame);
  uint32_t converted_number = (uint32_t) number;
  add_to_stack(frame, converted_number);
}

int32_t uint32_to_int(uint32_t value) {
  union {
    uint32_t u32;
    int32_t i;
  } converter;
  converter.u32 = value;
  return converter.i;
}

uint32_t int_to_uint32(int32_t value) {
  union {
    uint32_t u32;
    int32_t i;
  } converter;
  converter.i = value;
  return converter.u32;
}

int64_t uint64_to_long(uint64_t value) {
  union {
    uint64_t u64;
    int64_t l;
  } converter;
  converter.u64 = value;
  return converter.l;
}

uint64_t long_to_uint64(int64_t value) {
  union {
    uint64_t u64;
    int64_t l;
  } converter;
  converter.l = value;
  return converter.u64;
}

float uint32_to_float(uint32_t value) {
  union {
    uint32_t u32;
    float f;
  } converter;
  converter.u32 = value;
  return converter.f;
}

uint32_t float_to_uint32(float value) {
  union {
    uint32_t u32;
    float f;
  } converter;
  converter.f = value;
  return converter.u32;
}

double uint64_to_double(uint64_t value) {
  union {
    uint64_t u64;
    double d;
  } converter;
  converter.u64 = value;
  return converter.d;
}

uint64_t double_to_uint64(double value) {
  union {
    uint64_t u64;
    double d;
  } converter;
  converter.d = value;
  return converter.u64;
}

void double_to_ints(double d, uint32_t* hi, uint32_t* lo) {
    // União para acessar os bytes de um double como dois inteiros de 32 bits
    union {
        double d;
        uint64_t u;
    } u;

    u.d = d;  // Armazena o valor de double na união

    // Extrai os 32 bits mais significativos (parte alta)
    *hi = (int)(u.u >> 32);  // Desloca os 32 bits mais altos para a parte baixa (32 bits)
    
    // Extrai os 32 bits menos significativos (parte baixa)
    *lo = (int)(u.u & 0xFFFFFFFF);  // Máscara para pegar os 32 bits baixos
}