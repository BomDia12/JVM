#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "instructions.h"

void i2l(Frame * frame, Instruction Instruction);
void i2f(Frame * frame, Instruction Instruction);
void i2d(Frame * frame, Instruction Instruction);
void l2i(Frame * frame, Instruction Instruction);
void l2f(Frame * frame, Instruction Instruction);
void l2d(Frame * frame, Instruction Instruction);
void f2i(Frame * frame, Instruction Instruction);
void f2l(Frame * frame, Instruction Instruction);
void f2d(Frame * frame, Instruction Instruction);
void d2i(Frame * frame, Instruction Instruction);
void d2l(Frame * frame, Instruction Instruction);
void d2f(Frame * frame, Instruction Instruction);
void i2b(Frame * frame, Instruction Instruction);
void i2c(Frame * frame, Instruction Instruction);
void i2s(Frame * frame, Instruction Instruction);
int32_t uint32_to_int(uint32_t value);
uint32_t int_to_uint32(int32_t value);
int64_t uint64_to_long(uint64_t value);
uint64_t long_to_uint64(int64_t value);
float uint32_to_float(uint32_t value);
uint32_t float_to_uint32(float value);
double uint64_to_double(uint64_t value);
uint64_t double_to_uint64(double value);
void double_to_ints(double d, int* hi, int* lo);

#endif