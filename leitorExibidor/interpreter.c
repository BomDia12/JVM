#include "interpreter.h"

void run_class_file(ClassFile * class_file) {
  uint16_t this_class = class_file->this_class;
  Constant * super = getNestedString(class_file, class_file->super_class);
  char * super_name = super->ConstantUnion.utf8_info.bytes;

  if (strcmp(super_name, "java/lang/Object") != 0) {
    read_file(strcat("exemplos/", strcat(super_name, ".class")));
    ClassFile * super_class_file = read_class_file();
    class_file->super_class_object = super_class_file;
    pushToClassFileBuffer(super_class_file);
  }

  // TODO: Load interfaces
  // TODO: Load static fields
  Frame firstFrame = {
    .this_class = class_file,
    .this_method = NULL,
    .stack_top = NULL,
    .stack_size = 0,
    .next = NULL,
  };

  for (int i = 0; i < class_file->methods_count; i++) {
    Method * method = class_file->methods[i];
    char * method_name = getNestedString(class_file, method->name_index)->ConstantUnion.utf8_info.bytes;
  }
}

uint32_t call_method(Frame * current_frame, ClassFile * class_file, char * method_name) {
  Frame * call_frame;
  if (current_frame->next != NULL) {
    call_frame = malloc(sizeof(Frame));
    call_frame->next = current_frame;
  } else {
    call_frame = current_frame;
  }

  Method * method = get_method(class_file, method_name);
  if (method == NULL) {
    printf("Method not found\n");
    return -1;
  }

  Attribute * code_attribute;
  for (int i = 0; i < method->attributes_count; i++) {
    Attribute * attribute = method->attributes[i];
    if (attribute->attribute_type == 2) {
      code_attribute = attribute;
      break;
    }
  }

  if (code_attribute == NULL) {
    printf("Code attribute not found\n");
    return -2;
  }

  call_frame->this_class = class_file;
  call_frame->this_method = method;
  call_frame->stack_top = NULL;
  call_frame->stack_size = 0;
  call_frame->local_variables = malloc(sizeof(LocalVariables) * code_attribute->attribute_union.code_attribute.max_locals);

  call_frame->pc.position = 0;
  call_frame->pc.buffer = code_attribute->attribute_union.code_attribute.code;
  for (; call_frame->pc.position < code_attribute->attribute_union.code_attribute.code_length; call_frame->pc.position++) {
    Instruction instruction = read_instruction_buffer(&call_frame->pc);
    int res = instruction.type->opcode_function(call_frame, instruction);
    if (res != 0) {
      // deal with responses
      return res;
    }
  }

  return 0;
}
