#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "types.h"
#include "instructions.h"
#include "conversions.h"
#include <math.h>

int iadd(Frame * frame, Instruction Instruction);
int ladd(Frame * frame, Instruction Instruction);
int fadd(Frame * frame, Instruction Instruction);
int dadd(Frame * frame, Instruction Instruction);
int isub(Frame * frame, Instruction Instruction);
int lsub(Frame * frame, Instruction Instruction);
int fsub(Frame * frame, Instruction Instruction);
int dsub(Frame * frame, Instruction Instruction);
int imul(Frame * frame, Instruction Instruction);
int lmul(Frame * frame, Instruction Instruction);
int fmul(Frame * frame, Instruction Instruction);
int dmul(Frame * frame, Instruction Instruction);
int idiv(Frame * frame, Instruction Instruction);
int ldiv_(Frame * frame, Instruction Instruction);
int fdiv(Frame * frame, Instruction Instruction);
int ddiv(Frame * frame, Instruction Instruction);
int irem(Frame * frame, Instruction Instruction);
int lrem(Frame * frame, Instruction Instruction);
int frem(Frame * frame, Instruction Instruction);
int drem_(Frame * frame, Instruction Instruction);
int ineg(Frame * frame, Instruction Instruction);
int lneg(Frame * frame, Instruction Instruction);
int fneg(Frame * frame, Instruction Instruction);
int dneg(Frame * frame, Instruction Instruction);
int ishl(Frame * frame, Instruction Instruction);
int lshl(Frame * frame, Instruction Instruction);
int ishr(Frame * frame, Instruction Instruction);
int lshr(Frame * frame, Instruction Instruction);
int iushr(Frame * frame, Instruction Instruction);
int lushr(Frame * frame, Instruction Instruction);
int iand(Frame * frame, Instruction Instruction);
int land(Frame * frame, Instruction Instruction);
int ior(Frame * frame, Instruction Instruction);
int lor(Frame * frame, Instruction Instruction);
int ixor(Frame * frame, Instruction Instruction);
int lxor(Frame * frame, Instruction Instruction);
int iinc(Frame * frame, Instruction Instruction);

#endif