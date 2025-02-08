#ifndef STORES_H
#define STORES_H

#include "types.h"
#include "instructions.h"

// Funções para armazenar valores nas variáveis locais
int istore(Frame *frame, Instruction instruction);
int lstore(Frame *frame, Instruction instruction);
int fstore(Frame *frame, Instruction instruction);
int dstore(Frame *frame, Instruction instruction);
int astore(Frame *frame, Instruction instruction);

// Funções para armazenar valores nas variáveis locais de índice fixo
int istore_0(Frame *frame);
int istore_1(Frame *frame);
int istore_2(Frame *frame);
int istore_3(Frame *frame);
int lstore_0(Frame *frame);
int lstore_1(Frame *frame);
int lstore_2(Frame *frame);
int lstore_3(Frame *frame);
int fstore_0(Frame *frame);
int fstore_1(Frame *frame);
int fstore_2(Frame *frame);
int fstore_3(Frame *frame);
int dstore_0(Frame *frame);
int dstore_1(Frame *frame);
int dstore_2(Frame *frame);
int dstore_3(Frame *frame);
int astore_0(Frame *frame);
int astore_1(Frame *frame);
int astore_2(Frame *frame);
int astore_3(Frame *frame);


#endif
