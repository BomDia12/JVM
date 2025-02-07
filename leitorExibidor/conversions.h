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
void double_to_ints(double d, int* hi, int* lo);

#endif