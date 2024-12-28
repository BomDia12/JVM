#include "reader.h"
#include "header.h"
#include "output.h"

int main (int argc, char *argv[]) {
  
  if (argc < 2) {
    printf("No file provided\n");
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  read_file(argv[1]);

  ClassFile * class_file = read_class_file();
  print_class_file(class_file);
  free_class_file(class_file);
  
  return 0;
}
