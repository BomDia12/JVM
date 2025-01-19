#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções auxiliares de leitura
uint32_t readU4(FILE *fp);
uint16_t readU2(FILE *fp);
uint8_t readU1(FILE *fp);

// Implementação das funções principais
ClassFile *read_class_file(char path[]) {
    if (!strstr(path, ".class")) {
        fprintf(stderr, "Arquivo não é .class\n");
        return NULL;
    }

    FILE *fp = fopen(path, "rb");
    if (!fp) {
        fprintf(stderr, "Não foi possível abrir o arquivo\n");
        return NULL;
    }

    ClassFile *classFile = (ClassFile *)malloc(sizeof(ClassFile));
    if (!classFile) {
        fprintf(stderr, "Erro de alocação de memória\n");
        fclose(fp);
        return NULL;
    }

    classFile->magic_number = readU4(fp);
    if (classFile->magic_number != 0xCAFEBABE) {
        fprintf(stderr, "Magic number não bateu: %x\n", classFile->magic_number);
        fclose(fp);
        free(classFile);
        return NULL;
    }

    classFile->minor_version = readU2(fp);
    classFile->major_version = readU2(fp);

    classFile->constant_pool_count = readU2(fp);

    classFile->constant_pool = read_constant_pool(fp, classFile->constant_pool_count);

    classFile->access_flags = readU2(fp);
    classFile->this_class = readU2(fp);
    classFile->super_class = readU2(fp);

    classFile->interfaces_count = readU2(fp);
 
    classFile->interfaces = malloc(classFile->interfaces_count * sizeof(uint16_t));
    for (uint16_t i = 0; i < classFile->interfaces_count; i++) {
        classFile->interfaces[i] = readU2(fp);
    }

    classFile->fields_count = readU2(fp);
    classFile->fields = read_fields(fp, classFile->fields_count);

    // Leitura de métodos
    classFile->methods_count = readU2(fp);
    classFile->methods = read_methods(fp, classFile->methods_count);

    // Leitura de atributos
    classFile->attributes_count = readU2(fp);
    classFile->attributes = malloc(classFile->attributes_count * sizeof(Attribute));
    read_attributes(fp, classFile->attributes, classFile->attributes_count);

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
        constant_pool[i].tag = readU1(fp);
        switch (constant_pool[i].tag) {
          case 7: // class
            constant->CONSTANT_Class.name_index = readU2(fp);
            break;
          case 9: // fieldRef
            constant->CONSTANT_Fieldref.class_index = readU2(fp);
            constant->CONSTANT_Fieldref.name_and_type_index = readU2(fp);
            break;
          case 10: // MethodRef
            constant->CONSTANT_Methodref.class_index = readU2(fp);
            constant->CONSTANT_Methodref.name_and_type_index = readU2(fp);
            break;
          case 11: // InterfaceMethod
            constant->CONSTANT_InterfaceMethodref.class_index = readU2(fp);
            constant->CONSTANT_InterfaceMethodref.name_and_type_index = readU2(fp);
            break;
          case 8: // String
            constant->CONSTANT_String.string_index = readU2(fp);
            break;
          case 3: // Integer
            constant->CONSTANT_Integer.bytes = readU4(fp);
            break;
          case 4: // Float
            constant->CONSTANT_Float.bytes = readU4(fp);
            break;
          case 5: // Long
            constant->CONSTANT_Long.high_bytes = readU4(fp);
            constant->CONSTANT_Long.low_bytes = readU4(fp);
            constant++;
            cp_index++;
            break;
          case 6: // Double
            constant->CONSTANT_Double.high_bytes = readU4(fp);
            constant->CONSTANT_Double.low_bytes = readU4(fp);
            constant++;
            cp_index++;
            break;
          case 12: // NameAndType
            constant->CONSTANT_NameAndType.name_index = readU2(fp);
            constant->CONSTANT_NameAndType.descriptor_index = readU2(fp);
            break;
          case 1: // utf8
            constant->CONSTANT_Utf8.length = readU2(fp);
            constant->CONSTANT_Utf8.bytes = (u1 *)malloc(sizeof(u1) * constant->CONSTANT_Utf8.length);
            for (int i = 0; i < constant->CONSTANT_Utf8.length; i++)
            {
              constant->CONSTANT_Utf8.bytes[i] = readU1(fp);
            }
            break;
          case 15: // MethodHandle
            constant->CONSTANT_MethodHandle.reference_kind = readU1(fp);
            constant->CONSTANT_MethodHandle.reference_index = readU2(fp);
            break;
          case 16: // MethodType
            constant->CONSTANT_MethodType.descriptor_index = readU2(fp);
            break;
          case 18: // InvokeDynamic
            constant->CONSTANT_InvokeDynamic.bootstrap_method_attr_index = readU2(fp);
            constant->CONSTANT_InvokeDynamic.name_and_type_index = readU2(fp);
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
        fields[i].access_flags = readU2(fp);
        fields[i].name_index = readU2(fp);
        fields[i].descriptor_index = readU2(fp);
        fields[i].attributes_count = readU2(fp);

        fields[i].attributes = malloc(fields[i].attributes_count * sizeof(Attribute));
        read_attributes(fp, fields[i].attributes, fields[i].attributes_count);
    }
    return fields;
}

Method *read_methods(FILE *fp, uint16_t methods_count) {
    Method *methods = malloc(methods_count * sizeof(Method));
    for (uint16_t i = 0; i < methods_count; i++) {
        methods[i].access_flags = readU2(fp);
        methods[i].name_index = readU2(fp);
        methods[i].descriptor_index = readU2(fp);
        methods[i].attributes_count = readU2(fp);

        methods[i].attributes = malloc(methods[i].attributes_count * sizeof(Attribute));
        read_attributes(fp, methods[i].attributes, methods[i].attributes_count);
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

// Funções de leitura auxiliar
uint32_t readU4(FILE *fp) { uint32_t value; fread(&value, sizeof(uint32_t), 1, fp); return __builtin_bswap32(value); }
uint16_t readU2(FILE *fp) { uint16_t value; fread(&value, sizeof(uint16_t), 1, fp); return __builtin_bswap16(value); }
uint8_t readU1(FILE *fp) { uint8_t value; fread(&value, sizeof(uint8_t), 1, fp); return value; }
