# MiniC89 Abstract Machine ISA (v0.1)

본 문서는 MiniC89 프로그램을 브라우저에서 실행/시각화하기 위한
**교육용 추상 머신(Educational Abstract Machine)** 과 그 바이트코드 ISA를 정의한다.

- 구현 언어: C
- 실행 환경: WASM(브라우저)에서 동작하는 VM
- 설계 목표: 단순성, 결정적 실행, 단계 실행(step) 시각화 친화성

> 주의: 본 문서의 추상 머신은 C 표준의 “C abstract machine”을 그대로 구현하는 것이 아니라,
> MiniC89 교육 목적에 맞게 정의한 별도의 실행 모델이다.

---

## 1. 값(Value)과 타입(Type)

VM은 런타임 값에 대해 아래 두 타입만을 가진다.

### 1.1 I16 (16-bit signed integer)
- 표현: 16-bit 2의 보수
- 값 범위: -32768 .. 32767

### 1.2 FUN (function reference; 함수 참조/함수 포인터 값)
- 의미: 함수 테이블의 항목을 가리키는 참조값
- 표현: 0 이상의 정수 ID로 표현할 수 있다.
  - `0`은 **null function reference** 를 의미한다.
  - `1..N`은 유효한 함수 ID.

> MiniC89 언어에서 `int`는 I8에 해당하며,
> “함수 포인터” 변수/표현식은 FUN에 해당한다.

---

## 2. 머신 상태(Machine State)

머신 상태는 다음 구성요소로 정의한다.

### 2.1 프로그램 카운터(PC)
- PC는 `(func_id, ip)` 쌍이다.
  - `func_id`: 현재 실행 중인 함수 ID
  - `ip`: 해당 함수의 **명령어 인덱스**(0부터)

### 2.2 Operand Stack
- 값(Value)들의 스택.
- 대부분의 명령은 스택에서 값을 pop/push 하여 계산한다.

### 2.3 Call Stack (프레임 스택)
각 프레임(Frame)은 다음을 가진다.

- `return_pc`: 호출자 복귀 위치 `(func_id, ip)`
- `locals[]`: 로컬 슬롯 배열
- `func_id`: 현재 프레임이 속한 함수 ID

#### locals의 초기 상태
- 함수 호출 시, 해당 함수의 `local_count`만큼 locals 슬롯이 생성된다.
- **모든 locals는 UNINIT 상태로 초기화**된다.
- 단, 매개변수(parameter)에 해당하는 슬롯은 호출 인자로 즉시 채워진다.

> UNINIT는 “미초기화” 상태를 의미하며, LOAD 시 UB(trap)의 근거가 된다.

### 2.4 실행 상태(Status)
- `RUNNING`
- `HALTED` (정상 종료)
- `TRAPPED` (오류/UB 감지로 중단)

### 2.5 디버그 상태(시각화용)
- `current_source_line` (정수, 선택)
- 구현은 바이트코드에 삽입된 `DBG_LINE` 명령을 통해 이를 갱신할 수 있다.

---

## 3. 모듈/함수 단위(Program Representation)

### 3.1 Module
- Module은 함수 테이블 `functions[1..N]`을 가진다.
- 함수 ID 1..N은 고정된 순서로 할당된다(컴파일러가 결정).

### 3.2 Function Metadata
각 함수는 최소 다음 메타데이터를 가진다.

- `name`: 함수 이름(디버깅/표시용)
- `param_count`: 매개변수 개수 (0..255)
- `local_count`: locals 슬롯 개수 (param 포함; 0..255)
- `code[]`: 명령어 배열
- (선택) `locals_debug[]`: 각 locals 슬롯의 변수명/스코프 정보(시각화용)

#### locals 슬롯 배치 규칙(권장; 컴파일러 규칙)
- `locals[0 .. param_count-1]`  : 매개변수
- `locals[param_count .. local_count-1]`: 지역변수

---

## 4. UB(Undefined Behavior) 처리 정책 (추상 머신 관점)

MiniC89 언어에서 UB는 “정의되지 않은 동작”이다.
이 추상 머신은 교육/시각화를 위해 다음 정책을 채택한다.

- VM이 UB를 **감지한 경우 즉시 TRAPPED로 전환**할 수 있다.
- TRAPPED 전환 시, 가능한 경우 원인을 함께 기록할 수 있다
  (예: `TRAP_INT_OVERFLOW`, `TRAP_DIV_ZERO`, `TRAP_UNINIT_READ`, ...).

이 정책은 “UB를 숨기지 않고 드러내는 교육”에 부합한다.

---

## 5. 명령어(Instruction) 형식

### 5.1 기본 규칙
- `ip`는 “명령어 인덱스” 단위로 증가한다.
- 점프 명령은 **현재 함수 내부의 ip**를 대상으로 한다.
- 한 step은 기본적으로 **명령어 1개 실행**이다.

### 5.2 표기법
- 스택 효과를 다음처럼 표기한다.
  - Before: `[..., a, b]`
  - After:  `[..., result]`

---

## 6. ISA: 명령어 집합

아래 명령어들은 v0.1에서 “필수(core)”로 정의한다.

---

### 6.1 디버그/무효 명령

#### `NOP`
- 효과: 아무 것도 하지 않는다.

#### `DBG_LINE line`
- 효과: `current_source_line = line` 로 갱신한다.
- 실행 의미는 없으며 시각화 목적이다.

---

### 6.2 상수/스택 조작

#### `PUSH_I16 k`
- 입력: `k`는 -32768 .. 32767 범위의 정수 상수
- 스택: `[...] -> [..., I16(k)]`

#### `PUSH_FUN fid`
- 스택: `[...] -> [..., FUN(fid)]`
- 제약: `fid`는 1..N의 유효한 함수 ID여야 한다.
  - 아니면 TRAP(`TRAP_BAD_FUNID`)

#### `PUSH_NULLFUN`
- 스택: `[...] -> [..., FUN(0)]`

#### `POP`
- 스택: `[..., x] -> [...]`

#### `DUP`
- 스택: `[..., x] -> [..., x, x]`

---

### 6.3 로컬 접근

#### `LOAD_LOCAL slot`
- 스택: `[...] -> [..., v]`
- 동작:
  - locals[slot] 값을 스택에 push
- TRAP:
  - slot 범위 밖: `TRAP_BAD_LOCAL`
  - locals[slot]이 UNINIT: `TRAP_UNINIT_READ`

#### `STORE_LOCAL slot`
- 스택: `[..., v] -> [..., v]`   *(C의 “대입식이 값으로 평가됨”을 반영)*
- 동작:
  - 스택에서 v pop
  - locals[slot] = v 로 저장
  - 동일한 v를 다시 push (대입식 결과)
- TRAP:
  - slot 범위 밖: `TRAP_BAD_LOCAL`

> 주: “대입문”(`x = expr;`)에서는 컴파일러가 마지막에 `POP`을 추가하여 결과를 버린다.

---

### 6.4 정수 연산 (I8)

#### 공통 타입 규칙
- 아래 연산은 스택에서 I16 두 개(또는 한 개)를 요구한다.
- 타입이 I16이 아니면 TRAP(`TRAP_TYPE`)

#### `ADD`
- 스택: `[..., a, b] -> [..., (a+b)]`
- TRAP(UB 감지):
  - 결과가 [-32768, 32767] 범위 밖이면 `TRAP_INT_OVERFLOW`

#### `SUB`
- 스택: `[..., a, b] -> [..., (a-b)]`
- TRAP:
  - overflow면 `TRAP_INT_OVERFLOW`

#### `MUL`
- 스택: `[..., a, b] -> [..., (a*b)]`
- TRAP:
  - overflow면 `TRAP_INT_OVERFLOW`

#### `NEG`
- 스택: `[..., a] -> [..., (-a)]`
- TRAP:
  - a == -32768 이면 overflow → `TRAP_INT_OVERFLOW`

#### `DIV`
- 스택: `[..., a, b] -> [..., (a/b)]`
- TRAP(UB 감지):
  - b == 0 → `TRAP_DIV_ZERO`
  - a == -32768 && b == -1 → `TRAP_INT_OVERFLOW`

#### `MOD`
- 스택: `[..., a, b] -> [..., (a%b)]`
- TRAP(UB 감지):
  - b == 0 → `TRAP_DIV_ZERO`
  - a == -32768 && b == -1 → `TRAP_INT_OVERFLOW`

---

### 6.5 비교/논리 (결과는 I8 0/1)

#### `EQ`
- 스택: `[..., x, y] -> [..., I16(x==y ? 1 : 0)]`
- 허용:
  - I16 vs I16
  - FUN vs FUN
- TRAP:
  - 타입이 섞이면 `TRAP_TYPE`

#### `NE`
- 스택: `[..., x, y] -> [..., I16(x!=y ? 1 : 0)]`
- 허용/TRAP는 EQ와 동일

#### `LT`, `LE`, `GT`, `GE`
- 스택: `[..., a, b] -> [..., I16(a<b ? 1 : 0)]` 등
- 허용: I16 vs I16만
- TRAP:
  - FUN 포함 시 `TRAP_TYPE`

#### `LNOT`
- 스택: `[..., a] -> [..., I16(a==0 ? 1 : 0)]`
- 허용: I16만
- TRAP: 타입 불일치 시 `TRAP_TYPE`

> `&&`/`||`의 short-circuit은 별도 명령이 아니라
> `JZ/JNZ/JMP` 조합으로 컴파일한다.

---

### 6.6 제어 흐름

#### `JMP target_ip`
- 동작: `ip = target_ip`
- TRAP:
  - target_ip가 코드 범위 밖이면 `TRAP_BAD_JUMP`

#### `JZ target_ip`
- 스택: `[..., cond] -> [...]`
- 동작:
  - cond는 I6이어야 함
  - cond == 0 이면 `ip = target_ip`, 아니면 다음 명령으로 진행
- TRAP:
  - cond 타입 불일치: `TRAP_TYPE`
  - target_ip 범위 밖: `TRAP_BAD_JUMP`

#### `JNZ target_ip`
- 스택: `[..., cond] -> [...]`
- 동작:
  - cond != 0 이면 점프
- TRAP는 JZ와 동일

---

### 6.7 함수 호출/반환

#### `CALL_DIRECT fid`
- 스택: `[..., arg1, arg2, ..., argN] -> [..., ret]`
- 동작:
  - N은 `functions[fid].param_count`
  - 스택에서 args를 pop하여 새 프레임 locals[0..N-1]에 채운다
  - 새 프레임으로 전환하고 `(func_id=fid, ip=0)`부터 실행
  - return 시 ret(I16)이 호출자 스택에 push된다
- TRAP:
  - fid가 유효하지 않으면 `TRAP_BAD_FUNID`
  - args 개수 부족/스택 언더플로는 `TRAP_STACK`
  - 인자 타입이 I16이 아니면 `TRAP_TYPE` (MiniC89의 함수 인자는 int만 허용)

#### `CALL_IND expected_param_count`
- 스택: `[..., arg1, arg2, ..., argN, fun] -> [..., ret]`
  - 여기서 N == expected_param_count
- 동작:
  - fun은 FUN이어야 함
  - fun == 0 이면 TRAP(UB): `TRAP_CALL_NULLFUN`
  - fid = fun의 함수 ID
  - `functions[fid].param_count == expected_param_count` 를 검사
    - 불일치면 TRAP: `TRAP_BAD_SIGNATURE`
  - args를 pop하여 새 프레임 locals에 채우고 진입
- TRAP:
  - fun 타입 불일치: `TRAP_TYPE`
  - 기타는 CALL_DIRECT와 동일

#### `RET`
- 스택: `[..., ret] -> [...]`
- 동작:
  - ret은 I16이어야 함
  - 현재 프레임을 pop하고 return_pc로 복귀
  - 호출자 스택에 ret을 push
- TRAP:
  - ret 타입 불일치: `TRAP_TYPE`
  - call stack 언더플로(엔트리에서 RET 등): `TRAP_CALLSTACK`

---

## 7. 프로그램 시작/종료 규칙(호스트 규약)

- 호스트는 엔트리 함수 ID(`entry_fid`)를 지정한다.
- VM은 `CALL_DIRECT entry_fid`와 동일한 방식으로 시작한다(인자 없음 권장).
- 엔트리 함수가 `RET`하면 VM은 `HALTED`로 전환하며,
  그 반환값(I16)이 프로그램 결과가 된다.

> 일반적인 모드는 `int main(void)`를 entry로 삼는다.
> (단, 이 문서는 online judge 규약을 포함하지 않는다.)

---

## 8. 시각화에 필요한 최소 디버그 메타데이터(권장)

ISA 자체와 별개로, 시각화(UI)를 위해 아래 메타데이터를 권장한다.

- 각 함수의 locals 슬롯에 대해:
  - `name` (변수명)
  - `slot`
  - `scope_begin_ip`, `scope_end_ip` (스코프 표시용)
- `DBG_LINE` 삽입 또는 (ip -> line) 매핑 테이블

---

## 9. 매우 작은 예시(참고)

### 소스
```c
int add1(int x) {
    return x + 1;
}
```

### 바이트코드(예시)
```
0: DBG_LINE 1
1: LOAD_LOCAL 0
2: PUSH_I16 1
3: ADD
4: RET
```
