#include "reader.h"

int main (int argc, char *argv[]) {
  
  if (argc < 2) {
    printf("No file provided\n");
    printf("Usage: %s <file>\n", argv[0]);
    return 1;
  }

  read_file(argv[1]);

  uint16_t magic = read_u16();
  printf("Magic number: %d\n", magic);

  return 0;
}
