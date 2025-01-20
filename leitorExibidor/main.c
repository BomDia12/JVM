#include "reader.h"
#include "header.h"
#include "output.h"
#include <stdio.h>

int main (int argc, char *argv[]) {
  
  if (argc < 2) {
    printf("No file provided\n");
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  read_file(argv[1]);
  printf("ANTES DO HEADER\n");

  ClassFile * class_file = read_class_file();
  printf("ANTES DO PRINT\n");
  print_class_file(class_file);

  free_class_file(class_file);
  free_buffer();
  free_code_buffer();
  
  return 0;
}
