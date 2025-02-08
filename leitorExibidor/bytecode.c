#include "bytecode.h"

Instruction read_instruction() {
  Buffer * code_buffer = get_code_buffer();
  return read_instruction_buffer(code_buffer);
}

Instruction read_instruction_buffer(Buffer * code_buffer) {
  InstructionType * instruction_type = get_instruction_type(read_u8_buffer(code_buffer));
  Instruction instruction;
  instruction.type = instruction_type;
  if (instruction_type->operand_count == 0) {
    return instruction;
  }

  instruction.operands = malloc(instruction_type->operand_count * sizeof(uint8_t));
  for (int i = 0; i < instruction_type->operand_count; i++) {
    instruction.operands[i] = read_u8_buffer(code_buffer);
  }
  return instruction;
}
