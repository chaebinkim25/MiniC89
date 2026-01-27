# MiniC89 Abstract Machine ISA (v0.11)

본 문서는 MiniC89 프로그램을 브라우저에서 실행/시각화하기 위한
**교육용 추상 머신(Educational Abstract Machine)** 과 그 바이트코드 ISA를 정의한다.

- 구현 언어: C
- 실행 환경: WASM(브라우저)에서 동작하는 VM
- 설계 목표: 단순성, 결정적 실행, 단계 실행(step) 시각화 친화성

> 주의: 본 문서의 추상 머신은 C 표준의 “C abstract machine”을 그대로 구현하는 것이 아니라,
> MiniC89 교육 목적에 맞게 정의한 별도의 실행 모델이다.

---

## 1. 데이터 타입 (Data Types)

이 머신은 단 두 가지의 기본 타입만을 다룬다.

| 타입 | 설명 | 비트/범위 | 비고 |
| :--- | :--- | :--- | :--- |
| **I16** | 16-bit Signed Integer | -32,768 ~ 32,767 | C 언어의 `int`에 대응 (교육용 축소 모델) |
| **FUN** | Function Reference | 0 (NULL), 1..N | 함수 테이블 인덱스. 함수 포인터 역할 |

---

## 2. 아키텍처 및 상태 (Machine Architecture)

이 가상 머신은 전형적인 **스택 머신** 구조를 따르며, 시각화를 위해 **Call Stack**과 **Operand Stack**을 명시적으로 분리한다.

### 2.1 레지스터 (Registers)
* **PC (Program Counter):** `(func_id, ip)` 쌍. 현재 실행 중인 명령어 위치.
* **SP (Stack Pointer):** 구현 레벨에서 Operand Stack의 최상단을 가리킴.
* **FP (Frame Pointer):** 구현 레벨에서 현재 Call Stack Frame을 가리킴.

### 2.2 메모리 구조 (Memory Structure)
1. **Code Area:** 읽기 전용. `functions[1..N]` 테이블과 각 함수의 바이트코드.
2. **Operand Stack:** 연산의 중간 결과값이 저장되는 공간. (Push/Pop 방식)
3. **Call Stack (Frame Stack):** 함수 호출 시마다 생성되는 Frame들의 스택.
    * **Frame 구조:**
        * `return_pc`: 복귀 주소
        * `locals[]`: 지역 변수 저장소 (Parameter 포함)
            * 각 슬롯은 값과 함께 **상태(INIT/UNINIT)** 플래그를 가짐.

### 2.3 실행 상태 (Lifecycle Status)
* **RUNNING:** 정상 실행 중.
* **HALTED:** `main` 함수 리턴으로 인한 정상 종료.
* **TRAPPED:** 런타임 오류 또는 UB 감지로 인한 비정상 종료.

---

## 3. 명령어 집합 (Instruction Set)

모든 명령어는 1바이트의 **Opcode**와 0개 이상의 **Operand**를 가진다.

### 3.1 스택 및 상수 조작 (Stack & Constants)

| 명령어 | Operand | 스택 변화 (Before -> After) | 설명/TRAP |
| :--- | :--- | :--- | :--- |
| **PUSH_I16** | `val` (i16) | `[...]` -> `[..., val]` | 상수 정수 푸시 |
| **PUSH_FUN** | `fid` (u16) | `[...]` -> `[..., fun]` | 함수 참조 푸시 (`TRAP_BAD_FUNID`) |
| **PUSH_NULL**| - | `[...]` -> `[..., null]` | NULL 함수 포인터 푸시 |
| **POP** | - | `[..., v]` -> `[...]` | 스택 최상단 값 제거 (문장 끝 처리용) |
| **DUP** | - | `[..., v]` -> `[..., v, v]` | 최상단 값 복제 |

### 3.2 로컬 변수 접근 (Locals)

| 명령어 | Operand | 스택 변화 | 설명/TRAP |
| :--- | :--- | :--- | :--- |
| **LOAD** | `idx` (u8) | `[...]` -> `[..., val]` | `locals[idx]` 로드.<br>**TRAP:** `UNINIT_READ` (미초기화 읽기) |
| **STORE** | `idx` (u8) | `[..., val]` -> `[..., val]` | `locals[idx]`에 저장.<br>**주의:** 값은 스택에 남음 (C의 대입 표현식 특성) |

### 3.3 산술 연산 (Arithmetic - I16)

모든 산술 연산은 오버플로우 발생 시 C 언어의 UB 정책에 따라 **TRAP**을 발생시킨다.

| 명령어 | 스택 변화 (`a, b` -> `res`) | TRAP 조건 (Undefined Behavior) |
| :--- | :--- | :--- |
| **ADD** | `[..., a, b]` -> `[..., a+b]` | `TRAP_INT_OVERFLOW` |
| **SUB** | `[..., a, b]` -> `[..., a-b]` | `TRAP_INT_OVERFLOW` |
| **MUL** | `[..., a, b]` -> `[..., a*b]` | `TRAP_INT_OVERFLOW` |
| **DIV** | `[..., a, b]` -> `[..., a/b]` | `TRAP_DIV_ZERO`, `TRAP_INT_OVERFLOW` (MIN/-1) |
| **MOD** | `[..., a, b]` -> `[..., a%b]` | `TRAP_DIV_ZERO`, `TRAP_INT_OVERFLOW` |
| **NEG** | `[..., a]` -> `[..., -a]` | `TRAP_INT_OVERFLOW` (MIN값 반전 시) |

### 3.4 비교 및 논리 (Comparison & Logic)

결과값은 참일 때 `1`, 거짓일 때 `0` (I16 타입)이다.

| 명령어 | 스택 변화 | 설명 |
| :--- | :--- | :--- |
| **EQ / NE** | `[..., a, b]` -> `[..., 0/1]` | 동등 비교 (I16, FUN 타입 허용) |
| **LT / LE** | `[..., a, b]` -> `[..., 0/1]` | 크기 비교 (I16만 허용) |
| **GT / GE** | `[..., a, b]` -> `[..., 0/1]` | 크기 비교 (I16만 허용) |
| **LNOT** | `[..., a]` -> `[..., 0/1]` | 논리 부정 (`!a`) |

### 3.5 제어 흐름 (Control Flow)

| 명령어 | Operand | 스택 변화 | 동작/설명 |
| :--- | :--- | :--- | :--- |
| **JMP** | `offset` | - | 무조건 점프 (`ip = target`) |
| **JZ** | `offset` | `[..., cond]` -> `[...]` | `cond == 0` 이면 점프 |
| **JNZ** | `offset` | `[..., cond]` -> `[...]` | `cond != 0` 이면 점프 |

### 3.6 함수 호출 (Function Call)

| 명령어 | Operand | 스택 변화 | 동작/설명 |
| :--- | :--- | :--- | :--- |
| **CALL** | `fid` (u16) | `[..., args]` -> `[..., ret]` | **Direct Call.**<br>인자 개수/타입 검사 후 새 프레임 생성 |
| **CALL_IND**| `argc` (u8) | `[..., args, fun]` -> `[..., ret]` | **Indirect Call.**<br>`fun` 포인터 검증(`NULL` 체크), 서명 검사 후 호출 |
| **RET** | - | `[..., ret]` -> `[...]` | 현재 프레임 제거, `ret` 값을 호출자 스택으로 이동 |

### 3.7 디버그 및 기타 (Debug)

| 명령어 | Operand | 동작 |
| :--- | :--- | :--- |
| **NOP** | - | 아무 동작 안 함 |
| **DBG_LINE**| `line` (u16)| `current_line = line` 갱신 (소스코드 하이라이팅용) |

---

## 4. 시각화 및 교육적 특징 (Educational Features)

이 ISA는 브라우저 상의 시각화를 위해 다음과 같은 메타데이터 활용을 권장한다.

1. **변수 유효 범위(Scope) 시각화:**
    * `locals_debug` 테이블을 이용해 현재 IP에서 유효하지 않은(Scope 밖인) 로컬 변수는 UI에서 "비활성화(dimmed)" 처리한다.
2. **Call Stack 애니메이션:**
    * `CALL` 명령 시 새 프레임이 쌓이는 과정과 `RET` 시 사라지는 과정을 애니메이션으로 보여준다.
3. **UB 강조:**
    * `TRAP` 발생 시, 단순히 멈추는 것이 아니라 **"왜 멈췄는지"** (예: `TRAP_UNINIT_READ`)를 팝업하고, 해당 메모리 슬롯을 붉게 표시한다.
---

## 5. 매우 작은 예시(참고)

### 5.1 표현식 즉시 반환
### 소스
```c
int add1(int a) {
    return a + 1;
}
```

### 바이트 코드
```
func_id: 2, name: "add1", params: 1, locals: 1 (a)

0: DBG_LINE 2        ; return a + 1;
1: LOAD 0            ; Load a
2: PUSH_I16 1        ; Push constant 1
3: ADD               ; a + 1
4: RET               ; Return top of stack
```

### 5.2 지역 변수 사용
### 소스
```c
int add(int a, int b) {
    int sum = a + b;
    return sum;
}
```

### 바이트코드(예시)
```
func_id: 1, name: "add", params: 2, locals: 3 (a, b, sum)

0: DBG_LINE 2        ; 소스 2번째 줄
1: LOAD 0            ; Load a (UNINIT 체크 -> OK)
2: LOAD 1            ; Load b
3: ADD               ; a + b (Overflow 체크)
4: STORE 2           ; sum = result (값은 스택에 남음)
5: POP               ; 대입식의 결과값 버림 (문장 종료)
6: DBG_LINE 3        ; 소스 3번째 줄
7: LOAD 2            ; return sum (Load sum)
8: RET               ; 함수 종료
```
