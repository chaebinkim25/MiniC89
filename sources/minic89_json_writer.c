/* minic89_json_writer.c */

#include "minic89_vm.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* JSON Writer Core */

typedef enum { CTX_OBJ = 1, CTX_ARR = 2 } CtxKind;

typedef struct {
    CtxKind kind;
    int first;
} JsonCtx;

struct JsonWriter {
    char *buf;
    size_t len;
    size_t cap;
    JsonCtx ctx[MAX_JSON_DEPTH];
    int depth;
};

static JsonWriter *jw_new(size_t initial_cap) 
{
    JsonWriter *w = (JsonWriter*)malloc(sizeof(JsonWriter));
    if (!w) return NULL;

    w->buf = (char*)malloc(initial_cap);
    if (!w->buf) { free(w); return NULL; }

    w->len = 0;
    w->cap = initial_cap;
    w->depth = 0;

    return w;
}

static void jw_free(JsonWriter *w) 
{
    if (!w) return;
    free(w->buf);
    free(w);
}

static int jw_reserve(JsonWriter *w, size_t more) 
{
    size_t need = w->len + more;
    if (need <= w->cap) return 0;

    size_t new_cap = w->cap ? w->cap : 256;
    while (new_cap < need) new_cap *= 2;

    char *p = (char*)realloc(w->buf, new_cap);
    if (!p) return -1;

    w->buf = p;
    w->cap = new_cap;

    return 0;
}

static int jw_putc(JsonWriter *w, char c) 
{
    if (jw_reserve(w, 1)) return -1;

    w->buf[w->len++] = c;

    return 0;
}

static int jw_puts(JsonWriter *w, const char *s) 
{
    size_t n = strlen(s);

    if (jw_reserve(w, n)) return -1;

    memcpy(w->buf + w->len, s, n);
    w->len += n;

    return 0;
}

static int jw_before_pair_or_elem(JsonWriter *w) 
{
    if (w->depth <= 0) return 0;

    JsonCtx *c = &w->ctx[w->depth - 1];

    if (!c->first) {
        if (jw_putc(w, ',')) return -1;
    } else {
        c->first = 0;
    }

    return 0;
}

static int jw_string(JsonWriter *w, const char *s) 
{
    const unsigned char *p = (const unsigned char*)s;

    if (jw_putc(w, '"')) return -1;

    while (*p) {

        unsigned char ch = *p++;
        if (ch == '\n') {
            if (jw_puts(w, "\\n")) return -1;
        } 
        else if (ch == '\t') {
            if (jw_puts(w, "\\t")) return -1;
        }
        else if (ch == '\r') {
            if (jw_puts(w, "\\r")) return -1;
        } 
        else if (ch == '"') {
            if (jw_puts(w, "\\\"")) return -1;
        } 
        else if (ch == '\\') {
            if (jw_puts(w, "\\\\")) return -1;
        } 
        else if (ch < 0x20) {
            char tmp[7];
            snprintf(tmp, sizeof(tmp), "\\u%04x", (unsigned)ch);
            if (jw_puts(w, tmp)) return -1;
        } 
        else {
            if (jw_putc(w, (char)ch)) return -1;
        }
    }

    if (jw_putc(w, '"')) return -1;

    return 0;
}

static int jw_i32(JsonWriter *w, i32 x) 
{
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%ld", (long)x);

    return jw_puts(w, tmp);
}

static int jw_u32(JsonWriter *w, u32 x) 
{
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%lu", (unsigned long)x);

    return jw_puts(w, tmp);
}

static int jw_null(JsonWriter *w) 
{ 
    return jw_puts(w, "null"); 
}

static int jw_obj_begin(JsonWriter *w) 
{
    if (w->depth >= MAX_JSON_DEPTH - 1) return -2;

    if (jw_putc(w, '{')) return -1;
    w->ctx[w->depth].kind = CTX_OBJ;
    w->ctx[w->depth].first = 1;
    w->depth++;

    return 0;
}

static int jw_obj_end(JsonWriter *w) 
{
    if (w->depth <= 0) return -2;

    w->depth--;
    if (jw_putc(w, '}')) return -1;

    return 0;
}

static int jw_arr_begin(JsonWriter *w) 
{
    if (w->depth >= MAX_JSON_DEPTH - 1) return -2;    

    if (jw_putc(w, '[')) return -1;
    w->ctx[w->depth].kind = CTX_ARR;
    w->ctx[w->depth].first = 1;
    w->depth++;

    return 0;
}

static int jw_arr_end(JsonWriter *w) 
{
    if (w->depth <= 0) return -2;

    w->depth--;
    if (jw_putc(w, ']')) return -1;

    return 0;
}

static int jw_key(JsonWriter *w, const char *key) 
{
    if (w->depth <= 0) return -2;
    if (w->ctx[w->depth - 1].kind != CTX_OBJ) return -3;
    
    if (jw_before_pair_or_elem(w)) return -1;
    if (jw_string(w, key)) return -1;
    if (jw_putc(w, ':')) return -1;

    return 0;
}

static int jw_key_str(JsonWriter *w, const char *k, const char *v) 
{
    if (jw_key(w, k)) return -1;
    if (jw_string(w, v)) return -1;

    return 0;
}

static int jw_key_u32(JsonWriter *w, const char *k, u32 v) 
{
    if (jw_key(w, k)) return -1;
    if (jw_u32(w, v)) return -1;

    return 0;
}

static int jw_arr_elem(JsonWriter *w) 
{
    return jw_before_pair_or_elem(w);
}

/* Value, PC */

static int jw_write_value(JsonWriter *w, Value v) 
{
    if (v.tag == VAL_I16) {
        if (jw_i32(w, (i32)v.as.num)) return -1;
    }
    else if (v.tag == VAL_FUN) {
        if (jw_obj_begin(w)) return -1;
        if (jw_key_str(w, "t", "fun")) return -1;
        if (jw_key_u32(w, "v", v.as.fun_id)) return -1;
        if (jw_obj_end(w)) return -1;
    }
    else if (v.tag == VAL_UNINIT) {
        if (jw_obj_begin(w)) return -1;
        if (jw_key_str(w, "t", "uninit")) return -1;
        if (jw_obj_end(w)) return -1;
    }
    else {
        /* bad value tag */
        return -2;
    }

    return 0;
}

static int jw_write_pc(JsonWriter *w, PC pc) 
{
    if (jw_obj_begin(w)) return -1;
    if (jw_key_u32(w, "fid", (u32)pc.fid)) return -1;
    if (jw_key_u32(w, "ip", (u32)pc.ip)) return -1;
    if (jw_obj_end(w)) return -1;

    return 0;
}

/* Status, Trap, Halt */ 

static const char *status_str(VMStatus st) 
{
    switch (st) {
        case VM_RUNNING: return "RUNNING";
        case VM_HALTED:  return "HALTED";
        case VM_TRAPPED: return "TRAPPED";
        default:         return "BADSTATUS";
    }
}

static const char *trap_code_str(TrapCode c) 
{
    switch (c) {
        case TRAP_NONE:           return "TRAP_NONE";
        case TRAP_INT_OVERFLOW:   return "TRAP_INT_OVERFLOW";
        case TRAP_DIV_ZERO:       return "TRAP_DIV_ZERO";
        case TRAP_UNINIT_READ:    return "TRAP_UNINIT_READ";
        case TRAP_TYPE:           return "TRAP_TYPE";
        case TRAP_BAD_LOCAL:      return "TRAP_BAD_LOCAL";
        case TRAP_BAD_FUNID:      return "TRAP_BAD_FUNID";
        case TRAP_BAD_JUMP:       return "TRAP_BAD_JUMP";
        case TRAP_CALL_NULLFUN:   return "TRAP_CALL_NULLFUN";
        case TRAP_BAD_SIGNATURE:  return "TRAP_BAD_SIGNATURE";
        case TRAP_STACK:          return "TRAP_STACK";
        case TRAP_CALLSTACK:      return "TRAP_CALLSTACK";
        case TRAP_STEP_LIMIT:     return "TRAP_STEP_LIMIT";
        default:                  return "TRAP_INTERNAL";
    }
}

static int jw_write_trap(JsonWriter *w, const TrapInfo *t) 
{
    if (jw_obj_begin(w)) return -1;
    if (jw_key_str(w, "code", trap_code_str(t->code))) return -1;

    /* To Do: 모든 트랩에 대해 추가 정보 문서화, jw에 추가 */

    if (jw_obj_end(w)) return -1;

    return 0;
}

static int jw_write_halt(JsonWriter *w, const HaltInfo *h) 
{
    if (jw_obj_begin(w)) return -1;
    if (jw_key(w, "result")) return -1;
    if (jw_write_value(w, h->result)) return -1;
    if (jw_obj_end(w)) return -1;

    return 0;
}

/* Frame */

static int jw_write_frame(JsonWriter *w, const Frame *fr) 
{
    u32 i;
    if (jw_obj_begin(w)) return -1;
    if (jw_key_u32(w, "fid", (u32)fr->fid)) return -1;
    if (jw_key(w, "return_pc")) return -1;

    if (fr->ret_pc.fid == 0) {
        if (jw_null(w)) return -1;
    } 
    else {
        if (jw_write_pc(w, fr->ret_pc)) return -1;
    }

    if (jw_key(w, "locals")) return -1;
    if (jw_arr_begin(w)) return -1;

    for (i = 0; i < fr->local_count; i++) {
        if (jw_arr_elem(w)) return -1;
        if (jw_write_value(w, fr->locals[i])) return -1;
    }

    if (jw_arr_end(w)) return -1;
    if (jw_obj_end(w)) return -1;

    return 0;
}

/* Public API (VM Snapshot) */

const char *vm_build_snapshot_json(VM *vm, size_t *out_len) 
{
    JsonWriter *w;
    u16 i;

    if (!vm->jw) {
        vm->jw = jw_new(VM_SNAPSHOT_BUF_SIZE); 
        if (!vm->jw) return NULL;
    }

    w = vm->jw;
    w->len = 0;
    w->depth = 0;

    if (jw_obj_begin(w)) return NULL;

    if (jw_key_str(w, "schema_version", "MiniC89.VM.Snapshot.v0.2")) return NULL;
    if (jw_key_u32(w, "step", (u32)vm->step)) return NULL;
    if (jw_key_str(w, "status", status_str(vm->status))) return NULL;

    /* PC */

    if (jw_key(w, "pc")) return NULL;

    if (vm->status == VM_HALTED) {
        if (jw_null(w)) return NULL;
    } 
    else {
        if (jw_write_pc(w, vm->pc)) return NULL;
    }

    /* Operand Stack */

    if (jw_key(w, "operand_stack")) return NULL;
    if (jw_arr_begin(w)) return NULL;

    for (i = 0; i < vm->operand.size; i++) {
        if (jw_arr_elem(w)) return NULL;
        if (jw_write_value(w, vm->operand.data[i])) return NULL;
    }

    if (jw_arr_end(w)) return NULL;

    /* Call Stack */

    if (jw_key(w, "call_stack")) return NULL;
    if (jw_arr_begin(w)) return NULL;

    for (i = 0; i < vm->call.size; i++) {
        Frame *fr = vm->call.data[i];
        if (jw_arr_elem(w)) return NULL;
        if (jw_write_frame(w, fr)) return NULL;
    }

    if (jw_arr_end(w)) return NULL;

    /* Exit-info */

    if (vm->status == VM_TRAPPED) {
        if (jw_key(w, "trap")) return NULL;
        if (jw_write_trap(w, &vm->exit.trap)) return NULL;
    }

    if (vm->status == VM_HALTED) {
        if (jw_key(w, "halt")) return NULL;
        if (jw_write_halt(w, &vm->exit.halt)) return NULL;
    }

    /* Wrap-up*/

    if (jw_obj_end(w)) return NULL;
    if (jw_putc(w, '\0')) return NULL;

    if (out_len) *out_len = (w->len > 0) ? (w->len - 1) : 0;

    return w->buf;
}
