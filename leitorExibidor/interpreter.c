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

void call_method(Frame * frame, ClassFile * class_file, uint16_t index) {
  Frame * call_frame;
  if (frame->next != NULL) {
    call_frame = malloc(sizeof(Frame));
    call_frame->next = frame;
  } else {
    call_frame = frame;
  }

  
}
