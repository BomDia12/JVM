#include "bytecode.h"

Instruction * read_instruction() {
  Buffer * code_buffer = get_code_buffer();
  InstructionType * instruction_type = &instructions[read_u8(code_buffer)];
  Instruction * instruction = malloc(sizeof(Instruction));
  instruction->opcode = instruction_type->opcode;
  instruction->operand_count = instruction_type->operand_count;
  instruction->operands = malloc(instruction->operand_count * sizeof(uint8_t));
  for (int i = 0; i < instruction_type->operand_count; i++) {
    read_u32(code_buffer);
  }
  return NULL;
}
