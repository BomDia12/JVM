
#include "conversions.h"

int i2l(Frame * frame, Instruction Instruction) {
  int32_t number = uint32_to_int(remove_from_stack(frame));
  if (number > 0x7fffffff) {
    add_to_stack(frame, 0xffffffff);
  } else {
    add_to_stack(frame, 0);
  }
  add_to_stack(frame, number);

  return 0;
}

int i2f(Frame * frame, Instruction Instruction) {
  int32_t number = uint32_to_int(remove_from_stack(frame));
  float f_number = (float) number;
  uint32_t converted_number = float_to_uint32(f_number);
  add_to_stack(frame, converted_number);

  return 0;
}

int i2d(Frame * frame, Instruction Instruction) {
  int32_t number = uint32_to_int(remove_from_stack(frame));
  double converted_number = (double) number;
  int hi;
  int lo;
  double_to_ints(converted_number, &hi, &lo);
  add_to_stack(frame, hi);
  add_to_stack(frame, lo);

  return 0;
}

int l2i(Frame * frame, Instruction Instruction) {
  uint32_t low = remove_from_stack(frame);
  uint32_t high = remove_from_stack(frame);
  // uint64_t number = high << 32 | low;
  add_to_stack(frame, low);

  return 0;
}

int l2f(Frame * frame, Instruction Instruction) {
  uint64_t low = (uint64_t) remove_from_stack(frame);
  uint64_t high = (uint64_t) remove_from_stack(frame);
  uint64_t number = high << 32 | low;
  float converted_number = (float) uint64_to_long(number);
  add_to_stack(frame, float_to_uint32(converted_number));

  return 0;
}

int l2d(Frame * frame, Instruction Instruction) {
  uint64_t low = (uint64_t) remove_from_stack(frame);
  uint64_t high = (uint64_t) remove_from_stack(frame);
  uint64_t number = high << 32 | low;
  double converted_number = (double) uint64_to_long(number);
  uint32_t hi;
  uint32_t lo;
  double_to_ints(converted_number, &hi, &lo);
  add_to_stack(frame, hi);
  add_to_stack(frame, lo);

  return 0;
}

int f2i(Frame * frame, Instruction Instruction) {
  float number = uint32_to_float(remove_from_stack(frame));
  uint32_t converted_number = int_to_uint32((int32_t) number);
  add_to_stack(frame, converted_number);

  return 0;
}

int f2l(Frame * frame, Instruction Instruction) {
  float number = uint32_to_float(remove_from_stack(frame));
  int64_t converted_number = (int64_t) number;
  uint64_t u_converted_number = long_to_uint64(converted_number);
  uint32_t low = (uint32_t) u_converted_number;
  uint32_t high = (uint32_t) (u_converted_number >> 32);
  add_to_stack(frame, high);
  add_to_stack(frame, low);

  return 0;
}

int f2d(Frame * frame, Instruction Instruction) {
  float number = uint32_to_float(remove_from_stack(frame));
  double converted_number = (double) number;
  uint32_t hi;
  uint32_t lo;
  double_to_ints(converted_number, &hi, &lo);
  add_to_stack(frame, hi);
  add_to_stack(frame, lo);

  return 0;
}

int d2i(Frame * frame, Instruction Instruction) {
  uint64_t low = (uint64_t) remove_from_stack(frame);
  uint64_t high = (uint64_t) remove_from_stack(frame);
  uint64_t number = high << 32 | low;
  double converted_number = uint64_to_double(number);
  int32_t i_number = (int32_t) converted_number;
  uint32_t final_number = int_to_uint32(i_number);
  add_to_stack(frame, final_number);

  return 0;
}

int d2l(Frame * frame, Instruction Instruction) {
  uint64_t low = (uint64_t) remove_from_stack(frame);
  uint64_t high = (uint64_t) remove_from_stack(frame);
  uint64_t number = high << 32 | low;
  double converted_number = uint64_to_double(number);
  int64_t final_i_number = (int64_t) converted_number;
  uint64_t final_long_number = long_to_uint64(final_i_number);
  uint32_t final_low = (uint32_t) final_long_number;
  uint32_t final_high = (uint32_t) (final_long_number >> 32);
  add_to_stack(frame, final_high);
  add_to_stack(frame, final_low);
  
  return 0;
}

int d2f(Frame * frame, Instruction Instruction) {
  uint64_t low = (uint64_t) remove_from_stack(frame);
  uint64_t high = (uint64_t) remove_from_stack(frame);
  uint64_t number = high << 32 | low;
  double converted_number = uint64_to_double(number);
  float final_float_number = (float) converted_number;
  uint32_t final_number = float_to_uint32(final_float_number);
  add_to_stack(frame, final_number);

  return 0;
}

int i2b(Frame * frame, Instruction Instruction) {
  int32_t number = uint32_to_int(remove_from_stack(frame));
  int8_t b_number = (int8_t) number;
  int32_t i_number = (int32_t) b_number;
  uint32_t converted_number = int_to_uint32(i_number);
  add_to_stack(frame, converted_number);

  return 0;
}

int i2s(Frame * frame, Instruction Instruction) {
  int32_t number = uint32_to_int(remove_from_stack(frame));
  int16_t converted_number = (int16_t) (number &= 0x0000FFFF);
  int32_t i_converted_number = (int32_t) converted_number;
  uint32_t u_converted_number = int_to_uint32(i_converted_number);
  add_to_stack(frame, u_converted_number);
  
  return 0;
}

int i2c(Frame * frame, Instruction Instruction) {
  int32_t number = uint32_to_int(remove_from_stack(frame));
  char c_number = (char) number;
  uint32_t converted_number = (uint32_t) c_number;;
  add_to_stack(frame, converted_number);

  return 0;
}

int8_t uint8_to_byte(uint8_t value) {
  union {
    uint8_t u8;
    int8_t b;
  } converter;
  converter.u8 = value;
  return converter.b;
}

uint8_t byte_to_uint8(int8_t value) {
  union {
    uint8_t u8;
    int8_t b;
  } converter;
  converter.b = value;
  return converter.u8;
}

int16_t uint16_to_short(uint16_t value) {
  union {
    uint16_t u16;
    int16_t s;
  } converter;
  converter.u16 = value;
  return converter.s;
}

uint16_t short_to_uint16(int16_t value) {
  union {
    uint16_t u16;
    int16_t s;
  } converter;
  converter.s = value;
  return converter.u16;
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


