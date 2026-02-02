/* minic89_vm.h */

#ifndef MINIC89_VM_H
#define MINIC89_VM_H

#include <stddef.h>
#include <limits.h>

/* size_t */
#define MC89_SIZE_T_MAX         ((size_t)-1)

/* i16, u16, i32, u32 */

#if USHRT_MAX == 0xFFFF
    typedef short i16;
    typedef unsigned short u16;
#elif UINT_MAX == 0xFFFF
    typedef int i16;
    typedef unsigned int u16;
#else
    #error "Cannot find 16-bit integer type on this platform."
#endif

#if UINT_MAX == 0xFFFFFFFFU
    typedef int i32;
    typedef unsigned int u32;
#elif ULONG_MAX == 0xFFFFFFFFUL
    typedef long i32;
    typedef unsigned long u32;
#else
    #error "Cannot find 32-bit integer type on this platform."
#endif

#define MC89_U16_MAX_U32        ((u32)0xFFFFu)

/* Value */

typedef enum {
    VAL_I16    = 0,
    VAL_FUN    = 1,
    VAL_UNINIT = 2
} ValueTag;

typedef struct {
    ValueTag tag;
    union {
        i16  num;    
        u16  fun_id; 
    } as;
} Value;

static Value vm_value_i16(i16 x) {
    Value v;
    v.tag = VAL_I16;
    v.as.num = x;
    return v;
}

static Value vm_value_fun(u16 fid) {
    Value v;
    v.tag = VAL_FUN;
    v.as.fun_id = fid;
    return v;
}

static Value vm_value_uninit(void) {
    Value v;
    v.tag = VAL_UNINIT;
    v.as.num = -1;
    return v;
}

/* PC, Frame */

typedef struct {
    u16 fid;
    u16 ip; 
} PC;

typedef struct Frame {
    u16 fid;
    u16 local_count;
    PC ret_pc;
    Value locals[1];   /* local_count==0 허용, malloc >= sizeof(Frame) */
} Frame;

/* Return codes */

#define MC89_RET_OK             0
#define MC89_RET_ERR_BADARG     -1
#define MC89_RET_ERR_OOM        -2
#define MC89_RET_ERR_LIMIT      -3
#define MC89_RET_ERR_EMPTY      -4

/* Operand Stack, Call Stack */

#define MC89_STACK_DEFAULT_CAP  ((u32)16u)

typedef struct {
    Value *data;
    u16    size;
    u16    cap;
} ValueStack;

typedef struct {
    Frame **data;
    u16     size;
    u16     cap;
} FrameStack;

/* VM Status, Trap, Halt */

typedef enum {
    VM_RUNNING = 0,
    VM_HALTED  = 1,
    VM_TRAPPED = 2
} VMStatus;

typedef enum {
    TRAP_NONE = 0,
    TRAP_INT_OVERFLOW,
    TRAP_DIV_ZERO,
    TRAP_UNINIT_READ,
    TRAP_TYPE,
    TRAP_BAD_LOCAL,
    TRAP_BAD_FUNID,
    TRAP_BAD_JUMP,
    TRAP_CALL_NULLFUN,
    TRAP_BAD_SIGNATURE,
    TRAP_STACK,
    TRAP_CALLSTACK,
    TRAP_STEP_LIMIT,
    TRAP_INTERNAL
} TrapCode;

typedef struct {
    TrapCode code;
    u16 a;
    u16 b;
    i32 x;                 
} TrapInfo;

typedef struct {
    Value result;
} HaltInfo;

typedef union {
    TrapInfo trap;
    HaltInfo halt;
} ExitInfo;

/* JSON writer */

#define MAX_JSON_DEPTH 32
typedef struct JsonWriter JsonWriter;

/* VM */

typedef struct {
    VMStatus status;    
    u32 step;
    PC pc;
    ValueStack operand;
    FrameStack call;
    ExitInfo exit;
    JsonWriter *jw;
} VM;

/* Helpers for VM runtime - stack */

int  valuestack_init(ValueStack *s, u16 cap);
void valuestack_free(ValueStack *s);
int  valuestack_push(ValueStack *s, Value v);
int  valuestack_pop(ValueStack *s, Value *out);

int  framestack_init(FrameStack *s, u16 cap);
void framestack_free(FrameStack *s);
int  framestack_push(FrameStack *s, Frame *fr);
int  framestack_pop(FrameStack *s, Frame **out);

/* Helpers for VM runtime - frame */

Frame *frame_new(u16 fid, u16 local_count, const PC *ret_pc_or_null);
void   frame_free(Frame *fr);

/* Helpers for VM runtime - trap and halt */

void vm_trap(VM *vm, TrapCode code, int info1, int info2);
void vm_halt(VM *vm, Value result);

/* Helpers for VM runtime - 16-bit int */

int      mc89_i16_checked_add(i16 a, i16 b, i16 *out);
int      mc89_i16_checked_sub(i16 a, i16 b, i16 *out);
int      mc89_i16_checked_mul(i16 a, i16 b, i16 *out);
int      mc89_i16_checked_neg(i16 a, i16 *out);
TrapCode mc89_i16_checked_div(i16 a, i16 b, i16 *out);
TrapCode mc89_i16_checked_mod(i16 a, i16 b, i16 *out);

/* Snapshot API */

#define VM_SNAPSHOT_BUF_SIZE  4096
const char *vm_build_snapshot_json(VM *vm, size_t *out_len);

#endif /* MINIC89_VM_H */
