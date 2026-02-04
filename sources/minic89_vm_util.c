/* minic89_vm_util.c */

#include "minic89_vm.h"

/* i16 range check */

static int mc89_is_i16_in_range(i32 x) 
{
    if (x < (i32)MC89_I16_MIN) return 0;
    if (x > (i32)MC89_I16_MAX) return 0;
    return 1;
}

static int mc89_is_i16_overflow(i32 x) 
{
    if (x > (i32)MC89_I16_MAX) return 1;
    if (x < (i32)MC89_I16_MIN) return 1;
    return 0;
}

/* TRAP helper */

void vm_trap(VM *vm, TrapCode code, i16 info1, i16 info2, u32 info3) 
{
    if (vm == NULL) return;

    if (vm->status == VM_TRAPPED) return;
    if (vm->status == VM_HALTED)  return;

    vm->status = VM_TRAPPED;

    if (code == TRAP_NONE) code = TRAP_INTERNAL;

    vm->exit.trap.code  = code;
    vm->exit.trap.info1 = info1;
    vm->exit.trap.info2 = info2;
    vm->exit.trap.info3 = info3;
}

void vm_halt(VM *vm, Value result) 
{
    if (vm == NULL) return;
    if (vm->status == VM_TRAPPED) return;
    
    vm->status = VM_HALTED;
    vm->exit.halt.result = result;
}

/* 16-bit arithmetic */

static TrapCode mc89_i16_range_check(i32 r, i16 *out) 
{
    if (mc89_is_i16_overflow(r)) return TRAP_INT_OVERFLOW;

    if (out != NULL) 
        *out = (i16)r;

    return TRAP_NONE;
}

TrapCode mc89_i16_checked_add(i16 a, i16 b, i16 *out) 
{
    return mc89_i16_range_check((i32)a + (i32)b, out);
}

TrapCode mc89_i16_checked_sub(i16 a, i16 b, i16 *out) 
{
    return mc89_i16_range_check((i32)a - (i32)b, out);
}

TrapCode mc89_i16_checked_neg(i16 a, i16 *out) 
{
    return mc89_i16_range_check(-(i32)a, out);
}

TrapCode mc89_i16_checked_mul(i16 a, i16 b, i16 *out) 
{
    return mc89_i16_range_check((i32)a * (i32)b, out);
}

static i32 mc89_i16_abs(i16 x)
{
    return (x < (i16)0) ? -(i32)x : (i32)x;
}

TrapCode mc89_i16_checked_div(i16 a, i16 b, i16 *out) 
{
    i32 a_mag, b_mag, res;

    if (b == (i16)0) return TRAP_DIV_ZERO;

    a_mag = mc89_i16_abs(a);
    b_mag = mc89_i16_abs(b);

    res = a_mag / b_mag;

    if ((a < 0) ^ (b < 0)) {
        res = -res;
    }

    return mc89_i16_range_check(res, out);
}

TrapCode mc89_i16_checked_mod(i16 a, i16 b, i16 *out) 
{
    i32 a_mag, b_mag, res;

    if (b == (i16)0) return TRAP_DIV_ZERO;

    a_mag = mc89_i16_abs(a);
    b_mag = mc89_i16_abs(b);

    res = a_mag % b_mag;

    if (a < 0) {
        res = -res;
    }

    return mc89_i16_range_check(res, out);
}
