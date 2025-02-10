#ifndef RETURN_H
#define RETURN_H

#include "types.h"
#include "conversions.h"

int ireturn(Frame * frame, Instruction Instruction);
int lreturn(Frame * frame, Instruction Instruction);
int freturn(Frame * frame, Instruction Instruction);
int dreturn(Frame * frame, Instruction Instruction);
int areturn(Frame * frame, Instruction Instruction);
int return_(Frame * frame, Instruction Instruction);

#endif