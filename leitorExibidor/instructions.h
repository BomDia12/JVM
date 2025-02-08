#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "types.h"
#include <math.h>

InstructionType * get_instruction_type(uint8_t opcode);

void nop(Frame * frame);

void add_to_stack(Frame * frame, uint32_t value);
uint32_t remove_from_stack(Frame * frame);
int32_t uint32_to_int(uint32_t value);
uint32_t int_to_uint32(int32_t value);
int64_t uint64_to_long(uint64_t value);
uint64_t long_to_uint64(int64_t value);
float uint32_to_float(uint32_t value);
uint32_t float_to_uint32(float value);
double uint64_to_double(uint64_t value);
uint64_t double_to_uint64(double value);

void load_constant(Frame * frame, Instruction instruction);

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

#endif
