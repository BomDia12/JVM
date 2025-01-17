#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

// Arthur

uint8_t read_u8();
uint8_t read_u8(Buffer * buffer);
uint16_t read_u16();
uint16_t read_u16(Buffer * buffer);
uint32_t read_u32();
uint32_t read_u32(Buffer * buffer);
uint64_t read_u64();
uint64_t read_u64(Buffer * buffer);

void read_file(char* filename);

Buffer * get_buffer();
Buffer * get_code_buffer();

void free_buffer();
void free_code_buffer();

#endif