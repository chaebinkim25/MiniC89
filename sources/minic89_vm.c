#include <stdio.h>
#include "minic89_vm.h"

// --- 헬퍼 매크로 ---
#define PUSH(val) do { \
    if (vm->sp >= MAX_STACK) { vm->trap = TRAP_STACK_OVERFLOW; return; } \
    vm->stack[vm->sp++] = (val); \
} while(0)

#define POP() (vm->sp > 0 ? vm->stack[--vm->sp] : (vm->trap = TRAP_STACK_UNDERFLOW, (Value){0}))

#define PEEK() (vm->sp > 0 ? vm->stack[vm->sp - 1] : (vm->trap = TRAP_STACK_UNDERFLOW, (Value){0}))

#define CHECK_TYPE(val, expected) do { \
    if ((val).type != (expected)) { vm->trap = TRAP_TYPE_MISMATCH; return; } \
} while(0)

// 값 생성 헬퍼
Value VAL_INT(i16 v) { return (Value){ .type = VAL_I16, .as.i_val = v }; }
Value VAL_FN(u16 id) { return (Value){ .type = VAL_FUN, .as.fun_id = id }; }

// --- VM 실행 루프 (단일 단계) ---
void vm_step(VM* vm) {
    if (!vm->running || vm->trap != TRAP_NONE) return;

    // Fetch
    Function* func = &vm->functions[vm->pc_fid];
    if (vm->pc_ip >= func->code_size) {
        vm->trap = TRAP_BAD_JUMP; // 코드 범위 초과
        return;
    }
    Instruction inst = func->code[vm->pc_ip];
    
    // PC 증가 (점프 명령에서 덮어씌워질 수 있음)
    vm->pc_ip++;

    // Decode & Execute
    switch (inst.opcode) {
        case OP_NOP: break;
        
        case OP_DBG_LINE:
            vm->current_source_line = inst.operand;
            break;

        case OP_PUSH_I16:
            PUSH(VAL_INT(inst.operand));
            break;

        case OP_PUSH_FUN:
            if (inst.operand < 1 || inst.operand > vm->function_count) {
                vm->trap = TRAP_BAD_FUNID; return;
            }
            PUSH(VAL_FN(inst.operand));
            break;

        case OP_POP:
            POP();
            break;

        case OP_DUP: {
            Value v = PEEK();
            PUSH(v);
            break;
        }

        case OP_LOAD: {
            int slot = inst.operand;
            if (slot >= func->local_count) { vm->trap = TRAP_BAD_LOCAL; return; }
            Value v = vm->frames[vm->fp].locals[slot];
            if (v.type == VAL_UNINIT) { vm->trap = TRAP_UNINIT_READ; return; }
            PUSH(v);
            break;
        }

        case OP_STORE: {
            int slot = inst.operand;
            if (slot >= func->local_count) { vm->trap = TRAP_BAD_LOCAL; return; }
            // STORE는 스택 값을 제거하지 않고 유지함 (C 대입식 특성)
            Value v = PEEK(); 
            vm->frames[vm->fp].locals[slot] = v;
            break;
        }

        // --- 산술 연산 (ADD 예시) ---
        case OP_ADD: {
            Value b = POP();
            Value a = POP();
            CHECK_TYPE(a, VAL_I16);
            CHECK_TYPE(b, VAL_I16);
            
            // Overflow Check
            i16 res = a.as.i_val + b.as.i_val;
            if ((b.as.i_val > 0 && a.as.i_val > 32767 - b.as.i_val) ||
                (b.as.i_val < 0 && a.as.i_val < -32768 - b.as.i_val)) {
                vm->trap = TRAP_INT_OVERFLOW; return;
            }
            PUSH(VAL_INT(res));
            break;
        }
        
        // ... (SUB, MUL, DIV 등은 유사한 방식으로 구현) ...

        // --- 제어 흐름 ---
        case OP_JMP:
            vm->pc_ip = inst.operand;
            break;

        case OP_JZ: {
            Value cond = POP();
            CHECK_TYPE(cond, VAL_I16);
            if (cond.as.i_val == 0) vm->pc_ip = inst.operand;
            break;
        }

        // --- 함수 호출 ---
        case OP_CALL: {
            u16 target_fid = inst.operand;
            if (target_fid < 1 || target_fid > vm->function_count) {
                vm->trap = TRAP_BAD_FUNID; return;
            }
            Function* target_func = &vm->functions[target_fid];

            // 프레임 준비
            if (vm->fp + 1 >= MAX_CALL_STACK) { vm->trap = TRAP_CALL_STACK_OVERFLOW; return; }
            vm->fp++;
            Frame* new_frame = &vm->frames[vm->fp];
            
            // 인자 전달 (Stack -> Locals 역순 Pop)
            // 주의: 인자는 스택에 [arg1, arg2] 순으로 쌓여있으므로, arg2가 먼저 pop됨
            for (int i = target_func->param_count - 1; i >= 0; i--) {
                Value arg = POP();
                // 단순화를 위해 타입 체크 생략 (필요 시 여기서 arg 타입 검사)
                new_frame->locals[i] = arg; 
            }

            // 나머지 로컬 초기화 (UNINIT)
            for (int i = target_func->param_count; i < target_func->local_count; i++) {
                new_frame->locals[i].type = VAL_UNINIT;
            }

            // 복귀 주소 저장 및 PC 갱신
            new_frame->return_ip = vm->pc_ip; // CALL 다음 명령
            new_frame->func_id = target_fid;
            new_frame->prev_fp = vm->fp - 1; // 단순화된 모델에서는 필요 없을 수 있음

            vm->pc_fid = target_fid;
            vm->pc_ip = 0;
            break;
        }

        case OP_RET: {
            Value ret_val = POP(); // 리턴값 확보
            
            if (vm->fp == 0) {
                // main 함수 리턴 -> 프로그램 종료
                vm->running = false;
                // 결과값은 보통 출력하거나 종료 코드로 사용
            } else {
                // 복귀 처리
                u16 ret_ip = vm->frames[vm->fp].return_ip;
                u16 caller_fid = vm->frames[vm->fp - 1].func_id; // 이전 프레임의 함수 ID (구현 방식에 따라 다름)
                
                // 실제로는 이전 프레임이 누구였는지 Call Stack에서 찾아야 함
                // 여기서는 vm->fp를 감소시키기 전에 정보를 얻어야 함
                
                // 호출자 복구
                vm->fp--; 
                vm->pc_fid = vm->frames[vm->fp].func_id;
                vm->pc_ip = ret_ip;
                
                // 리턴값 푸시
                PUSH(ret_val);
            }
            break;
        }

        default:
            // 구현되지 않은 Opcode
            break;
    }
}
