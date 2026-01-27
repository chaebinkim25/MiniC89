# MiniC89 VM 상태 스냅샷 JSON 스키마 (v0.2)

본 문서는 MiniC89 추상 머신(VM)의 실행 상태를 브라우저 UI가 시각화할 수 있도록,
VM이 외부로 노출하는 **상태 스냅샷(JSON)** 의 형식과 그 **JSON Schema**를 정의한다.

- 이 문서는 **언어 표준(Language Standard)** 이 아니라,
  **구현(컴파일러/VM)과 UI 사이의 인터페이스 규격**이다.
- 스냅샷은 보통 “step 실행”마다 1개씩 생성된다.

---

## 1. 스냅샷 의미

### 1.1 스냅샷은 “명령 실행 경계”의 상태이다
- 스냅샷의 `pc`는 **다음에 실행할 명령어의 위치**를 가리킨다.
- 예외:
  - `status == TRAPPED`인 경우 `pc`는 **트랩을 발생시킨 명령어의 위치**를 가리킨다.
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

- I16 정수: `{ "t": "i16", "v": -32768..32767 }`
- 함수 참조(FUN): `{ "t": "fun", "v": 0.. }`  
  - `v == 0`이면 null function reference
- 미초기화(UNINIT): `{ "t": "uninit" }`

> `UNINIT`는 locals 슬롯이 아직 초기화되지 않았음을 의미한다.

---

## 3. 프로그램 카운터(PC), step, status의 의미

### 3.1 PC
- `pc = { fid, ip }`
  - fid: 함수 ID
  - ip: 그 함수 코드 배열에서의 명령 인덱스(0부터)

### 3.2 step 번호
- `step = 0`은 **실행 시작 직전(첫 명령 실행 전)** 스냅샷을 권장한다.
- 이후 VM이 한 번 “명령 실행을 시도(step attempt)”할 때마다 `step`을 1 증가시킨다.
  - 성공하면 `RUNNING` 유지 + `pc`는 다음 명령 위치로 이동
  - TRAP이면 `TRAPPED` 상태 + `pc`는 **트랩을 일으킨 명령 위치**로 유지/표시

### 3.3 status가 TRAP 일 때

`status == TRAPPED`이면 `trap` 객체가 반드시 포함된다.

- `trap.code`는 트랩 원인(예: `TRAP_INT_OVERFLOW`, `TRAP_UNINIT_READ` 등)을 나타낸다.
- `trap.at_pc`는 트랩이 발생한 위치이다.
- `trap.at_source`는 해당 시점의 `DBG_LINE` 기반 소스 위치(가능하면 제공)이다.
- `trap.details`는 UI가 추가 설명을 표시할 수 있도록 선택적으로 제공한다.

### 3.4 status가 HALT 일 때

`status == HALTED`이면 `halt` 객체가 반드시 포함된다.

- `halt.result`는 엔트리 함수의 반환값(I16)이다.

---

## 4. Metadata JSON 스키마 

### 4.1 Metadata가 제공해야 하는 정보
UI가 스냅샷을 해석/표시하기 위해 필요한 정적 정보:

- 함수 테이블(fid → 함수 이름, param/local 개수)
- 각 함수의 바이트코드 디스어셈블(명령 리스트)
- ip → 소스 위치 매핑(라인 하이라이트용)
- 로컬 슬롯(slot) → 변수명(+스코프 범위)

### 4.2 Metadata JSON Schema (Draft 2020-12)

아래 스키마는 스냅샷 JSON을 검증하기 위한 **공식 JSON Schema**이다.

```json
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://minic89.local/schema/vm-metadata-v0.2.json",
  "title": "MiniC89 VM Metadata v0.2",
  "type": "object",
  "additionalProperties": false,
  "required": ["schema_version", "isa_version", "functions"],
  "properties": {
    "schema_version": { "const": "MiniC89.VM.Metadata.v0.2" },
    "isa_version": { "type": "string" },

    "limits": {
      "description": "선택: 실행 제한(예: step limit). 스냅샷을 가볍게 하기 위해 여기로 이동.",
      "type": "object",
      "additionalProperties": false,
      "required": [],
      "properties": {
        "step_limit": { "type": ["integer", "null"], "minimum": 0 }
      }
    },

    "functions": {
      "type": "array",
      "minItems": 1,
      "items": { "$ref": "#/$defs/functionMeta" }
    }
  },

  "$defs": {
    "instruction": {
      "type": "object",
      "additionalProperties": false,
      "required": ["op", "args"],
      "properties": {
        "op": { "type": "string" },
        "args": {
          "type": "array",
          "items": { "type": ["integer", "string", "null"] }
        }
      }
    },

    "sourceLoc": {
      "type": "object",
      "additionalProperties": false,
      "required": ["line"],
      "properties": {
        "line": { "type": ["integer", "null"], "minimum": 1 }
      }
    },

    "sourceMapEntry": {
      "description": "ip가 이 값 이상일 때 적용되는 소스 위치(변경 지점 테이블). ip 오름차순 정렬 권장.",
      "type": "object",
      "additionalProperties": false,
      "required": ["ip", "loc"],
      "properties": {
        "ip": { "type": "integer", "minimum": 0 },
        "loc": { "$ref": "#/$defs/sourceLoc" }
      }
    },

    "localDebug": {
      "type": "object",
      "additionalProperties": false,
      "required": ["slot", "name", "kind"],
      "properties": {
        "slot": { "type": "integer", "minimum": 0 },
        "name": { "type": "string" },
        "kind": { "type": "string", "enum": ["param", "local"] },

        "scope": {
          "description": "선택: 스코프 범위. 제공 시 UI가 스코프 밖 변수를 숨기거나 흐리게 표시 가능.",
          "type": ["object", "null"],
          "additionalProperties": false,
          "required": ["ip_start", "ip_end"],
          "properties": {
            "ip_start": { "type": "integer", "minimum": 0 },
            "ip_end": { "type": "integer", "minimum": 0 }
          }
        }
      }
    },

    "functionMeta": {
      "type": "object",
      "additionalProperties": false,
      "required": ["fid", "name", "param_count", "local_count", "code"],
      "properties": {
        "fid": { "type": "integer", "minimum": 1 },
        "name": { "type": "string" },

        "param_count": { "type": "integer", "minimum": 0 },
        "local_count": { "type": "integer", "minimum": 0 },

        "code": {
          "description": "디스어셈블. UI가 pc로 현재 명령을 찾는 데 사용.",
          "type": "array",
          "items": { "$ref": "#/$defs/instruction" }
        },

        "source_map": {
          "description": "선택: ip -> (file,line) 매핑. 제공 시 스냅샷에 source가 없어도 라인 하이라이트 가능.",
          "type": "array",
          "items": { "$ref": "#/$defs/sourceMapEntry" }
        },

        "locals": {
          "description": "선택: slot -> 변수명/종류/스코프. 제공 시 locals 배열을 변수 테이블로 표시 가능.",
          "type": "array",
          "items": { "$ref": "#/$defs/localDebug" }
        }
      }
    }
  }
}
```

### 4.3 Metadata 사용 방법 (UI 규칙)

UI는 스냅샷의 `pc = {fid, ip}`를 가지고:
1. `functions[]`에서 `fid`가 같은 함수 메타데이터를 찾는다.
2. 현재 명령은 `function.code[ip]`로 얻는다.
3. 현재 소스 라인은 `function.source_map`에서
   - `ip <= current_ip`인 entry중 가장 마지막 entry의 `loc.line`을 사용한다.
   - 없으면 라인 표시 불가

locals 표시:
- 스냅샷 프레임의 `locals[k]`는 slot=k의 값이다.
- `function.locals`가 있으면 slot->name 매핑으로 "변수이름:값"을 보여준다.
- scope가 있으면 ip 범위 밖 변수는 흐리게 처리

---

## 5. Snapshot JSON 스키마 

### 5.1 Snapshot이 포함해야 하는 정보

- 실행 상태(status), step, pc
- operand stack (값들)
- call stack (각 프레임의 fid/return_pc/locals 값 배열)
- TRAP시 trap 정보
- HALT시 halt 정보

### 4.2 Snapshot JSON Schema (Draft 2020-12)
```json
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "$id": "https://minic89.local/schema/vm-snapshot-v0.2.json",
  "title": "MiniC89 VM Snapshot v0.2",
  "type": "object",
  "additionalProperties": false,
  "required": ["schema_version", "step", "status", "pc", "operand_stack", "call_stack"],
  "properties": {
    "schema_version": { "const": "MiniC89.VM.Snapshot.v0.2" },

    "step": { "type": "integer", "minimum": 0 },

    "status": { "type": "string", "enum": ["RUNNING", "HALTED", "TRAPPED"] },

    "pc": { "$ref": "#/$defs/pcNullable" },

    "operand_stack": {
      "type": "array",
      "items": { "$ref": "#/$defs/value" }
    },

    "call_stack": {
      "type": "array",
      "items": { "$ref": "#/$defs/frame" }
    },

    "trap": { "$ref": "#/$defs/trap" },
    "halt": { "$ref": "#/$defs/halt" }
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

    "value": {
      "description": "v0.2: i16는 정수(number)로 직접 표현. fun/uninit는 객체로 표현.",
      "oneOf": [
        { "type": "integer", "minimum": -32768, "maximum": 32767 },

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

    "frame": {
      "type": "object",
      "additionalProperties": false,
      "required": ["fid", "return_pc", "locals"],
      "properties": {
        "fid": { "type": "integer", "minimum": 1 },

        "return_pc": {
          "description": "엔트리 프레임이면 null일 수 있음.",
          "$ref": "#/$defs/pcNullable"
        },

        "locals": {
          "description": "locals[k]는 slot=k의 값이다. 길이는 해당 함수의 local_count와 일치하는 것이 권장된다.",
          "type": "array",
          "items": { "$ref": "#/$defs/value" }
        }
      }
    },

    "trap": {
      "type": "object",
      "additionalProperties": false,
      "required": ["code"],
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

        "details": {
          "description": "선택: UI가 추가 정보를 표시할 수 있는 자유 형식 객체(예: slot 번호, 기대 시그니처 등).",
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
        "result": { "$ref": "#/$defs/value" }
      }
    }
  }
}
```

## 6. 스냅샷 예시

### 6.1 Metadata 예시

C 소스 코드:
```c
int main
{
  return 0;
}
```

Snapshot:
```json
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "schema_version": "MiniC89.VM.Metadata.v0.2",
  "isa_version": "MiniC89.ISA.v0.1",
  
  "limits": { "step_limit": 1000 },

  "functions": [
    {
      "fid": 1,
      "name": "main",
      "param_count": 0,
      "local_count": 0,
      
      "code": [
        { "op": "PUSH_I16", "args": [0] }, // ip: 0
        { "op": "RET", "args": [] }        // ip: 1
      ],

      "source_map": [
        {
          "ip": 0,            // 0번 명령어부터는
          "loc": { "line": 3 } // 소스코드 3번째 줄("return 0;")이다.
        }
      ],

      "locals": []
    }
  ]
}
```

### 6.2 RUNNING 예시
C 소스 코드:
```c
int main
{
  return 0;
}
```

Snapshot (RET 실행할 차례):
```json
{
  "schema_version": "MiniC89.VM.Snapshot.v0.2",
  "step": 2,
  "status": "RUNNING",
  "pc": {
    "fid": 1,
    "ip": 1
  },
  "operand_stack": [
    0
  ],
  "call_stack": [
    {
      "fid": 1,
      "return_pc": null,
      "locals": []
    }
  ]
}
```



### 6.3 HALTED 예시
C 소스 코드:
```c
int main
{
  return 0;
}
```

Snapshot (RET 실행 후):
```json
{
  "$schema": "https://json-schema.org/draft/2020-12/schema",
  "schema_version": "MiniC89.VM.Snapshot.v0.2",
  "step": 3,
  "status": "HALTED",
  "pc": null,
  "operand_stack": [],
  "call_stack": [],
  "halt": {
    "result": 0
  }
}
```

## 7. 구현 메모
- 스냅샷 생성 시:

  - locals는 slot 인덱스 순서 배열로 내보내기 → UI가 가장 처리하기 쉬움

- 함수 포인터 값은 { "t":"fun","v":fid }로 내보내면

  - UI는 metadata로 함수명을 즉시 표시 가능

- 소스 라인은 스냅샷에서 제거했으므로

  - 반드시 metadata의 source_map을 채우는 것을 권장
  
---
