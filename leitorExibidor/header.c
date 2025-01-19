#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atribute.h"
#include "reader.h"

ClassFile *read_class_file(char path[]) {
    if (!strstr(path, ".class")) {
        fprintf(stderr, "Arquivo não é .class\n");
        return NULL;
    }

    read_file(path);

    ClassFile *classFile = (ClassFile *)malloc(sizeof(ClassFile));
    if (!classFile) {
        fprintf(stderr, "Erro de alocação de memória\n");
        fclose(fp);
        return NULL;
    }

    classFile->magic_number = read_u32();
    if (classFile->magic_number != 0xCAFEBABE) {
        fprintf(stderr, "Magic number não bateu: %x\n", classFile->magic_number);
        fclose(fp);
        free(classFile);
        return NULL;
    }

    classFile->minor_version = read_u16();
    classFile->major_version = read_u16();

    classFile->constant_pool_count = read_u16();
    classFile->constant_pool = read_constant_pool(fp, classFile->constant_pool_count);

    classFile->access_flags = read_u16();
    classFile->this_class = read_u16();
    classFile->super_class = read_u16();

    classFile->interfaces_count = read_u16();
    classFile->interfaces = malloc(classFile->interfaces_count * sizeof(uint16_t));
    for (uint16_t i = 0; i < classFile->interfaces_count; i++) {
        classFile->interfaces[i] = read_u16();
    }

    classFile->fields_count = read_u16();
    classFile->fields = read_fields(fp, classFile->fields_count);

    classFile->methods_count = read_u16();
    classFile->methods = read_methods(fp, classFile->methods_count);

    classFile->attributes_count = read_u16();
    classFile->attributes = malloc(classFile->attributes_count * sizeof(Attribute));
    rread_attributes(field->attributes_count);

    fclose(fp);
    return classFile;
}

Constant *read_constant_pool(FILE *fp, uint16_t constant_pool_count) {
    Constant *constant_pool = malloc(constant_pool_count * sizeof(Constant));
    if (!constant_pool) {
        fprintf(stderr, "Erro de alocação de memória para constant pool\n");
        return NULL;
    }

    for (uint16_t i = 1; i < constant_pool_count; i++) {
        constant_pool[i].tag = read_u8();
        switch (constant_pool[i].tag) {
          case 7: // class
            constant->CONSTANT_Class.name_index = read_u16();
            break;
          case 9: // fieldRef
            constant->CONSTANT_Fieldref.class_index = read_u16();
            constant->CONSTANT_Fieldref.name_and_type_index = read_u16();
            break;
          case 10: // MethodRef
            constant->CONSTANT_Methodref.class_index = read_u16();
            constant->CONSTANT_Methodref.name_and_type_index = read_u16();
            break;
          case 11: // InterfaceMethod
            constant->CONSTANT_InterfaceMethodref.class_index = read_u16();
            constant->CONSTANT_InterfaceMethodref.name_and_type_index = read_u16();
            break;
          case 8: // String
            constant->CONSTANT_String.string_index = read_u16();
            break;
          case 3: // Integer
            constant->CONSTANT_Integer.bytes = read_u32();
            break;
          case 4: // Float
            constant->CONSTANT_Float.bytes = read_u32();
            break;
          case 5: // Long
            constant->CONSTANT_Long.high_bytes = read_u32();
            constant->CONSTANT_Long.low_bytes = read_u32();
            constant++;
            cp_index++;
            break;
          case 6: // Double
            constant->CONSTANT_Double.high_bytes = read_u32();
            constant->CONSTANT_Double.low_bytes = read_u32();
            constant++;
            cp_index++;
            break;
          case 12: // NameAndType
            constant->CONSTANT_NameAndType.name_index = read_u16();
            constant->CONSTANT_NameAndType.descriptor_index = read_u16();
            break;
          case 1: // utf8
            constant->CONSTANT_Utf8.length = read_u16();
            constant->CONSTANT_Utf8.bytes = (u1 *)malloc(sizeof(u1) * constant->CONSTANT_Utf8.length);
            for (int i = 0; i < constant->CONSTANT_Utf8.length; i++)
            {
              constant->CONSTANT_Utf8.bytes[i] = readU1(fp);
            }
            break;
          case 15: // MethodHandle
            constant->CONSTANT_MethodHandle.reference_kind = readU1(fp);
            constant->CONSTANT_MethodHandle.reference_index = read_u16();
            break;
          case 16: // MethodType
            constant->CONSTANT_MethodType.descriptor_index = read_u16();
            break;
          case 18: // InvokeDynamic
            constant->CONSTANT_InvokeDynamic.bootstrap_method_attr_index = read_u16();
            constant->CONSTANT_InvokeDynamic.name_and_type_index = read_u16();
      break;
            default:
                fprintf(stderr, "Tag desconhecida: %d\n", constant_pool[i].tag);
                exit(1);
        }
    }
    return constant_pool;
}

Field *read_fields(FILE *fp, uint16_t fields_count) {
    Field *fields = malloc(fields_count * sizeof(Field));
    for (uint16_t i = 0; i < fields_count; i++) {
        fields[i].access_flags = read_u16();
        fields[i].name_index = read_u16();
        fields[i].descriptor_index = read_u16();
        fields[i].attributes_count = read_u16();

        fields[i].attributes = malloc(fields[i].attributes_count * sizeof(Attribute));
        read_attributes(field->attributes_count);
    }
    return fields;
}

Method *read_methods(FILE *fp, uint16_t methods_count) {
    Method *methods = malloc(methods_count * sizeof(Method));
    for (uint16_t i = 0; i < methods_count; i++) {
        methods[i].access_flags = read_u16();
        methods[i].name_index = read_u16();
        methods[i].descriptor_index = read_u16();
        methods[i].attributes_count = read_u16();

        methods[i].attributes = malloc(methods[i].attributes_count * sizeof(Attribute));
        read_attributes(field->attributes_count);
    }
    return methods;
}

void free_class_file(ClassFile *class_file) {
    if (!class_file) return;

    free_constant_pool(class_file->constant_pool);
    free_fields(class_file->fields);
    free_methods(class_file->methods);
    free(class_file->attributes);
    free(class_file->interfaces);

    free(class_file);
}

void free_constant_pool(Constant *constant_pool) {
    if (!constant_pool) return;
    free(constant_pool);
}

void free_fields(Field *fields) {
    if (!fields) return;
    free(fields);
}

void free_methods(Method *methods) {
    if (!methods) return;
    free(methods);
}

ClassFile * get_current_class_file() {
  static ClassFile class_file;
  return &class_file;
}