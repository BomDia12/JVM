#include "interpreter.h"

int run_class_file(ClassFile * class_file) {
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

  int res = call_method(&firstFrame, class_file, "main").status;
  if (res != 0) {
    printf("Erro ao executar o método main\n");
    return -1;
  }

  return 0;
}

MethodResponses call_method(Frame * current_frame, ClassFile * class_file, char * method_name) {
  MethodResponses res = {
    .status = 0,
    .value = 0,
  };
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
    res.status = -1;
    return res;
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
    res.status = -2;
    return res;
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
    int result = instruction.type->opcode_function(call_frame, instruction);
    if (result != 0) {
      // deal with responses
      if (result == 1) {
        res.value = (uint32_t) NULL;
      } else if (result == 2) {
        res.value = call_frame->local_variables->variables[0];
      }
      break;
    }
  }

  while (call_frame->stack_top != NULL) {
    Stack * stack = call_frame->stack_top->next;
    free(call_frame->stack_top);
    call_frame->stack_top = stack;
  }
  free(call_frame->local_variables);
  free(call_frame);

  return res;
}
