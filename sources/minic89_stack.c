/* minic89_stack.c */

#include "minic89_vm.h"
#include <stdlib.h> 

/* ValueStack internal: reserve */

static int valuestack_reserve(ValueStack *s, u32 min_cap) 
{
    u32 new_cap;
    size_t bytes;
    Value *p;

    if (!s) return MC89_RET_ERR_BADARG;
    if (min_cap > MC89_U16_MAX_U32) return MC89_RET_ERR_LIMIT;
    if ((u32)s->cap >= min_cap) return MC89_RET_OK;

    new_cap = (u32)s->cap;
    if (new_cap == (u32)0u) new_cap = MC89_STACK_DEFAULT_CAP;

    while (new_cap < min_cap) {
        if (new_cap >= 32768u) {
            new_cap = MC89_U16_MAX_U32;
            break;
        }
        new_cap *= 2u;
    }

    if (new_cap < min_cap) return MC89_RET_ERR_LIMIT;
    if ((size_t)new_cap > (MC89_SIZE_T_MAX / sizeof(Value))) return MC89_RET_ERR_LIMIT;

    bytes = (size_t)new_cap * sizeof(Value);

    if (s->data == NULL) {
        p = (Value*)malloc(bytes);
        if (p == NULL) return MC89_RET_ERR_OOM;
    }
    else {
        p = (Value*)realloc(s->data, bytes);
        if (p == NULL) return MC89_RET_ERR_OOM;
    }

    s->data = p;
    s->cap  = (u16)new_cap;

    return MC89_RET_OK;
}

/* ValueStack public API */

int valuestack_init(ValueStack *s, u32 cap) 
{
    int rc;

    if (s == NULL) return MC89_RET_ERR_BADARG;

    s->data = NULL;
    s->size = 0;
    s->cap  = 0;

    if (cap == 0u) cap = MC89_STACK_DEFAULT_CAP;

    rc = valuestack_reserve(s, cap);
    if (rc != MC89_RET_OK) {
        valuestack_free(s);
        return rc;
    }

    return MC89_RET_OK;
}

void valuestack_free(ValueStack *s) 
{
    if (s == NULL) return;

    if (s->data != NULL) free(s->data);

    s->data = NULL;
    s->size = 0;
    s->cap  = 0;
}

int valuestack_push(ValueStack *s, Value v) 
{
    int rc;
    u32 need;

    if (s == NULL) return MC89_RET_ERR_BADARG;
    if (s->size == (u16)0xFFFFu) return MC89_RET_ERR_LIMIT;

    need = (u32)s->size + (u32)1u;

    rc = valuestack_reserve(s, need);
    if (rc != MC89_RET_OK) return rc;

    s->data[s->size] = v;
    s->size = (u16)((u32)s->size + (u32)1u);
    return MC89_RET_OK;
}

int valuestack_pop(ValueStack *s, Value *out) {
    if (s == NULL) return MC89_RET_ERR_BADARG;
    if (s->size == 0u) return MC89_RET_ERR_EMPTY;

    s->size = (u16)((u32)s->size - (u32)1u);

    if (out != NULL) *out = s->data[s->size];

    return MC89_RET_OK;
}

/* FrameStack internal: reserve */

static int framestack_reserve(FrameStack *s, u32 min_cap) 
{
    u32 new_cap;
    size_t bytes;
    Frame **p;

    if (s == NULL) return MC89_RET_ERR_BADARG;

    if (min_cap == (u32)0u) return MC89_RET_OK;
    if (min_cap > MC89_U16_MAX_U32) return MC89_RET_ERR_LIMIT;

    if ((u32)s->cap >= min_cap) return MC89_RET_OK;

    new_cap = (u32)s->cap;
    if (new_cap == (u32)0u) new_cap = MC89_STACK_DEFAULT_CAP;

    while (new_cap < min_cap) {
        if (new_cap >= 32768u) {
            new_cap = MC89_U16_MAX_U32;
            break;
        }
        new_cap *= 2u;
    }

    if (new_cap < min_cap) return MC89_RET_ERR_LIMIT;

    if ((size_t)new_cap > (MC89_SIZE_T_MAX / sizeof(Frame*))) return MC89_RET_ERR_LIMIT;
    bytes = (size_t)new_cap * sizeof(Frame*);

    if (s->data == NULL) {
        p = (Frame**)malloc(bytes);
        if (p == NULL) return MC89_RET_ERR_OOM;
    } else {
        p = (Frame**)realloc(s->data, bytes);
        if (p == NULL) return MC89_RET_ERR_OOM;
    }

    s->data = p;
    s->cap  = (u16)new_cap;
    return MC89_RET_OK;
}

/* FrameStack public API */

int framestack_init(FrameStack *s, u32 cap) 
{
    int rc;

    if (s == NULL) return MC89_RET_ERR_BADARG;

    s->data = NULL;
    s->size = 0;
    s->cap  = 0;

    if (cap == 0u) cap = MC89_STACK_DEFAULT_CAP;

    rc = framestack_reserve(s, cap);
    if (rc != MC89_RET_OK) {
        framestack_free(s);
        return rc;
    }
    return MC89_RET_OK;
}

void framestack_free(FrameStack *s) 
{
    if (s == NULL) return;

    if (s->data != NULL) free(s->data);

    s->data = NULL;
    s->size = 0;
    s->cap  = 0;
}

int framestack_push(FrameStack *s, Frame *fr) 
{
    int rc;
    u32 need;

    if (s == NULL) return MC89_RET_ERR_BADARG;
    if (fr == NULL) return MC89_RET_ERR_BADARG;

    if (s->size == (u16)0xFFFFu) return MC89_RET_ERR_LIMIT;

    need = (u32)s->size + (u32)1u;

    rc = framestack_reserve(s, need);
    if (rc != MC89_RET_OK) return rc;

    s->data[s->size] = fr;
    s->size = (u16)((u32)s->size + (u32)1u);
    return MC89_RET_OK;
}

int framestack_pop(FrameStack *s, Frame **out) 
{
    if (s == NULL) return MC89_RET_ERR_BADARG;
    if (s->size == 0u) return MC89_RET_ERR_EMPTY;

    s->size = (u16)((u32)s->size - (u32)1u);
    if (out != NULL) *out = s->data[s->size];
    return MC89_RET_OK;
}
