# MiniC89 Language Standard
**Draft Version:** v0.2  
**Status:** Writing

본 문서는 사이버보안학과 신입생 교육을 목적으로 하는  
C89 부분집합 언어 **MiniC89**의 공식 표준을 정의한다.

이 표준은 **학생, TA, 채점기, 컴파일러/VM 구현자** 모두의 공통 기준이다.

---

## 1. Introduction

### 1.1 Purpose

본 문서는 사이버보안학과 신입생 교육을 목적으로 하는
C89 부분집합 언어 MiniC89의 공식 언어 표준을 정의한다.

이 표준은 학생, TA, 자동 채점기, 컴파일러/VM 구현자가
공통으로 참조하는 단일 기준(source of truth)이다.

### 1.2 Design Goals

- 초심자를 위한 최소 언어
- ISO C89 의미론 보존
- 위험한 동작을 숨기지 않음
- 결정적 시각화와 의미론 분리
- 단일 번역 단위, 단순 실행 모델

---

### 1.3 Relationship to ISO C89

- MiniC89는 ISO C89의 엄격한 부분집합이다.
- 모든 유효한 MiniC89 프로그램은 유효한 C89 프로그램이다.
- 그 역은 성립하지 않는다.
---

## 2. Conformance

### 2.1 Language Conformance
MiniC89 프로그램은 본 표준의 모든 MUST / MUST NOT 규칙을
만족해야 한다.

---

### 2.2 Implementation Conformance
MiniC89 구현체는 다음을 만족해야 한다.

- 본 표준에 정의되지 않은 문법을 허용하지 않는다.
- MUST 오류를 컴파일 타임에 검출한다.
- 오류 코드를 반드시 출력한다.
---
### 2.3 Normative Keywords and Document Conventions (Normative)

본 절은 본 표준 문서 전체에서 사용되는 규범 키워드의 의미와,
“규범(Normative) / 비규범(Non-Normative)” 텍스트의 효력을 정의한다.

---

#### 2.3.1 Normative vs Non-Normative Text

- 본 표준에서 다음에 해당하는 내용은 “규범적(Normative)”이며,
  MiniC89 적합성(conformance) 판단의 기준이 된다.
  - 제목에 (Normative)가 명시된 절/하위절
  - "Normative Rules" 하위 섹션의 모든 문장
  - "EBNF Definition (Normative)"에 포함된 문법 정의
  - "Operator Hierarchy (Normative)" 및 우선순위/결합 규칙 표
  - "Diagnostics (Normative)"에 포함된 오류 코드/발생 조건/필수 메시지

- 다음에 해당하는 내용은 “비규범적(Non-Normative)”이며,
  구현/채점/학생 이해를 돕기 위한 설명일 뿐 언어 의미를 추가/변경하지 않는다.
  - "Notes (Non-Normative)"
  - "Informal Description (Non-Normative)"
  - "Allowed Examples", "Forbidden Examples" (단, 예제에 “MUST” 등의 규범 문구가 포함된 경우는 예외)

- 규범적 텍스트와 비규범적 텍스트(예제/노트)가 충돌할 경우,
  규범적 텍스트가 우선한다.
  - 예제는 “설명 목적”이며, 언어를 정의하지 않는다.

- 본 표준의 규범 키워드는 대문자(MUST, SHOULD 등)로 쓰인 경우에만
  규범적 의미를 갖는다. (소문자 must/should 등의 일반 표현은 규범적 의미가 없다.)

---

#### 2.3.2 Requirement Keywords

본 표준에서 사용되는 규범 키워드는 다음 의미를 갖는다.

- MUST
  - 절대적인 요구사항이다.
  - 프로그램 또는 구현체가 이를 위반하면 MiniC89 적합(conforming)으로 간주될 수 없다.

- MUST NOT
  - 절대적인 금지사항이다.
  - 프로그램 또는 구현체가 이를 위반하면 MiniC89 적합으로 간주될 수 없다.

- SHOULD
  - 강하게 권장되는 요구사항이다.
  - 정당한 이유가 있는 경우에 한해 위반할 수 있으나,
    그 결과(호환성/교육 목적/채점/이식성 저하 등)를 충분히 이해하고 문서화해야 한다.

- SHOULD NOT
  - 강하게 권장되는 금지사항이다.
  - 정당한 이유가 있는 경우에 한해 허용될 수 있으나,
    그 결과를 충분히 이해하고 문서화해야 한다.

- MAY
  - 선택 사항이다.
  - 구현체/프로그램은 해당 기능을 제공/사용해도 되고 제공/사용하지 않아도 된다.

(필요 시)
- REQUIRED는 MUST와 동일한 의미로 사용될 수 있다.
- OPTIONAL은 MAY와 동일한 의미로 사용될 수 있다.

---

#### 2.3.3 Conformance and Diagnostics Terminology

- Conforming Program
  - 본 표준의 문법(EBNF)과 모든 정적 제약(MUST/MUST NOT)을 만족하는 프로그램을 말한다.
  - 단, 특정 입력/실행 경로에서 Undefined Behavior(UB)를 유발할 수 있는 프로그램도
    “문법적으로는 적합”할 수 있으나, UB가 발생한 이후의 동작은 정의되지 않는다.

- Conforming Implementation
  - 본 표준이 요구하는 문법/의미 규칙을 만족하고,
    본 표준이 “진단을 요구(MUST detect)”하는 모든 상황을 진단하는 구현체를 말한다.

- Compile-time
  - 파싱, 정적 분석, 의미 분석, 코드 생성 등 실행 이전 단계를 의미한다.
  - 인터프리터/VM 기반 구현체의 경우에도, 사용자 코드 실행 이전에 수행되는
    모든 정적 검사 단계를 포함한다.

- Diagnostic
  - 컴파일 타임에 보고되는 오류/경고 메시지를 말한다.
  - 본 표준이 오류 코드를 규정한 경우, 구현체는 반드시 오류 코드와 메시지를 함께 출력 MUST 한다.

- “MUST be Compile-time Error”
  - 구현체는 해당 프로그램을 거부(reject) MUST 하며,
    최소 1개의 진단을 error 수준으로 보고 MUST 한다.
  - 본 표준이 특정 오류 코드(MC89-Exxx)를 지정한 경우,
    구현체는 그 오류 코드를 포함하여 보고 MUST 한다.

- Undefined Behavior (UB)
  - 본 표준이 UB로 정의한 상황이 실행 중 발생하면,
    그 이후 프로그램의 동작은 정의되지 않는다.
  - UB에 대한 진단은 본 표준이 별도로 요구하지 않는 한 필수는 아니다.
  - 단, 구현체는 UB를 정적으로 검출 가능하다면 진단을 추가로 보고 MAY 한다.

- Unspecified Behavior
  - 표준이 일부 동작을 “지정하지 않음”으로 남겨둔 경우를 말한다.
  - 예: 대부분의 연산자에서 피연산자 평가 순서, 함수 인자 평가 순서.
  - 구현체는 이 경우들에 대해 특정 동작을 가정해서는 안 된다.

- Implementation-defined Behavior
  - 표준이 구현마다 달라질 수 있음을 허용하되, 구현이 반드시 문서화해야 하는 동작을 말한다.
  - MiniC89는 교육/채점 목적상 implementation-defined 동작을 최소화하는 것을 목표로 하며,
    본 표준에 등장하는 경우 구현체는 그 내용을 문서화 MUST 한다.
    
## 3. Lexical Elements

### 3.1 Tokens

MiniC89의 토큰은 다음으로 구성된다.

- Keywords
- Identifiers
- Integer constants
- Operators
- Punctuators

---

### 3.2 Keywords
다음 키워드는 예약어이다.

int  
if  
else  
for  
return  
break  
continue  
---

### 3.3 Identifiers

- 식별자는 알파벳 또는 '_'로 시작 MUST 한다.
- 이후 알파벳, 숫자, '_'의 조합으로 구성된다.
- 키워드와 동일한 이름은 사용할 수 없다.
---

### 3.4 Integer Constants

- 10진 정수 리터럴만 허용된다.
- 부호는 리터럴의 일부가 아니다.
- 범위를 벗어난 정수 리터럴은 컴파일 오류이다.

---

### 3.5 Comments and Whitespace

- /* ... */ 형식의 주석만 허용된다.
- // 주석은 허용되지 않는다.
- 공백과 개행은 토큰 구분에만 영향을 준다.

---

### 3.6 Lexical Grammar (Normative)

#### 3.6.1 Source Character Set (Normative)
- MiniC89 소스는 다음 문자들을 포함 MUST 한다.
  - 공백류: SP(0x20), HT(0x09), VT(0x0B), FF(0x0C), LF(0x0A), CR(0x0D)
  - 인쇄 가능 ASCII: 0x21..0x7E
- 위 범위 밖 문자가 등장하면 구현체는 컴파일 타임 오류로 진단 MUST 한다.
  - 오류 코드: MC89-E101 (Invalid Character)

#### 3.6.2 Regular Definitions (Normative)
본 절에서 정규 정의(regular definition)는 ASCII 기준이다.

(1) Letter / Digit
- <letter> := [A-Za-z]
- <digit>  := [0-9]
- <nondigit> := <letter> | "_"

(2) Identifier
- <identifier> := <nondigit> (<nondigit> | <digit>)*

(3) Integer Constant (decimal only)
- <integer-constant> := "0" | [1-9]<digit>*
- 즉, 선행 0이 있는 형태(예: 00, 077)는 허용되지 않는다.

(4) Whitespace
- <whitespace> := one or more of (SP | HT | VT | FF | LF | CR)

(5) Block Comment (C-style only)
- <comment> starts with "/*" and ends with the first subsequent "*/".
- 주석은 중첩(nesting)되지 않는다.
- EOF까지 "*/"를 만나지 못하면 오류 코드 MC89-E104로 진단 MUST 한다.

#### 3.6.3 Tokenization Rules (Normative)
- 구현체는 소스 파일을 왼쪽에서 오른쪽으로 스캔하며 토큰을 생성 MUST 한다.
- <whitespace> 및 <comment>는 토큰 경계로 취급되며, 토큰 스트림에 포함되지 않는다.
- 구현체는 다음 “최장 일치(maximal munch)” 원칙을 적용 MUST 한다.
  - 동일 위치에서 둘 이상의 토큰 후보가 가능하면, 더 긴 후보를 선택한다.
  - 특히 연산자/구분기호에서 2글자 토큰은 1글자 토큰보다 우선한다.
    예: "=="는 "=" "="로 분리되지 않는다.

키워드와 식별자 규칙:
- 스캔된 문자열이 키워드 집합과 정확히 일치하고, 그 양끝이 식별자 문자(<nondigit>|<digit>)로
  확장되지 않는 경우, 해당 토큰은 Keyword로 분류 MUST 한다.
- 그렇지 않으면 <identifier>에 매칭되는 토큰은 Identifier로 분류 MUST 한다.
  예: "intx"는 Keyword "int" + "x"가 아니라 Identifier "intx"이다.

정수 리터럴(10진만) 규칙:
- <integer-constant>에 부합하지 않는 숫자 시작 토큰은 “잘못된 정수 리터럴”로 진단 MUST 한다.
  다음은 최소로 오류(MC89-E103)로 진단 MUST 한다.
  - 0으로 시작하며 길이가 2 이상인 숫자열: 00, 077, 0123
  - 0x 또는 0X로 시작하는 형태: 0x10
  - 숫자열 뒤에 식별자 문자가 붙어 분리되지 않는 형태: 123abc
- 위 오류의 진단 코드는 MC89-E103 (Invalid Integer Literal)이다.

연산자/구분기호 토큰 집합(최소):
- 2글자 연산자: "<=", ">=", "==", "!=", "&&", "||"
- 1글자 연산자: "+", "-", "*", "/", "%", "<", ">", "=", "!"
- 구분기호: "(", ")", "{", "}", ";", ","

주석 시작 처리:
- 스캔 위치에서 "/*"가 보이면 <comment>를 형성 MUST 한다.
- "//"는 주석이 아니며 특별 취급하지 않는다.
  (플랫폼 정책으로 "//" 형태를 별도 진단하고 싶으면, MC89-E203으로 진단 MAY)

#### 3.6.4 Allowed Examples
(1) Identifier
    int main() {
        int _x1;
        _x1 = 0;
        return _x1;
    }

(2) Integer constants (decimal only)
    int main() {
        return 0 + 7 + 127;
    }

(3) Block comment treated as whitespace
    int main() {
        /* this is a comment */
        return 0;
    }

#### 3.6.5 Forbidden Examples (MUST be Compile-time Error)
(1) Invalid character (MC89-E101)
    int main() { return 0; } @

(2) Unterminated comment (MC89-E104)
    /* unterminated comment

(3) Invalid integer literal (MC89-E103: leading zero / hex / digit+letters)
    int main() { return 077; }      /* ERROR: MC89-E103 */
    int main() { return 0x10; }     /* ERROR: MC89-E103 */
    int main() { return 123abc; }   /* ERROR: MC89-E103 */

(4) Invalid identifier usage (MC89-E102: keyword used where identifier required)
    int if;  /* ERROR: MC89-E102 */

#### 3.6.6 Notes (Non-Normative)
- 본 절은 3.3/3.4/3.5의 서술을 “정식 정의”로 보강하기 위한 것이다.
- “정수 리터럴 값 범위(예: 0..127)”의 의미론/범위 규칙은 Chapter 5에 따른다.

---

## 4. Syntax (Grammar)

### 4.1 Grammar Notation
- 문법은 EBNF로 기술된다.
- EBNF에 없는 문법은 존재하지 않는다.

### 4.2 Program Grammar (Translation Unit) -- Normative
> 이 절은 MiniC89 프로그램의 **최상위 문법 구조**를 정의한다.
>
> 이 절의 EBNF는 **번역 단위(translation unit)의 유일한 규범적 정의**이다.

#### EBNF Definition (Normative)
```ebnf
BEGIN REPLACEMENT (4.2.1 EBNF Definition)

```ebnf
/* ------------------------------------------------------------
 * Translation Unit (MiniC89)  — aligned with C89 3.7
 * ------------------------------------------------------------ */

/* For readability, we define <program> as an alias of <translation-unit>. */
<program>                 ::= <translation-unit> ;

<translation-unit>        ::= { <external-declaration> } ;

/* In ANSI C89, external-declaration includes both function-definition and declaration.
 * MiniC89 restricts it to function-definition only.
 */
<external-declaration>    ::= <function-definition> ;
```

#### Normative Rules
- 파일 스코프 (file scope)에서는 **오직 함수 정의만 허용 MUST**한다.
- 전역 변수, 전역 선언, 함수 프로토타입은 **문법적으로 존재하지 않으며 MUST NOT 허용**한다.
- 프로그램은 **정확히 하나의 엔트리 함수 `int main()`을 MUST 포함**해야 한다.
  - `main`은 매개변수를 가질 수 없다.
- 본 절에서 사용되는 `<function-definition>` 및 매개변수 관련 논터미널의 규범 정의는 **9.1절**에 있다.
- 
#### Allowed Examples
```c
int main() {
  return 0;
}
```

#### Forbidden Examples (MUST be Compile-time Error)

##### (1) No main
```c
int f() { return 1; }  /* ERROR: no main */
```

##### (2) Prototype / global variable
```c
int f(int a);      /* ERROR: prototypes are not allowed */
int main() { return 0; }
```
```c
int g;             /* ERROR: global variables are not allowed */
int main() { return 0; }
```

#### Notes (Non-Normative)
- MiniC89는 **ISO C89의 "translation unit" 개념을 단순화**한 모델을 사용한다.
- 헤더 파일, 전처리, 분할 컴파일 개념은 존재하지 않는다.
- 이로 인해 모든 이름 해석은 **단일 파일, 단일 번역 단위**에서 이루어진다.

### 4.3 Disallowed Constructs and Prohibitions

본 절은 ISO C89에 존재하지만 MiniC89에서는 제거되었거나 금지되는 구성요소를 정의한다.
MiniC89 구현체는 본 절에 해당하는 프로그램을 컴파일 타임에 거부(reject) MUST 한다.

#### Normative Rules
- 본 절의 금지 사항은 “유효한 MiniC89 프로그램”의 범위를 정의한다.
- 구현체는 금지 사항을 발견하면 최소 1개의 진단(error)을 보고 MUST 한다.
- 금지 사항이 “문법(EBNF)에 존재하지 않음”으로 정의된 경우, 구현체는 해당 프로그램을
  문법적으로 유효한 MiniC89 프로그램으로 취급 MUST NOT 한다.
- 금지 사항이 “정적 의미 규칙 위반”으로 정의된 경우, 구현체는 파싱 성공 여부와 무관하게
  해당 프로그램을 거부 MUST 한다. (Diagnostics 코드가 지정된 경우 그 코드를 사용 MUST)

---

#### 4.3.1 Lexically Disallowed Forms (MUST be rejected during tokenization)

다음 항목은 MiniC89의 토큰 집합(Chapter 3)에 존재하지 않으며,
해당 형태가 소스에 등장하면 구현체는 토큰화 단계에서 오류로 진단 MUST 한다.

Normative Rules
- 아래 항목이 등장하면 구현체는 컴파일 타임 오류를 보고 MUST 한다.
- 권장 오류 코드는 다음과 같다.
  - 잘못된 문자/형태: MC89-E101
  - 종료되지 않은 주석: MC89-E104
  - 잘못된 정수 리터럴: MC89-E103

Lexically disallowed (at minimum)
- 전처리 지시문: `#include`, `#define` 등 (`#`로 시작하는 전처리 라인 전체)
- 문자열 리터럴: "..."
- 문자 상수: 'a', '\n' 등
- (선택 정책) 라인 주석: `// ...`  (MiniC89는 /* */만 주석으로 인정)

Allowed Examples
    int main() {
        return 0;
    }

Forbidden Examples (MUST be Compile-time Error)
(1) Preprocessor directive
    #include <stdio.h>
    int main() { return 0; }

(2) String literal
    int main() {
        return "hi";   /* ERROR */
    }

(3) Character constant
    int main() {
        return 'a';    /* ERROR */
    }

Notes (Non-Normative)
- MiniC89가 “C89 부분집합”이라는 것은 “MiniC89 프로그램은 C89에서도 유효”임을 뜻하며,
  C89의 모든 구문을 MiniC89가 허용한다는 뜻이 아니다.

---

#### 4.3.2 Syntactically Disallowed Constructs (Not in MiniC89 EBNF)

다음 항목은 MiniC89의 EBNF(Chapter 4, 6, 7, 8, 9)에 존재하지 않으며,
따라서 해당 형태는 MiniC89 문법으로 파싱될 수 없어야 한다.

Normative Rules
- 아래 항목을 포함하는 프로그램은 MiniC89 문법으로 유효 MUST NOT 하다.
- 구현체가 더 정밀한 진단 코드를 제공할 수 있다면, 다음을 SHOULD 따른다.
  - 전역 선언/프로토타입 관련: MC89-E404, MC89-E405
  - C99-style for 선언: MC89-E302
  - 선언 위치 위반: MC89-E301
  - 금지된 연산자/구문(++, ?: 등): MC89-E203

Syntactically disallowed (at minimum)
- 파일 스코프에서의 전역 변수/선언 (external object definitions)
- 파일 스코프에서의 함수 프로토타입(선언만 있고 본문이 없는 형태)
- `int` 이외의 타입/키워드: char, float, double, short, long, unsigned, signed, void 등
- 사용자 정의 타입: struct, union, enum, typedef
- 포인터/배열 관련 선언 및 구문: `*`(선언자), `&`, `[]`
- 증감 연산자: `++`, `--`
- sizeof 연산
- 조건(삼항) 연산자: `?:`
- 비트 연산자: `& | ^ ~ << >>`
- (7.1.1에 의해) 콤마 연산자: (E1, E2) 형태
- 전처리(3.6에서 이미 lexical 금지로도 처리 가능)

Allowed Examples
    int main() {
        int x;
        x = 1 + 2 * 3;
        return x;
    }

Forbidden Examples (MUST be Compile-time Error)
(1) Global variable (not allowed at file scope)
    int g;
    int main() { return 0; }

(2) Function prototype (not allowed)
    int f(int a);
    int main() { return 0; }

(3) Pointer/array (not in grammar)
    int main() {
        int *p;      /* ERROR */
        return 0;
    }

Notes (Non-Normative)
- 구현체가 “전체 C89 파서”를 사용하더라도, 위 항목들은 MiniC89 관점에서 반드시 거부해야 한다.
  즉, “파싱 성공”은 “MiniC89로 허용”을 의미하지 않는다.

---

#### 4.3.3 Semantically Disallowed but Syntactically Valid Forms (Static semantic errors)

다음 항목은 MiniC89 문법으로는 파싱될 수 있으나,
정적 의미 규칙(Chapter 9, Chapter 11 Diagnostics)을 위반하므로 금지된다.

Normative Rules
- 아래 항목이 발견되면 구현체는 컴파일 타임 오류로 거부 MUST 한다.
- 본 항목은 “표준 라이브러리 호출 금지”를 포함한다. MiniC89에는 표준 라이브러리가 없으며,
  프로그램 외부에 정의된 함수를 호출할 수 없다.

Semantically disallowed (at minimum)
- 선언되지 않은 변수 사용: MC89-E201
- 초기화되지 않은 변수 읽기: MC89-E202
- 프로그램 내에 정의되지 않은 함수 호출(표준 라이브러리 호출 포함): MC89-E407
  - 예: printf, scanf, puts, getchar 등 (예시는 비한정 목록)
- 함수 인자 개수 불일치: MC89-E408

Allowed Examples
    int add(int a, int b) { return a + b; }
    int main() { return add(1, 2); }

Forbidden Examples (MUST be Compile-time Error)
(1) Standard library call (treated as undefined function in MiniC89)
    int main() {
        printf(1);   /* ERROR: MC89-E407 */
        return 0;
    }

(2) Undefined variable
    int main() {
        x = 1;       /* ERROR: MC89-E201 */
        return 0;
    }

Notes (Non-Normative)
- “표준 라이브러리 호출 금지”는 문법으로 금지할 수 없으므로(식별자는 항상 문법적으로 가능),
  정적 의미 규칙(정의 존재성 검사)으로 금지한다.
---

## 5. Types

### 5.1 Integer Type

#### Normative Rules
- MiniC89에는 오직 하나의 타입 `int`만 존재 MUST 한다.
- MiniC89의 `int`는 정확히 8-bit이며, 표현은 2의 보수(two’s complement) MUST 이다.
- 따라서 `int`의 값 범위는 다음과 같이 고정된다.
  - INT_MIN = -128
  - INT_MAX =  127
- 모든 변수, 매개변수, 함수 반환값은 `int` 타입 MUST 이다.

정수 리터럴(10진 정수 상수) 정책:
- 10진 정수 리터럴의 값은 0 이상 127 이하 MUST 이다.
- 위 범위를 벗어나는 정수 리터럴은 컴파일 타임 오류(MUST be Compile-time Error)이다.
  - 진단 코드: MC89-E103 (invalid integer literal)

#### Allowed Example
##### 범위 내 리터럴/연산
```c
int main() {
    int x;
    x = 127;
    x = x - 1;    /* 126 */
    return x;
}
```

##### -128을 “128 리터럴 없이” 만들기
```c
int main() {
    int m;
    m = -127 - 1; /* -128 */
    return m;
}
```

#### Forbidden Examples
##### 정수 리터럴 범위 위반 (구현이 8-bit 정책을 채택하는 경우)
```c
int main() {
    int x;
    x = 128;      /* ERROR: integer literal out of range */
    return 0;
}
```

##### 허용 타입 위반
```c
int main() {
    char c;           /* ERROR: only 'int' type is allowed */
    return 0;
}
```

#### Notes (Non-Normative)
- 본 절은 “타입이 하나뿐인 C89 부분집합”을 목표로 한다.
- int의 비트폭을 표준에서 “MUST로 고정”할지(예: 8-bit) “SHOULD로 둘지”는 프로젝트 정책으로 결정한다.
  (온라인 저지/채점 안정성을 최우선하면 고정(MUST) 권장)

---
### 5.2 Arithmetic Semantics and Undefined Behavior

#### Normative Rules
- MiniC89의 산술 연산은 “수학적 정수(정확한 정수)”에서 수행한 뒤,
  그 결과가 `int` 범위(INT_MIN..INT_MAX)에 포함되는지 검사 MUST 한다.
- 다음 연산자들의 결과가 `int` 범위를 벗어나면 Undefined Behavior(UB) MUST 이다.
  - 단항: `+`, `-`
  - 이항: `+`, `-`, `*`, `/`, `%`
- 나눗셈과 나머지 연산에 대해:
  - 제수(divisor)가 0이면 UB MUST 이다.
  - `a / b`는 정수 나눗셈의 몫을 의미하며(구현은 교육/채점 목적상 결정적으로 제공 SHOULD),
    그 몫이 범위를 벗어나면 UB MUST 이다.
  - `a % b`는 나머지를 의미하며, 제수가 0이면 UB MUST 이다.
- 다음은 위 규칙에서 즉시 따라오는 대표 UB 사례이다.
  - `-(-128)`은 결과가 128이므로 UB
  - `(-128) / (-1)`은 결과가 128이므로 UB
- wrap-around(모듈러) 동작은 정의하지 않는다(MUST NOT).

#### Allowed Examples
##### 범위 내 산술
```c
int main() {
    int a;
    int b;
    a = 100;
    b = 27;
    return a + b;   /* 127 */
}
```

##### 0으로 나누기를 피하는 형태
```c
int main() {
    int x;
    x = 10;
    if (x != 0) return 100 / x;
    return 0;
}
```

#### Forbidden Examples (MUST be Compile-time Error under Chapter 11 constant-folding policy)
아래 예제들은 “컴파일 타임 상수식(CTCE)”로 구성되어 있으며,
Chapter 11의 CTCE 정책에 의해 구현체는 컴파일 타임에 오류로 진단 MUST 한다.

##### 상수식 0으로 나누기 (MC89-E206)
```c
int main() {
    return 1 / 0;     /* ERROR: MC89-E206 */
}
```

##### 상수식 오버플로 (MC89-E207)
```c
int main() {
    return 127 + 1;   /* ERROR: MC89-E207 */
}
```

##### -(-128) 오버플로 (MC89-E207)
```c
int main() {
    return -(-127 - 1);  /* ERROR: MC89-E207 (i.e., -(-128)) */
}
```

##### (-128)/(-1) 오버플로 (MC89-E207)
```c
int main() {
    return (-127 - 1) / -1;  /* ERROR: MC89-E207 */
}
```

##### 미초기화 변수 읽기 (MC89-E202)
```c
int main() {
    int x;
    return x;         /* ERROR: MC89-E202 */
}
```

#### Notes (Non-Normative)
- 본 표준은 오버플로 시 wrap-around를 제공하지 않는다.
- UB는 “정의되지 않은 동작”이므로, CTCE가 아닌 경우 구현이 런타임에서 어떤 결과를 내더라도
  언어 의미로 보장되지 않는다.
  단, 구현체는 UB를 검출 가능하다면 추가 진단을 보고 MAY 한다.

---
### 5.3 Truth Values and Conditional Context (Normative)

#### Normative Rules
- MiniC89에는 별도의 boolean 타입이 존재하지 않는다.
- 어떤 표현식 `E`가 “조건식(conditional context)”으로 사용될 때,
  `E`의 평가 결과는 다음 규칙으로 참/거짓으로 해석 MUST 한다.
  - 결과가 0이면 false
  - 결과가 0이 아니면 true
- 다음 구문에서의 `E`는 conditional context MUST 이다.
  (a) `if (E) S`
  (b) `if (E) S1 else S2`
  (c) `for (init; E; step) S` 의 조건 항 `E`
  (d) 논리 연산자 `E1 && E2`, `E1 || E2`의 각 피연산자

#### Allowed Examples
    int main() {
        int x;
        x = 0;
        if (x) return 1;   /* false */
        x = -3;
        if (x) return 2;   /* true  */
        return 0;
    }

#### Forbidden Examples
(템플릿 최소 요건 충족용: 조건식에서 미초기화 읽기는 정적 오류)
    int main() {
        int x;
        if (x) return 1;   /* ERROR: MC89-E202 (read of uninitialized variable) */
        return 0;
    }

#### Notes (Non-Normative)
- 이 규칙은 C 계열 언어의 전통적인 “0/비0” 진리값 규칙과 동일하다.

---

## 6. Declarations

#### EBNF Definition (Normative)
```ebnf
/* ------------------------------------------------------------
 * Declarations (MiniC89) — block scope only
 * ------------------------------------------------------------ */

/* A declaration declares one or more int variables. */
<declaration>            ::= <int-declaration> ;

<int-declaration>        ::= "int" <init-declarator-list> ";" ;

<init-declarator-list>   ::= <init-declarator>
                             { "," <init-declarator> } ;

/* Optional initializer */
<init-declarator>        ::= <identifier>
                           | <identifier> "=" <assignment-expression> ;
```

#### Normative Rules

- 블록 내부에서 선언은 문장보다 앞에 위치 MUST 한다.
- 선언 뒤에 선언은 허용된다.
- 문장 뒤에 선언은 허용되지 않는다.
  
---
#### Allowed Examples
```c
int main() {
    int x;
    int y;
    x = 1;
    y = 2;
}
```

#### Forbidden Examples
```c
int main() {
    int x;
    x = 1;
    int y;
}
```
---

## 7. Expressions

### 7.1 Expression Grammar (Normative)
- 허용되는 식:
  - 산술
  - 비교
  - 논리
  - 대입
  - 함수 호출

- 허용되지 않는 식:
  - 콤마 연산식

#### EBNF Definition (Normative)
```ebnf
/* Top */
<expression>                 ::= <assignment-expression> ;

/* Assignment (right-associative) */
<assignment-expression>      ::= <logical-or-expression>
                               | <lvalue> "=" <assignment-expression> ;

<lvalue>                     ::= <identifier> ;

/* Logical (left-associative) */
<logical-or-expression>      ::= <logical-and-expression>
                                 { "||" <logical-and-expression> } ;

<logical-and-expression>     ::= <equality-expression>
                                 { "&&" <equality-expression> } ;

/* Equality (left-associative) */
<equality-expression>        ::= <relational-expression>
                                 { ( "==" | "!=" ) <relational-expression> } ;

/* Relational (left-associative) */
<relational-expression>      ::= <additive-expression>
                                 { ( "<" | "<=" | ">" | ">=" ) <additive-expression> } ;

/* Additive (left-associative) */
<additive-expression>        ::= <multiplicative-expression>
                                 { ( "+" | "-" ) <multiplicative-expression> } ;

/* Multiplicative (left-associative) */
<multiplicative-expression>  ::= <unary-expression>
                                 { ( "*" | "/" | "%" ) <unary-expression> } ;

/* Unary (right-associative) */
<unary-expression>           ::= <postfix-expression>
                               | ( "+" | "-" | "!" ) <unary-expression> ;

/* Postfix */
<postfix-expression>         ::= <primary-expression>
                                 { <call-suffix> } ;

<call-suffix>                ::= "(" [ <argument-list> ] ")" ;

<argument-list>              ::= <assignment-expression>
                                 { "," <assignment-expression> } ;

/* Primary */
<primary-expression>         ::= <integer-constant>
                               | <identifier>
                               | "(" <expression> ")" ;
```

---

#### Normative Rules
##### Operator Hierarchy
- 구현체는 7.1의 계층 구조에 따라 **연산자 우선순위**를 **MUST** 해석한다.
- 결합 규칙은 다음과 같이 **MUST** 적용한다.
  - `=`: **right-associative**
  - 그 외 이항 연산자(`|| && == != < <= > >= + - * / %`): **left-associative**
  - 단항 연산자(`+ - !`): **right-associative**

##### Precedence Table (Highest → Lowest)
1. Postfix call: `f(...)`
2. Unary: `+x`, `-x`, `!x`
3. Multiplicative: `* / %`
4. Additive: `+ -`
5. Relational: `< <= > >=`
6. Equality: `== !=`
7. Logical AND: `&&`
8. Logical OR: `||`
9. Assignment: `=`

---

##### Evaluation Order
- MiniC89는 ISO C89와 동일하게, 대부분의 연산자에서 **피연산자의 평가 순서를 지정하지 않는다**.
- 이항 연산자 `A op B`에서 `A`와 `B`의 평가 순서는 **미지정(unspecified)** 이며, 구현체는 특정 순서를 **가정해서는 안된다**.
- 함수 호출 `f(a1, a2, ..., an)`에서
  - 함수 식별자 `f`의 확인과
  - 각 인자 표현식 `ai`의 평가 순서는 **지정되지 않는다**.
- 다음 연산자는 예외적으로 **단락 평가(short-circuit evaluation)** 을 **MUST** 따른다.
  - `A && B`: `A`가 0이면 `B`는 평가되지 않는다.
  - `A || B`: `A`가 0이 아니면 `B`는 평가되지 않는다.
- 평가 순서에 의존하는 MiniC89 프로그램은 **비이식적(non-portable)** 이며, 구현체는 이를 **컴파일 타임 진단(오류 또는 경고)** 할 수 있다.

#### Allowed Examples
```c
int main() {
  int a;
  int b;
  a = 1;
  b = 2;
  return a + b;  /* order irrelevant */
}
```

```c
int f(int x) { return x + 1; }

int main() {
  return f(3);   /* single argument, no ambiguity */
}
```

#### Forbidden / Problematic Examples
> 다음 예제들은 **평가 순서에 의존**하며,
>
> MiniC89 구현체는 **오류 또는 경고를 발생시킬 수 있다**.

```c
int f(int x) { return x; }

int main() {
  int i;
  i = 0;
  return f(i) + (i = 1);  /* evaluation order dependent */
}
```

```c
int g(int x) { return x; }

int main() {
    int i;
    i = 1;
    return g(i = 2) + g(i);  /* unspecified behavior dependency */
}
```

#### Notes (Non-Normative)
- `<argument-list>`에서의 `,`는 **함수 인자 구분자**이며, **콤마 연산자**가 아니다.
- 오버플로, 0으로 나누기, 미초기화 읽기는 Types/UB 절의 규칙을 따른다.
- MiniC89 구현체(컴파일러/VM)은 **교육적 시각화**를 위해 내부적으로 특정 평가 순서(예: left-to-right)를 사용할 수 있다.
- 이러한 내부 실행 순서는 **언어 의미를 규정하지 않으며**, 다른 구현체에서도 동일하게 동작할 것이라는 보장은 없다.
- 본 절의 목적은 "결정적 시각화"와 "C89 의미론 보존"을 **명확히 분리**하는 데 있다.

### 7.1.2 Assignment Expressions (Normative)

#### Normative Rules
- MiniC89의 대입 연산자 `=`는 다음 형태만 허용 MUST 한다.
  - <identifier> "=" <assignment-expression>
  (좌변은 반드시 단일 식별자이며, 그 외 형태는 허용되지 않는다.)
- 대입 표현식 `x = E`의 의미는 다음과 같다.
  - `E`를 평가하여 값 v를 얻는다.
  - v를 변수 x에 저장한다.
  - 대입 표현식 전체의 값(value)은 v이다.
- 대입 연산자 `=`는 우결합(right-associative) MUST 이다.
  - 따라서 `a = b = c`는 `a = (b = c)`로 해석 MUST 한다.
- 체인 대입은 허용된다.
  - `a = b = c`는 유효한 MiniC89 표현식이다.
- 단, 동일 full-expression 내에서 같은 변수에 대한 다중 대입 또는
  대입과 그 외의 사용(읽기/쓰기)이 결합되어 “평가 순서 의존/부작용 충돌”을 만들면
  구현체는 MC89-E208로 컴파일 타임 오류를 보고 MUST 한다.
  (정확한 판정 규칙은 Diagnostics의 MC89-E208 정의를 따른다.)

#### Allowed Examples
(1) 기본 체인 대입
    int main() {
        int a;
        int b;
        int c;
        a = 0;
        b = 0;
        c = 3;
        a = b = c;      /* a=3, b=3 */
        return a + b;   /* 6 */
    }

(2) 선언과 분리된 체인 대입 (권장 스타일)
    int main() {
        int x;
        int y;
        x = 1;
        y = 2;
        x = y = 0;
        return x + y;   /* 0 */
    }

#### Forbidden Examples (MUST be Compile-time Error)
(1) 같은 변수에 대한 다중 대입 (MC89-E208)
    int main() {
        int a;
        a = 0;
        a = (a = 1);    /* ERROR: MC89-E208 (a에 대한 쓰기 2회) */
        return a;
    }

(2) 같은 변수에 대한 대입 + RHS 밖 추가 사용 혼합 (MC89-E208)
    int main() {
        int u;
        int v;
        u = 0;
        v = (u = 1) + u;  /* ERROR: MC89-E208 (u가 RHS 밖에서 다시 읽힘) */
        return v;
    }

(3) 좌변이 식별자가 아닌 경우 (MC89-E204 또는 MC89-E205)
    int main() {
        int x;
        (x) = 1;        /* ERROR: invalid assignment target */
        return 0;
    }

#### Notes (Non-Normative)
- MiniC89에서 체인 대입을 허용하는 이유:
  - C89과의 자연스러운 대응(우결합 대입)
  - “대입식이 값을 가진다”는 C 계열 표현식 모델을 교육적으로 유지
- 다만 부작용 충돌을 유발하는 표현식은 MC89-E208로 거부하여
  평가 순서에 의존하는 코드를 교육적으로 차단한다.

### 7.2 Boolean Interpretation (Normative)

#### Normative Rules
- MiniC89에는 별도의 boolean 타입이 존재하지 않는다.
- 조건식(conditional context)에서 표현식 `E`는 다음 규칙으로 참/거짓으로 해석 MUST 한다.
  - `E`의 평가 결과가 0이면 false
  - `E`의 평가 결과가 0이 아니면 true
- 다음 구문에서의 조건식은 “conditional context”로 간주 MUST 한다.
  (a) `if (E) ...` 및 `if (E) ... else ...`
  (b) `for ( ... ; E ; ... )`의 `E` (조건 항)
  (c) 논리 연산자 `&&`, `||`의 각 피연산자

- 논리 부정 `!E`의 결과는 다음과 같이 정의 MUST 한다.
  - `E`가 0이면 `!E`는 1
  - `E`가 0이 아니면 `!E`는 0

#### Allowed Examples
(1) if 조건
    int main() {
        int x;
        x = 0;
        if (x) return 1;
        return 0;   /* 실행됨 */
    }

(2) nonzero는 true
    int main() {
        int x;
        x = -3;
        if (x) return 1;  /* 실행됨 */
        return 0;
    }

(3) ! 연산
    int main() {
        int a;
        int b;
        a = !0;     /* 1 */
        b = !5;     /* 0 */
        return a + b;  /* 1 */
    }

#### Forbidden Examples
(템플릿 최소 요건 충족용: 아래는 “금지 문법”이 아니라 UB/정적 오류 예시로 제공한다.)

(1) 미초기화 조건식 (정적 오류: MC89-E202)
    int main() {
        int x;
        if (x) return 1;  /* ERROR: MC89-E202 */
        return 0;
    }

#### Notes (Non-Normative)
- 본 규칙은 C 계열 언어의 전통적인 “0/비0” 규칙과 동일하다.
- 10.5.1의 조건식 규칙은 본 절을 실행 모델 관점에서 재진술한 것이다.


## 8. Statements

#### EBNF Definition (Normative)
```ebnf
/* ------------------------------------------------------------
 * Statements (MiniC89)
 * ------------------------------------------------------------ */

<statement>            ::= <compound-statement>
                         | <selection-statement>
                         | <iteration-statement>
                         | <jump-statement>
                         | <expression-statement> ;

/* { declarations... statements... } with C89 rule enforced */
<compound-statement>   ::= "{" <block-item-seq> "}" ;

/* Declaration placement rule:
 * declarations may appear only before any statements in the same block.
 *
 * <declaration> is defined in 6.1 (Declarations).
 */
<block-item-seq>       ::= { <declaration> } { <statement> } ;

/* Expression statement (includes empty statement ;) */
<expression-statement> ::= ";" | <expression> ";" ;

/* if / if-else */
<selection-statement>  ::= "if" "(" <expression> ")" <statement>
                           [ "else" <statement> ] ;

/* for loop */
<iteration-statement>  ::= "for" "(" <for-init> ";" <for-cond> ";" <for-step> ")"
                           <statement> ;

<for-init>             ::= /* empty */ | <expression> ;
<for-cond>             ::= /* empty */ | <expression> ;
<for-step>             ::= /* empty */ | <expression> ;

/* return / break / continue */
<jump-statement>       ::= "return" [ <expression> ] ";"
                         | "break" ";"
                         | "continue" ";" ;

```

---

#### Normative Rules
- 블록 내부에서 선언은 **0개 이상 연속으로만** 나타날 수 있으며, **어떤 문장 뒤에도 선언이 올 수 없다 (MUST NOT)**.
- `if`/`else`는 문법에 따라 **가장 가까운 `if`와 결합**한다.
- `for`의 `(init; cond; step)` 각 항은 비어 있을 수 있다.
- `break`/`continue`는 반복문 내부에서만 유효해야 하며, 반복문 밖에서 사용시 구현체는 **컴파일 오류**를 **MUST** 발생시킨다. (문법에 없는 정적 의미 규칙이기 때문에, Diagnostics에서 필수 오류로 연결)
- MiniC89의 모든 함수는 반환 타입이 `int`이므로,
  `return;` (표현식 없는 return)은 허용되지 않는다(MUST NOT).
  구현체는 이를 컴파일 타임 오류로 진단 MUST 하며,
  오류 코드는 MC89-E306을 사용 MUST 한다.
- `return E;`에서 `E`는 7장 Expression Grammar에 따라 유효한 <expression>이어야 하며,
  `return`은 즉시 함수 실행을 종료 MUST 한다.
---

#### Allowed Examples
##### Compound + declarations-at-top
```c
int main() {
  int a;
  int b = 2;
  a = 1;
  return a + b;
}
```
---

##### if / else (dangling-else)
```c
int main() {
  int x;
  x = 0;
  if (x)
    if (1) x = 1;
    else x = 2;  /* else는 안쪽 if에 붙음 */
  return x;
}
```

---

##### for with empty parts
```c
int main() {
  int i;
  i = 0;
  for (; i < 3; i = i + 1);
  return i;
}
```

---
##### break / continue
```c
int main() {
  int i;
  i = 0;
  for (; i < 10; i = i + 1) {
    if (i == 3) continue;
    if (i == 7) break;
  }
  return i;
}
```

#### Forbidden Examples (MUST be Compile-time Error)

##### Declaration after statement (C89 rule violation)
```c
int main() {
  int x;
  x = 1;
  int y;  /* ERROR: declaration after statement */
  y = 2;
  return x + y;
}
```

##### C99-style for declaration
```c
int main() {
  int sum;
  sum = 0;
  for (int i = 0; i < 10; i = i + 1) { /* ERROR */
    sum = sum + i;
  }
  return sum;
}
```

##### break / continue outside loop
```c
int main() {
  break;    /* ERROR */
  return 0;
}
```
```c
int main() {
  continue;    /* ERROR */
  return 0;
}
```
#### Notes (Non-Normative)
- `;` 단독은 `empty statement`로 허용된다.
- `for(;;)`는 무한 루프를 의미한다(단, 실행 모델/UB 규칙은 별도 절을 따른다).

## 9. Functions

#### EBNF Definition (Normative)
```ebnf
/* ------------------------------------------------------------
 * Function Definition (MiniC89) — aligned with C89 3.7.1
 * ------------------------------------------------------------ */

/* Parameters: only 'int name' */
<parameter-list>          ::= <parameter-decl> { "," <parameter-decl> } ;

<parameter-decl>          ::= "int" <identifier> ;

/* No prototypes, no global variables */
<external-declaration>    ::= <function-definition> ;
```
> ✅ 결과적으로 파일 스코프에서 허용되는 건 함수 정의뿐이다.
> ❌ int x; 같은 전역 변수, int f(int a); 같은 프로토타입은 문법으로 존재하지 않는다.

---

#### Normative Rules

- 프로그램은 0개 이상의 함수 정의로 구성된다.
- 모든 함수의 반환 타입은 `int`이어야 한다.
- 모든 매개변수는 `"int" <identifier>` 형태여야 한다.
- 함수 이름은 프로그램 내에서 **유일 MUST** 하다(중복 정의 금지).
- 프로그램은 엔트리 포인트로 `int main()` 함수를 **반드시(MUST) 포함**해야 한다.
  - `main`은 매개변수를 가지면 안 된다.
- MiniC89는 `implicit function declaration`을 허용하지 않는다.
  - 호출되는 모든 함수는 프로그램 내에 정의가 **존재 MUST** 한다.
- 함수 호출의 인자 개수(arity)는 정의의 매개변수 개수와 **정확히 일치 MUST** 한다. 

---

#### Allowed Examples
```c
int add(int a, int b) {
  return a + b;
}
int main() {
  int test_add_1_2 = add(1, 2);
  return 0;
}
```

```c
int fact(int n) {
  if (n <= 1) return 1;
  return n * fact(n - 1);
}
int main() {
  int test_fact_5 = fact(5);
  return 0;
}
```

#### Forbidden Examples (MUST be Compile-time Error)
##### Non-int parameter type
```c
int f(char x) { return 0; }  /* ERROR: only int allowed */
int main() { return 0; }
```
##### Duplicate function definition
```c
int f() { return 1; }
int f() { return 2; }     /* ERROR: duplicate */
int main() { return 0; }  
```

##### Call to undefined function / arity mismatch
```c
int main() {
  return foo(1);    /* ERROR: undefined function*/
}
```
```c
int f(int a, int b) { return a + b; }
int main() {
  return f(1);       /* ERROR: arity mismatch */
}
```
#### Missing return expression in int function (MC89-E306)
```c
int main() {
    return;   /* ERROR: MC89-E306 */
}
```
   
## Chapter 10. Program Execution Model
### Abstract Machine (Normative)

---

## 10.1 Purpose

본 장은 MiniC89 프로그램의 **실행 의미(semantics)** 를 정의한다.  
이 의미는 특정 구현(컴파일러, 인터프리터, VM, WASM 등)과 무관하며,  
모든 MiniC89 구현체는 본 장의 규칙과 **의미적으로 동일 MUST** 하다.

---

## 10.2 Abstract Machine Components

MiniC89 추상 머신은 다음 구성 요소로 이루어진다.

---

### 10.2.1 Program

- 하나의 MiniC89 프로그램은 **단일 translation unit**이다.
- 프로그램은 **함수 정의들의 집합**으로 구성된다.
- 파일 스코프에서 허용되는 실행 단위는 함수 정의뿐이다.

---

### 10.2.2 Program Counter (PC)

- Program Counter(PC)는 **현재 실행 중인 문장(statement)** 을 가리킨다.
- PC는 문장 단위로 이동한다.
- MiniC89는 **문장 간 실행 순서만 정의**한다.
- 식(expression) 내부의 세부 평가 순서는 **정의하지 않는다**.
  - 단, `&&`와 `||`의 단락 평가는 예외로 한다.

---

### 10.2.3 Call Stack

- 실행 중인 함수 호출들은 **Call Stack** 으로 관리된다.
- 각 함수 호출은 하나의 **Stack Frame** 을 생성한다.
- 함수가 반환되면 해당 Stack Frame은 제거(pop)된다.

---

### 10.2.4 Stack Frame

각 Stack Frame은 다음 정보를 포함한다.

- 반환 주소 (Return PC)
- 매개변수들의 집합
- 지역 변수들의 집합

#### Normative Rules

- 매개변수와 지역 변수는 **해당 함수 호출 동안에만 존재 MUST** 한다.
- 함수 호출마다 **독립적인 Stack Frame이 생성 MUST** 한다.
- 재귀 호출은 새로운 Stack Frame을 생성함으로써 지원된다.

---

## 10.3 Memory Model

### 10.3.1 Objects

- MiniC89에서 객체(object)는 **int 타입 변수** 뿐이다.
- 각 객체는 하나의 저장 위치(storage)를 가진다.

---

### 10.3.2 Lifetime

- 매개변수와 지역 변수의 lifetime은:
  - 함수 진입 시 시작
  - 함수 반환 시 종료
- lifetime이 종료된 객체에 접근하는 행위는 **Undefined Behavior** 이다.

---

## 10.4 Execution Semantics

### 10.4.1 Program Start

- 프로그램 실행은 **`main` 함수의 첫 문장**에서 시작 MUST 한다.
- `main` 호출 이전에는 사용자 코드가 실행되지 않는다.

---

### 10.4.2 Statement Execution

- 문장은 **순차적으로 실행**된다.
- 제어 흐름 문장(`if`, `for`, `break`, `continue`, `return`)은
  다음에 실행될 문장을 명시적으로 변경한다.

---

### 10.4.3 Function Call

#### Normative Rules

- 함수 호출 시 다음 단계가 수행된다.
  1. 새로운 Stack Frame이 생성된다.
  2. 인자 표현식이 평가된다.
     - 평가 순서는 **지정되지 않는다** (Chapter 7 참조).
  3. 인자 값이 매개변수로 **값 복사(call-by-value)** 된다.
  4. PC는 호출된 함수의 첫 문장으로 이동한다.
- 함수는 **정확히 하나의 int 반환값**을 생성한다.

---

### 10.4.4 Function Return

- `return E;` 문이 실행되면:
  1. 표현식 `E`가 평가된다.
  2. 평가 결과가 호출자에게 반환된다.
  3. 현재 Stack Frame은 제거된다.
  4. PC는 반환 주소로 이동한다.
- `return` 문은 함수 실행을 **즉시 종료 MUST** 한다.

---

## 10.5 Control Flow Semantics

### 10.5.1 Conditional (`if / else`)

- 조건식 결과가 0이면 false, 0이 아니면 true로 해석한다.
- true 분기 또는 false 분기 중 **정확히 하나만 실행 MUST** 한다.

---

### 10.5.2 Iteration (`for`)

- `for(init; cond; step)`의 실행 순서는 다음과 같다.
  1. `init` 실행
  2. `cond` 평가
  3. 조건이 참이면:
     - loop body 실행
     - `step` 실행
     - 다시 `cond` 평가로 이동
- `cond`가 생략된 경우 항상 참으로 간주한다.

---

### 10.5.3 `break` / `continue`

- `break`:
  - 가장 가까운 반복문을 즉시 종료한다.
- `continue`:
  - 가장 가까운 반복문의 다음 iteration으로 이동한다.

---

## 10.6 Undefined Behavior

다음은 MiniC89에서 **Undefined Behavior (UB)** 이다.

- 정수 오버플로
- 0으로 나누기
- lifetime이 종료된 객체 접근
- 미초기화 변수 읽기
- 평가 순서에 의존하는 부작용 표현식
- 정의되지 않은 함수 호출

UB 발생 이후의 프로그램 동작은 **정의되지 않는다**.

---

## 10.7 Observability and Visualization (Non-Normative)

- 구현체는 교육 목적을 위해 다음 상태를 시각적으로 표시 MAY 한다.
  - Call Stack
  - 현재 Stack Frame
  - 지역 변수 값
  - 현재 실행 중인 문장
- 이러한 시각화는 **언어 의미를 규정하지 않는다**.

---

## 11. Diagnostics

### 11.a Lexical-related Diagnostics (Normative)
> 적용 범위:
> 본 절의 오류들은 MiniC89 구현체가 반드시(MUST) 컴파일 타임에 검출해야 하는
> lexical/tokenization 단계의 오류이다. 경고로 대체할 수 없다.

#### 11.a.1 Mandatory Lexical Errors

##### MC89-E101 — Invalid Character
Condition (MUST detect)
- 입력 소스에 MiniC89 토큰(키워드/식별자/정수 리터럴/연산자/구분기호/주석/공백)의 일부로
  해석될 수 없는 문자가 등장한 경우.

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E101: invalid character

Example
    int @x;    /* MC89-E101 */


##### MC89-E102 — Invalid Identifier
Condition (MUST detect)
- 문법상 <identifier>가 와야 하는 위치(예: 변수 선언자, 함수 이름, 매개변수 이름, lvalue)에
  식별자가 아닌 토큰이 등장한 경우.
- 특히 키워드가 식별자 위치에 등장한 경우는 MUST MC89-E102로 진단한다.

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E102: invalid identifier

Example
    int if;     /* MC89-E102 (keyword used where identifier is required) */


##### MC89-E103 — Invalid Integer Literal
Condition (MUST detect)
- 정수 리터럴이 MiniC89 규칙(10진 정수)과 일치하지 않는 경우.
- 다음 중 하나라도 만족하면 MC89-E103이다.
  (1) 16진/8진 표기 사용 (예: 0x10, 077 등)
  (2) 숫자 이외 문자를 포함
  (3) `int`로 표현 가능한 범위를 벗어남 (범위는 Chapter 5.1에 따름)

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E103: invalid integer literal

Example
    int main() { return 0x10; }   /* MC89-E103 */
    int main() { return 077; }    /* MC89-E103 */


##### MC89-E104 — Unterminated Comment
Condition (MUST detect)
- /* 로 시작한 주석이 */ 로 종료되기 전에 파일 끝(EOF)에 도달한 경우.

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E104: unterminated comment

Example
    /* unterminated comment



### 11.b Expression / Type Diagnostics (Normative)
> 적용 범위:
> 본 절의 오류들은 MiniC89 구현체가 반드시(MUST) 컴파일 타임에 검출해야 하는
> 표현식/정적 의미 오류이다. (경고로 대체 불가)
>
> 단, Chapter 5에서 UB로 분류된 항목이라도, 본 장에서 "MUST detect"로 규정된 경우에는
> 구현체는 반드시 컴파일 타임 오류로 보고 MUST 한다.

#### 11.b.1 Compile-time Detectability Policy (Constant-folding)
정책(최소 요건):
- 구현체는 다음을 “컴파일 타임 상수식(CTCE: compile-time constant expression)”으로 정의하고,
  CTCE는 반드시 평가(상수 접기) MUST 한다.

CTCE 정의 (Normative)
- CTCE는 다음 요소만으로 구성된 <expression>이다.
  - <integer-constant>
  - 괄호 ( ... )
  - Chapter 7에서 허용된 단항/이항 연산자 (단, 식별자/함수호출/대입은 포함되지 않는다)
- CTCE에 식별자, 함수 호출, 대입(=)이 포함되면 CTCE가 아니다.

CTCE 평가 규칙 (Normative)
- CTCE는 수학적 정수(정확한 정수)에서 평가한다.
- 평가 과정 또는 평가 결과가 Chapter 5의 UB 조건(예: 0으로 나누기, 오버플로)을 만족하면,
  구현체는 해당 오류 코드로 컴파일 타임 오류를 MUST 보고한다.
  - 0으로 나누기(상수식) -> MC89-E206
  - 오버플로(상수식)     -> MC89-E207
- CTCE가 아닌 식에서의 0으로 나누기/오버플로는 런타임 UB이며,
  구현체는 추가 진단을 보고 MAY 한다.


#### 11.b.2 Mandatory Expression / Type Errors

##### MC89-E201 — Undefined Variable
Condition (MUST detect)
- 변수로 해석되는 식별자가 사용되었으나,
  해당 지점에서 유효한 범위(scope)에 그 식별자의 변수 선언(지역 변수 또는 매개변수)이
  존재하지 않는 경우.
- (참고) 함수 호출 형태 `id(...)`의 id 해석 실패는 MC89-E407을 사용한다.

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E201: undefined variable '<name>'

Example
    int main() {
        x = 1;       /* MC89-E201 */
        return 0;
    }


##### MC89-E202 — Uninitialized Variable Read
Condition (MUST detect)
- 지역 변수(매개변수 제외)가 초기화되기 전에 그 값을 읽는 경우.
- 구현체는 “definitely initialized” 분석을 수행 MUST 하며,
  모든 실행 경로에서 해당 읽기 지점 이전에 초기화가 보장되지 않으면
  MC89-E202로 오류를 보고 MUST 한다.

초기화 규칙 (Normative)
- 매개변수는 함수 진입 시 초기화된 것으로 간주한다.
- `int x;`는 초기화되지 않은 변수 x를 생성한다.
- `int x = E;`는 E의 평가가 성공적으로 끝난 후 x가 초기화된 것으로 간주한다.
- `x = E;`는 E의 평가가 성공적으로 끝난 후 x가 초기화된 것으로 간주한다.

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E202: read of uninitialized variable '<name>'

Example
    int main() {
        int x;
        return x;    /* MC89-E202 */
    }


##### MC89-E203 — Invalid Operator / Disallowed Operator
Condition (MUST detect)
- MiniC89에서 허용되지 않은 연산자/표현이 등장한 경우.
- 최소로 다음 항목은 MUST MC89-E203으로 진단한다.
  - ++, --
  - sizeof
  - 비트 연산자: &, |, ^, ~, <<, >>
  - 조건 연산자: ? :
  - 콤마 연산자 (함수 인자 구분자 ','는 제외)
  - 배열/포인터/구조체 관련 연산: [], ->, .

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E203: invalid operator or disallowed operator

Example
    int main() {
        int x;
        x++;         /* MC89-E203 */
        return x;
    }


##### MC89-E204 — Invalid Assignment Target
Condition (MUST detect)
- 대입 `=`의 좌변이 MiniC89의 lvalue 규칙을 만족하지 않는 경우.
- MiniC89에서 대입의 좌변은 반드시 단일 식별자(<identifier>) MUST 이다.

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E204: invalid assignment target

Example
    int main() {
        int x;
        (x) = 1;     /* MC89-E204 */
        return 0;
    }


##### MC89-E205 — Invalid Expression Form
Condition (MUST detect)
- 표현식이 Chapter 7의 EBNF로 파싱될 수 없는 경우(표현식 문법 오류).
- 단, 더 구체적인 오류 코드(E203/E204 등)가 적용 가능한 경우,
  구현체는 가능한 한 그 코드를 사용 SHOULD 한다.

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E205: invalid expression

Example
    int main() {
        int x;
        x = ;        /* MC89-E205 */
        return 0;
    }


##### MC89-E206 — Division by Zero (Detected at Compile-time)
Condition (MUST detect)
- 나눗셈 `/` 또는 나머지 `%`의 우변이 CTCE이고,
  CTCE 평가 결과가 0인 경우.

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E206: division by zero

Example
    int main() { return 1 / 0; }          /* MC89-E206 */
    int main() { return 1 / (2 - 2); }    /* MC89-E206 */


##### MC89-E207 — Integer Overflow (Detected at Compile-time)
Condition (MUST detect)
- CTCE 평가 과정 또는 평가 결과가 `int` 표현 범위를 벗어나는 경우.
  (int 범위는 Chapter 5.1에 따름)
- CTCE 평가 중 다음도 오버플로로 간주한다(Chapter 5 UB와 일치).
  - -MIN_INT (예: -(-128))
  - MIN_INT / -1 (예: -128 / -1)

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E207: integer overflow in constant expression

Example (int 범위가 -128..127인 정책의 예)
    int main() { return 127 + 1; }        /* MC89-E207 */
    int main() { return -(-128); }        /* MC89-E207 */


##### MC89-E208 — Evaluation Order Dependency (Static)
Condition (MUST detect)
- 하나의 full-expression(예: `E;`, `return E;`, `for(...;E;...)`, `int x = E;`) 안에서,
  어떤 변수 v에 대해 다음 중 하나가 성립하면 MC89-E208이다.
  (1) v에 대한 대입(쓰기)이 2회 이상 발생
  (2) v에 대한 대입(쓰기)이 1회 발생하고, 그 외의 v 사용(읽기/쓰기)이
      “그 대입의 우변(RHS) 내부”가 아닌 위치에서 발생

RHS 내부의 의미 (Normative)
- v에 대한 대입이 `v = RHS` 형태일 때,
  RHS 내부에 포함된 모든 하위식은 “RHS 내부”로 간주한다.

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E208: expression depends on unspecified evaluation order (variable '<name>')

Examples
(1) 쓰기 2회
    int main() {
        int x;
        x = (x = 1);      /* MC89-E208 */
        return 0;
    }

(2) 쓰기 + RHS 밖 읽기
    int f(int x) { return x; }

    int main() {
        int i;
        i = 0;
        return f(i) + (i = 1);   /* MC89-E208 */
    }

(3) RHS 내부가 아닌 곳에서 읽기/쓰기 혼합
    int main() {
        int u;
        int v;
        u = 0;
        v = (u = 1) + u;         /* MC89-E208 (u가 RHS 밖에서 다시 읽힘) */
        return v;
    }
    
### 11.x Statement-related Diagnostics (Normative)
> **적용 범위**
>
> 본 절의 오류들은 **MiniC89 구현체가 반드시(MUST) 검출해야 하는 컴파일 타임 오류**이다.
>
> 경고로 대체하는 것은 허용되지 않는다.

---
### 11.x.1 Error Code Naming Convention
- Statements 관련 오류 코드는 다음 범위를 사용한다.
```cpp
MC89-E3xx  // Statement-related static errors
```
- 각 오류는:
  - **오류 코드**
  - **규범적 발생 조건**
  - **최소 오류 메시지 요건**
    반드시 포함한다.

---

### 11.x.2 Mandatory Statement Errors
### MC89-E301 -- Declaration After Statement
#### Condition (MUST detect)
- 하나의 블록 `{ ... }` 내부에서
  - 어떤 statement가 등장한 이후
  - declaration이 다시 등장한 경우
#### Example
```c
{
  int x;
  x = 1;
  int y;  /* MC89-E301 */
}
```
#### Required Message
```
error MC89-E301: declaration after statement is not allowed
```
---

### MC89-E302 -- C99-style for Declaration
#### Condition (MUST detect)
- `for`문의 초기화 구문에 declaration이 등장한 경우
#### Example
```c
for (int i = 0; i < 10; i = i + 1) { } /* MC89-E302 */
```
#### Required Message
error MC89-E302: declaration in for-initializer is not allowed

---

### MC89-E303 -- break Outside Loop
#### Condition (MUST detect)
- `break`문이 반복문(`for`) 외부에 위치한 경우
#### Example
```c
break;  /* MC89-E303 */
```
#### Required Message
```
error MC89-E303: 'break' statement not within a loop
```

---

### MC89-E304 -- continue Outside Loop
#### Condition (MUST detect)
- `continue`문이 반복문(`for`) 외부에 위치한 경우
#### Example
```c
continue;  /* MC89-E304 */
```
#### Required Message
```
error MC89-E304: 'continue' statement not within a loop
```

### MC89-E305 -- Invalid return Statement
#### Condition (MUST detect)
- `return`문이 함수 본문이 아닌 위치에서 사용된 경우 (MiniC89에서는 전역 실행 문장이 존재하지 않으므로, 보통은 파서 단계에서 발생)
#### Example
```c
return 1;  /* MC89-E305 */
```
#### Required Message
```
error MC89-E305: 'return' statement outside of function
```

### MC89-E306 -- Missing return Expression
#### Condition (MUST detect)
- 반환 타입이 `int`인 함수에서
- `return;`처럼 표현식이 없는 return이 사용된 경우
#### Example
```c
int f() {
  return;   /* MC89-E306 */
}
```

#### Required Message
```
error MC89-E306: return expression required for function returning 'int'
```
> 이 오류는 **SHOULD** 수준이다.
>
> 구현 단순성을 위해 생략 가능.

### MC89-E307 -- Unreachable Statement
#### Condition (SHOULD detect)
- `return`, `break`, `continue` 뒤에
- 동일 블록 내에서 도달 불가능한 statement가 존재하는 경우
#### Example
```c
int f() {
  return 1;
  x = 2;  /* unreachable */
}
```
#### Required Message
```
warning MC89-E307: unreachable statement
```
#### Notes (Non-Normative)
> 이 오류는 **SHOULD** 수준이다.
>
> 구현 단순성을 위해 생략 가능하다다.

### 11.x.3 Mapping from Grammar to Diagnostics (Normative)
|Grammar Rule|Error Code|
|`<block-item-seq>` 위반 | MC89-E301 |
|`<for-init>`에 declaration | MC89-E302 |
|`break` 의미 규칙 위반 | MC89-E303 |
|`continue` 의미 규칙 위반 | MC89-E304 |
|`return` 위치 오류 | MC89-E305 |
|`return` 표현식 누락 | MC89-E306 |
|도달 불가능 문장 (권장 진단) | MC89-E307 |

### 11.x.4 Conformance Requirement
- MiniC89 구현체는 위 오류들을:
  - **반드시 컴파일 타임에 검출 MUST**
  - **정확한 오류 코드와 함께 보고 MUST**
- 오류 코드 없이 단순 문자열 메시지만 출력하는 구현체는
  MiniC89 표준 적합(conforming)이 아니다. 

### 11.y Function-related Diagnostics (Normative)
> **적용 범위**: Functions 관련 필수 오류는 `MC89-E4xx`를 사용한다.
>
> 다음 항목들은 **반드시(MUST) 컴파일 타임에 검출**되어야 하며, 경고로 대체 불가.

### MC89-E401 -- Missing main
#### Condition (MUST detect)
- 프로그램 내에 `int main()` 정의가 존재하지 않음
#### Message
```
error MC89-E401: missing required entry function 'int main()'
```

### MC89-E402 -- Invalid main Signature
#### Condition (MUST detect)
- `main`이 매개변수를 갖거나, 반환 타입이 `int`가 아님(사실상 문법/타입 위반)
#### Message
```
error MC89-E402: invalid signature for 'main' (expected: int main())
```

### MC89-E403 -- Duplicate Function Definition
#### Condition (MUST detect)
- 동일 이름의 함수 정의가 2개 이상 존재
#### Message
```
error MC89-E403: duplicate definition of function '<name>'
```

### MC89-E404 -- Function Prototype Not Allowed
#### Condition (MUST detect)
- 파일 스코프에서 함수 프로토타입(선언만 있고 본문이 없는 형태)가 등장
#### Message
```
error MC89-E404: function prototypes are not allowed in MiniC89
```

### MC89-E405 -- Global Declaration Not Allowed
#### Condition (MUST detect)
- 파일 스코프에 전역 변수/선언이 등장
#### Message
```
error MC89-E405: global declarations are not allowed (only function definitions permitted)
```

### MC89-E406 -- Invalid Parameter Declaration
#### Condition (MUST detect)
- 매개변수가 `int <identifier>` 형태가 아님
- 매개변수 타입이 `int`가 아님(예: `char`, `long` 등)
#### Message
```
error MC89-E406: invalid parameter declaration (only 'int <identifier>' allowed)
```

### MC89-E407 -- Call to Undefined Function
#### Condition (MUST detect)
- 호출된 함수에 대해 프로그램 내 정의를 찾을 수 없음
#### Message
```
error MC89-E407: call to undefined function '<name>'
```

### MC89-E408 -- Argument Count Mismatch
#### Condition (MUST detect)
- 호출 인자 개수 ≠ 함수 정의의 매개변수 개수
#### Message
```
error MC89-E408: argument count mismatch in call to '<name>'
```

### 11.y.1 Mapping from Functions Grammar to Diagnostics (Normative)
|Rule / Situation|Error Code|
|`main` 없음 | MC89-E401 |
|`main` 시그니처 오류 | MC89-E402 |
|함수 중복 정의 | MC89-E403 |
|프로토타입 사용 | MC89-E404 |
|전역 변수 선언 | MC89-E405 |
|매개변수 선언 오류 | MC89-E406 |
|미정의 함수 호출 | MC89-E407 |
|인자 개수 불일치 | MC89-E408 |


---

## 12. Standard Library

### 12.1 Standard Library Policy

#### Normative Rules
- MiniC89에는 표준 라이브러리(Standard Library)가 존재하지 않는다.
- MiniC89 구현체는 `printf`, `scanf` 등 C 표준 라이브러리 함수의 사용을
  “언어 기능”으로 제공 MUST NOT 한다.
- 프로그램이 호출하는 모든 함수는 같은 프로그램(동일 translation unit) 내에
  정의가 존재 MUST 한다. (미정의 함수 호출은 컴파일 타임 오류)
- 전처리 지시문(예: `#include`, `#define`)은 MiniC89 문법에 존재하지 않으며,
  구현체는 이를 허용 MUST NOT 한다.

#### Allowed Examples
(사용자 정의 함수만 사용)
    int add(int a, int b) { return a + b; }

    int main() {
        return add(1, 2);
    }

#### Forbidden Examples
(1) 표준 라이브러리 함수 호출
    int main() {
        printf(1);      /* ERROR: call to undefined function 'printf' */
        return 0;
    }

(2) 전처리 지시문 사용
    #include <stdio.h>  /* ERROR: preprocessor directives are not allowed */
    int main() { return 0; }

(3) 교육용 내장 함수 가정 (정책이 “없음”인 경우)
    int main() {
        return input(); /* ERROR: call to undefined function 'input' */
    }

#### Notes (Non-Normative)
- 본 표준은 I/O를 언어에서 제거하여 “상태 변화/반환값/스택 프레임” 관찰을 중심으로 한다.
- 온라인 저지에서 입출력이 필요해지면, 별도의 “플랫폼 API(비표준)”로 분리하는 것을 권장한다.

---

## 13. Annex

(Annex는 기본적으로 비규범(Non-Normative)이며, 예시/참고 자료를 제공한다.)

### Annex A. Standard Examples

#### Normative Rules
- Annex의 내용은 정보 제공 목적이며, 언어 의미를 정의 MUST NOT 한다.
- Annex의 예제와 본문 규범(Normative Rules/EBNF)이 충돌할 경우,
  본문 규범이 우선 MUST 한다.

#### Allowed Examples
(1) 단순 산술/대입
    int main() {
        int x;
        x = 1 + 2 * 3;
        return x;
    }

(2) if/else
    int main() {
        int x;
        x = 10;
        if (x < 5) x = 1;
        else x = 2;
        return x;
    }

(3) for + break/continue
    int main() {
        int i;
        int s;
        i = 0;
        s = 0;
        for (; i < 10; i = i + 1) {
            if (i == 3) continue;
            if (i == 7) break;
            s = s + i;
        }
        return s;
    }

(4) 재귀
    int fact(int n) {
        if (n <= 1) return 1;
        return n * fact(n - 1);
    }

    int main() {
        return fact(5);
    }

#### Forbidden Examples
(Annex A에서는 보통 금지 예제가 필요 없지만, 템플릿 최소 요건 충족을 위해 “대표 반례” 1개를 둔다.)

    int main() {
        int x;
        x = 1;
        int y;      /* ERROR: declaration after statement */
        return x;
    }

#### Notes (Non-Normative)
- 예제들은 교육 목적의 난이도/주제 다양성을 위한 것이며, 완전성(coverage)을 보장하지 않는다.


### Annex B. Forbidden / Invalid Programs

#### Normative Rules
- 본 절의 프로그램들은 “컴파일 타임 오류가 되어야 하는 대표 사례”이다.
- 구현체는 해당 유형의 오류를 Diagnostics 규칙에 따라 진단 MUST 한다.

#### Allowed Examples
(이 절은 “금지 예제 모음”이므로 Allowed Examples는 형식 요건 충족용으로 1개만 둔다.)
    int main() { return 0; }

#### Forbidden Examples
(1) C99-style for 선언 (MC89-E302)
    int main() {
        int s;
        s = 0;
        for (int i = 0; i < 10; i = i + 1) { s = s + i; }
        return s;
    }

(2) break outside loop (MC89-E303)
    int main() {
        break;
        return 0;
    }

(3) continue outside loop (MC89-E304)
    int main() {
        continue;
        return 0;
    }

(4) 함수 중복 정의 (MC89-E403)
    int f() { return 1; }
    int f() { return 2; }
    int main() { return 0; }

(5) 미정의 함수 호출 (MC89-E407)
    int main() { return foo(1); }

#### Notes (Non-Normative)
- 필요하면 각 금지 예제 옆에 “기대 오류 코드”를 주석으로 고정해도 좋다.


### Annex C. Undefined / Removed Behaviors

#### Normative Rules
- 본 절의 예시는 UB 또는 본 언어에서 제거된 요소를 설명하기 위한 것이다.
- UB 예시는 “런타임 의미가 정의되지 않음”을 보여주며, 구현체의 특정 동작을 요구하지 않는다.

#### Allowed Examples
(UB를 회피하는 안전한 형태)
    int main() {
        int x;
        x = 10;
        if (x != 0) return 100 / x;
        return 0;
    }

#### Forbidden Examples
(1) UB: 0으로 나누기
    int main() {
        return 1 / 0;
    }

(2) UB: 미초기화 읽기
    int main() {
        int x;
        return x;
    }

(3) UB: 오버플로 (8-bit 정책 기준)
    int main() {
        return 127 + 1;
    }

(4) 제거된 문법: 전처리
    #define X 1
    int main() { return X; }

#### Notes (Non-Normative)
- “평가 순서 의존” 예시는 Expressions 7.5에 이미 존재하므로 중복을 피할 수 있다.

---


## Diagnostics — Error Code Summary
### (Normative)

---

## 1. Purpose

본 문서는 MiniC89 Language Standard에서 정의한 모든 진단(Diagnostics) 오류 코드 체계를
하나의 표로 요약한다.

이 문서는 다음 대상의 단일 기준(source of truth)이다.

- 컴파일러
- 인터프리터 / VM
- 온라인 저지
- IDE / LSP
- TA 및 채점 시스템

---

## 2. Conformance Requirement

- MiniC89 구현체는 모든 MUST 오류를 컴파일 타임에 검출 MUST 한다.
- 오류는 반드시 다음을 포함 MUST 한다.
  - 오류 코드
  - 최소 규격 오류 메시지
- 오류 코드 없이 문자열 메시지만 출력하는 구현체는
  MiniC89 표준 비적합(non-conforming)이다.

---

## 3. Error Code Categories

Range        Category
MC89-E1xx    Lexical / Token errors
MC89-E2xx    Expression / Type errors
MC89-E3xx    Statement / Control-flow errors
MC89-E4xx    Function / Program structure errors

---

## 4. MC89-E1xx — Lexical Errors

Code        Name                    Condition
MC89-E101   Invalid Character       정의되지 않은 문자가 토큰에 등장
MC89-E102   Invalid Identifier      식별자 규칙 위반
MC89-E103   Invalid Integer Literal 정수 리터럴 형식 오류
MC89-E104   Unterminated Comment    주석이 종료되지 않음

Example:
    int @x;    /* MC89-E101 */

---

## 5. MC89-E2xx — Expression / Type Errors

Code        Name                            Condition
MC89-E201   Undefined Variable              선언되지 않은 변수 사용
MC89-E202   Uninitialized Variable Read     초기화되지 않은 변수 읽기
MC89-E203   Invalid Operator                금지된 연산자 사용 (++/--/sizeof 등)
MC89-E204   Invalid Assignment Target       lvalue가 아닌 대상에 대입
MC89-E205   Invalid Expression Form         문법적으로 허용되지 않은 식
MC89-E206   Division by Zero                컴파일 타임에 판별 가능한 0으로 나누기
MC89-E207   Integer Overflow (Detected)     컴파일 타임에 검출 가능한 오버플로
MC89-E208   Evaluation Order Dependency     평가 순서 의존 표현식

Example:
    x = y++;     /* MC89-E203 */

---

## 6. MC89-E3xx — Statement / Control-flow Errors

Code        Name                        Condition
MC89-E301   Declaration After Statement 블록 내 선언 규칙 위반
MC89-E302   Declaration in for-init     C99-style for 선언
MC89-E303   break Outside Loop          반복문 외부 break
MC89-E304   continue Outside Loop       반복문 외부 continue
MC89-E305   return Outside Function     함수 외부 return
MC89-E306   Missing return Expression   int 함수에서 return;
MC89-E307   Unreachable Statement       도달 불가능 문장 (SHOULD)

Example:
    {
        x = 1;
        int y;   /* MC89-E301 */
    }

---

## 7. MC89-E4xx — Function / Program Errors

Code        Name                            Condition
MC89-E401   Missing main                   int main() 없음
MC89-E402   Invalid main Signature         main 시그니처 오류
MC89-E403   Duplicate Function Definition  함수 중복 정의
MC89-E404   Function Prototype Not Allowed 함수 선언만 존재
MC89-E405   Global Declaration Not Allowed 전역 변수/선언
MC89-E406   Invalid Parameter Declaration 매개변수 규칙 위반
MC89-E407   Call to Undefined Function     미정의 함수 호출
MC89-E408   Argument Count Mismatch        인자 개수 불일치

Example:
    int f(int a);
    int main() { return 0; }   /* MC89-E404 */

---

## 8. Diagnostics Severity Rules

Severity    Meaning
error       컴파일 실패 (MUST)
warning     컴파일 가능하나 비권장 (SHOULD)

- MC89-E307만 warning 허용
- 나머지는 모두 error MUST

---

## 9. Grammar ↔ Diagnostics Mapping (Summary)

Area        Error Codes
Lexical     E101–E104
Expressions E201–E208
Statements  E301–E307
Functions   E401–E408

---

## 10. Implementation Checklist (Normative)

MiniC89 구현체는 다음을 만족해야 한다.

- 모든 오류 코드 정의
- MUST 오류 전부 컴파일 타임 검출
- 오류 코드 + 메시지 동시 출력
- Grammar 오류와 Semantic 오류 구분
- UB는 오류 또는 경고로 진단

이를 만족하지 못한 구현체는
MiniC89 Language Standard 비적합이다.

---

End of Diagnostics Summary



MiniC89 Language Standard (v0.1) — To-Do List
(현재 붙여준 초안 기준, “표준으로 배포 가능한 상태”까지 남은 작업)

[우선순위 표기]
- P0: 배포/채점/구현에 즉시 영향 (반드시)
- P1: 표준 완성도/모호성 제거 (권장)
- P2: 교육 품질/편의 (선택)

============================================================
A. 문서 구조/템플릿 정비
============================================================

[P0] (필수) Normative 키워드 정의 절 추가
- MUST / MUST NOT / SHOULD / MAY의 의미를 문서 초반(2장 또는 0장)에서 명시.
- “Normative / Non-Normative”의 효력(적합성 판단 기준)을 명시.

[P0] (필수) “각 절 강제 템플릿” 적용 여부 점검
- 현재 1~3장은 규칙/예제/금지가 있으나, 5장(Types)·12장·13장(Annex)은 템플릿이 비어 있음.
- 최소 요건(규칙≥2, 허용 예제≥1, 금지 예제≥1)을 못 채운 절을 표시하고 채우기.

[P0] (필수) 문서 내 중복 섹션 제거/정리
- 11장 뒤에 “Diagnostics — Error Code Summary”가 문서에 한 번 더 붙어 있음(중복).
  -> 둘 중 하나만 남기고, 나머지는 “별도 파일 링크/참조”로 정리.

[P1] 제목/번호 체계 통일
- “## Chapter 10 …” 같은 표현과 “## 10 …” 혼용 제거.
- 4.2/4.3 등 번호가 바뀌면 cross-reference(“Chapter 7 참조” 등)도 함께 정리.

============================================================
B. 문법(EBNF) 보강/정합성
============================================================

[P0] (필수) 4.2 Program Grammar에 <function-definition> 등 미정의 논터미널 추가
- 현재 4.2.1은 <program>만 있고 <function-definition>이 정의되지 않음.
  -> 4.2에 아래를 포함해야 함:
     - <function-definition>
     - <parameter-list>, <parameter-decl>
     - (9장에 중복된 문법은 “참조로 대체”하거나 “4장만 규범”으로 정리)

[P0] (필수) 6장 Declarations의 EBNF를 “규범”으로 확정
- 현재 6장은 규칙+예제만 있고, 선언 EBNF는 8장에만 등장(참조 형태).
  -> 선언 문법은 6장 또는 4장(문법 장)에 규범 EBNF로 고정하고, 8장은 참조만 하도록 정리.

[P1] Lexical 레벨(식별자/정수/주석) EBNF 또는 정규 정의 추가
- 3장에서 서술만 있고 “정식 정의”가 부족함.
- 최소:
  - <identifier> 정의
  - <integer-constant> 정의(10진만)
  - 주석/공백 처리 규칙(토큰 경계)

[P1] “금지 문법” 목록 확장/정확화
- 현재 4.3 목록에 문자열 리터럴/전처리/표준 라이브러리 호출 등 추가 여부를 정리.
- 문법적으로 금지인지(파싱 실패), 의미 규칙으로 금지인지(정적 오류) 구분.

============================================================
C. 타입/값/UB 정책 확정
============================================================

[P0] (필수) int의 크기/범위 정책 결정 후 문서에 고정
- 현재 문서: “int만 존재, 오버플로 UB”까지만 존재.
- 프로젝트 합의(예: int=8-bit, -128..127)를 채택할지/아닐지 결정 후,
  - 정수 리터럴 허용 범위
  - 연산 결과 범위 밖(오버플로) 처리(UB)
  - -(-128), -128 / -1 같은 예외 UB
  를 5장에 규범적으로 박기.

[P1] 조건식의 참/거짓 규칙을 10.5.1 외에도 “Expressions/Types”에서 재확인
- “0=false, nonzero=true”를 표준 문장으로 고정(지금은 실행모델에만 있음).

[P1] “미초기화 변수 읽기 UB”의 진단 정책 결정
- 컴파일러가 반드시 잡아야 하는지(MUST error),
  가능하면 경고(SHOULD),
  또는 “검출 가능 시 진단”으로 둘지 결정.

============================================================
D. Expressions 정리(용어/오해 제거)
============================================================

[P0] (필수) 7.3 제목 수정
- 현재 제목: “Evaluation Order (Normative, for Determinism)”
- 내용은 “평가 순서 지정하지 않음(unspecified)”이므로 제목에서 “for Determinism” 제거.
  -> 결정적 시각화는 7.6 Notes(Non-Normative)로만 유지.

[P0] (필수) “콤마 연산자 금지” 문구를 규범으로 명확화
- argument-list의 ','는 구분자이며 연산자가 아님(7.6 Note에 있음).
- 이를 7.x 규범 규칙(MUST NOT: comma operator)로도 명시하고,
  (1,2) 같은 표현식이 왜 금지인지 예제로 고정.

[P1] “대입식 허용 범위” 확정
- 현재 <lvalue>는 <identifier>만 허용: 좋음.
- 체인 대입(a=b=c) 허용 여부는 문법상 허용(우결합)임. 교육 정책상 유지/금지 결정.

============================================================
E. Statements 정리(예제/오류/정적 의미)
============================================================

[P0] (필수) 8.3 if/else 예제 코드 수정
- 현재 예제는 함수 닫는 '}'가 빠져 있음.
  -> 문서 예제는 모두 “컴파일 가능한 완전한 코드”로 유지.

[P0] (필수) 8.4 “continue outside loop” 금지 예제 추가(현재 break만 있음)
- break 금지 예제는 있는데 continue 금지 예제가 없음.
  -> E304와 1:1로 맞추기.

[P1] return 규칙 명확화
- 문법상 return; 허용(8장) + 의미 규칙으로 금지(E306) 형태.
  -> “int 함수에서 return;는 오류”를 8장 규범 규칙에도 명시.

============================================================
F. Functions/Program 의미 규칙 정리
============================================================

[P0] (필수) 4장(문법)과 9장(함수) 중복 정리
- 권장 구조:
  - 4장: 문법(EBNF)만 “규범 원본”
  - 9장: 의미 규칙 + 금지 사례 + Diagnostics만
- 현재 9.1에 여전히 EBNF가 있음 -> “참조”로 바꾸거나 삭제.

[P1] “정의는 나중에 나와도 호출 가능” 여부를 규범으로 명시
- 프로토타입 금지 상태에서, forward call을 허용하려면 구현은 2-pass 필요.
- 표준에서:
  - “프로그램 내 어딘가에 정의가 존재하면 호출 가능” (대부분 기대하는 형태)
  또는
  - “정의가 호출보다 먼저 와야 함”
  중 하나를 선택해 규범으로 고정.

============================================================
G. Abstract Machine(실행 의미) 보강
============================================================

[P1] “관찰 가능한 상태”를 Annex 또는 10.7에 체크리스트로 구체화
- PC가 “문장 단위”인지, “바이트코드 단위”인지 표현 정리.
- 표준은 “문장 단위 의미”로 두고, 구현(바이트코드/스텝)은 Non-Normative로 분리.

[P1] UB 목록과 Diagnostics의 관계 명시
- UB는 “정의되지 않음”이지만, 구현이 “검출 가능 시 진단”할 수 있음.
- 어떤 UB는 MUST error로 할지(예: return; in int function),
  어떤 UB는 “검출 가능 시 진단”으로 둘지 구분.

============================================================
H. Diagnostics(전체 체계) 완성
============================================================

[P0] (필수) 11장 내부 오류 코드/번호 불일치 수정
- 현재:
  - “MC89-E306 -- Unreachable Statement”라고 써놓고,
    메시지는 “warning MC89-E307”로 되어 있음.
  - 그리고 Mapping 표에는 E306(표현식 누락)도 있음.
- 정리해야 할 정답:
  - MC89-E306 = Missing return expression (int 함수에서 return;)
  - MC89-E307 = Unreachable statement (SHOULD/warning)
  로 고정하고, 제목/설명/표 모두 일치시킬 것.

[P0] (필수) E1xx(lexical), E2xx(expression/type) MUST 오류 정의 추가
- 지금 문서에는 E3xx/E4xx가 상세하지만 E1xx/E2xx는 “요약표”만 있고,
  “발생 조건/필수 메시지”가 없음.
- 최소로라도 다음을 규범화:
  - E101~E104: 조건 + required message
  - E201~E208: 조건 + required message
  - “검출 가능 시” 정책(division by zero constant 등)

[P1] 오류 메시지 포맷(온라인 저지/IDE 연동) 고정
- 예: "error <CODE>: <message> (line:col)"
- line/col 출력이 MUST인지 SHOULD인지 결정.

============================================================
I. Standard Library(12장) 정책 결론
============================================================

[P0] (필수) 12.1 Built-in Functions 처리
- 현재 12.1은 TODO 주석 상태.
- 프로젝트 합의가 “I/O 없음”이면:
  - 12장을 “MiniC89에는 표준 라이브러리가 존재하지 않는다”로 규범화하고
  - input()/output() 언급을 제거.
- 반대로 내장함수를 넣을 거면:
  - 함수 시그니처, 의미, 부작용, UB/EOF 등을 규범 정의.

============================================================
J. Annex(13장) 채우기
============================================================

[P1] Annex A: “표준 예제” 5~10개 선정(단순/재귀/루프/중첩 if)
[P1] Annex B: “금지 예제”를 오류 코드별로 매핑(E3xx/E4xx 중심)
[P2] Annex C: “제거/축소한 UB/implementation-defined”를 명시(교육 정책)

============================================================
K. 오타/표기/품질 이슈(즉시 수정 권장)
============================================================

[P0] (필수) 오타 수정
- 4.2.4: "inf f(int a);" -> "int f(int a);"
- 7.2: "Loweset" -> "Lowest"
- 7.3: "evalutaion" -> "evaluation"
- 8.5: "Non-NOrmative" -> "Non-Normative"
- 11.y E406 메시지: "incalid" -> "invalid"

[P0] (필수) 문서 예제들의 “컴파일 가능성” 일괄 점검
- 괄호/중괄호 누락, 세미콜론, return 누락 등.

============================================================
결과물 기준(완료 정의)
============================================================

[P0 완료] 다음이 모두 만족되면 “v0.1 표준(실사용)”로 간주 가능:
- 4장 Program Grammar 완전 정의(미정의 논터미널 없음)
- 12장 정책 결정(없음/있음 중 하나로 규범화)
- 11장 오류 코드/번호 불일치 0개
- 문서 내 예제 “컴파일 가능/불가능”이 의도대로 검증됨
- Diagnostics에서 E1xx/E2xx도 “조건+필수 메시지”까지 포함

원하면, 위 TODO를 “이슈 트래커용”으로 바로 쓰게:
- GitHub Issue 제목/본문 템플릿
- 체크박스 + 담당(학생/TA/컴파일러/채점기) 라벨
형태로 재정렬해줄 수도 있음.

