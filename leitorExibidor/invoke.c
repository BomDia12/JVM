#include "invoke.h"

Arguments * get_arguments(Frame * frame, char include_this, char * method_descriptor) {
  uint16_t argument_amount = get_argument_amount(frame->this_method->descriptor_index);
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

int invoke_dynamic(Frame * frame, Instruction instruction) {
  uint16_t method_index = (((uint16_t) instruction.operands[0]) << 8) | instruction.operands[1];
  Constant * methodref = getFromConstantPool(frame->this_class, method_index);
  char * class_name = getNestedString(frame->this_class, methodref->ConstantUnion.methodref_info.class_index);
  Constant * name_and_type = getFromConstantPool(frame->this_class, methodref->ConstantUnion.methodref_info.name_and_type_index);

  char * method_name = getNestedString(frame->this_class, name_and_type->ConstantUnion.name_and_type_info.name_index);
  char * method_descriptor = getNestedString(frame->this_class, name_and_type->ConstantUnion.name_and_type_info.descriptor_index);

  Arguments * arguments = get_arguments(frame, 1, method_descriptor);

  return 0;
}
