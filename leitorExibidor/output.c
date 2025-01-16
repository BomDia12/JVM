#include <stdio.h>
#include "output.h"

void print_class_file(ClassFile * class_file) {
  printf("assinatura: 0x%x\n", class_file->magic);
  printf("Versão: %d.%d\n", class_file->major_version, class_file->minor_version);
  printf("número de entradas no pool de constantes: %d\n", class_file->constant_pool_count);
  printf("endereço do pool de constantes: %p\n", class_file->constant_pool);
  printf("flags de acesso: %d\n", class_file->access_flags);
  // TODO: printar interpretação das flags de acesso
  print_access_flags_translation(class_file->access_flags);
  printf("índice da classe: %d\n", class_file->this_class);
  printf("índice da super classe: %d\n", class_file->super_class);
  printf("número de superinterfaces diretas: %d\n", class_file->interfaces_count);
  printf("endereço do array de interfaces: %p\n", class_file->interfaces);
  printf("número de fields: %d\n", class_file->fields_count);
  printf("endereço do array de fields: %p\n", class_file->fields);
  printf("número de methods: %d\n", class_file->methods_count);
  printf("endereço do array de methods: %p\n", class_file->methods);
  printf("número de attributes: %d\n", class_file->attributes_count);
  printf("endereço do array de attributes: %p\n", class_file->attributes);

  printf("Pool de constantes:\n");
  for (int i = 1; i < class_file->constant_pool_count; i++) {
    print_constant_pool(class_file->constant_pool + i);
  }
}

void print_constant_pool(Constant * constant_pool) {
  switch (cp->tag) {
    case 1:
      printf("CONSTANT_Utf8_info\n");
      printf("Tamanho: %d\n", cp->utf8_info.length);
      printf("String: %s\n", cp->utf8_info.bytes);
      break;
    case 3:
      printf("CONSTANT_Integer_info\n");
      printf("Valor: %d\n", cp->integer_info.bytes);
      break;
    case 4:
      printf("CONSTANT_Float_info\n");
      printf("Valor: %f\n", cp->float_info.bytes);
      break;
    case 5:
      printf("CONSTANT_Long_info\n");
      printf("Valor: %ld\n", (cp->long_info.high_bytes << 32) | cp->long_info.low_bytes);
      break;
    case 6:
      printf("CONSTANT_Double_info\n");
      printf("Valor: %lf\n", (cp->double_info.high_bytes << 32) | cp->double_info.low_bytes);
      break;
    case 7:
      printf("CONSTANT_Class_info\n");
      printf("Index: %d\n", cp->class_info.name_index);
      break;
    case 8:
      printf("CONSTANT_String_info\n");
      printf("Index: %d\n", cp->string_info.string_index);
      break;
    case 9:
      printf("CONSTANT_Fieldref_info\n");
      printf("Index da classe: %d\n", cp->fieldref_info.class_index);
      printf("Index de nome e tipo: %d\n", cp->fieldref_info.name_and_type_index);
      break;
    case 10:
      printf("CONSTANT_Methodref_info\n");
      printf("Index da classe: %d\n", cp->methodref_info.class_index);
      printf("Index de nome e tipo: %d\n", cp->methodref_info.name_and_type_index);
      break;
    case 11:
      printf("CONSTANT_InterfaceMethodref_info\n");
      printf("Index da classe: %d\n", cp->interface_methodref_info.class_index);
      printf("Index de nome e tipo: %d\n", cp->interface_methodref_info.name_and_type_index);
      break;
    case 12:
      printf("CONSTANT_NameAndType_info\n");
      printf("Index de nome: %d\n", cp->name_and_type_info.name_index);
      printf("Index de tipo: %d\n", cp->name_and_type_info.signature_index);
      break;
    default:
      break;
  }
}

void print_fields(Field * fields) {}

void print_methods(Method * methods) {}

void print_attributes(Attribute * attributes) {}

void print_access_flags_translation(uint16_t access_flags) {
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