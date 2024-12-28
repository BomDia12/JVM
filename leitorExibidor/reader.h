#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

uint8_t read_u8();
uint16_t read_u16();
uint32_t read_u32();
uint64_t read_u64();

void read_file(char* filename);

Buffer * get_buffer();

void free_buffer();

#endif