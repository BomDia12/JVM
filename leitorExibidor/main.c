#include "reader.h"
#include "header.h"
#include "output.h"
#include "interpreter.h"
#include "string.h"

int main (int argc, char *argv[]) {
  
  if (argc < 2) {
    printf("No file provided\n");
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }
  

  read_file(argv[1]);

  ClassFile * class_file = read_class_file();
  pushToClassFileList(class_file);

  if (argc > 3) {
    if (strcmp(argv[3], "-show") == 0) {
      print_class_file(class_file);

      free_class_file(class_file);
      free_buffer();
      return 0;
    }
  }

  int res = run_class_file(class_file);

  free_class_file(class_file);
  free_buffer();
  free_array_list(get_array_list());
  free_string_list(get_string_list());
  
  return res;
}
