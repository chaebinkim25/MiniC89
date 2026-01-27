# MiniC89 VM 상태 스냅샷 JSON 스키마 (v0.1)

본 문서는 MiniC89 추상 머신(VM)의 실행 상태를 브라우저 UI가 시각화할 수 있도록,
VM이 외부로 노출하는 **상태 스냅샷(JSON)** 의 형식과 그 **JSON Schema**를 정의한다.

- 이 문서는 **언어 표준(Language Standard)** 이 아니라,
  **구현(컴파일러/VM)과 UI 사이의 인터페이스 규격**이다.
- 스냅샷은 보통 “step 실행”마다 1개씩 생성된다.

---

## 1. 스냅샷 의미(중요)

### 1.1 스냅샷은 “명령 실행 경계”의 상태이다
- 스냅샷의 `pc`는 **다음에 실행할 명령어의 위치**를 가리킨다.
- 예외:
  - `status == TRAPPED`인 경우 `pc`는 **트랩을 발생시킨 명령어의 위치**를 가리킨다(하이라이트 용).
  - `status == HALTED`인 경우 `pc`는 `null`일 수 있다.

### 1.2 스택/프레임 배열의 방향
- `operand_stack`은 **바닥(bottom) → 꼭대기(top)** 순서로 나열한다.
  - 즉, 배열의 마지막 요소가 stack top.
- `call_stack`은 **가장 오래된 프레임(바닥) → 현재 프레임(꼭대기)** 순서로 나열한다.
  - 즉, 배열의 마지막 프레임이 현재 실행 중인 프레임.

### 1.3 source line
- `source.line`은 VM이 마지막으로 실행한 `DBG_LINE`의 값이다.
- 매핑 정보가 없거나 아직 `DBG_LINE`이 실행되지 않았다면 `null`일 수 있다.

---

## 2. 값(Value) 표현

VM은 값(Value)을 다음 3종류로만 표현한다.

- I8 정수: `{ "t": "i8", "v": -128..127 }`
- 함수 참조(FUN): `{ "t": "fun", "v": 0.. }`  
  - `v == 0`이면 null function reference
- 미초기화(UNINIT): `{ "t": "uninit" }`

> `UNINIT`는 locals 슬롯이 아직 초기화되지 않았음을 의미한다.

---

## 3. TRAP 정보

`status == TRAPPED`이면 `trap` 객체가 반드시 포함된다.

- `trap.code`는 트랩 원인(예: `TRAP_INT_OVERFLOW`, `TRAP_UNINIT_READ` 등)을 나타낸다.
- `trap.at_pc`는 트랩이 발생한 위치이다.
- `trap.at_source`는 해당 시점의 `DBG_LINE` 기반 소스 위치(가능하면 제공)이다.
- `trap.details`는 UI가 추가 설명을 표시할 수 있도록 선택적으로 제공한다.

---

## 4. HALT 정보

`status == HALTED`이면 `halt` 객체가 반드시 포함된다.

- `halt.result`는 엔트리 함수의 반환값(I8)이다.

---

## 5. JSON Schema (Draft 2020-12)

아래 스키마는 스냅샷 JSON을 검증하기 위한 **공식 JSON Schema**이다.

```json
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://minic89.local/schema/vm-snapshot-v0.1.json",
  "title": "MiniC89 VM Snapshot v0.1",
  "type": "object",
  "additionalProperties": false,
  "required": [
    "schema_version",
    "step",
    "status",
    "pc",
    "source",
    "operand_stack",
    "call_stack"
  ],
  "properties": {
    "schema_version": {
      "const": "MiniC89.VM.Snapshot.v0.1"
    },

    "step": {
      "type": "integer",
      "minimum": 0,
      "description": "스냅샷 시퀀스 번호(또는 실행된 명령 개수). step=0은 초기 스냅샷을 권장."
    },

    "status": {
      "type": "string",
      "enum": ["RUNNING", "HALTED", "TRAPPED"]
    },

    "pc": {
      "description": "현재(다음) 실행 위치. TRAPPED일 때는 트랩 발생 명령 위치. HALTED일 때 null 가능.",
      "$ref": "#/$defs/pcNullable"
    },

    "next_instruction": {
      "description": "선택: pc 위치의 디코딩된 명령(표시용).",
      "$ref": "#/$defs/instruction"
    },

    "source": {
      "description": "DBG_LINE 기반 소스 위치(선택적으로 file 포함).",
      "$ref": "#/$defs/source"
    },

    "operand_stack": {
      "type": "array",
      "description": "바닥->꼭대기 순서. 마지막 원소가 top.",
      "items": { "$ref": "#/$defs/value" }
    },

    "call_stack": {
      "type": "array",
      "description": "바닥(가장 오래된 프레임)->현재 프레임 순서. 마지막 프레임이 현재 프레임.",
      "items": { "$ref": "#/$defs/frame" }
    },

    "trap": {
      "description": "status==TRAPPED인 경우 필수.",
      "$ref": "#/$defs/trap"
    },

    "halt": {
      "description": "status==HALTED인 경우 필수.",
      "$ref": "#/$defs/halt"
    },

    "counters": {
      "description": "선택: 실행 제한/계측 정보.",
      "$ref": "#/$defs/counters"
    }
  },

  "allOf": [
    {
      "if": { "properties": { "status": { "const": "TRAPPED" } } },
      "then": { "required": ["trap"] }
    },
    {
      "if": { "properties": { "status": { "const": "HALTED" } } },
      "then": { "required": ["halt"] }
    },
    {
      "if": { "properties": { "status": { "enum": ["RUNNING", "TRAPPED"] } } },
      "then": {
        "properties": { "pc": { "$ref": "#/$defs/pc" } }
      }
    }
  ],

  "$defs": {
    "pc": {
      "type": "object",
      "additionalProperties": false,
      "required": ["fid", "ip"],
      "properties": {
        "fid": { "type": "integer", "minimum": 1 },
        "ip": { "type": "integer", "minimum": 0 }
      }
    },

    "pcNullable": {
      "oneOf": [
        { "type": "null" },
        { "$ref": "#/$defs/pc" }
      ]
    },

    "source": {
      "type": "object",
      "additionalProperties": false,
      "required": ["line"],
      "properties": {
        "file": { "type": ["string", "null"] },
        "line": { "type": ["integer", "null"], "minimum": 1 }
      }
    },

    "value": {
      "oneOf": [
        {
          "type": "object",
          "additionalProperties": false,
          "required": ["t", "v"],
          "properties": {
            "t": { "const": "i8" },
            "v": { "type": "integer", "minimum": -128, "maximum": 127 }
          }
        },
        {
          "type": "object",
          "additionalProperties": false,
          "required": ["t", "v"],
          "properties": {
            "t": { "const": "fun" },
            "v": { "type": "integer", "minimum": 0 }
          }
        },
        {
          "type": "object",
          "additionalProperties": false,
          "required": ["t"],
          "properties": {
            "t": { "const": "uninit" }
          }
        }
      ]
    },

    "localSlot": {
      "type": "object",
      "additionalProperties": false,
      "required": ["slot", "value"],
      "properties": {
        "slot": { "type": "integer", "minimum": 0 },
        "name": { "type": ["string", "null"] },
        "value": { "$ref": "#/$defs/value" }
      }
    },

    "frame": {
      "type": "object",
      "additionalProperties": false,
      "required": ["fid", "return_pc", "locals"],
      "properties": {
        "fid": { "type": "integer", "minimum": 1 },
        "func_name": { "type": ["string", "null"] },

        "return_pc": {
          "description": "엔트리 프레임이면 null일 수 있음.",
          "$ref": "#/$defs/pcNullable"
        },

        "param_count": { "type": ["integer", "null"], "minimum": 0 },
        "local_count": { "type": ["integer", "null"], "minimum": 0 },

        "locals": {
          "type": "array",
          "items": { "$ref": "#/$defs/localSlot" }
        }
      }
    },

    "instruction": {
      "type": "object",
      "additionalProperties": false,
      "required": ["op", "args"],
      "properties": {
        "op": { "type": "string" },
        "args": {
          "type": "array",
          "items": {
            "type": ["integer", "string", "null"]
          }
        }
      }
    },

    "trap": {
      "type": "object",
      "additionalProperties": false,
      "required": ["code", "at_pc"],
      "properties": {
        "code": {
          "type": "string",
          "enum": [
            "TRAP_INT_OVERFLOW",
            "TRAP_DIV_ZERO",
            "TRAP_UNINIT_READ",
            "TRAP_TYPE",
            "TRAP_BAD_LOCAL",
            "TRAP_BAD_FUNID",
            "TRAP_BAD_JUMP",
            "TRAP_CALL_NULLFUN",
            "TRAP_BAD_SIGNATURE",
            "TRAP_STACK",
            "TRAP_CALLSTACK",
            "TRAP_STEP_LIMIT",
            "TRAP_INTERNAL"
          ]
        },
        "message": { "type": ["string", "null"] },
        "at_pc": { "$ref": "#/$defs/pc" },
        "at_source": { "$ref": "#/$defs/source" },
        "details": {
          "type": ["object", "null"],
          "additionalProperties": true
        }
      }
    },

    "halt": {
      "type": "object",
      "additionalProperties": false,
      "required": ["result"],
      "properties": {
        "result": { "$ref": "#/$defs/value" },
        "at_pc": { "$ref": "#/$defs/pcNullable" }
      }
    },

    "counters": {
      "type": "object",
      "additionalProperties": false,
      "required": ["steps_executed"],
      "properties": {
        "steps_executed": { "type": "integer", "minimum": 0 },
        "step_limit": { "type": ["integer", "null"], "minimum": 0 }
      }
    }
  }
}
```
---

## 6. 스냅샷 예시

### 6.1 RUNNING 예시

```json
{
  "schema_version": "MiniC89.VM.Snapshot.v0.1",
  "step": 0,
  "status": "RUNNING",
  "pc": { "fid": 1, "ip": 0 },
  "next_instruction": { "op": "DBG_LINE", "args": [1] },
  "source": { "file": "main.c", "line": null },
  "operand_stack": [],
  "call_stack": [
    {
      "fid": 1,
      "func_name": "main",
      "return_pc": null,
      "param_count": 0,
      "local_count": 2,
      "locals": [
        { "slot": 0, "name": "i",   "value": { "t": "uninit" } },
        { "slot": 1, "name": "sum", "value": { "t": "uninit" } }
      ]
    }
  ],
  "counters": { "steps_executed": 0, "step_limit": 100000 }
}
```

### 6.2 TRAPPED 예시(미초기화 읽기)
```json
{
  "schema_version": "MiniC89.VM.Snapshot.v0.1",
  "step": 7,
  "status": "TRAPPED",
  "pc": { "fid": 1, "ip": 3 },
  "next_instruction": { "op": "LOAD_LOCAL", "args": [1] },
  "source": { "file": "main.c", "line": 5 },
  "operand_stack": [],
  "call_stack": [
    {
      "fid": 1,
      "func_name": "main",
      "return_pc": null,
      "locals": [
        { "slot": 0, "name": "i",   "value": { "t": "i8", "v": 3 } },
        { "slot": 1, "name": "sum", "value": { "t": "uninit" } }
      ]
    }
  ],
  "trap": {
    "code": "TRAP_UNINIT_READ",
    "message": "read of uninitialized local slot",
    "at_pc": { "fid": 1, "ip": 3 },
    "at_source": { "file": "main.c", "line": 5 },
    "details": { "slot": 1 }
  }
}
```

### 6.3 HALTED 예시
```json
{
  "schema_version": "MiniC89.VM.Snapshot.v0.1",
  "step": 42,
  "status": "HALTED",
  "pc": null,
  "source": { "file": "main.c", "line": 12 },
  "operand_stack": [],
  "call_stack": [],
  "halt": {
    "result": { "t": "i8", "v": 0 },
    "at_pc": null
  }
}
```

## 7. 구현 메모(권장)
- VM은 `step()` 호출마다:
  1. 현재 `pc`의 명령 실행
  2. 상태 갱신
  3. 새 스냅샷 생성/반환
 - UI는 연속 스냅샷의 diff로 변화를 표시할 수 있다.
 - `next_instruction`은 UI가 디스어셈블을 따로 하지 않아도 되게 해준다(권장).

---
