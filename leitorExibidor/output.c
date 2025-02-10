#include <stdio.h>
#include "output.h"
#include "reader.h"

void print_class_file(ClassFile * class_file) {
  printf("assinatura: 0x%x\n", class_file->magic);
  printf("Versão: %d.%d\n", class_file->major_version, class_file->minor_version);
  printf("número de entradas no pool de constantes: %d\n", class_file->constant_pool_count);
  printf("flags de acesso: %d\n", class_file->access_flags);
  print_classfile_access_flags_translation(class_file->access_flags);
  printf("índice da classe: %d\n", class_file->this_class);
  printf("índice da super classe: %d\n", class_file->super_class);
  printf("número de superinterfaces diretas: %d\n", class_file->interfaces_count);
  printf("número de fields: %d\n", class_file->fields_count);
  printf("número de methods: %d\n", class_file->methods_count);
  printf("número de attributes: %d\n", class_file->attributes_count);

  print_title("Pool de constantes:");
  for (int i = 0; i < (class_file->constant_pool_count - 1); i++) {
    print_constant_pool(class_file->constant_pool[i], i + 1);
  }


  print_title("Fields");
  for (int i = 0; i < class_file->fields_count; i++) {
    printf("Field %d:\n", i);
    print_fields(class_file->fields[i]);
  }

  print_title("Methods");
  for (int i = 0; i < class_file->methods_count; i++) {
    printf("Método %d:\n", i);
    print_methods(class_file->methods[i]);
  }

  print_title("Atributos de classe");
  for (int i = 0; i < class_file->attributes_count; i++) {
    printf("Atributo %d:\n", i);
    print_attributes(class_file->attributes[i]);
  }
}

void print_divider() {
  printf("================================================================================\n");
}

void print_title(const char * string) {
  printf("\n");
  print_divider();
  printf("\n%s\n\n", string);
  print_divider();
  printf("\n");
}

void print_constant_pool(Constant * constant, uint32_t index) {
  Constant * cp = constant;
  printf("Index: %d\n", index);
  switch (cp->tag) {
    case 1:
      printf("CONSTANT_Utf8_info\n");
      printf("Tamanho: %d\n", cp->ConstantUnion.utf8_info.length);
      printf("String: %s\n", cp->ConstantUnion.utf8_info.bytes);
      break;
    case 3:
      printf("CONSTANT_Integer_info\n");
      printf("Valor: %d\n", cp->ConstantUnion.integer_info.bytes);
      break;
    case 4:
      printf("CONSTANT_Float_info\n");
      printf("Valor: %f\n", (float)cp->ConstantUnion.float_info.bytes);
      break;
    case 5:
      printf("CONSTANT_Long_info\n");
      printf("Valor: %ld\n", (long)cp->ConstantUnion.long_info.high_bytes | cp->ConstantUnion.long_info.low_bytes);
      break;
    case 6:
      printf("CONSTANT_Double_info\n");
      printf("Valor: %lf\n", (double)((((long long) cp->ConstantUnion.double_info.high_bytes) << 32) | cp->ConstantUnion.double_info.low_bytes));
      break;
    case 7:
      printf("CONSTANT_Class_info\n");
      printf("Index: %d\n", cp->ConstantUnion.class_info.name_index);
      break;
    case 8:
      printf("CONSTANT_String_info\n");
      printf("referencia: %d\n", cp->ConstantUnion.string_info.string_index);
      break;
    case 9:
      printf("CONSTANT_Fieldref_info\n");
      printf("Index da classe: %d\n", cp->ConstantUnion.fieldref_info.class_index);
      printf("Index de nome e tipo: %d\n", cp->ConstantUnion.fieldref_info.name_and_type_index);
      break;
    case 10:
      printf("CONSTANT_Methodref_info\n");
      printf("Index da classe: %d\n", cp->ConstantUnion.methodref_info.class_index);
      printf("Index de nome e tipo: %d\n", cp->ConstantUnion.methodref_info.name_and_type_index);
      break;
    case 11:
      printf("CONSTANT_InterfaceMethodref_info\n");
      printf("Index da classe: %d\n", cp->ConstantUnion.interface_methodref_info.class_index);
      printf("Index de nome e tipo: %d\n", cp->ConstantUnion.interface_methodref_info.name_and_type_index);
      break;
    case 12:
      printf("CONSTANT_NameAndType_info\n");
      printf("Index de nome: %d\n", cp->ConstantUnion.name_and_type_info.name_index);
      printf("Index de tipo: %d\n", cp->ConstantUnion.name_and_type_info.descriptor_index);
      break;
    default:
      break;
  }
}

void print_fields(Field * fields) {
  printf("Flags de acesso: %d\n", fields->access_flags);
  print_fields_access_flags_translation(fields->access_flags);
  printf("Index de nome: %d\n", fields->name_index);
  printf("Index de tipo: %d\n", fields->descriptor_index);
  printf("Número de atributos: %d\n", fields->attributes_count);
  if (fields->attributes_count > 0) {
    print_title("Attributes");
    for (int i = 0; i < fields->attributes_count; i++) {
      printf("Atributo %d:\n", i);
      print_attributes(fields->attributes[i]);
    }
  }
}

void print_methods(Method * methods) {
  printf("Flags de acesso: %d\n", methods->access_flags);
  print_methods_access_flags_translation(methods->access_flags);
  printf("Index de nome: %d\n", methods->name_index);
  printf("Index de tipo: %d\n", methods->descriptor_index);
  printf("Numero de atributos: %d\n", methods->attributes_count);
  if (methods->attributes_count > 0) {
    print_title("Attributes");
    for (int i = 0; i < methods->attributes_count; i++) {
      printf("Atributo %d:\n", i);
      print_attributes(methods->attributes[i]);
    }
    printf("\n");
    print_divider();
    printf("\n");
  }
}

void print_attributes(Attribute * attributes) {
  const char * type_names[5] = {"Não implementado","ConstantValue", "Code", "Exceptions", "InnerClasses"};

  printf("Index de nome: %d\n", attributes->attribute_name_index);
  printf("Tamanho: %d\n", attributes->attribute_length);
  printf("Tipo de atributo: %s\n", type_names[attributes->attribute_type]);
  
  // If it's a code attribute
  if (attributes->attribute_type == 2) {
    printf("Profundidade máxima da pilha de operandos: %d\n", attributes->attribute_union.code_attribute.max_stack);
    printf("Número de variáveis locais: %d\n", attributes->attribute_union.code_attribute.max_locals);
    printf("Número de bytes no array code: %d\n", attributes->attribute_union.code_attribute.code_length);
    
    printf("Código:\n");
    print_code(attributes->attribute_union.code_attribute);

    printf("Número de tabelas de exceções: %d\n", attributes->attribute_union.code_attribute.exception_table_length);
    printf("Tabelas de exceções: %p\n", attributes->attribute_union.code_attribute.exception_table);
    printf("Número de atributos: %d\n", attributes->attribute_union.code_attribute.attributes_count);
  }

  // If it's a constant value attribute
  if (attributes->attribute_type == 1) {
    printf("Index da constante: %d\n", attributes->attribute_union.constantvalue_attribute.constantvalue_index);
  }

  // If it's an exception attribute
  if (attributes->attribute_type == 3) {
    printf("Numero de exceções: %d\n", attributes->attribute_union.exceptions_attribute.number_of_exceptions);
    printf("Índice da tabela de exceções: %p\n", attributes->attribute_union.exceptions_attribute.exception_index_table);
  }

  // If it's an inner classes attribute
  if (attributes->attribute_type == 4) {
    printf("Numero de classes: %d\n", attributes->attribute_union.innerclasses_attribute.number_of_classes);
    printf("Classes:\n");
    for (int i = 0; i < attributes->attribute_union.innerclasses_attribute.number_of_classes; i++) {
      printf("Inner class info index: %d\n", attributes->attribute_union.innerclasses_attribute.classes[i].inner_class_info_index);
      printf("Outer class info index: %d\n", attributes->attribute_union.innerclasses_attribute.classes[i].outer_class_info_index);
      printf("Inner name index: %d\n", attributes->attribute_union.innerclasses_attribute.classes[i].inner_name_index);
      printf("Inner class access flags: %d\n", attributes->attribute_union.innerclasses_attribute.classes[i].inner_class_access_flags);
      print_inner_classes_access_flags_translation(attributes->attribute_union.innerclasses_attribute.classes[i].inner_class_access_flags);
    }
  }
}

void print_code(CodeAttribute code) {
  Buffer * code_buffer = get_code_buffer();
  code_buffer->position = 0;
  code_buffer->buffer = code.code;
  print_title("Seção de código");
  int i = 0;
  while (code_buffer->position < code.code_length) {
    i++;
    Instruction instruction = read_instruction();
    print_instruction(instruction, i);
    if (instruction.type->opcode == 0xc4) {
      // TODO: Print wide
    }
  }
  printf("\n");
  print_divider();
  printf("\n");
};

void print_instruction(Instruction instruction, int i) {
  printf("Opcode: %d\n", instruction.type->opcode);
  printf("Mnemônico: %s\n", instruction.type->mnemonic);
  if (instruction.type->operand_count > 0) {
    printf("Operandos: ");
    for (int i = 0; i < instruction.type->operand_count; i++) {
      printf("%d ", instruction.operands[i]);
    }
    printf("\n");
  }
}

void print_classfile_access_flags_translation(uint16_t access_flags) {
    switch (access_flags & 0x000f) {
      case 0x0001:
        printf("ACC_PUBLIC\n");
        break;
      default:
        break;
    }
    
    switch (access_flags & 0x00f0) {
      case 0x0010:
        printf("ACC_FINAL\n");
        break;
      case 0x0020:
        printf("ACC_SUPER\n");
        break;
      default:
        break;
    }

    switch (access_flags & 0x0f00) {
      case 0x0200:
        printf("ACC_INTERFACE\n");
        break;
      case 0x0400:
        printf("ACC_ABSTRACT\n");
        break;
      default:
        break;
    }

    switch (access_flags & 0xf000) {
      case 0x1000:
        printf("ACC_SYNTHETIC\n");
        break;
      case 0x2000:
        printf("ACC_ANNOTATION\n");
        break;
      case 0x4000:
        printf("ACC_ENUM\n");
        break;
      default:
        break;
    }
}

void print_fields_access_flags_translation(uint16_t access_flags) {
  switch (access_flags & 0x000f) {
    case 0x0001:
      printf("ACC_PUBLIC\n");
      break;
    case 0x0002:
      printf("ACC_PRIVATE\n");
      break;
    case 0x0004:
      printf("ACC_PROTECTED\n");
      break;
    case 0x0008:
      printf("ACC_STATIC\n");
      break;
    default:
      break;
  }

  switch (access_flags & 0x00f0) {
    case 0x0010:
      printf("ACC_FINAL\n");
      break;
    case 0x0040:
      printf("ACC_VOLATILE\n");
      break;
    case 0x0080:
      printf("ACC_TRANSIENT\n");
      break;
    default:
      break;
  }

  switch (access_flags & 0xf000) {
    case 0x1000:
      printf("ACC_SYNTHETIC\n");
      break;
    case 0x4000:
      printf("ACC_ENUM\n");
      break;
    default:
      break;
  }
}

void print_methods_access_flags_translation(uint16_t access_flags) {
  switch (access_flags & 0x000f) {
    case 0x0001:
      printf("ACC_PUBLIC\n");
      break;
    case 0x0002:
      printf("ACC_PRIVATE\n");
      break;
    case 0x0004:
      printf("ACC_PROTECTED\n");
      break;
    case 0x0008:
      printf("ACC_STATIC\n");
      break;
    default:
      break;
  }

  switch (access_flags & 0x00f0) {
    case 0x0010:
      printf("ACC_FINAL\n");
      break;
    case 0x0020:
      printf("ACC_SYNCHRONIZED\n");
      break;
    case 0x0040:
      printf("ACC_BRIDGE\n");
      break;
    case 0x0080:
      printf("ACC_VARARGS\n");
      break;
    default:
      break;
  }

  switch (access_flags & 0x0f00) {
    case 0x0100:
      printf("ACC_NATIVE\n");
      break;
    case 0x0400:
      printf("ACC_ABSTRACT\n");
      break;
    case 0x0800:
      printf("ACC_STRICT\n");
      break;
    default:
      break;
  }

  switch (access_flags & 0xf000) {
    case 0x1000:
      printf("ACC_SYNTHETIC\n");
      break;
    default:
      break;
  }
}

void print_inner_classes_access_flags_translation(uint16_t access_flags) {
  switch (access_flags & 0x000f) {
    case 0x0001:
      printf("ACC_PUBLIC\n");
      break;
    case 0x0002:
      printf("ACC_PRIVATE\n");
      break;
    case 0x0004:
      printf("ACC_PROTECTED\n");
      break;
    case 0x0008:
      printf("ACC_STATIC\n");
      break;
    default:
      break;
  }

  switch (access_flags & 0x00f0) {
    case 0x0010:
      printf("ACC_FINAL\n");
      break;
    default:  
      break;
  }

  switch (access_flags & 0x0f00) {
    case 0x0200:
      printf("ACC_INTERFACE\n");
      break;
    case 0x0400:
      printf("ACC_ABSTRACT\n");
      break;
    default:
      break;
  }
}

const char * get_version(uint16_t major) {
  const char * versions[] = {
    "JDK 1.1",
    "JDK 1.2",
    "JDK 1.3",
    "JDK 1.4",
    "Java SE 5.0",
    "Java SE 6.0",
    "Java SE 7",
    "Java SE 8",
    "Java SE 9",
    "Java SE 10",
    "Java SE 11",
    "Java SE 12",
    "Java SE 13",
    "Java SE 14",
    "Java SE 15",
    "Java SE 16",
    "Java SE 17",
    "Java SE 18"
  };

  return versions[major - 45];
}

int instance_of(Frame * frame, Instruction instruction) {
  uint16_t index = (((uint16_t) instruction.operands[0]) << 8) | instruction.operands[1];
  char * class_name = getNestedString(frame->this_class, index);
  Object * object = get_object(remove_from_stack(frame));
  char * object_class_name = getNestedString(object->class, object->fields[0]->field->name_index);

  if (strcmp(class_name, object_class_name) == 0) {
    add_to_stack(frame, int_to_uint32(1));
  } else {
    add_to_stack(frame, int_to_uint32(0));
  }

  return 0;
}

int checkcast(Frame * frame, Instruction instruction) {
  uint16_t index = (((uint16_t) instruction.operands[0]) << 8) | instruction.operands[1];
  char * class_name = getNestedString(frame->this_class, index);
  uint32_t ref = remove_from_stack(frame);
  Object * object = get_object(ref);
  if (object == NULL) {
    add_to_stack(frame, ref);
    return 0;
  }
  char * object_class_name = getNestedString(object->class, object->fields[0]->field->name_index);

  if (strcmp(class_name, object_class_name) != 0) {
    return -9;
  } else {
    add_to_stack(frame, ref);
  }

  return 0;
}

int athrow(Frame * frame, Instruction instruction) {
  return -10;
}
