#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

// Arthur

uint8_t read_u8();
uint8_t read_u8_buffer(Buffer * buffer);
uint16_t read_u16();
uint16_t read_u16_buffer(Buffer * buffer);
uint32_t read_u32();
uint32_t read_u32_buffer(Buffer * buffer);

void read_file(char* filename);

Buffer * get_buffer();
Buffer * get_code_buffer();



void free_buffer();

#endif