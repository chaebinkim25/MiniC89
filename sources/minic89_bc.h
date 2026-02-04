/* minic89_bc.h */

#ifndef MINIC89_BC_H
#define MINIC89_BC_H

#include "minic89_vm.h"

/* Opcode */

typedef enum {
    OP_NOP = 0,
    OP_DBG_LINE,
    OP_PUSH_I16,
    OP_PUSH_FUN,
    OP_PUSH_NULLFUN,
    OP_POP,
    OP_DUP,
    OP_LOAD_LOCAL,
    OP_STORE_LOCAL,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_NEG,
    OP_DIV,
    OP_MOD,
    OP_EQ,
    OP_NE,
    OP_LT,
    OP_LE,
    OP_GT,
    OP_GE,
    OP_LNOT,
    OP_JMP,
    OP_JZ,
    OP_JNZ,
    OP_CALL_DIRECT,
    OP_CALL_IND,
    OP_RET
} OpCode;

/* Instruction */

typedef struct {
    u16 op;
    u16 x;
    u16 y;
} Instr;

/* Debug info */

typedef struct {
    u16 ip;
    u16 line;
} LineEntry;

typedef struct {
    u16 entry_count;
    const LineEntry *entries;
} DebugInfo;

/* Function */

typedef struct {
    u16 fid;
    u16 param_count; 
    u16 local_count;
    u16 code_len;
    const Instr *code;
    const DebugInfo *debug;
} Function;

/* Module */

typedef struct Module {
    u16 func_count;
    const Function *funcs;
} Module;

#endif /* MINIC89_BC_H */
