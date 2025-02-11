#ifndef LOADS_H
#define LOADS_H

#include "types.h"
#include "instructions.h"
#include "conversions.h"
#include "string.h"
#include "header.h" 

// Funções para carregar constantes
int aconst_null(Frame * frame, Instruction instruction);
int load_constant_m1(Frame * frame, Instruction instruction);
int load_constant_0(Frame *frame, Instruction instruction);
int load_constant_1(Frame *frame, Instruction instruction);
int load_constant_2(Frame *frame, Instruction instruction);
int load_constant_3(Frame *frame, Instruction instruction);
int load_constant_4(Frame *frame, Instruction instruction);
int load_constant_5(Frame *frame, Instruction instruction);

// Funções para carregar constantes longas e de ponto flutuante
int lconst_0(Frame *frame, Instruction instruction);
int lconst_1(Frame *frame, Instruction instruction);
int fconst_0(Frame *frame, Instruction instruction);
int fconst_1(Frame *frame, Instruction instruction);
int fconst_2(Frame *frame, Instruction instruction);
int dconst_0(Frame *frame, Instruction instruction);
int dconst_1(Frame *frame, Instruction instruction);

// Funções para carregar constantes da pool de constantes
int ldc(Frame *frame, Instruction instruction);
int ldc_w(Frame *frame, Instruction instruction);
int ldc2_w(Frame *frame, Instruction instruction);

// Funções para carregar variáveis locais
int iload(Frame *frame, Instruction instruction);
int lload(Frame *frame, Instruction instruction);
int fload(Frame *frame, Instruction instruction);
int dload(Frame *frame, Instruction instruction);
int aload(Frame *frame, Instruction instruction);

// Funções para carregar variáveis locais de índice fixo
int iload_0(Frame *frame, Instruction instruction);
int iload_1(Frame *frame, Instruction instruction);
int iload_2(Frame *frame, Instruction instruction);
int iload_3(Frame *frame, Instruction instruction);
int lload_0(Frame *frame, Instruction instruction);
int lload_1(Frame *frame, Instruction instruction);
int lload_2(Frame *frame, Instruction instruction);
int lload_3(Frame *frame, Instruction instruction);
int fload_0(Frame *frame, Instruction instruction);
int fload_1(Frame *frame, Instruction instruction);
int fload_2(Frame *frame, Instruction instruction);
int fload_3(Frame *frame, Instruction instruction);
int dload_0(Frame *frame, Instruction instruction);
int dload_1(Frame *frame, Instruction instruction);
int dload_2(Frame *frame, Instruction instruction);
int dload_3(Frame *frame, Instruction instruction);
int aload_0(Frame *frame, Instruction instruction);
int aload_1(Frame *frame, Instruction instruction);
int aload_2(Frame *frame, Instruction instruction);
int aload_3(Frame *frame, Instruction instruction);

#endif
