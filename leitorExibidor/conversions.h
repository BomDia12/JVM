#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "instructions.h"

int i2l(Frame * frame, Instruction Instruction);
int i2f(Frame * frame, Instruction Instruction);
int i2d(Frame * frame, Instruction Instruction);
int l2i(Frame * frame, Instruction Instruction);
int l2f(Frame * frame, Instruction Instruction);
int l2d(Frame * frame, Instruction Instruction);
int f2i(Frame * frame, Instruction Instruction);
int f2l(Frame * frame, Instruction Instruction);
int f2d(Frame * frame, Instruction Instruction);
int d2i(Frame * frame, Instruction Instruction);
int d2l(Frame * frame, Instruction Instruction);
int d2f(Frame * frame, Instruction Instruction);
int i2b(Frame * frame, Instruction Instruction);
int i2c(Frame * frame, Instruction Instruction);
int i2s(Frame * frame, Instruction Instruction);
int8_t uint8_to_byte(uint8_t value);
uint8_t byte_to_uint8(int8_t value);
int16_t uint16_to_short(uint16_t value);
uint16_t short_to_uint16(int16_t value);
int32_t uint32_to_int(uint32_t value);
uint32_t int_to_uint32(int32_t value);
int64_t uint64_to_long(uint64_t value);
uint64_t long_to_uint64(int64_t value);
float uint32_to_float(uint32_t value);
uint32_t float_to_uint32(float value);
double uint64_to_double(uint64_t value);
uint64_t double_to_uint64(double value);
void double_to_ints(double d, uint32_t* hi, uint32_t* lo);

#endif