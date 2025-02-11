#include "loads.h"

int aconst_null(Frame * frame, Instruction instruction) {
  add_to_stack(frame, (uint32_t) NULL);
  return 0;
}

int load_constant_m1(Frame * frame, Instruction instruction) {
  add_to_stack(frame, int_to_uint32(-1));
  return 0;
}

int load_constant_0(Frame * frame, Instruction instruction) {
  add_to_stack(frame, 0);
  return 0;
}

int load_constant_1(Frame * frame, Instruction instruction) {
  add_to_stack(frame, 1);
  return 0;
}
  
int load_constant_2(Frame * frame, Instruction instruction) {
  add_to_stack(frame, 2);
  return 0;
}

int load_constant_3(Frame * frame, Instruction instruction) {
  add_to_stack(frame, 3);
  return 0;
}

int load_constant_4(Frame * frame, Instruction instruction) {
  add_to_stack(frame, 4);
  return 0;
}
  
int load_constant_5(Frame * frame, Instruction instruction) {
  add_to_stack(frame, 5);
  return 0;
}

int lconst_0(Frame *frame, Instruction instruction) {
  int32_t high = 0; 
  int32_t low  = 0; 

  add_to_stack(frame, high);  
  add_to_stack(frame, low);
  return 0;
}

int lconst_1(Frame *frame, Instruction instruction) {
  int32_t high = 0; 
  int32_t low  = 1; 

  add_to_stack(frame, high);  
  add_to_stack(frame, low);
  return 0;  
}

int fconst_0(Frame *frame, Instruction instruction) {
  int32_t value = 0;

  add_to_stack(frame, value);
  return 0;
}

int fconst_1(Frame *frame, Instruction instruction) {
  float value = 1.0;
  add_to_stack(frame, float_to_uint32(value));

  return 0;
}

int fconst_2(Frame *frame, Instruction instruction) {
  float value = 1.0;

  add_to_stack(frame, float_to_uint32(value));

  return 0;
}

int dconst_0(Frame *frame, Instruction instruction) {
  int32_t high = 0; 
  int32_t low  = 0; 

  add_to_stack(frame, high);  
  add_to_stack(frame, low);
  return 0;  
}

int dconst_1(Frame *frame, Instruction instruction) {
  double value = 1.0;
  uint32_t hi, lo;
  
  double_to_ints(value, &hi, &lo);
  add_to_stack(frame, hi);
  add_to_stack(frame, lo);

  return 0;
}

int ldc(Frame *frame, Instruction instruction) {
  uint8_t index = instruction.operands[0];
  Constant * constant = getFromConstantPool(frame->this_class, index);
  
  switch (constant->tag) {
    case 3:
      add_to_stack(frame, constant->ConstantUnion.integer_info.bytes);
      break;
    case 8: 
      uint16_t string_index = constant->ConstantUnion.string_info.string_index;
      Constant *string_constant = getFromConstantPool(frame->this_class, string_index);
      if (string_constant->tag == 1) { 
        String * string = malloc(sizeof(String));
        string->size = string_constant->ConstantUnion.utf8_info.length + 1;
        string->string = malloc(sizeof(char) * string->size);
        for (int i = 0; i < string->size - 1; i++) {
          string->string[i] = string_constant->ConstantUnion.utf8_info.bytes[i];
        }
        string->string[string->size - 1] = '\0';
        uint32_t index = add_string(string);
        Object * object = malloc(sizeof(Object));
        object->class = get_string_class_file();
        object->fields = malloc(sizeof(ActiveField *) * 1);
        object->fields[0] = malloc(sizeof(ActiveField));
        object->fields[0]->field = object->class->fields[0];
        object->fields[0]->value = index;

        uint32_t ref = add_object(object);
        add_to_stack(frame, ref);
      } else {
        add_to_stack(frame, string_index);
      }
      break;
    case 4: 
      add_to_stack(frame, constant->ConstantUnion.float_info.bytes);
      break;
    case 5:
      add_to_stack(frame, constant->ConstantUnion.long_info.low_bytes);
      add_to_stack(frame, constant->ConstantUnion.long_info.high_bytes);
      break;
    case 6: 
      add_to_stack(frame, constant->ConstantUnion.double_info.low_bytes);
      add_to_stack(frame, constant->ConstantUnion.double_info.high_bytes);
      break;
    default:
      break;
  }
  return 0;
}

int ldc_w(Frame *frame, Instruction instruction) {
  uint16_t index = (instruction.operands[0] << 8) | instruction.operands[1];

  Constant *constant = frame->this_class->constant_pool[index];

  switch (constant->tag) {
    case 3: {  
      int32_t value = constant->ConstantUnion.integer_info.bytes;
      add_to_stack(frame, value);
      break;
    }
    case 4: { 
      uint32_t value = constant->ConstantUnion.float_info.bytes;
      add_to_stack(frame, value);
      break;
    }
    case 5: {
      uint32_t high = constant->ConstantUnion.long_info.high_bytes;
      uint32_t low = constant->ConstantUnion.long_info.low_bytes;

      add_to_stack(frame, high);
      add_to_stack(frame, low);
      break;
    }
    case 6: { 
      uint32_t high = constant->ConstantUnion.double_info.high_bytes;
      uint32_t low = constant->ConstantUnion.double_info.low_bytes;

      add_to_stack(frame, high);
      add_to_stack(frame, low);
      break;
    }
    case 8: {
      uint16_t string_index = constant->ConstantUnion.string_info.string_index;
      Constant *string_constant = frame->this_class->constant_pool[string_index];
      if (string_constant->tag == 1) { 
        String * string = malloc(sizeof(String));
        string->size = string_constant->ConstantUnion.utf8_info.length;
        string->string = malloc(sizeof(char) * string->size);
        for (int i = 0; i < string->size; i++) {
          string->string[i] = string_constant->ConstantUnion.utf8_info.bytes[i];
        }
        uint32_t index = add_string(string);
        Object * object = malloc(sizeof(Object));
        object->class = get_string_class_file();
        object->fields = malloc(sizeof(ActiveField *) * 1);
        object->fields[0] = malloc(sizeof(ActiveField));
        object->fields[0]->field = object->class->fields[0];
        object->fields[0]->value = index;

        uint32_t ref = add_object(object);
        add_to_stack(frame, ref);
      }
      break;
    }
    default:
      printf("Tipo de constante não tratado: %d\n", constant->tag);
      break;
  }
  return 0;
}


int ldc2_w(Frame *frame, Instruction instruction) {
  uint16_t index = (instruction.operands[0] << 8) | instruction.operands[1];

  Constant *constant = frame->this_class->constant_pool[index];

  switch (constant->tag) {
    case 5: {
      uint32_t high = constant->ConstantUnion.long_info.high_bytes;
      uint32_t low = constant->ConstantUnion.long_info.low_bytes;
      add_to_stack(frame, high);
      add_to_stack(frame, low);  
      break;
    }
    case 6: {
      uint32_t high = constant->ConstantUnion.double_info.high_bytes;
      uint32_t low = constant->ConstantUnion.double_info.low_bytes;
      add_to_stack(frame, high);
      add_to_stack(frame, low);
      break;
    }
    default:
      printf("Tipo de constante não tratado para ldc2_w: %d\n", constant->tag);
      break;
  }
  return 0;
}

int iload(Frame *frame, Instruction instruction) {
  uint8_t index = instruction.operands[0];
  int32_t value = frame->local_variables[index];  
  add_to_stack(frame, value);
  return 0;
}

int lload(Frame *frame, Instruction instruction) {
  uint8_t index = instruction.operands[0];
  

  uint32_t high = frame->local_variables[index];   
  uint32_t low = frame->local_variables[index + 1];

  add_to_stack(frame, high);
  add_to_stack(frame, low);

  return 0;
}

int fload(Frame *frame, Instruction instruction) {
  uint8_t index = instruction.operands[0];
  
  uint32_t value = frame->local_variables[index];
  
  add_to_stack(frame, value);
  return 0;
}

int dload(Frame *frame, Instruction instruction) {
  uint8_t index = instruction.operands[0];
  
  uint32_t high = frame->local_variables[index];
  uint32_t low  = frame->local_variables[index + 1];
  
  add_to_stack(frame, high);
  add_to_stack(frame, low);

  return 0;
}

int aload(Frame *frame, Instruction instruction) {
  uint8_t index = instruction.operands[0];

  uint32_t obj = frame->local_variables[index];

  add_to_stack(frame, obj);
  return 0;
}

int iload_0(Frame *frame, Instruction instruction) {
  int32_t value = frame->local_variables[0];  
  
  add_to_stack(frame, value);
  return 0;
}

int iload_1(Frame *frame, Instruction instruction) {
  int32_t value = frame->local_variables[1];  
  
  add_to_stack(frame, value);
  return 0; 
}

int iload_2(Frame *frame, Instruction instruction) {
  int32_t value = frame->local_variables[2];  
  
  add_to_stack(frame, value);
  return 0;  
}

int iload_3(Frame *frame, Instruction instruction) {
  int32_t value = frame->local_variables[3];  
  add_to_stack(frame, value);
  return 0; 
}

int lload_0(Frame *frame, Instruction instruction) {
  uint32_t high = frame->local_variables[0];
  uint32_t low = frame->local_variables[1];

  add_to_stack(frame, high);
  add_to_stack(frame, low);

  return 0;
}

int lload_1(Frame *frame, Instruction instruction) {
  uint32_t high = frame->local_variables[1]; 
  uint32_t low = frame->local_variables[2];
  
  add_to_stack(frame, high);
  add_to_stack(frame, low);

  return 0;
}

int lload_2(Frame *frame, Instruction instruction) {
  uint32_t high = frame->local_variables[2];
  uint32_t low = frame->local_variables[3];

  add_to_stack(frame, high);
  add_to_stack(frame, low);

  return 0;
}

int lload_3(Frame *frame, Instruction instruction) {
  uint32_t high = frame->local_variables[3];
  uint32_t low = frame->local_variables[4];

  add_to_stack(frame, high);
  add_to_stack(frame, low);
  return 0;
}

int fload_0(Frame *frame, Instruction instruction) {
  uint32_t value = frame->local_variables[0];
  add_to_stack(frame, value);
  return 0;
}

int fload_1(Frame *frame, Instruction instruction) {
  uint32_t value = frame->local_variables[1];
  add_to_stack(frame, value);
  return 0;
}

int fload_2(Frame *frame, Instruction instruction) {
  uint32_t value = frame->local_variables[2];
  add_to_stack(frame, value);
  return 0;
}

int fload_3(Frame *frame, Instruction instruction) {
  uint32_t value = frame->local_variables[3];
  add_to_stack(frame, value);
  return 0;
}

int dload_0(Frame *frame, Instruction instruction) {
  uint32_t high = frame->local_variables[0];
  uint32_t low = frame->local_variables[1];

  add_to_stack(frame, high);
  add_to_stack(frame, low);
  return 0;
}

int dload_1(Frame *frame, Instruction instruction) {
  uint32_t high = frame->local_variables[1];
  uint32_t low = frame->local_variables[2];
  
  add_to_stack(frame, high);
  add_to_stack(frame, low);
  return 0;
}

int dload_2(Frame *frame, Instruction instruction) {
  uint32_t high = frame->local_variables[2];
  uint32_t low = frame->local_variables[1];
  
  add_to_stack(frame, high);
  add_to_stack(frame, low);
  return 0;
}

int dload_3(Frame *frame, Instruction instruction) {
  uint32_t high = frame->local_variables[3];
  uint32_t low = frame->local_variables[4];
  
  add_to_stack(frame, high);
  add_to_stack(frame, low);
  return 0;
}

int aload_0(Frame *frame, Instruction instruction) {
  uint32_t ref = frame->local_variables[0];
  add_to_stack(frame, ref);
  return 0;
}


int aload_1(Frame *frame, Instruction instruction) {
  uint32_t ref = frame->local_variables[1];
  add_to_stack(frame, ref);
  return 0;
}

int aload_2(Frame *frame, Instruction instruction) {
  uint32_t ref = frame->local_variables[2];
  add_to_stack(frame, ref);
  return 0;
}

int aload_3(Frame *frame, Instruction instruction) {
  uint32_t ref = frame->local_variables[3];
  add_to_stack(frame, ref);
  return 0;
}




