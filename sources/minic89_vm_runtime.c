/*minic89_vm_runtime.c*/
#include "minic89_vm.h"
#include <stdlib.h>
#include <stddef.h>

Frame *frame_new(u16 fid, u16 local_count, const PC *ret_pc_or_null) 
{
    Frame *fr;
    u16 i;

    size_t required_slots = (local_count > 0) ? local_count : 1;
    size_t size = sizeof(Frame) + (sizeof(Value) * required_slots);

    fr = (Frame*)malloc(size);
    if (!fr) return NULL;

    fr->fid = fid;
    fr->local_count = local_count;

    if (ret_pc_or_null) {
        fr->ret_pc = *ret_pc_or_null;
    } else {
        fr->ret_pc.fid = 0; 
        fr->ret_pc.ip  = 0;
    }

    for (i = 0; i < local_count; i++) {
        fr->locals[i] = vm_value_uninit();
    }
    return fr;
}

void frame_delete(Frame *fr) 
{
    if (!fr) return;
    free(fr);
}
