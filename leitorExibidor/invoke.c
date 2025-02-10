#include "invoke.h"

Arguments * get_arguments(Frame * frame, char include_this, char * method_descriptor) {
  uint16_t argument_amount = get_argument_amount(method_descriptor);
  if (include_this) {
    argument_amount++;
  }
  Arguments * arguments = malloc(sizeof(Arguments));
  arguments->size = argument_amount;
  arguments->arguments = malloc(sizeof(uint32_t) * argument_amount);
  for (int i = argument_amount - 1; i >= 0; i--) {
    arguments->arguments[i] = remove_from_stack(frame);
  }

  return arguments;
}

int common_invoke(Frame * frame, Instruction instruction, char include_this) {
  uint16_t method_index = (((uint16_t) instruction.operands[0]) << 8) | instruction.operands[1];
  Constant * methodref = getFromConstantPool(frame->this_class, method_index);
  Constant * name_and_type = getFromConstantPool(frame->this_class, methodref->ConstantUnion.methodref_info.name_and_type_index);

  char * method_name = getNestedString(frame->this_class, name_and_type->ConstantUnion.name_and_type_info.name_index);
  char * method_descriptor = getNestedString(frame->this_class, name_and_type->ConstantUnion.name_and_type_info.descriptor_index);

  Arguments * arguments = get_arguments(frame, include_this, method_descriptor);

  char * class_name = getNestedString(frame->this_class, methodref->ConstantUnion.methodref_info.class_index);
  char * current_class_name = getNestedString(frame->this_class, frame->this_class->this_class);
  if (strcmp(class_name, current_class_name) != 0) {
    // TODO: Implement get from other class
    return -1;
  }

  Method * method = get_method(frame->this_class, method_name, method_descriptor);
  if (method == NULL) {
    return -1;
  }

  MethodResponses res = call_method(frame, frame->this_class, method, arguments);
  if (res.status != 0) {
    return res.status;
  }

  add_to_stack(frame, res.value);

  return 0;
}

int invoke_dynamic(Frame * frame, Instruction instruction) {
  int res = common_invoke(frame, instruction, 1);
  return res;
}

int invoke_interface(Frame * frame, Instruction instruction) {
  int res = common_invoke(frame, instruction, 0);
  return res;
}

int invoke_special(Frame * frame, Instruction instruction) {
  int res = common_invoke(frame, instruction, 1);
  return res;
}

int invoke_static(Frame * frame, Instruction instruction) {
  int res = common_invoke(frame, instruction, 0);
  return res;
}

int invoke_virtual(Frame *frame, Instruction instruction) {
  uint16_t method_index = (((uint16_t) instruction.operands[0]) << 8) | instruction.operands[1];

  Constant *methodref = getFromConstantPool(frame->this_class, method_index);
  Constant *name_and_type = getFromConstantPool(frame->this_class, methodref->ConstantUnion.methodref_info.name_and_type_index);
  char *method_name = getNestedString(frame->this_class, name_and_type->ConstantUnion.name_and_type_info.name_index);
  char *method_descriptor = getNestedString(frame->this_class, name_and_type->ConstantUnion.name_and_type_info.descriptor_index);

  if (strcmp(method_name, "println") == 0) {
    char type = method_descriptor[1];

    switch (type) {
      case 'I': {
        uint32_t value = remove_from_stack(frame);
        printf("%d\n", value);
        break;
      }
      case 'J': { // Tipo long
        uint32_t high = constant->ConstantUnion.long_info.high_bytes;
        uint32_t low = constant->ConstantUnion.long_info.low_bytes;
        printf("Long: High = %d, Low = %d\n", high, low);
        break;
      }
      case 'F': {
        int32_t raw = remove_from_stack(frame);
        float value;

        memcpy(&value, &raw, sizeof(float));

        printf("%f\n", value);
        break;
      }
      case 'D': { // double
        double value;
        uint32_t high = remove_from_stack(frame);
        uint32_t low = remove_from_stack(frame);
        uint32_t raw[2] = {low, high};

        memcpy(&value, raw, sizeof(double));

        printf("%lf\n", value);
        break;
      }
      case 'C': {
          uint16_t value = remove_from_stack(frame);
          printf("%c\n", (char)value);
          break;
      }
      case 'Z': {
          uint32_t value = remove_from_stack(frame);
          printf("%s\n", value ? "true" : "false");
          break;
      }
      case 'S': {
          uint16_t value = remove_from_stack(frame);
          printf("%d\n", (int16_t)value);
          break;
      }
      case 'B': { 
          uint8_t value = remove_from_stack(frame);
          printf("%d\n", (int8_t)value);
          break;
      }
      case 'L': { 
          
          break;
      }
      default:
          printf("Tipo não suportado para println: %c\n", type);
          break;
    }

    remove_from_stack(frame);
    return 0;
  }

  fprintf(stderr, "Método %s não suportado no invoke_virtual simplificado.\n", method_name);
  return -1;
}

