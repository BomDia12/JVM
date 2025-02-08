#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "types.h"
#include "instructions.h"
#include <math.h>

void iadd(Frame * frame, Instruction Instruction);
void ladd(Frame * frame, Instruction Instruction);
void fadd(Frame * frame, Instruction Instruction);
void dadd(Frame * frame, Instruction Instruction);
void isub(Frame * frame, Instruction Instruction);
void lsub(Frame * frame, Instruction Instruction);
void fsub(Frame * frame, Instruction Instruction);
void dsub(Frame * frame, Instruction Instruction);
void imul(Frame * frame, Instruction Instruction);
void lmul(Frame * frame, Instruction Instruction);
void fmul(Frame * frame, Instruction Instruction);
void dmul(Frame * frame, Instruction Instruction);
void idiv(Frame * frame, Instruction Instruction);
void ldiv(Frame * frame, Instruction Instruction);
void fdiv(Frame * frame, Instruction Instruction);
void ddiv(Frame * frame, Instruction Instruction);
void irem(Frame * frame, Instruction Instruction);
void lrem(Frame * frame, Instruction Instruction);
void frem(Frame * frame, Instruction Instruction);
void drem(Frame * frame, Instruction Instruction);
void ineg(Frame * frame, Instruction Instruction);
void lneg(Frame * frame, Instruction Instruction);
void fneg(Frame * frame, Instruction Instruction);
void dneg(Frame * frame, Instruction Instruction);
void ishl(Frame * frame, Instruction Instruction);
void lshl(Frame * frame, Instruction Instruction);
void ishr(Frame * frame, Instruction Instruction);
void lshr(Frame * frame, Instruction Instruction);
void iushr(Frame * frame, Instruction Instruction);
void lushr(Frame * frame, Instruction Instruction);
void iand(Frame * frame, Instruction Instruction);
void land(Frame * frame, Instruction Instruction);
void ior(Frame * frame, Instruction Instruction);
void lor(Frame * frame, Instruction Instruction);
void ixor(Frame * frame, Instruction Instruction);
void lxor(Frame * frame, Instruction Instruction);
void iinc(Frame * frame, Instruction Instruction);

#endif