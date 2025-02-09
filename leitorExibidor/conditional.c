#include "conditional.h"

int ifeq(Frame * frame, Instruction Instruction) {
  uint32_t value = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value) == 0) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int ifne(Frame * frame, Instruction Instruction) {
  uint32_t value = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value) != 0) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int iflt(Frame * frame, Instruction Instruction) {
  uint32_t value = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value) < 0) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int ifle(Frame * frame, Instruction Instruction) {
  uint32_t value = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value) <= 0) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int ifgt(Frame * frame, Instruction Instruction) {
  uint32_t value = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value) > 0) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int ifge(Frame * frame, Instruction Instruction) {
  uint32_t value = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value) >= 0) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int if_icmpeq(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value1) == uint32_to_int(value2)) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int if_icmpne(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value1) != uint32_to_int(value2)) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int if_icmplt(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value1) < uint32_to_int(value2)) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int if_icmple(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value1) <= uint32_to_int(value2)) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int if_icmpgt(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value1) > uint32_to_int(value2)) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int if_icmpge(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (uint32_to_int(value1) >= uint32_to_int(value2)) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int if_acmpeq(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (value1 == value2) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int if_acmpne(Frame * frame, Instruction Instruction) {
  uint32_t value2 = remove_from_stack(frame);
  uint32_t value1 = remove_from_stack(frame);
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  if (value1 != value2) {
    frame->pc.position += branchbytes16 - 1;
  }
  return 0;
}

int goto_(Frame * frame, Instruction Instruction) {
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  frame->pc.position += branchbytes16 - 1;
  return 0;
}

int jsr(Frame * frame, Instruction Instruction) {
  uint16_t branchbyte1 = Instruction.operands[0];
  uint16_t branchbyte2 = Instruction.operands[1];
  uint16_t branchbytes = branchbyte1 << 8;
  branchbytes |= branchbyte2;
  int16_t branchbytes16 = uint16_to_short(branchbytes);
  uint32_t address = frame->pc.position + 1;
  frame->pc.position += branchbytes16 - 1;
  add_to_stack(frame, address);
  return 0;
}

int ret(Frame * frame, Instruction Instruction) {
  uint8_t index = Instruction.operands[0];
  frame->pc.position == frame->local_variables->variables[index] - 1;
  return 0;
}