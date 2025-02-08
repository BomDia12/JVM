#include "stores.h"
# include "instructions.h"

int istore(Frame *frame, Instruction instruction) {
    uint8_t index = instruction.operands[0];  
    int32_t value = remove_from_stack(frame);  
    frame->local_variables->variables[index] = value;
    return 0;
}

int lstore(Frame *frame, Instruction instruction) {
    uint8_t index = instruction.operands[0];  

    uint32_t low = remove_from_stack(frame);
    uint32_t high = remove_from_stack(frame); 
    
    frame->local_variables->variables[index] = high;
    frame->local_variables->variables[index + 1] = low;

    return 0;
}

int fstore(Frame *frame, Instruction instruction) {
    uint8_t index = instruction.operands[0];  
    uint32_t value = remove_from_stack(frame);  
    frame->local_variables->variables[index] = value;
    return 0;
}

int dstore(Frame *frame, Instruction instruction) {
    uint8_t index = instruction.operands[0];

    uint32_t low = remove_from_stack(frame);
    uint32_t high = remove_from_stack(frame); 

    frame->local_variables->variables[index] = high;
    frame->local_variables->variables[index + 1] = low;
    return 0;
}

int astore(Frame *frame, Instruction instruction) {
    uint8_t index = instruction.operands[0];  
    uint32_t ref = remove_from_stack(frame);  
    frame->local_variables->variables[index] = ref;
    return 0;
}

int istore_0(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[0] = value;
    return 0;
}

int istore_1(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[1] = value;
    return 0;
}

int istore_2(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[2] = value;
    return 0;
}

int istore_3(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[3] = value;
    return 0;
}

int lstore_0(Frame *frame, Instruction instruction) {
    uint32_t low = remove_from_stack(frame);
    uint32_t high = remove_from_stack(frame);

    frame->local_variables->variables[0] = high;
    frame->local_variables->variables[1] = low;
    return 0;
}

int lstore_1(Frame *frame, Instruction instruction) {
    uint32_t low = remove_from_stack(frame);
    uint32_t high = remove_from_stack(frame);

    frame->local_variables->variables[1] = high;
    frame->local_variables->variables[2] = low;
    return 0;
}

int lstore_2(Frame *frame, Instruction instruction) {
    uint32_t low = remove_from_stack(frame);
    uint32_t high = remove_from_stack(frame);

    frame->local_variables->variables[2] = high;
    frame->local_variables->variables[3] = low;
    return 0;
}

int lstore_3(Frame *frame, Instruction instruction) {
    uint32_t low = remove_from_stack(frame);
    uint32_t high = remove_from_stack(frame);

    frame->local_variables->variables[3] = high;
    frame->local_variables->variables[4] = low;
    return 0;
}

int fstore_0(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[0] = value;
    return 0;
}

int fstore_1(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[1] = value;
    return 0;
}

int fstore_2(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[2] = value;
    return 0;
}

int fstore_3(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[3] = value;
    return 0;
}

int dstore_0(Frame *frame, Instruction instruction) {
    uint32_t low = remove_from_stack(frame);
    uint32_t high = remove_from_stack(frame);

    frame->local_variables->variables[0] = high;
    frame->local_variables->variables[0 + 1] = low;

    return 0;
}

int dstore_1(Frame *frame, Instruction instruction) {
    uint32_t low = remove_from_stack(frame);
    uint32_t high = remove_from_stack(frame);

    frame->local_variables->variables[1] = high;
    frame->local_variables->variables[1 + 1] = low;
    
    return 0;
}

int dstore_2(Frame *frame, Instruction instruction) {
    uint32_t low = remove_from_stack(frame);
    uint32_t high = remove_from_stack(frame);

    frame->local_variables->variables[2] = high;
    frame->local_variables->variables[2 + 1] = low;
    
    return 0;
}

int dstore_3(Frame *frame, Instruction instruction) {
    uint32_t low = remove_from_stack(frame);
    uint32_t high = remove_from_stack(frame);

    frame->local_variables->variables[3] = high;
    frame->local_variables->variables[3 + 1] = low;
    
    return 0;
}

int astore_0(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[0] = value;
    return 0;
}

int astore_1(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[1] = value;
    return 0;
}

int astore_2(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[2] = value;
    return 0;
}

int astore_3(Frame *frame, Instruction instruction) {
    uint32_t value = remove_from_stack(frame);
    frame->local_variables->variables[2] = value;
    return 0;
}