#ifndef STACKOPS_H
#define STACKOPS_H

#include "types.h"
#include "conversions.h"

int pop(Frame * frame, Instruction Instruction);
int pop2(Frame * frame, Instruction Instruction);
int dup(Frame * frame, Instruction Instruction);
int dup_x1(Frame * frame, Instruction Instruction);
int dup_x2(Frame * frame, Instruction Instruction);
int dup2(Frame * frame, Instruction Instruction);
int dup2_x1(Frame * frame, Instruction Instruction);
int dup2_x2(Frame * frame, Instruction Instruction);
int swap(Frame * frame, Instruction Instruction);
int lcmp(Frame * frame, Instruction Instruction);
int fcmp(Frame * frame, Instruction Instruction);
int dcmp(Frame * frame, Instruction Instruction);
int bipush(Frame * frame, Instruction Instruction);
int sipush(Frame * frame, Instruction Instruction);

#endif