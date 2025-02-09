#include "wide.h"

int wide(Frame * frame, Instruction instruction) {
  uint8_t opcode = read_u8_buffer(&frame->pc);
  uint16_t index, const_;
  uint32_t value, high, low;

  switch (opcode) {
    case 0x84: // iinc
      index = read_u16_buffer(&frame->pc);
      const_ = read_u16_buffer(&frame->pc);
      frame->local_variables[index] = int_to_uint32(uint16_to_short(const_) + uint32_to_int(frame->local_variables[index]));
      break;
    case 0x15: // iload
    case 0x17: // fload
    case 0x19: // aload
      index = read_u16_buffer(&frame->pc);
      value = frame->local_variables[index];
      add_to_stack(frame, value);
      break;
    case 0x16: // lload
    case 0x18: // dload
      index = read_u16_buffer(&frame->pc);
      high = frame->local_variables[index];
      low = frame->local_variables[index + 1];
      add_to_stack(frame, high);
      add_to_stack(frame, low);
      break;
    case 0x36: // istore
    case 0x38: // fstore
    case 0x3a: // astore
      index = read_u16_buffer(&frame->pc);
      value = remove_from_stack(frame);
      frame->local_variables[index] = value;
      break;
    case 0x37: // lstore
    case 0x39: // dstore
      index = read_u16_buffer(&frame->pc);
      high = remove_from_stack(frame);
      low = remove_from_stack(frame);
      frame->local_variables[index] = high;
      frame->local_variables[index + 1] = low;
      break;
    default:
      printf("Tipo de wide não tratado: %d\n", opcode);
      break;
  }

  return 0;
}
