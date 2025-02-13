#include "reader.h"

Buffer * get_buffer() {
  static Buffer buffer;
  return &buffer;
}

Buffer * get_code_buffer() {
  static Buffer code_buffer;
  return &code_buffer;
}

void read_file(char * filename) {
  Buffer * buffer = get_buffer();

  if (buffer->buffer != NULL) {
    free(buffer->buffer);
  }

  FILE * file = fopen(filename, "rb");
  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  buffer->buffer = malloc(size);
  fread(buffer->buffer, 1, size, file);
  fclose(file);

  buffer->position = 0;
}

uint8_t read_u8() {
  Buffer * buffer = get_buffer();
  return read_u8_buffer(buffer);
}

uint8_t read_u8_buffer(Buffer * buffer) {
  uint8_t value = buffer->buffer[buffer->position];
  buffer->position++;
  return value;
}

uint16_t read_u16() {
  Buffer * buffer = get_buffer();
  return read_u16_buffer(buffer);
}

uint16_t read_u16_buffer(Buffer * buffer) {
  uint16_t value = buffer->buffer[buffer->position] << 8;
  value |= buffer->buffer[buffer->position + 1];
  buffer->position += 2;
  return value;
}

uint32_t read_u32() {
  Buffer * buffer = get_buffer();
  return read_u32_buffer(buffer);
}

uint32_t read_u32_buffer(Buffer * buffer) {
  uint32_t value = buffer->buffer[buffer->position] << 24;
  value |= buffer->buffer[buffer->position + 1] << 16;
  value |= buffer->buffer[buffer->position + 2] << 8;
  value |= buffer->buffer[buffer->position + 3];
  buffer->position += 4;
  return value;
}

void free_buffer() {
  Buffer * buffer = get_buffer();
  if (buffer->buffer != NULL) {
    free(buffer->buffer);
    buffer->buffer = NULL;
  }
}
