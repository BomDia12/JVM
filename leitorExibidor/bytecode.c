#include "bytecode.h"

Instruction read_instruction() {
  Buffer * code_buffer = get_code_buffer();
  InstructionType * instruction_type = &instructions[read_u8(code_buffer)];
  Instruction instruction;
  instruction.opcode = instruction_type->opcode;
  instruction.operand_count = instruction_type->operand_count;
  if (instruction.operand_count == 0) {
    return instruction;
  }

  instruction.operands = malloc(instruction.operand_count * sizeof(uint8_t));
  for (int i = 0; i < instruction_type->operand_count; i++) {
    instruction.operands[i] = read_u8(code_buffer);
  }
  return instruction;
}
