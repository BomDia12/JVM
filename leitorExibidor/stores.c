#include "stores.h"

int istore(Frame *frame, Instruction instruction) {
    uint8_t index = instruction.operands[0];  
    int32_t value = pop_from_stack(frame);  
    frame->local_variables->variables[index] = value;
    return 0;
  }
  
  int lstore(Frame *frame, Instruction instruction) {
    uint8_t index = instruction.operands[0];  
    int64_t value = pop_from_stack(frame);  
    *(int64_t *)&frame->local_variables->variables[index] = value;
    return 0;
  }
  
  int fstore(Frame *frame, Instruction instruction) {
    uint8_t index = instruction.operands[0];  
    float value = pop_from_stack(frame);  
    *(float *)&frame->local_variables->variables[index] = value;
    return 0;
  }
  
  int dstore(Frame *frame, Instruction instruction) {
    uint8_t index = instruction.operands[0];  
    double value = pop_from_stack(frame);  
    *(double *)&frame->local_variables->variables[index] = value;
    return 0;
  }
  
  int astore(Frame *frame, Instruction instruction) {
    uint8_t index = instruction.operands[0];  
    Object *ref = (Object *) pop_from_stack(frame);  
    *(Object **)&frame->local_variables->variables[index] = ref;
    return 0;
  }
  
  int istore_0(Frame *frame) {
    int32_t value = pop_from_stack(frame);
    frame->local_variables->variables[0] = value;
    return 0;
  }
  
  int istore_1(Frame *frame) {
    int32_t value = pop_from_stack(frame);
    frame->local_variables->variables[1] = value;
    return 0;
  }
  
  int istore_2(Frame *frame) {
    int32_t value = pop_from_stack(frame);
    frame->local_variables->variables[2] = value;
    return 0;
  }
  
  int istore_3(Frame *frame) {
    int32_t value = pop_from_stack(frame);
    frame->local_variables->variables[3] = value;
    return 0;
  }
  
  int lstore_0(Frame *frame) {
    int64_t value = pop_from_stack(frame);
    frame->local_variables->variables[0] = value;
    return 0;
  }
  
  int lstore_1(Frame *frame) {
    int64_t value = pop_from_stack(frame);
    frame->local_variables->variables[1] = value;
    return 0;
  }
  
  int lstore_2(Frame *frame) {
    int64_t value = pop_from_stack(frame);
    frame->local_variables->variables[2] = value;
    return 0;
  }
  
  int lstore_3(Frame *frame) {
    int64_t value = pop_from_stack(frame);
    frame->local_variables->variables[3] = value;
    return 0;
  }
  
  int fstore_0(Frame *frame) {
    float value = pop_from_stack(frame);
    frame->local_variables->variables[0] = *((uint32_t*)&value);
    return 0;
  }
  
  int fstore_1(Frame *frame) {
    float value = pop_from_stack(frame);
    frame->local_variables->variables[1] = *((uint32_t*)&value);
    return 0;
  }
  
  int fstore_2(Frame *frame) {
    float value = pop_from_stack(frame);
    frame->local_variables->variables[2] = *((uint32_t*)&value);
    return 0;
  }
  
  int fstore_3(Frame *frame) {
    float value = pop_from_stack(frame);
    frame->local_variables->variables[3] = *((uint32_t*)&value);
    return 0;
  }
  
  int dstore_0(Frame *frame) {
    double value = pop_from_stack(frame);
    frame->local_variables->variables[0] = *((uint64_t*)&value); 
    return 0;
  }
  
  int dstore_1(Frame *frame) {
    double value = pop_from_stack(frame);
    frame->local_variables->variables[1] = *((uint64_t*)&value);
    return 0;
  }
  
  int dstore_2(Frame *frame) {
    double value = pop_from_stack(frame);
    frame->local_variables->variables[2] = *((uint64_t*)&value);
    return 0;
  }
  
  int dstore_3(Frame *frame) {
    double value = pop_from_stack(frame);
    frame->local_variables->variables[3] = *((uint64_t*)&value);
    return 0;
  }
  
  int astore_0(Frame *frame) {
    Object *value = pop_from_stack(frame);
    frame->local_variables->variables[0] = (uint8_t)(uintptr_t)value;
    return 0;
  }
  
  int astore_1(Frame *frame) {
    Object *value = pop_from_stack(frame);
    frame->local_variables->variables[1] = (uint8_t)(uintptr_t)value;
    return 0;
  }
  
  int astore_2(Frame *frame) {
    Object *value = pop_from_stack(frame);
    frame->local_variables->variables[2] = (uint8_t)(uintptr_t)value;
    return 0;
  }
  
  int astore_3(Frame *frame) {
    Object *value = pop_from_stack(frame);
    frame->local_variables->variables[3] = (uint8_t)(uintptr_t)value;
    return 0;
  }