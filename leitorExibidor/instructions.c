#include "instructions.h"

void load_constant(Frame * frame, Instruction instruction) {
  add_to_stack(frame, 0);
}

void add_to_stack(Frame * frame, uint32_t value) {
  Stack * stack = malloc(sizeof(Stack));
  stack->self = value;
  stack->next = frame->stack_top;
  frame->stack_top = stack;
}

uint32_t remove_from_stack(Frame * frame) {
  Stack * stack = frame->stack_top;
  uint32_t value = stack->self;
  frame->stack_top = stack->next;
  free(stack);
  return value;
}

void i2l(Frame * frame, Instruction Instruction) {
  uint32_t oi = remove_from_stack(frame);
  if (oi > 0x7fffffff) {
    add_to_stack(frame, 0xffffffff);
  } else {
    add_to_stack(frame, 0);
  }
  add_to_stack(frame, oi);
}

int32_t uint32_to_int(uint32_t value) {
  union {
    uint32_t u32;
    int32_t i;
  } converter;
  converter.u32 = value;
  return converter.i;
}

uint32_t int_to_uint32(int32_t value) {
  union {
    uint32_t u32;
    int32_t i;
  } converter;
  converter.i = value;
  return converter.u32;
}

int64_t uint64_to_long(uint64_t value) {
  union {
    uint64_t u64;
    int64_t l;
  } converter;
  converter.u64 = value;
  return converter.l;
}

uint64_t long_to_uint64(int64_t value) {
  union {
    uint64_t u64;
    int64_t l;
  } converter;
  converter.l = value;
  return converter.u64;
}

float uint32_to_float(uint32_t value) {
  union {
    uint32_t u32;
    float f;
  } converter;
  converter.u32 = value;
  return converter.f;
}

uint32_t float_to_uint32(float value) {
  union {
    uint32_t u32;
    float f;
  } converter;
  converter.f = value;
  return converter.u32;
}

double uint64_to_double(uint64_t value) {
  union {
    uint64_t u64;
    double d;
  } converter;
  converter.u64 = value;
  return converter.d;
}

uint64_t double_to_uint64(double value) {
  union {
    uint64_t u64;
    double d;
  } converter;
  converter.d = value;
  return converter.u64;
}

InstructionType * get_instruction_type(uint8_t opcode) {
  static InstructionType instructions[] = {
    {0x00, 0, "nop", nop},
    {0x01, 0, "aconst_null"},
    {0x02, 0, "iconst_m1"},
    {0x03, 0, "iconst_0", load_constant},
    {0x04, 0, "iconst_1"},
    {0x05, 0, "iconst_2"},
    {0x06, 0, "iconst_3"},
    {0x07, 0, "iconst_4"},
    {0x08, 0, "iconst_5"},
    {0x09, 0, "lconst_0"},
    {0x0a, 0, "lconst_1"},
    {0x0b, 0, "fconst_0"},
    {0x0c, 0, "fconst_1"},
    {0x0d, 0, "fconst_2"},
    {0x0e, 0, "dconst_0"},
    {0x0f, 0, "dconst_1"},
    {0x10, 1, "bipush"},
    {0x11, 2, "sipush"},
    {0x12, 1, "ldc"},
    {0x13, 2, "ldc_w"},
    {0x14, 2, "ldc2_w"},
    {0x15, 1, "iload"},
    {0x16, 1, "lload"},
    {0x17, 1, "fload"},
    {0x18, 1, "dload"},
    {0x19, 1, "aload"},
    {0x1a, 0, "iload_0"},
    {0x1b, 0, "iload_1"},
    {0x1c, 0, "iload_2"},
    {0x1d, 0, "iload_3"},
    {0x1e, 0, "lload_0"},
    {0x1f, 0, "lload_1"},
    {0x20, 0, "lload_2"},
    {0x21, 0, "lload_3"},
    {0x22, 0, "fload_0"},
    {0x23, 0, "fload_1"},
    {0x24, 0, "fload_2"},
    {0x25, 0, "fload_3"},
    {0x26, 0, "dload_0"},
    {0x27, 0, "dload_1"},
    {0x28, 0, "dload_2"},
    {0x29, 0, "dload_3"},
    {0x2a, 0, "aload_0"},
    {0x2b, 0, "aload_1"},
    {0x2c, 0, "aload_2"},
    {0x2d, 0, "aload_3"},
    {0x2e, 0, "iaload"},
    {0x2f, 0, "laload"},
    {0x30, 0, "faload"},
    {0x31, 0, "daload"},
    {0x32, 0, "aaload"},
    {0x33, 0, "baload"},
    {0x34, 0, "caload"},
    {0x35, 0, "saload"},
    {0x36, 1, "istore"},
    {0x37, 1, "lstore"},
    {0x38, 1, "fstore"},
    {0x39, 1, "dstore"},
    {0x3a, 1, "astore"},
    {0x3b, 0, "istore_0"},
    {0x3c, 0, "istore_1"},
    {0x3d, 0, "istore_2"},
    {0x3e, 0, "istore_3"},
    {0x3f, 0, "lstore_0"},
    {0x40, 0, "lstore_1"},
    {0x41, 0, "lstore_2"},
    {0x42, 0, "lstore_3"},
    {0x43, 0, "fstore_0"},
    {0x44, 0, "fstore_1"},
    {0x45, 0, "fstore_2"},
    {0x46, 0, "fstore_3"},
    {0x47, 0, "dstore_0"},
    {0x48, 0, "dstore_1"},
    {0x49, 0, "dstore_2"},
    {0x4a, 0, "dstore_3"},
    {0x4b, 0, "astore_0"},
    {0x4c, 0, "astore_1"},
    {0x4d, 0, "astore_2"},
    {0x4e, 0, "astore_3"},
    {0x4f, 0, "iastore"},
    {0x50, 0, "lastore"},
    {0x51, 0, "fastore"},
    {0x52, 0, "dastore"},
    {0x53, 0, "aastore"},
    {0x54, 0, "bastore"},
    {0x55, 0, "castore"},
    {0x56, 0, "sastore"},
    {0x57, 0, "pop"},
    {0x58, 0, "pop2"},
    {0x59, 0, "dup"},
    {0x5a, 0, "dup_x1"},
    {0x5b, 0, "dup_x2"},
    {0x5c, 0, "dup2"},
    {0x5d, 0, "dup2_x1"},
    {0x5e, 0, "dup2_x2"},
    {0x5f, 0, "swap"},
    {0x60, 0, "iadd", iadd},
    {0x61, 0, "ladd", ladd},
    {0x62, 0, "fadd", fadd},
    {0x63, 0, "dadd", dadd},
    {0x64, 0, "isub", isub},
    {0x65, 0, "lsub", lsub},
    {0x66, 0, "fsub", fsub},
    {0x67, 0, "dsub", dsub},
    {0x68, 0, "imul", imul},
    {0x69, 0, "lmul", lmul},
    {0x6a, 0, "fmul", fmul},
    {0x6b, 0, "dmul", dmul},
    {0x6c, 0, "idiv", idiv},
    {0x6d, 0, "ldiv", ldiv},
    {0x6e, 0, "fdiv", fdiv},
    {0x6f, 0, "ddiv", ddiv},
    {0x70, 0, "irem", irem},
    {0x71, 0, "lrem", lrem},
    {0x72, 0, "frem", frem},
    {0x73, 0, "drem", drem},
    {0x74, 0, "ineg", ineg},
    {0x75, 0, "lneg", lneg},
    {0x76, 0, "fneg", fneg},
    {0x77, 0, "dneg", dneg},
    {0x78, 0, "ishl", ishl},
    {0x79, 0, "lshl", lshl},
    {0x7a, 0, "ishr", ishr},
    {0x7b, 0, "lshr", lshr},
    {0x7c, 0, "iushr", iushr},
    {0x7d, 0, "lushr", lushr},
    {0x7e, 0, "iand", iand},
    {0x7f, 0, "land", land},
    {0x80, 0, "ior", ior},
    {0x81, 0, "lor", lor},
    {0x82, 0, "ixor", ixor},
    {0x83, 0, "lxor", lxor},
    {0x84, 2, "iinc"},
    {0x85, 0, "i2l"},
    {0x86, 0, "i2f"},
    {0x87, 0, "i2d"},
    {0x88, 0, "l2i"},
    {0x89, 0, "l2f"},
    {0x8a, 0, "l2d"},
    {0x8b, 0, "f2i"},
    {0x8c, 0, "f2l"},
    {0x8d, 0, "f2d"},
    {0x8e, 0, "d2i"},
    {0x8f, 0, "d2l"},
    {0x90, 0, "d2f"},
    {0x91, 0, "i2b"},
    {0x92, 0, "i2c"},
    {0x93, 0, "i2s"},
    {0x94, 0, "lcmp"},
    {0x95, 0, "fcmpl"},
    {0x96, 0, "fcmpg"},
    {0x97, 0, "dcmpl"},
    {0x98, 0, "dcmpg"},
    {0x99, 2, "ifeq"},
    {0x9a, 2, "ifne"},
    {0x9b, 2, "iflt"},
    {0x9c, 2, "ifge"},
    {0x9d, 2, "ifgt"},
    {0x9e, 2, "ifle"},
    {0x9f, 2, "if_icmpeq"},
    {0xa0, 2, "if_icmpne"},
    {0xa1, 2, "if_icmplt"},
    {0xa2, 2, "if_icmpge"},
    {0xa3, 2, "if_icmpgt"},
    {0xa4, 2, "if_icmple"},
    {0xa5, 2, "if_acmpeg"},
    {0xa6, 2, "if_acmpne"},
    {0xa7, 2, "goto"},
    {0xa8, 2, "jsr"},
    {0xa9, 1, "ret"},
    {0xaa, 16, "tableswitch"},
    {0xab, 8, "lookupswitch"},
    {0xac, 0, "ireturn"},
    {0xad, 0, "lreturn"},
    {0xae, 0, "freturn"},
    {0xaf, 0, "dreturn"},
    {0xb0, 0, "areturn"},
    {0xb1, 0, "return"},
    {0xb2, 2, "getstatic"},
    {0xb3, 2, "putstatic"},
    {0xb4, 2, "getfield"},
    {0xb5, 2, "putfield"},
    {0xb6, 2, "invokevirtual"},
    {0xb7, 2, "invokespecial"},
    {0xb8, 2, "invokestatic"},
    {0xb9, 4, "invokeinterface"},
    {0xba, 4, "invokedynamic"},
    {0xbb, 2, "new"},
    {0xbc, 1, "newarray"},
    {0xbd, 2, "anewarray"},
    {0xbe, 0, "arraylength"},
    {0xbf, 0, "athrow"},
    {0xc0, 2, "checkcast"},
    {0xc1, 2, "instanceof"},
    {0xc2, 0, "monitorenter"},
    {0xc3, 0, "monitorexit"},
    {0xc4, 5, "wide"},
    {0xc5, 3, "multianewarray"},
    {0xc6, 2, "ifnull"},
    {0xc7, 2, "ifnonnull"},
    {0xc8, 4, "goto_w"},
    {0xc9, 4, "jsr_w"},
    {0xca, 0, "breakpoint"},
    // A partir daqui, é apenas para preenchimento, até o 0xfe
    {0xcb, 0, "filler1"},
    {0xcc, 0, "filler2"},
    {0xcd, 0, "filler3"},
    {0xce, 0, "filler4"},
    {0xcf, 0, "filler5"},
    {0xd0, 0, "filler6"},
    {0xd1, 0, "filler7"},
    {0xd2, 0, "filler8"},
    {0xd3, 0, "filler9"},
    {0xd4, 0, "filler10"},
    {0xd5, 0, "filler11"},
    {0xd6, 0, "filler12"},
    {0xd7, 0, "filler13"},
    {0xd8, 0, "filler14"},
    {0xd9, 0, "filler15"},
    {0xda, 0, "filler16"},
    {0xdb, 0, "filler17"},
    {0xdc, 0, "filler18"},
    {0xdd, 0, "filler19"},
    {0xde, 0, "filler20"},
    {0xdf, 0, "filler21"},
    {0xe0, 0, "filler22"},
    {0xe1, 0, "filler23"},
    {0xe2, 0, "filler24"},
    {0xe3, 0, "filler25"},
    {0xe4, 0, "filler26"},
    {0xe5, 0, "filler27"},
    {0xe6, 0, "filler28"},
    {0xe7, 0, "filler29"},
    {0xe8, 0, "filler30"},
    {0xe9, 0, "filler31"},
    {0xea, 0, "filler32"},
    {0xeb, 0, "filler33"},
    {0xec, 0, "filler34"},
    {0xed, 0, "filler35"},
    {0xee, 0, "filler36"},
    {0xef, 0, "filler37"},
    {0xf0, 0, "filler38"},
    {0xf1, 0, "filler39"},
    {0xf2, 0, "filler40"},
    {0xf3, 0, "filler41"},
    {0xf4, 0, "filler42"},
    {0xf5, 0, "filler43"},
    {0xf6, 0, "filler44"},
    {0xf7, 0, "filler45"},
    {0xf8, 0, "filler46"},
    {0xf9, 0, "filler47"},
    {0xfa, 0, "filler48"},
    {0xfb, 0, "filler49"},
    {0xfc, 0, "filler50"},
    {0xfd, 0, "filler51"},
    {0xfe, 0, "impdep1"},
    {0xff, 0, "impdep2"}
    // other instructions
  };

  return &instructions[opcode];
};

void nop(Frame * frame) {
  printf("Nop\n");
}
