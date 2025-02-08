#ifndef STORES_H
#define STORES_H

#include "types.h"
#include "instructions.h"

// Funções para armazenar valores nas variáveis locais
void istore(Frame *frame, Instruction instruction);
void lstore(Frame *frame, Instruction instruction);
void fstore(Frame *frame, Instruction instruction);
void dstore(Frame *frame, Instruction instruction);
void astore(Frame *frame, Instruction instruction);

// Funções para armazenar valores nas variáveis locais de índice fixo
void istore_0(Frame *frame);
void istore_1(Frame *frame);
void istore_2(Frame *frame);
void istore_3(Frame *frame);
void lstore_0(Frame *frame);
void lstore_1(Frame *frame);
void lstore_2(Frame *frame);
void lstore_3(Frame *frame);
void fstore_0(Frame *frame);
void fstore_1(Frame *frame);
void fstore_2(Frame *frame);
void fstore_3(Frame *frame);
void dstore_0(Frame *frame);
void dstore_1(Frame *frame);
void dstore_2(Frame *frame);
void dstore_3(Frame *frame);
void astore_0(Frame *frame);
void astore_1(Frame *frame);
void astore_2(Frame *frame);
void astore_3(Frame *frame);


#endif
