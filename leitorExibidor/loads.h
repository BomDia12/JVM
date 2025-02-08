#ifndef LOADS_H
#define LOADS_H

#include "types.h"
#include "instructions.h"

// Funções para carregar constantes
void load_constant_0(Frame *frame, Instruction instruction);
void load_constant_1(Frame *frame, Instruction instruction);
void load_constant_2(Frame *frame, Instruction instruction);
void load_constant_3(Frame *frame, Instruction instruction);
void load_constant_4(Frame *frame, Instruction instruction);
void load_constant_5(Frame *frame, Instruction instruction);

// Funções para carregar constantes longas e de ponto flutuante
void lconst_0(Frame *frame, Instruction instruction);
void lconst_1(Frame *frame, Instruction instruction);
void fconst_0(Frame *frame, Instruction instruction);
void fconst_1(Frame *frame, Instruction instruction);
void fconst_2(Frame *frame, Instruction instruction);
void dconst_0(Frame *frame, Instruction instruction);
void dconst_1(Frame *frame, Instruction instruction);

// Funções para carregar valores imediatos
void bipush(Frame *frame, Instruction instruction);
void sipush(Frame *frame, Instruction instruction);

// Funções para carregar constantes da pool de constantes
void ldc(Frame *frame, Instruction instruction);
void ldc_w(Frame *frame, Instruction instruction);
void ldc2_w(Frame *frame, Instruction instruction);

// Funções para carregar variáveis locais
void iload(Frame *frame, Instruction instruction);
void lload(Frame *frame, Instruction instruction);
void fload(Frame *frame, Instruction instruction);
void dload(Frame *frame, Instruction instruction);
void aload(Frame *frame, Instruction instruction);

// Funções para carregar variáveis locais de índice fixo
void iload_0(Frame *frame, Instruction instruction);
void iload_1(Frame *frame, Instruction instruction);
void iload_2(Frame *frame, Instruction instruction);
void iload_3(Frame *frame, Instruction instruction);
void lload_0(Frame *frame, Instruction instruction);
void lload_1(Frame *frame, Instruction instruction);
void lload_2(Frame *frame, Instruction instruction);
void lload_3(Frame *frame, Instruction instruction);
void fload_0(Frame *frame, Instruction instruction);
void fload_1(Frame *frame, Instruction instruction);
void fload_2(Frame *frame, Instruction instruction);
void fload_3(Frame *frame, Instruction instruction);
void dload_0(Frame *frame, Instruction instruction);
void dload_1(Frame *frame, Instruction instruction);
void dload_2(Frame *frame, Instruction instruction);
void dload_3(Frame *frame, Instruction instruction);
void aload_0(Frame *frame, Instruction instruction);
void aload_1(Frame *frame, Instruction instruction);
void aload_2(Frame *frame, Instruction instruction);
void aload_3(Frame *frame, Instruction instruction);

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

#endif // LOADS_H
