#include "return.h"

int ireturn(Frame * frame, Instruction Instruction) {
  return 2;
}

int lreturn(Frame * frame, Instruction Instruction) {
  uint32_t low = remove_from_stack(frame);
  uint32_t high = remove_from_stack(frame);
  add_to_stack(frame->next, high);
  add_to_stack(frame, low);

  return 2;
}

int freturn(Frame * frame, Instruction Instruction) {
  return 2;
}

int dreturn(Frame * frame, Instruction Instruction) {
  uint32_t low = remove_from_stack(frame);
  uint32_t high = remove_from_stack(frame);
  add_to_stack(frame->next, high);
  add_to_stack(frame, low);

  return 2;
}

int areturn(Frame * frame, Instruction Instruction) {
  return 2;
}

int return_(Frame * frame, Instruction Instruction) {
  return 3;
}