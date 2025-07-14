#include "invoke.h"

Arguments * get_arguments(Frame * frame, char include_this, char * method_descriptor) {
  uint16_t argument_amount = get_argument_amount(method_descriptor);
  // printf("Argument amount: %d\n", argument_amount);
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
  char * class_name = getNestedString(frame->this_class, methodref->ConstantUnion.methodref_info.class_index);

  char * method_name = getNestedString(frame->this_class, name_and_type->ConstantUnion.name_and_type_info.name_index);
  if (strcmp(method_name, "<init>") == 0) {
    if (strcmp(class_name, "java/lang/Object") == 0 || strcmp(class_name, "java/lang/String") == 0 || strcmp(class_name, "java/lang/StringBuffer") == 0) {
      return 0;
    }
  }
  char * method_descriptor = getNestedString(frame->this_class, name_and_type->ConstantUnion.name_and_type_info.descriptor_index);

  // printf("Bom dia\n");
  Arguments * arguments = get_arguments(frame, include_this, method_descriptor);

  ClassFile * class_file;
  if (include_this) {
    Object * this_object = get_object(arguments->arguments[0]);
    class_file = this_object->class;
  } else {
    class_file = get_class_file(class_name);
  }
  
  if (class_file == NULL) {
    printf("Class file not found\n");
    return -1;
  }

  Method * method = get_method(class_file, method_name, method_descriptor);
  if (method == NULL) {
    printf("Method not found\n");
    printf("Method: %s %s: %s\n", class_name, method_name, method_descriptor);
    return -1;
  }

  MethodResponses res = call_method(frame, class_file, method, arguments);
  if (res.status < 0) {
    return res.status;
  }

  if (res.status == 0) {
    add_to_stack(frame, res.value);
  }

  return 0;
}

int invoke_dynamic(Frame * frame, Instruction instruction) {
  int res = common_invoke(frame, instruction, 0);
  return res;
}

int invoke_interface(Frame * frame, Instruction instruction) {
  int res = common_invoke(frame, instruction, 1);
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
  char * class_name = getNestedString(frame->this_class, methodref->ConstantUnion.methodref_info.class_index);
  if (strcmp(class_name, "java/lang/System") != 0 && strcmp(class_name, "java/lang/String") != 0 && strcmp(class_name, "java/io/PrintStream") != 0 && strcmp(class_name, "java/lang/StringBuffer") != 0) {
    return common_invoke(frame, instruction, 1);
  }
  Constant *name_and_type = getFromConstantPool(frame->this_class, methodref->ConstantUnion.methodref_info.name_and_type_index);
  char *method_name = getNestedString(frame->this_class, name_and_type->ConstantUnion.name_and_type_info.name_index);
  char *method_descriptor = getNestedString(frame->this_class, name_and_type->ConstantUnion.name_and_type_info.descriptor_index);
  if (strcmp(class_name, "java/lang/StringBuffer") == 0) {
    if (strcmp(method_name, "append") == 0) {
      return append(frame, instruction);
    }
    if (strcmp(method_name, "toString") == 0) {
      return toString(frame, instruction);
    }
    printf("método do string buffer não implementado\n");
    return -1;
  }

  if (strcmp(method_name, "println") == 0 || strcmp(method_name, "print") == 0) {
    char type = method_descriptor[1];

    switch (type) {
      case 'I': {
        int32_t value = uint32_to_int(remove_from_stack(frame));
        printf("%d", value);
        break;
      }
      case 'J': { // Tipo long
        uint64_t low = remove_from_stack(frame);
        uint64_t high = remove_from_stack(frame);
        uint64_t raw = low | (high << 32);
        int64_t value = uint64_to_long(raw);
        printf("%lld", value);
        break;
      }
      case 'F': {
        uint32_t raw = remove_from_stack(frame);

        printf("%f", uint32_to_float(raw));
        break;
      }
      case 'D': { // double
        double value;
        uint64_t low = remove_from_stack(frame);
        uint64_t high = remove_from_stack(frame);
        uint64_t raw = low | (high << 32);

        printf("%.15f", uint64_to_double(raw));
        break;
      }
      case 'C': {
        char value = remove_from_stack(frame);
        printf("%c", value);
        break;
      }
      case 'Z': {
        uint32_t value = remove_from_stack(frame);
        printf("%s", value ? "true" : "false");
        break;
      }
      case 'S': {
        uint16_t value = remove_from_stack(frame);
        printf("%d", uint16_to_short(value));
        break;
      }
      case 'B': {
        uint8_t value = remove_from_stack(frame);
        printf("%d", uint8_to_byte(value));
        break;
      }
      case 'L': {
        uint32_t ref = remove_from_stack(frame);
        Object * object = get_object(ref);
        String * string = get_string(object->fields[0]->value);
        printf("%s", string->string);
        break;
      }
      case ')':
        break;
      default: {
        printf("Tipo não suportado para println: %s\n", method_descriptor);
        break;
      }
    }

    if (strcmp(method_name, "println") == 0) {
      printf("\n");
    }

    return 0;
  }

  fprintf(stderr, "Método %s não suportado no invoke_virtual simplificado.\n", method_name);
  return -1;
}

