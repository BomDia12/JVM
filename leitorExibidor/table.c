#include "table.h"

int tableswitch(Frame * frame, Instruction instruction) {
  const uint32_t start = frame->pc.position - 1;
  const uint8_t padding = 3 - (start % 4);
  for (int i = 0; i < padding; i++) {
    read_u8_buffer(&frame->pc);
  }

  int32_t default_offset = uint32_to_int(read_u32_buffer(&frame->pc));
  int32_t low = uint32_to_int(read_u32_buffer(&frame->pc));
  int32_t high = uint32_to_int(read_u32_buffer(&frame->pc));
  int32_t index = uint32_to_int(remove_from_stack(frame));

  TableSwitch table_switch = {
    .size = high - low + 1,
    .offsets = malloc(sizeof(uint32_t) * (high - low + 1)),
  };

  for (int i = low; i <= high; i++) {
    table_switch.offsets[i - low] = uint32_to_int(read_u32_buffer(&frame->pc));
  }

  if (index >= low && index <= high) {
    frame->pc.position = start + table_switch.offsets[index - low];
  } else {
    frame->pc.position = start + default_offset;
  }

  return 0;
}

int lookupswitch(Frame * frame, Instruction instruction) {
  const uint32_t start = frame->pc.position - 1;
  const uint8_t padding = 3 - (start % 4);
  for (int i = 0; i < padding; i++) {
    read_u8_buffer(&frame->pc);
  }

  int32_t default_offset = uint32_to_int(read_u32_buffer(&frame->pc));
  uint32_t npairs = read_u32_buffer(&frame->pc);
  int32_t key = uint32_to_int(remove_from_stack(frame));

  for (int i = 0; i < npairs; i++) {
    int32_t match = uint32_to_int(read_u32_buffer(&frame->pc));
    int32_t offset = uint32_to_int(read_u32_buffer(&frame->pc));
    if (match == key) {
      frame->pc.position = start + offset;
      return 0;
    }
    if (match > key) {
      break;
    }
  }
  frame->pc.position = start + default_offset;

  return 0;
}
