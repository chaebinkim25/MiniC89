# MiniC89 Language Standard
**Draft Version:** v0.31
**Status:** Revision

본 문서는 사이버보안학과 신입생 교육을 목적으로 하는  
C89 부분집합 언어 **MiniC89**의 공식 표준을 정의한다.

이 표준은 **학생, TA, 채점기, 컴파일러/VM 구현자** 모두의 공통 기준이다.

---

### 1 Introduction
- 1.1 Purpose
- 1.2 Design Goals
- 1.3 Relationship to ISO C89

### 2 Conformance
- 2.1 Language Conformance
- 2.2 Implementation Conformance
- 2.3 Normative Keywords and Document Conventions (Normative)
  - 2.3.1 Normative vs Non-Normative Text
  - 2.3.2 Requirement Keywords
  - 2.3.3 Conformance and Diagnostics Terminology

### 3 Lexical Elements
- 3.1 Tokens
- 3.2 Keywords
- 3.3 Identifiers
- 3.4 Integer Constants
- 3.5 Comments and Whitespace
- 3.6 Lexical Grammar (Normative)
  - 3.6.1 Source Character Set (Normative)
  - 3.6.2 Regular Definitions (Normative)
  - 3.6.3 Tokenization Rules (Normative)
  - 3.6.4 Allowed Examples
  - 3.6.5 Forbidden Examples
  - 3.6.6 Notes (Non-Normative)

### 4 Syntax (Grammar)
- 4.1 Grammar Notation
- 4.2 Program Grammar (Translation Unit) (Normative)
  - 4.2.1 EBNF Definition (Normative)
  - 4.2.2 Normative Rules
  - 4.2.3 Allowed Examples
  - 4.2.4 Forbidden Examples
  - 4.2.5 Notes (Non-Normative)
- 4.3 Disallowed Constructs and Prohibitions
  - 4.3.1 Lexically Disallowed Forms
  - 4.3.2 Syntactically Disallowed Constructs
  - 4.3.3 Semantically Disallowed but Syntactically Valid Forms

### 5 Types
- 5.1 Integer Type (Normative)
- 5.2 Arithmetic Semantics and Undefined Behavior (Normative)
- 5.3 Truth Values and Conditional Context (Normative)
- 5.4 Undefined Behavior and Diagnostics Policy (Normative)
  - 5.4.1 Classification (Normative)
  - 5.4.2 Required Diagnostic Mapping (Normative)

### 6 Declarations
- 6.1 EBNF Definition (Normative)
- 6.2 Normative Rules
- 6.3 Examples

### 7 Expressions
- 7.1 Expression Grammar (Normative)
  - 7.1.1 EBNF Definition (Normative)
  - 7.1.2 Operator Hierarchy and Associativity (Normative) 
  - 7.1.3 Evaluation Order (Normative) 
- 7.2 Assignment Expressions (Normative) 
- 7.3 Boolean Interpretation (Normative) 

### 8 Statements
- 8.1 EBNF Definition (Normative)
- 8.2 Normative Rules
- 8.3 Allowed Examples
- 8.4 Forbidden Examples
- 8.5 Notes (Non-Normative)

### 9 Functions
- 9.1 Function Definition EBNF (Normative) 
- 9.2 Normative Rules
- 9.3 Allowed Examples
- 9.4 Forbidden Examples

### 10 Program Execution Model
- 10.1 Purpose
- 10.2 Abstract Machine Components
  - 10.2.1 Program
  - 10.2.2 Program Counter (PC)
  - 10.2.3 Call Stack
  - 10.2.4 Stack Frame
- 10.3 Memory Model
  - 10.3.1 Objects
  - 10.3.2 Lifetime
- 10.4 Execution Semantics
  - 10.4.1 Program Start
  - 10.4.2 Statement Execution
  - 10.4.3 Function Call
  - 10.4.4 Function Return
- 10.5 Control Flow Semantics
  - 10.5.1 Conditional (`if / else`)
  - 10.5.2 Iteration (`for`)
  - 10.5.3 `break` / `continue`
- 10.6 Undefined Behavior
- 10.7 Observability and Visualization (Non-Normative)
  - 10.7.1 Statement-level PC vs Implementation-level Step
  - 10.7.2 Observable State Checklist
  - 10.7.3 Suggested Presentation Rules

### 11 Diagnostics
- 11.1 Overview 
- 11.2 Diagnostic Message Format (Normative)
  - 11.2.1 One-line Format (Normative)
  - 11.2.2 Location Counting Rules (Normative)
  - 11.2.3 Examples (Non-Normative)
  - 11.2.4 Interaction with “Required Message” Fields (Normative)
- 11.3 Lexical Diagnostics (Normative) 
- 11.4 Expression / Type Diagnostics (Normative)
- 11.5 Statement Diagnostics (Normative)
- 11.6 Function / Program Diagnostics (Normative) 

### 12 Standard Library
- 12.1 Standard Library Policy (Normative)

### 13 Annex (기본 Non-Normative, 별도 표기 시 Normative)
- Annex A Standard Examples
- Annex B Forbidden / Invalid Programs
- Annex C Undefined / Removed Behaviors
- Annex D Diagnostics — Error Code Summary (Normative)
  - D.1 Purpose
  - D.2 Conformance Requirement
  - D.3 Error Code Categories
  - D.4 MC89-E1xx — Lexical Errors
  - D.5 MC89-E2xx — Expression / Type Errors
  - D.6 MC89-E3xx — Statement / Control-flow Errors
  - D.7 MC89-E4xx — Function / Program Errors
  - D.8 Diagnostics Severity Rules
  - D.9 Grammar ↔ Diagnostics Mapping (Summary)
  - D.10 Implementation Checklist (Normative)

---

## 1. Introduction

### 1.1 Purpose

MiniC89는 C 언어를 가장 낮은 진입 장벽으로 이해할 수 있게 만드는 것을 목적으로 한다.

### 1.2 Design Goals

- 초심자를 위한 최소 언어
- ANSI C89 의미론 보존
- 하드웨어 동작 단순화

### 1.3 Relationship to ANSI C89

- MiniC89는 ANSI C89의 엄격한 부분집합이다.
- 모든 유효한 MiniC89 프로그램은 유효한 C89 프로그램이다.
- 그 역은 성립하지 않는다.

---

## 2. Conformance

### 2.1 Language Conformance
MiniC89 프로그램은 본 표준의 모든 MUST / MUST NOT 규칙을 만족해야 한다.

### 2.2 Implementation Conformance
MiniC89 구현체는 다음을 만족해야 한다.

- 본 표준에 정의되지 않은 문법을 허용하지 않는다.
- 오류를 컴파일 타임에 검출하고, 오류 코드를 반드시 출력한다.

### 2.3 Normative Keywords and Document Conventions (Normative)

본 절은 본 표준 문서 전체에서 사용되는 규범 키워드의 의미와,
규범(Normative) / 비규범(Non-Normative) 텍스트의 효력을 정의한다.

#### 2.3.1 Normative vs Non-Normative Text

- 본 표준에서 다음에 해당하는 내용은 규범적(Normative)이며,
  MiniC89 적합성(conformance) 판단의 기준이 된다.
  - 제목에 (Normative)가 명시된 절/하위절
  - Normative Rules 하위 섹션의 모든 문장
  - EBNF Definition에 포함된 문법 정의
  - Operator Hierarchy 및 우선순위/결합 규칙 표
  - Diagnostics에 포함된 오류 코드/발생 조건/필수 메시지

- 다음에 해당하는 내용은 비규범적(Non-Normative)이며,
  구현/채점/학생 이해를 돕기 위한 설명일 뿐 언어 의미를 추가/변경하지 않는다.
  - Notes
  - Allowed Examples
  - Forbidden Examples

- 규범적 텍스트와 비규범적 텍스트(예제/노트)가 충돌할 경우,
  규범적 텍스트가 우선한다.
  - 예제는 설명 목적이며, 언어를 정의하지 않는다.

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

#### 2.3.3 Conformance and Diagnostics Terminology

- Conforming Program
  - 본 표준의 문법(EBNF)과 모든 정적 제약(MUST/MUST NOT)을 만족하는 프로그램을 말한다.
  - 단, 특정 입력/실행 경로에서 Undefined Behavior(UB)를 유발할 수 있는 프로그램도
    문법적으로는 적합할 수 있으나, UB가 발생한 이후의 동작은 정의되지 않는다.

- Conforming Implementation
  - 본 표준이 요구하는 문법/의미 규칙을 만족하고,
    본 표준이 진단을 요구(MUST detect)하는 모든 상황을 진단하는 구현체를 말한다.

- Compile-time
  - 파싱, 정적 분석, 의미 분석, 코드 생성 등 실행 이전 단계를 의미한다.
  - 인터프리터/VM 기반 구현체의 경우에도, 사용자 코드 실행 이전에 수행되는
    모든 정적 검사 단계를 포함한다.

- Diagnostic
  - 컴파일 타임에 보고되는 오류/경고 메시지를 말한다.
  - 본 표준이 오류 코드를 규정한 경우, 구현체는 반드시 오류 코드와 메시지를 함께 출력한다.

- MUST be Compile-time Error
  - 구현체는 해당 프로그램을 거부(reject)하며,
    최소 1개의 진단을 error 수준으로 보고한다.
  - 본 표준이 특정 오류 코드(MC89-Exxx)를 지정한 경우,
    구현체는 그 오류 코드를 포함하여 보고한다.

- Undefined Behavior (UB)
  - 본 표준이 UB로 정의한 상황이 실행 중 발생하면,
    그 이후 프로그램의 동작은 정의되지 않는다.
  - UB에 대한 진단은 본 표준이 별도로 요구하지 않는 한 필수는 아니다.
  - 단, 구현체는 UB를 정적으로 검출 가능하다면 진단을 추가로 보고한다.

- Unspecified Behavior
  - 표준이 일부 동작을 “지정하지 않음”으로 남겨둔 경우를 말한다.
  - 예: 대부분의 연산자에서 피연산자 평가 순서, 함수 인자 평가 순서.
  - 구현체는 이 경우들에 대해 특정 동작을 가정해서는 안 된다.

- Implementation-defined Behavior
  - 표준이 구현마다 달라질 수 있음을 허용하되, 구현이 반드시 문서화해야 하는 동작을 말한다.
  - MiniC89는 교육/채점 목적상 implementation-defined 동작을 최소화하는 것을 목표로 하며,
    본 표준에 등장하는 경우 구현체는 그 내용을 문서화 한다.

---
    
## 3. Lexical Elements

### 3.1 Tokens

MiniC89의 토큰은 다음으로 구성된다.

- Keywords
- Identifiers
- Integer constants
- Operators
- Punctuators

### 3.2 Keywords

**Normative Rule**  
MiniC89 구현체는 ANSI C89에서 정의된 모든 키워드를 keyword로 토큰화 한다.  
MiniC89가 키워드로 지원하는 것은 문법(EBNF)에 포함된 구문으로 제한된다.  
문법에 포함되지 않은 키워드가 등장한 프로그램은 컴파일 타임 오류로 거부한다 (오류 코드: MC89-E203).

다음 키워드는 예약어이다.

int  
if  
else  
for  
return  
break  
continue  

다음 키워드는 C89에 있기 때문에 MiniC89에서 쓰이지는 않지만 보존된 예약어이다. 

auto
double
struct
long
switch
case
enum
register
typedef
extern
union
const
float
short
unsigned
signed
void
default
goto
sizeof
volatile
do
static
while

**Note:** 
키워드로 토큰화는 해당 구문을 허용한다는 뜻이 아니라,
단지 해당 토큰이 식별자가 아님을 의미한다.

### 3.3 Identifiers

- 식별자는 알파벳 또는 '_'로 시작한다.
- 이후 알파벳, 숫자, '_'의 조합으로 구성된다.
- 키워드와 동일한 이름은 사용할 수 없다 (오류 코드: MC89-E102).

### 3.4 Integer Constants

- 10진 정수 리터럴만 허용된다.
- 부호는 리터럴의 일부가 아니다.
- 범위를 벗어난 정수 리터럴은 컴파일 오류이다 (오류 코드: MC89-E103).

### 3.5 Comments and Whitespace

- /* ... */ 형식의 주석만 허용된다.
- // 주석은 허용되지 않는다 (오류 코드: MC89-E105).
- 공백과 줄바꿈은 토큰 구분에만 영향을 준다.

---

### 3.6 Lexical Grammar

#### 3.6.1 Source Character Set (Normative)
MiniC89 소스는 다음 문자들만을 포함한다.

A. 공백 문자 (whitespaces)
- SP(0x20), HT(0x09), VT(0x0B), FF(0x0C), LF(0x0A), CR(0x0D)

B. 식별자 문자 (identifiers)
- 알파벳 대소문자: `A`-`Z`, `a`-`z`
- 숫자: `0`-`9`
- 밑줄: `_`  

C. 정수 리터럴을 구성하는 문자 (integer constants)
- 숫자: `0`-`9`

D. 연산자 문자 (operators)
- `+` `-` `*` `/` `%`
- `<` `>` `=` `!`
- `&` `|`  (논리 연산자 구성용)

E. 구분기호 (punctuators)
- `(` `)` `{` `}` `;` `,`

F. 주석 구성 문자
- `/` `*`  (C 스타일 주석 `/* ... */` 구성용)

위 범위에 속하지 않는 문자가 소스 파일에 등장하면, 구현체는 컴파일 타임 오류로 진단한다 (오류 코드: MC89-E101)

#### 3.6.2 Regular Definitions (Normative)
본 절에서는 ASCII 기준으로 정규 문법 (Regular Grammar)를 정의한다.

(1) Letter / Digit
```ebnf
<letter> := [A-Za-z]
<digit>  := [0-9]
<nondigit> := <letter> | "_"
```
- `<letter>`는 `A`부터 `Z`까지 또는 `a`부터 `z`까지의 알파벳 대소문자 하나다.
- `digit`은 `0`부터 `9`까지 숫자 하나다.
- `<nondigit>`은 `<letter>` 또는 밑줄 기호 `_`를 의미한다. 

(2) Identifier
```ebnf
<identifier> := <nondigit> (<nondigit> | <digit>)*
```

- `<identifier>`는 `<nondigit>`으로 시작하고, 0개 이상의 (`<nondigit>` 또는 `<digit>`)이 이어서 나오는 것이다.

(3) Integer Constant
```ebnf
<integer-constant> := "0" | [1-9]<digit>*
```

- `<integer-constant>`는 숫자 `0` 만으로 이뤄진 형태, 또는 `1`부터 `9`까지 숫자로 시작하고, 그 뒤에 0개 이상의 숫자가 있는 형태다. 
- 즉, 선행 `0` 뒤에 다른 숫자가 나오는 형태(예: `00`, `077`)은 허용되지 않는다.

(4) Whitespace
```ebnf
<whitespace> := one or more of (SP | HT | VT | FF | LF | CR)
```

- `<whitespace>`는 띄어쓰기 (SP), 탭 (HT), 세로탭 (VT), 페이지바꿈 (FF), 줄바꿈 (LF), 커서 왼쪽 끝 이동 기호 (CR) 중 하나를 의미한다.

(5) Block Comment (C-style only)
```ebnf
<comment> starts with "/*" and ends with the first subsequent "*/"
```

- 주석은 `/*`로 시작해서 `*/`로 끝난다.
- 주석은 중첩(nesting)되지 않는다.
- 파일의 끝(EOF)까지 `*/`를 만나지 못하면 오류로 진단한다. (오류 코드: MC89-E104).

#### 3.6.3 Tokenization Rules
- 구현체는 소스 파일을 왼쪽에서 오른쪽으로 스캔하며 토큰을 생성한다.
- `<whitespace>` 및 `<comment>`는 토큰 경계로 취급되며, 토큰 스트림에 포함되지 않는다.
- 구현체는 다음 최장 일치(maximal munch) 원칙을 적용한다.
  - 동일 위치에서 둘 이상의 토큰 후보가 가능하면, 더 긴 후보를 선택한다.
  - 특히 연산자/구분기호에서 2글자 토큰은 1글자 토큰보다 우선한다.
    예: `==`는 `=`와 `=`로 분리되지 않는다.
- 스캔 위치에서 `//`가 등장하면, 이는 MiniC89에서 허용되지 않는 라인 주석 형태이므로  
  구현체는 컴파일 타임 오류로 진단한다 (오류 코드: MC89-E105).

키워드와 식별자 규칙:
- 스캔된 문자열이 키워드 집합과 정확히 일치하고, 그 시작이 `<nondigit>`으로 확장되지 않고,
  끝이 식별자 문자(`<nondigit>`|`<digit>`)로 확장되지 않는 경우, 해당 토큰은 Keyword로 분류한다.
- 그렇지 않으면 `<identifier>`에 매칭되는 토큰은 Identifier로 분류한다.
  예: `intx`는 Keyword `int` + `x`가 아니라 Identifier `intx`이다.

정수 리터럴 규칙:
- `<integer-constant>`에 부합하지 않는 숫자 시작 토큰은 잘못된 정수 리터럴로 진단 한다 (오류 코드: MC89-E103).
  - 0으로 시작하며 길이가 2 이상인 숫자열: 00, 077, 0123
  - 0x 또는 0X로 시작하는 형태: 0x10
  - 숫자열 뒤에 식별자 문자가 붙어 분리되지 않는 형태: 123abc

연산자/구분기호 토큰 집합:
- 2글자 연산자: `<=`, `>=`, `==`, `!=`, `&&`, `||`
- 1글자 연산자: `+`, `-`, `*`, `/`, `%`, `<`, `>`, `=`, `!`
- 구분기호: `(`, `)`, `{`, `}`, `;`, `,`

주석 시작 처리:
- 스캔 위치에서 `/*`가 보이면 `<comment>`를 형성한다.
- `//`는 주석이 아니며 오류로 진단한다 (오류 코드: MC89-E203)

#### 3.6.4 Allowed Examples
(1) Identifier
```c
int main() {
    int _x1;
    _x1 = 0;
    return _x1;
}
```

(2) Integer constants
```c
int main() {
    return 0 + 7 + 127;
}
```

(3) Block comment treated as whitespace
```
int main() {
    /* this is a comment */
    return 0;
}
```

#### 3.6.5 Forbidden Examples (MUST be Compile-time Error)
(1) Invalid character (MC89-E101)
```c
int main() { return 0; } @
```

(2) Unterminated comment (MC89-E104)
```c
    /* unterminated comment
```

(3) Invalid integer literal (MC89-E103: leading zero / hex / digit+letters)
```c
int main() { return 077; }      /* ERROR: MC89-E103 */
```

```c
int main() { return 0x10; }     /* ERROR: MC89-E103 */
```

```c
int main() { return 123abc; }   /* ERROR: MC89-E103 */
```

(4) Invalid identifier usage
```c
int if;  /* ERROR: MC89-E102 */
```

#### 3.6.6 Notes (Non-Normative)
- 본 절은 3.3/3.4/3.5의 서술을 “정식 정의”로 보강하기 위한 것이다.
- 정수 리터럴 값 범위(예: 0..127)의 의미론/범위 규칙은 5.1 Integer Type에 따른다.
---

## 4. Syntax (Grammar)

### 4.1 Grammar Notation
본 표준에서 사용되는 문법 표기법은 EBNF (Extended Backus-Naur Form) 이다.
EBNF는 프로그래밍 언어의 구문 구조(syntax)를 공식적으로 정의하기 위한 표기법이다.

EBNF에서 사용되는 주요 표기 요소의 의미는 다음과 같다.

#### 비단말 기호 (Nonterminal)
- `<name>` 형태로 표기된다.
- 언어의 문법적 구성 요소를 나타낸다.
- 예: `<expression>`, `<statement>`, `<identifier>`

#### 단말 기호 (Terminal)
- 실제 소스 코드에 그대로 등장하는 토큰이다.
- 보통 따옴표로 감싸서 표기한다.

```ebnf
"if" "(" <expression> ")"
```

#### 정의 기호
- `::=`는 정의된다(is defined as)를 의미한다.
```ebnf
<statement> ::= <expression> ";"
```

Notes: `:=`도 정의된다를 의미하며, 본 표준에서는 토큰/정규 정의에서만 `:=`를 쓴다.

#### 선택
- `|`는 여러 대안 중 하나를 의미한다.
```ebnf
<statement> ::= <expression-statement> | <compound-statement>
```

#### 반복
- `{ x }`는 `x`를 0회 이상 반복하는 것을 의미한다.
```ebnf
<block-item-seq> ::= { <declaration> } { <statement> }
```

#### 선택적 요소
- `[ x ]`는 `x`가 있을 수도 있고 없을 수도 있음 (0개 또는 1개)를 의미한다.
```ebnf
<return-statement> ::= "return" [ <expression> ] ";"
```

#### 그룹화
- 괄호 `( ... )`는 여러 요소를 하나의 단위로 묶는다.
```ebnf
<unary-expression> ::= <postfix-expression>
                     | ( "+" | "-" | "!" ) <unary-expression>
```

### 4.2 Program Grammar
본 절에 제시된 EBNF는 MiniC89 프로그램 전체에 대한
유일한 규범적 문법 정의(normative grammar definition) 이다.

이 규칙에 따라 파싱될 수 없는 소스 코드는
MiniC89 프로그램으로 간주될 수 없다 (오류 코드: MC89-E205).

#### 4.2.1 EBNF Definition
```ebnf
<program>                 ::= { <external-declaration> } ;
<external-declaration>    ::= <function-definition> ;
```

#### 4.2.2 Normative Rules
- 본 절에서 사용되는 `<function-definition>` 및 매개변수 정의는 **9. Functions** 에 있다.
- 프로그램은 정확히 하나의 엔트리 함수 `int main()`을 포함해야 한다.
  - `main`은 매개변수를 가질 수 없다.
- 파일 스코프 (file scope)에서는 오직 함수 정의만 허용한다.
- 구현체는 파일 스코프에서 다음 패턴을 발견하면 지정된 오류 코드로 진단한다.

- Function prototype (금지, MC89-E404): `"int" <identifier> "(" <parameter-list> ")" ";"`
  `<parameter-list>`는 **9.1 Function Definition - EBNF Definition**에 정의되어 있다.
  
- Global declaration (금지, MC89-E405): `<declaration>`
  `<declaration>`은 **6.1 Declarations - EBNF Definition**에 정의되어 있다.
  
- 프로토타입 vs 함수 정의 판별 권장 알고리즘
  - `int` 다음에 `<identifier>`가 오지 않으면, 식별자 위치 위반 (MC89-E102)
  - `<identifer>` 다음 토큰이 `(` 이면:
    - `)`까지 `<parameter-list>` 파싱 시도
    - 그 다음 토큰을 확인:
      - 다음이 `{`면 함수 정의 (허용)
      - 다음이 `;`면 프로토타입 (금지, MC89-E404)
      - 식 문법 위반 (MC89-E205)
  - `<identifier>` 다음 토큰이 `(`가 아니면:
    - 파일 스코프 전역 변수 선언으로 간주 (MC89-E405) 

#### 4.2.3 Allowed Examples
```c
int main() {
  return 0;
}
```

#### 4.2.4 Forbidden Examples

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

#### 4.2.5 Notes
- MiniC89는 ANSI C89의 translation unit 개념을 단순화한 모델을 사용한다.
- 헤더 파일, 전처리, 분할 컴파일 개념은 존재하지 않는다.
- 이로 인해 모든 이름 해석은 단일 파일, 단일 번역 단위에서 이루어진다.
- 프로토타입, 전역 변수는 MiniC89 EBNF에 존재하지 않으므로 원칙적으로 문법 오류지만, 채점/교육 목적의 결정적 진단을 위해 구현체는 구체 코드(E404/E405)를 우선으로 한다. 

### 4.3 Disallowed Constructs and Prohibitions

본 절은 ANSI C89에 존재하지만 MiniC89에서는 제거되었거나 금지되는 구성요소를 정의한다.
MiniC89 구현체는 본 절에 해당하는 프로그램을 컴파일 타임에 거부한다.

#### 4.3.1 Normative Rules
- 본 절의 금지 사항은 유효한 MiniC89 프로그램의 범위를 정의한다.
- 구현체는 금지 사항을 발견하면 최소 1개의 진단(error)을 보고한다.
- 금지 사항이 문법(EBNF)에 존재하지 않음으로 정의된 경우, 구현체는 해당 프로그램을
  문법적으로 유효한 MiniC89 프로그램으로 취급하지 않는다.
- 금지 사항이 정적 의미 규칙 위반으로 정의된 경우, 구현체는 파싱 성공 여부와 무관하게
  해당 프로그램을 거부한다. 

#### 4.3.2 Lexically Disallowed Forms

다음 항목은 MiniC89의 **3. Lexical Elements**에 정의된 토큰 집합에 존재하지 않으며,
해당 형태가 소스에 등장하면 구현체는 토큰화 단계에서 오류로 진단한다.

- 전처리 지시문: `#`로 시작하는 전처리 라인 전체 (MC89-E106)
- 문자열 리터럴: `"`로 시작하는 문자열 리터럴 (MC89-E107) 
- 문자 리터럴: `'`로 시작하는 문자 상수 (MC89-E108)
- 실수 리터럴: `1.0`, `1E2` 등의 실수 상수 (Mc89-E109)
- 라인 주석: `//`로 시작하는 주석  (MC89-E105)

#### 4.3.2 Syntactically Disallowed Constructs


다음 항목은 MiniC89 문법으로 파싱될 수 없어야 한다.

- 파일 스코프에서의 전역 변수/선언 (MC89-E405)
- 파일 스코프에서의 함수 프로토타입 (MC89-E404)
- C99 스타일 `for` 선언 (MC89-E302)
- `int` 이외의 타입/키워드: `char`, `float`, `double`, `short`, `long`, `unsigned`, `signed`, `void` (MC89-E210)
- 사용자 정의 타입: `struct`, `union`, `enum`, `typedef` (MC89-E211)
- 포인터/배열 관련 선언 및 구문: `*`(선언자), `&`, `[]` (MC89-E212)
- 증감 연산자: `++`, `--` (MC89-E213)
- sizeof 연산자 (MC89-E214)
- 조건(삼항) 연산자: `?:` (MC89-E215)
- 비트 연산자: `& | ^ ~ << >>` (MC89-E216)
- 콤마 연산자: `E1, E2` 형태 (MC89-E217)
- 허용되지 않는 키워드: `while`, `do`, `switch`, `case`, `default`, `goto`, `case`,`default` (MC89-E110)

---

#### 4.3.3 Semantically Disallowed but Syntactically Valid Forms (Static semantic errors)

다음 항목은 MiniC89 문법으로는 파싱될 수 있으나,
정적 의미 규칙을 위반하므로 금지된다.

- 선언되지 않은 변수 사용: MC89-E201
- 초기화되지 않은 변수 읽기: MC89-E202
- 프로그램 내에 정의되지 않은 함수 호출(표준 라이브러리 호출 포함): MC89-E407
  - 예: printf, scanf, puts, getchar 등 (예시는 비한정 목록)
- 함수 인자 개수 불일치: MC89-E408

"표준 라이브러리 호출 금지"는 문법으로 금지할 수 없으므로(식별자는 항상 문법적으로 가능),
정적 의미 규칙(정의 존재성 검사)으로 금지한다.

---

## 5. Types

### 5.1 Integer Type

#### 5.1.1 Normative Rules
- MiniC89에는 오직 하나의 타입 `int`만 존재 MUST 한다.
- MiniC89의 `int`는 정확히 8-bit이며, 표현은 2의 보수다.
- 따라서 `int`의 값 범위는 다음과 같이 고정된다.
  - INT_MIN = -128
  - INT_MAX =  127
- 모든 변수, 매개변수, 함수 반환값은 `int` 타입 MUST 이다.

정수 리터럴 정책:
- 10진 정수 리터럴의 값은 0 이상 127 이하 MUST 이다.
- 위 범위를 벗어나는 정수 리터럴은 컴파일 타임 오류다.
  - 진단 코드: MC89-E103

#### 5.1.2 Allowed Example
**1) 범위 내 리터럴/연산**
```c
int main() {
    int x;
    x = 127;
    x = x - 1;    /* 126 */
    return x;
}
```

**2) -128을 “128 리터럴 없이” 만들기**
```c
int main() {
    int m;
    m = -127 - 1; /* -128 */
    return m;
}
```

#### 5.1.3 Forbidden Examples
**1) 정수 리터럴 범위 위반**
```c
int main() {
    int x;
    x = 128;      /* ERROR: integer literal out of range */
    return 0;
}
```

**2) 허용 타입 위반**
```c
int main() {
    char c;           /* ERROR: only 'int' type is allowed */
    return 0;
}
```

### 5.2 Arithmetic Semantics and Undefined Behavior

#### 5.2.1 Normative Rules
- MiniC89의 산술 연산은 정확한 정수에서 수행한 뒤,
  그 결과가 `int` 범위에 포함되는지 검사한다.
- 다음 연산자들의 결과가 `int` 범위를 벗어나면 Undefined Behavior(UB)다.
  - 단항: `+`, `-`
  - 이항: `+`, `-`, `*`, `/`, `%`
- 나눗셈과 나머지 연산에 대해:
  - 제수(divisor)가 0이면 UB다.
  - `a / b`는 정수 나눗셈의 몫을 의미하며,
    그 몫이 범위를 벗어나면 UB다.
  - `a % b`는 나머지를 의미하며, 제수가 0이면 UB다.
- wrap-around(모듈러) 동작은 정의하지 않는다.

#### 5.2.2 Allowed Examples
**1) 범위 내 산술 연산**
```c
int main() {
    int a;
    int b;
    a = 100;
    b = 27;
    return a + b;   /* 127 */
}
```

**2) 0으로 나누기를 피하는 형태**
```c
int main() {
    int x;
    x = 10;
    if (x != 0) return 100 / x;
    return 0;
}
```

#### Forbidden Examples

**1) 상수식 0으로 나누기**
```c
int main() {
    return 1 / 0;     /* ERROR: MC89-E206 */
}
```

**2) 상수식 오버플로**
```c
int main() {
    return 127 + 1;   /* ERROR: MC89-E207 */
}
```

**3) -(-128) 오버플로**
```c
int main() {
    return -(-127 - 1);  /* ERROR: MC89-E207 */
}
```

**4) (-128)/(-1) 오버플로**
```c
int main() {
    return (-127 - 1) / -1;  /* ERROR: MC89-E207 */
}
```

**5) 미초기화 변수 읽기**
```c
int main() {
    int x;
    return x;         /* ERROR: MC89-E202 */
}
```

#### 5.2.x Integer Division and Remainder Semantics (Normative)

**Normative Rules**
- `a / b` 및 `a % b`에서 `a`와 `b`는 `int` 값이다.
- `b == 0`이면 Undefined Behavior(UB) MUST 이다.  
  (CTCE에서 `b`가 0으로 판별되면 MC89-E206 MUST)
- `a == INT_MIN`이고 `b == -1`이면 결과가 `INT_MAX + 1`이 되므로 UB MUST 이다.  
  (CTCE에서 판별되면 MC89-E207 MUST)

**정의 (MUST)**
- `a / b`는 **0을 향한 절단(truncation toward zero)** 정수 몫을 의미 MUST 한다.
  - 즉, 실수 몫 `a / b`를 계산했을 때, 소수 부분을 버리고 0에 가까운 정수로 만든 값이 몫이다.
- `a % b`는 다음을 만족하는 **유일한 정수 r**로 정의 MUST 한다.
  - `a == (a / b) * b + r`
  - `|r| < |b|`
  - `r == 0` 또는 `r`의 부호(sign)는 `a`와 동일 MUST 하다. (dividend sign rule)

**결과 범위**
- `a / b` 및 `a % b`의 결과는 `int` 범위(INT_MIN..INT_MAX)에 있어야 하며,
  범위를 벗어나면 UB MUST 이다.
  - (현재 int 범위가 -128..127로 고정된 정책에서는 사실상 `INT_MIN / -1`만 문제가 됨)

---

### 예시 (Non-Normative)

> 아래 예시는 “0을 향한 절단” 규칙을 보여준다.

- `-7 / 3 == -2`  
- `-7 % 3 == -1`  (왜냐하면 `-7 == (-2)*3 + (-1)`)

- `7 / -3 == -2`  
- `7 % -3 == 1`   (왜냐하면 `7 == (-2)*(-3) + 1`)

- `-7 / -3 == 2`  
- `-7 % -3 == -1`

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
- 다음 연산자들의 결과 값은 반드시 `0` 또는 `1` MUST 이다.
  - 관계(비교) 연산자: `<`, `<=`, `>`, `>=`
  - 동등(비교) 연산자: `==`, `!=`
  - 논리 연산자: `&&`, `||`
  - 논리 부정: `!` (이미 규정되어 있으나, 본 규칙에 포함되어도 됨)

- 관계/동등 연산자에 대해:
  - 비교 결과가 참(true)이면 결과는 `1` MUST 이다.
  - 비교 결과가 거짓(false)이면 결과는 `0` MUST 이다.

- 논리 연산자에 대해:
  - `E1 && E2`의 결과는
    - 두 피연산자가 conditional context 해석에서 모두 true이면 `1`,
    - 그 외에는 `0` MUST 이다.
  - `E1 || E2`의 결과는
    - 두 피연산자 중 하나라도 true이면 `1`,
    - 둘 다 false이면 `0` MUST 이다.
  - `&&`/`||`는 Chapter 7의 단락 평가 규칙을 MUST 따른다.

> 즉, `&&`/`||`의 결과는 “C처럼 0/비0 전달”이 아니라 **항상 0/1로 정규화(normalize)** 된다.

#### Allowed Examples
```c
int main() {
    int x;
    x = 0;
    if (x) return 1;   /* false */
    x = -3;
    if (x) return 2;   /* true  */
    return 0;
}
```
```c
int main() {
  int a;
  int b;
  a = (3 < 5);     /* a = 1 */
  b = (3 == 5);    /* b = 0 */
  return a + b;    /* 1 */
}
```
```c
int main() {
  int x;
  x = (5 && -3);   /* x = 1 (둘 다 true) */
  x = (0 || 7);    /* x = 1 */
  x = (0 || 0);    /* x = 0 */
  return x;
}
```
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
### 5.4 Undefined Behavior and Diagnostics Policy (Normative)

#### Normative Rules
- Undefined Behavior(UB)란, 실행 중 특정 상황이 발생했을 때 그 이후 프로그램 동작이
  본 표준에 의해 정의되지 않는 것을 의미한다.
- UB가 발생한 프로그램에 대해 구현체가 어떤 동작(특정 값 출력, 종료, 경고 출력 등)을 하더라도,
  그것이 MiniC89 언어 의미를 “정의”하는 것으로 간주되어서는 안 된다(MUST NOT).

- UB에 대한 진단(Diagnostic)은 원칙적으로 필수가 아니다.
  단, 본 표준이 특정 상황을 “MUST detect”로 지정한 경우,
  구현체는 반드시 컴파일 타임 오류로 보고 MUST 한다.

- MiniC89는 교육/채점의 결정성을 위해, 다음 일부 상황을
  “UB로 분류될 수 있는 위험 행위”이더라도 정적 제약으로 끌어올려
  컴파일 타임 오류(MUST be Compile-time Error)로 금지한다.
  (즉, 유효한 MiniC89 프로그램에서는 해당 상황이 발생할 수 없다.)

#### 5.4.1 Classification (Normative)
본 표준은 위험 상황을 다음 세 부류로 나눈다.

A) Constraint Violations (MUST be Compile-time Error)
- 문법상 파싱이 가능하더라도, 표준이 금지(MUST NOT)한 정적 의미 위반.
- 구현체는 반드시 오류로 거부 MUST 한다. (해당 오류 코드 사용 MUST)

B) Compile-time Detectable UB in Constant Expressions (MUST be Compile-time Error)
- Chapter 11의 CTCE(컴파일 타임 상수식) 정책에 따라 상수식으로 판별 가능한 UB.
- 구현체는 반드시 오류로 거부 MUST 한다. (해당 오류 코드 사용 MUST)

C) Runtime UB (No required diagnostic; MAY diagnose)
- 상수식으로 판별되지 않거나 런타임 값에 의존하여 발생하는 UB.
- 구현체는 이를 실행 전/중에 검출 가능하다면 진단을 출력 MAY 하며,
  실행을 중단(trap) MAY 한다.
- 그러나 진단/중단 여부와 무관하게, UB가 발생한 이후의 동작은 정의되지 않는다.

#### 5.4.2 Required Diagnostic Mapping (Normative)
아래 표는 “UB/위험 패턴”과 Diagnostics 요구사항의 관계를 요약한다.

Case / Pattern                                             Class   Requirement / Code
------------------------------------------------------------------------------------------------
미초기화 변수 읽기(read of uninitialized variable)          A       MUST error: MC89-E202
평가 순서(unspecified order)에 의존하는 부작용 표현식        A       MUST error: MC89-E208
int 함수에서 return; (표현식 없는 return)                   A       MUST error: MC89-E306
CTCE에서 0으로 나누기(/ 또는 %)                              B       MUST error: MC89-E206
CTCE에서 정수 오버플로(범위 밖 결과, -MIN, MIN/-1 포함)      B       MUST error: MC89-E207
런타임 0으로 나누기(제수가 변수 등 CTCE가 아님)              C       UB, MAY diagnose (권장 코드: MC89-E206)
런타임 정수 오버플로(CTCE가 아님)                            C       UB, MAY diagnose (권장 코드: MC89-E207)

Notes (Non-Normative)
- “return; in int function”은 UB가 아니라 언어 제약 위반으로 분류(A)한다.
- E206/E207은 원칙적으로 CTCE에서 MUST error이며, 런타임에서 이를 감지하는 경우
  구현체는 동일 코드를 재사용 MAY 한다(필수 아님).

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
## 6.x Scope and Name Binding (Normative)  *(권장: Chapter 6 또는 Chapter 9에 신설)*

### 6.x.1 Scopes (Normative)

#### Normative Rules
- MiniC89에서 변수/매개변수의 유효 범위(scope)는 **블록(block) 기반 정적 스코프** MUST 이다.
- 각 `{ ... }`(compound-statement)는 새로운 **block scope**를 생성 MUST 한다.
- 함수의 매개변수(parameter)는 함수 진입 시 선언된 것으로 간주하며,
  함수 본문 전체에서 유효 MUST 하다.
  - 구현 단순성을 위해 매개변수는 “함수 최외곽 블록의 선행 선언”으로 취급 MAY 한다.
- 스코프는 중첩될 수 있으며, `{`에서 생성되고 해당 `}`에서 종료 MUST 한다.

> Note (Non-Normative):  
> 본 규칙은 C89의 블록 스코프 모델을 단순화한 것으로, MiniC89 프로그램은 항상 단일 파일 내에서 해석된다.

#### Allowed Examples
**(1) 서로 다른 이름 사용**
```c
int main() {
  int x;
  int y;
  x = 1;
  y = 2;
  return x + y;
}
```
**(2) sibling block에서의 재사용(이전 스코프가 종료된 뒤이므로 허용)**
```c
int main() {
  { int x; x = 1; }
  { int x; x = 2; }  /* OK: 첫 번째 x의 스코프는 이미 종료됨 */
  return 0;
}
```

#### Disallowed Examples
**(1) 같은 스코프 중복 선언**
```c
int main() {
  int x;
  int x;        /* ERROR: MC89-E209 */
  return 0;
}
```
**(2) 같은 선언 리스트 내부 중복**
```c
int main() {
  int x, x;     /* ERROR: MC89-E209 */
  return 0;
}
```
**(3) shadowing (inner block)**
```c
int main() {
  int x;
  { int x; }    /* ERROR: MC89-E209 (shadowing not allowed) */
  return 0;
}
```
**(4) 매개변수/지역변수 이름 충돌**
```c
int f(int x) {
  int x;        /* ERROR: MC89-E209 */
  return 0;
}
```
**(5) 매개변수 이름 중복**
```c
int f(int a, int a) {  /* ERROR: MC89-E209 */
  return 0;
}
```
---

### 6.x.2 Declaration Conflicts (Normative)

#### 정책 결정 (Normative): **Shadowing 금지**
MiniC89는 교육/채점 목적상 **shadowing(가려쓰기)을 허용하지 않는다.**

#### Normative Rules
- 어떤 스코프에서든, 선언이 새로운 이름 `<name>`을 도입할 때:
  - 현재 스코프에 동일 이름이 이미 존재하면 **중복 선언**이며 MUST NOT 허용한다.
  - 현재 스코프의 어떤 **enclosing(바깥) 스코프**에 동일 이름이 존재하면 **shadowing**이며 MUST NOT 허용한다.
- 위 규칙은 다음 모든 선언에 적용 MUST 한다.
  - 매개변수 선언
  - 지역 변수 선언(`int ...;`, `int ... = E;`)
- 또한 다음 형태의 “리스트 내부 중복”도 MUST NOT 허용한다.
  - `int x, x;`
  - `int f(int a, int a) { ... }`

#### 결과
- 위 규칙을 위반하는 프로그램은 **컴파일 타임 오류(MUST)** 로 거부 MUST 한다.

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

#### Callable Callee
- 어떤 호출 표현식 `C( args )`에서, `C`(callee)는 **함수 이름을 나타내는 식**이어야 MUST 한다.  
- MiniC89에서 함수 이름을 나타내는 식은 다음으로 한정한다.

  - `C`가 (괄호를 제거한 뒤) 단일 식별자 `id`이며,
  - `id`가 **함수 정의를 가리키는 이름**일 것

- 위 조건을 만족하지 않는 호출은 컴파일 타임 오류(MUST)이며 **MC89-E409**로 진단 MUST 한다.
- `C`가 `(<expression>)` 형태인 경우, 바깥 괄호를 제거하고 다시 판정한다.
  - 즉 `(f)(1)`은 허용될 수 있으나, `(f())(1)`은 불가(첫 호출 결과는 int)

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
 * Function Definition (MiniC89) — aligned with C89 3.7.1 (restricted)
 * ------------------------------------------------------------ */
<function-definition>   ::= "int" <identifier>
                            "(" [ <parameter-list> ] ")"
                            <compound-statement> ;

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
- 모든 함수의 반환 타입은 `int`이어야 한다. **MUST**
- 모든 매개변수는 `"int" <identifier>` 형태여야 한다. **MUST**
  - 위반 시 진단 코드는 MC89-E406을 사용 MUST 한다.
- 함수 이름은 프로그램 내에서 **유일 MUST** 하다(중복 정의 금지).
- 프로그램은 엔트리 포인트로 `int main()` 함수를 **반드시(MUST) 포함**해야 한다.
  - `main`은 매개변수를 가지면 안 된다.
  - 위반 시 진단 코드는 MC89-E402를 사용 MUST 한다. (Invalid main Signature)
- MiniC89는 `implicit function declaration`을 허용하지 않는다.
  - 호출되는 모든 함수는 프로그램 내에 정의가 **존재 MUST** 한다.
- 함수 호출의 인자 개수(arity)는 정의의 매개변수 개수와 **정확히 일치 MUST** 한다. 
- 함수 호출 `f(a1, ..., an)`이 유효하려면, 호출 위치보다 앞쪽(소스 코드 상에서 earlier in the translation unit)에
  `f`의 함수 정의가 존재 MUST 한다.
  (단, 현재 정의 중인 함수 자신의 본문에서의 `f(...)` 호출은 허용된다.)
- 프로토타입/전방 선언이 금지되어 있으므로, 정의가 뒤에 오는 함수에 대한 호출(forward call)은
  허용되지 않는다(MUST NOT).
  - 파일 스코프에서 `int f(int a);` 같은 프로토타입이 등장하면 MC89-E404 오류를 발생시킨다 (MUST)
- 위 규칙을 만족하지 않는 함수 호출은 컴파일 타임 오류로 진단 MUST 하며,
  오류 코드는 MC89-E407을 사용 MUST 한다.
- ISO C89의 K&R(old-style) 함수 정의는 MiniC89 문법에 존재하지 않으며 MUST NOT 허용한다.
  - 예: `int f(a) int a; { ... }` 는 MiniC89에서 문법 오류/매개변수 오류로 거부되어야 한다.
- 함수 정의가 중복되면 컴파일 타임 오류로 진단한다 (MUST)
  오류 코드는 MC89-E403을 쓴다.
- 반환 타입이 `int`인 함수에서, 제어 흐름(control flow)이 함수 본문의 닫는 중괄호 `}`에 도달하는 것은
  **허용되지 않는다(MUST NOT)**.
- 즉, 함수는 어떤 실행 경로에서든 **`return <expression>;`을 실행하거나**,
  또는 **정상 완료(normal completion) 없이 끝나지 않아야 한다**.
- 구현체는 “함수 끝 도달 가능”을 컴파일 타임에 검출 MUST 하며,
  해당 함수는 프로그램을 거부(reject) MUST 한다.
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

### Forward call not allowed: MC89-E407)
```c
int main() {
    return add(1, 2);    /* ERROR: MC89-E407 (add not defined yet) */
}

int add(int a, int b) {
    return a + b;
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
- 본 표준에서 PC는 문장 단위의 개념적 위치이며, 구현체의 내부 실행 단위는 비규범이다(10.7 참조).

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

### 10.7 Observability and Visualization (Non-Normative)

본 절은 교육 목적의 시각화/디버깅 기능을 위한 가이드이다.
본 절의 내용은 언어 의미(semantics)를 정의하지 않으며,
구현체가 제공하지 않아도 표준 적합성에 영향을 주지 않는다.

#### 10.7.1 Statement-level PC (Conceptual) vs Implementation-level Step (Non-Normative)

- 본 표준에서 Program Counter(PC)는 “현재 실행 중인 문장(statement)”을 가리키는
  개념적(추상적) 위치로 설명된다. (statement-level)
- 구현체(컴파일러/VM/인터프리터)는 내부적으로 바이트코드, IR, AST 워크리스트 등
  임의의 실행 단위를 사용할 수 있다. (implementation-level)
- 구현체가 내부 실행 단위를 사용하는 경우라도,
  사용자에게 표시되는 “현재 실행 위치”는 다음 중 하나로 매핑하여 제공할 수 있다.
  - 소스 코드의 문장(statement) 단위
  - 소스 코드의 토큰/표현식 하위 단계(선택)
  단, 이는 시각화 편의를 위한 것이며 언어 의미를 변경하지 않는다.

#### 10.7.2 Observable State Checklist (Non-Normative)

구현체는 다음 상태를 시각적으로 표시하거나 로그로 출력할 수 있다(MAY).
(아래 항목은 권장 체크리스트이며, 제공하지 않아도 표준 적합성에 영향을 주지 않는다.)

A. Control / Location
- [ ] 현재 함수 이름
- [ ] 현재 문장(statement) 위치 (예: line:col 또는 statement id)
- [ ] 호출 스택(call stack) 깊이
- [ ] 반환 지점(호출자에서의 return continuation 위치)

B. Call Stack / Frames
- [ ] 각 스택 프레임의 함수 이름
- [ ] 각 스택 프레임의 매개변수(parameter) 값
- [ ] 각 스택 프레임의 지역 변수(local) 값
- [ ] 현재 프레임(current frame) 강조 표시

C. Variables / Storage
- [ ] 변수 이름 -> 현재 값
- [ ] (선택) 변수의 “초기화 상태(initialized / uninitialized)” 표시
  - 단, 본 표준은 미초기화 읽기를 정적 오류(MC89-E202)로 금지하므로,
    정상 실행 중 “uninitialized 값을 읽는 상황”은 발생하지 않는다.

D. Execution Events (Optional)
- [ ] 함수 호출 이벤트(call)
- [ ] 함수 반환 이벤트(return) 및 반환값
- [ ] 분기 선택(if true/false)
- [ ] 루프 반복 횟수(for iteration count)
- [ ] break/continue 발생 지점

#### 10.7.3 Suggested Presentation Rules (Non-Normative)

- 표현식 내부의 평가 순서는 표준에서 대부분 “지정되지 않음”이므로,
  구현체가 특정 순서를 화면에 보여주더라도
  그것이 언어 의미의 일부인 것처럼 오해되지 않도록 SHOULD 표시한다.
  예:
  - “Visualization order: left-to-right (implementation choice)”
- 바이트코드/IR 단계 단위로 스텝 실행을 제공하는 경우,
  소스 문장(statement)과의 매핑을 함께 제공하면 교육 효과가 높다.

---

## 11. Diagnostics
- Undefined Behavior(UB)와 Diagnostics의 관계(어떤 UB를 MUST error로 금지하는지,
  어떤 UB는 검출 가능 시 진단 MAY 인지)는 5.4절을 따른다.
### 11.2 Diagnostic Message Format (Normative)

본 절은 MiniC89 구현체가 출력하는 진단(diagnostic)의 “기계 판독 가능한” 최소 포맷을 정의한다.
온라인 저지, IDE, LSP, 채점기는 본 포맷을 전제로 진단을 수집/표시할 수 있다.

#### 11.2.1 One-line Format (Normative)

Normative Rules
- 구현체는 각 진단을 정확히 1줄(one line)로 출력 MUST 한다.
- 각 진단 줄은 다음 형식을 정확히 따라야 한다.
```
  <severity> <code>: <message> (<line>:<col>)
```
- `<severity>`는 반드시 다음 중 하나이며, 소문자 MUST 한다.
  - error
  - warning

- `<code>`는 반드시 다음 형식 MUST 한다.
  - `MC89-E<ddd>`   (ddd는 3자리 10진수)

- `<message>`는 사람이 읽을 수 있는 설명 문자열이며, 다음을 만족 MUST 한다.
  - 개행 문자를 포함하지 않는다.
  - 구현체는 본 표준 각 오류 항목의 “Required Message”에서 제시한 문구를
    최소한 접두(prefix)로 포함 MUST 한다.
  - 구현체는 식별자 이름 등 추가 정보를 포함 MAY 한다.

- `(<line>:<col>)`은 소스 위치(location)이며, 다음을 만족 MUST 한다.
  - line과 col은 10진 정수
  - line과 col은 1-base(첫 줄=1, 첫 열=1)
  - 진단이 특정 토큰/구문에 귀속되는 경우, 그 “첫 문자 위치”를 사용 MUST 한다.
  - 진단이 소스의 단일 위치에 귀속되기 어려운 경우(예: missing main),
    (0:0)을 출력 MUST 한다.

- 각 진단 줄의 끝에는 LF('\n')로 줄바꿈 SHOULD 한다.
  (플랫폼에 따라 CRLF를 사용해도 무방하나, 채점기/IDE 호환을 위해 LF 권장)

#### 11.2.2 Location Counting Rules (Normative)

- line은 파일 시작부터 LF 기준 줄 수를 의미한다. (첫 줄 = 1)
- col은 해당 줄의 첫 문자부터의 문자 수를 의미한다. (첫 열 = 1)
- Tab(HT)은 1개의 문자로 col을 1 증가시키는 것으로 계산 MUST 한다.
  (탭 폭에 따른 “화면상 열” 계산은 금지)

#### 11.2.3 Examples (Non-Normative)

(1) 소스 위치가 있는 오류
  error MC89-E407: call to undefined function 'foo' (3:12)

(2) 경고 예시
  warning MC89-E307: unreachable statement (10:5)

(3) 소스 위치가 애매한 전역 오류
  error MC89-E401: missing required entry function 'int main()' (0:0)

#### 11.2.4 Interaction with “Required Message” Fields (Normative)

- 본 표준 각 오류 정의의 “Required Message”는
  위 포맷 중 `<severity> <code>: <message>` 부분의 최소 요구사항을 의미한다.
- 구현체는 모든 진단 출력에서, 해당 “Required Message”를 포함한 뒤,
  공백 1개를 두고 위치 정보 `(<line>:<col>)`를 반드시 덧붙여야 한다(MUST).

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

#### MC89-E105 — Line Comment Not Allowed
Condition (MUST detect)
- 입력 소스에서 `"//"` 토큰 시퀀스가 등장한 경우.

Required Message
```text
error MC89-E105: line comments ('//') are not allowed
```

Location
- 위치는 `//`의 첫 번째 `/` 문자의 (line:col)을 사용한다. MUST

Example
```c
int main() { return 0; } // hello
/*                   ^ MC89-E105 here */
```
#### MC89-E106 — Preprocessor Directive Not Allowed
**Condition (MUST detect)**
- 소스 코드에서 `'#'` 문자가 주석 밖에서 등장한 경우.

**Required Message**
```text
error MC89-E106: preprocessor directives are not allowed
```

**Location (Normative)**
- 위치는 해당 `#`의 첫 문자 위치 `(line:col)` ㅡㅕㄴㅆ

**Example**
```c
#include <stdio.h>   /* ERROR: MC89-E106 */
int main() { return 0; }
```

#### MC89-E107 — String Literal Not Allowed
**Condition (MUST detect)**
- 소스 코드에서 `"` 로 시작하는 문자열 리터럴이 등장한 경우

**Required Message**
```text
error MC89-E107: string literals are not allowed
```

**Example**
```c
int main() {
    return "hello";   /* MC89-E107 */
}
```

#### MC89-E108 — Character Constant Not Allowed
**Condition (MUST detect)**
- 소스 코드에서 `'a'`, `'\n'` 등 문자 상수가 등장한 경우

**Required Message**
```text
error MC89-E108: character constants are not allowed
```

**Example**
```c
int main() {
    return 'a';   /* MC89-E108 */
}
```

#### MC89-E109 — Floating Constant Not Allowed
**Condition (MUST detect)**
- 실수 상수 형태가 등장한 경우 (`1.0`, `0.5`, `.3`, `1e3`, `2E-1` 등)

**Required Message**
```text
error MC89-E109: floating-point constants are not allowed
```

**Example**
```c
int main() {
    return 1.5;   /* MC89-E109 */
}
```

#### MC89-E110 — Forbidden Keyword
**Condition (MUST detect)**
- 소스 코드에서 키워드 토큰이 등장하였으나,
  해당 키워드가 MiniC89에서 허용된 키워드 집합에 포함되지 않은 경우.
- 제어/분기/점프 키워드:  
  `while`, `do`, `switch`, `case`, `default`, `goto`
- 사용자 정의 타입 키워드:  
  `struct`, `union`, `enum`, `typedef`
- 기타 MiniC89에서 제거된 키워드:  
  `sizeof`
  
**Required Message**
```text
error MC89-E110: forbidden keyword '<keyword>'
```

**Location**
- 문제의 키워드 토큰의 첫 문자 위치를 사용한다.

**Example**
```c
int main() {
  while (1) { }   /* ERROR: MC89-E110 (forbidden keyword 'while') */
  return 0;
}
```

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
**Condition (MUST detect)**
- 지역 변수(매개변수 제외)가 초기화되기 전에 그 값을 읽는 경우.
- 구현체는 “definitely initialized” 분석을 수행 MUST 하며,
  모든 실행 경로에서 해당 읽기 지점 이전에 초기화가 보장되지 않으면
  MC89-E202로 오류를 보고 MUST 한다.

**초기화 규칙 (Normative)**
- 매개변수는 함수 진입 시 초기화된 것으로 간주한다.
- `int x;`는 초기화되지 않은 변수 x를 생성한다.
- `int x = E;`는 E의 평가가 성공적으로 끝난 후 x가 초기화된 것으로 간주한다.
- `x = E;`는 E의 평가가 성공적으로 끝난 후 x가 초기화된 것으로 간주한다.

**용어 정의 (Normative)**

- **Initialized set (DI)**  
  어떤 프로그램 지점에서 “반드시 초기화(definitely initialized)된 변수들의 집합”을 DI라 한다.

- **Read of variable v**  
  표현식에서 식별자 `v`가 **값으로 사용**되는 모든 경우를 말한다.  
  단, 대입식 `v = RHS`에서 좌변 `v`의 출현은 read로 간주 MUST NOT 한다.  
  (읽기는 RHS 내부의 `v` 출현만 해당)

- **Write of variable v**  
  대입식 `v = RHS`가 평가되어 저장이 수행되는 것을 write로 간주한다.

- **Reachable path (E202 목적의 “경로”)**  
  E202는 “표현식 값의 상호관계(예: `a==0`과 `a!=0`의 상보성)” 같은 정교한 추론을 요구하지 않는다.  
  따라서 아래 규칙에 따라 구성되는 CFG(control-flow graph)에서,  
  **CTCE로 명백히 배제되지 않는 모든 분기/반복 경로를 ‘가능한 경로’로 간주 MUST 한다.**

> 요약: E202는 “실행 가능 경로(feasible path) 정밀 판정”이 아니라,  
> “CTCE 상수만 반영한 보수적 CFG 경로” 기준으로 definite init을 정의한다.

**Required Message**
- 다음 형식을 포함 MUST 한다.
  - error MC89-E202: read of uninitialized variable '<name>'

**A. 분석 입력/출력 (Normative)**

구현체는 각 함수에 대해 다음 분석을 수행 MUST 한다.

- 입력:
  - 함수의 AST/CFG
  - 심볼 테이블(스코프에 있는 변수/매개변수)
- 출력:
  - 각 “읽기 지점(read site)”에서의 DI
  - DI에 포함되지 않은 변수 읽기 발견 시 **MC89-E202** MUST 진단

---

**B. CFG 기반 최소 알고리즘 (Normative)**

**B.1 초기 DI (Normative)**
- 함수 진입 시:
  - **모든 매개변수는 initialized로 간주**하므로 DI에 포함 MUST 한다.
  - 지역 변수는 선언되더라도, initializer가 없으면 DI에 포함 MUST NOT 한다.

**B.2 Join(합류) 규칙 (Normative)**
- CFG에서 여러 전이(edge)가 한 지점으로 합류할 때,
  해당 지점의 DI는 **모든 선행 경로에서 공통으로 initialized인 변수만 유지**해야 하므로,
  **교집합(intersection)** 을 meet 연산자로 사용 MUST 한다.

즉,
- `DI_in(node) = ⋂ DI_out(pred)`  (단, pred→node edge가 “reachable”일 때만 포함)

**B.3 Reachability 최소 규칙 (Normative)**
- 구현체는 CTCE를 이용해 다음 “분기/루프의 상수 판정”을 수행 MUST 한다.
  - `if (CTCE)`에서 CTCE 값이 0이면 then-branch edge는 unreachable
  - `if (CTCE)`에서 CTCE 값이 0이 아니면 else-branch edge는 unreachable
  - `for(...; CTCE; ...)`에서도 동일 (조건이 0이면 body 진입 edge unreachable)
- 위 경우를 제외하고, **비-CTCE 조건은 true/false 모두 가능하다고 간주 MUST 한다.**
  - (즉, 추가적인 상수 전파/관계 추론으로 분기를 제거하는 것은 “표준 요구”가 아니다)

> 이 규칙은 “보수적(거짓 양성 가능)”을 **표준이 의도적으로 선택**하는 부분이다.
> (동일 프로그램이 구현체마다 다르게 통과하는 것을 막기 위해)

---

**C. 문장(Statement) 전이 규칙 (Normative)**

아래 규칙은 “정상 완료(normal completion)” 기준의 DI 전이를 정의한다.

**C.1 선언 (Declarations)**
- `int x;`
  - `x`는 scope에 추가되지만 **DI에는 추가되지 않는다.**
- `int x = E;`
  - `E`를 평가하는 과정에서의 read는 DI 기준으로 검증 MUST
  - `E` 평가가 정상 종료한 뒤 `x`를 DI에 추가 MUST
- 하나의 선언문 `int d1, d2, ...;`에 여러 initializer가 있는 경우:
  - init-declarator를 **소스 순서대로(left-to-right)** 처리 MUST
  - 각 initializer `Ei`는 독립된 full-expression로 취급하며,
    `di`는 `Ei` 평가 후 initialized로 간주 MUST

**C.2 표현식 문장 / return**
- `E;`, `return E;`
  - `E` 내부의 모든 read는 해당 지점의 DI 기준으로 검증 MUST
  - `E` 평가 중 발생하는 write(대입)는, `E`가 정상 완료하면 DI에 반영 MUST

**C.3 if / if-else**
`if (E) S1 else S2` 에 대해:

- 조건식 분석 결과로 `(DI_true(E), DI_false(E))`를 계산 MUST
- then-branch 진입 DI = `DI_true(E)`
- else-branch 진입 DI = `DI_false(E)`
- if 문 정상 완료 후 DI = `DI_out(S1) ∩ DI_out(S2)` (도달 가능한 경로만)

`if (E) S1` (else 없음) 은 else-branch를 “empty statement”로 간주하여:
- else 쪽 DI_out은 `DI_false(E)` 그대로로 처리한다.

**C.4 for (반복문)**
`for (init; cond; step) body` 는 다음 순서의 CFG를 구성 MUST 한다.

1) `init` (비어있지 않으면 1회 평가)
2) `cond` (비어있으면 항상 참으로 간주)
3) `body`
4) `step` (비어있지 않으면 평가)
5) 다시 `cond`

**루프의 DI는 고정점(fixpoint)으로 계산 MUST**
- `DI_header` = cond 평가 직전의 DI (루프 헤더)
- 초기값: `DI_header₀ = DI_after(init)`
- 반복 갱신(개념적 정의):
  - `cond`를 `DI_header_k`로 분석하여 `DI_true/DI_false`
  - `body` 진입 DI = `DI_true(cond)`
  - `step` 진입 DI는:
    - body 정상 완료 경로 + continue 경로가 합류한 결과(교집합)
  - `DI_header_{k+1} = DI_after(init) ∩ DI_after(step)`  
    (첫 iteration은 init에서, 이후 iteration은 step에서 header로 오므로 교집합)

- 수렴할 때까지 반복하며, 최종 `DI_header*`를 사용 MUST 한다.

**break/continue 처리 (Normative)**
- `continue`는 “현재 루프의 step으로 이동”하는 edge를 생성 MUST
- `break`는 “루프 밖(루프 이후 문장)으로 이동”하는 edge를 생성 MUST
- 루프 이후 DI(`DI_after_loop`)는 다음 모든 exit 경로의 교집합 MUST:
  - `cond`가 false가 되어 종료되는 경로의 DI(`DI_false(cond)` at `DI_header*`)
  - `break`로 종료되는 모든 경로의 DI(각 break 지점의 DI_out을 교집합)

---

**D. 표현식(Expression) 분석 최소 규칙 (Normative)**

E202는 표현식 내부에서도 read를 검증해야 하므로,
표현식 분석은 다음 최소 의미를 만족 MUST 한다.

**D.1 기본 규칙**
- 정수 리터럴: DI 변화 없음
- 식별자 `v`:
  - `v ∈ DI`가 아니면 **MC89-E202 MUST**
- 단항 연산: 피연산자를 동일 DI로 분석
- 비교/산술 등 **비-단락 이항 연산자**(`+ - * / % < <= > >= == !=`):
  - 피연산자 평가 순서는 미지정이므로,  
    **각 피연산자는 동일한 DI_in으로 독립 분석 MUST** (서로의 write를 가정해서는 안 됨)
  - 단, 연산 전체가 정상 완료하면, 양쪽 피연산자에서 발생한 write는 모두 반영되어
    DI_out에 포함 MAY (일반적으로 union)

**D.2 대입식 `v = RHS`**
- RHS를 먼저 분석 MUST (RHS 내부 read는 현재 DI 기준)
- RHS가 정상 완료하면 `v`를 initialized로 만들어 DI_out에 포함 MUST

**D.3 `&&` / `||` (단락 평가 반영이 E202에서도 필수)**
E202는 `&&`/`||`의 단락 평가로 인해 “어느 경로에서 RHS가 평가되는지”가 달라지므로,
조건식 분석은 최소로 `(DI_true, DI_false)`를 반환 MUST 한다.

`A && B`
- `A`를 분석하여 `(DI_A_true, DI_A_false)`를 얻는다.
- `B`는 `A`가 true일 때만 평가되므로:
  - `B`는 `DI_A_true`를 입력으로 분석한다.
- 결과:
  - `DI_true(A&&B)  = DI_true(B)`  (A true & B true 경로)
  - `DI_false(A&&B) = DI_A_false ∩ DI_false(B)`  
    (A false 경로 + (A true & B false) 경로의 교집합)
- `A`가 CTCE이고 값이 0이면 `B`는 “평가되지 않음”으로 간주 MUST  
  (따라서 `B` 내부 read/write는 E202 판정에 포함 MUST NOT)

`A || B`
- `A`를 분석하여 `(DI_A_true, DI_A_false)`를 얻는다.
- `B`는 `A`가 false일 때만 평가되므로:
  - `B`는 `DI_A_false`를 입력으로 분석한다.
- 결과:
  - `DI_false(A||B) = DI_false(B)` (A false & B false 경로)
  - `DI_true(A||B)  = DI_A_true ∩ DI_true(B)`  
    (A true 경로 + (A false & B true) 경로의 교집합)
- `A`가 CTCE이고 값이 0이 아니면 `B`는 “평가되지 않음”으로 간주 MUST

**D.4 함수 호출 `f(a1, ..., an)`**
- 인자 평가 순서는 미지정이므로,
  **각 인자 `ai`는 동일 DI_in으로 독립 분석 MUST** (인자 간 write 전파 금지)
- 호출 전체가 정상 완료하면, 각 인자에서 발생한 write는 모두 반영되어 DI_out에 포함 MAY

---

**E. 보수성(거짓 양성) 정책을 표준으로 고정 (Normative)**

**E.1 보수성 원칙 (Normative)**
- **CTCE로 판별되는 상수 조건**만 도달 불가능(unreachable)로 취급 MUST 한다.
- 그 외 조건(식별자 포함/함수 호출 포함/대입 포함 등)은
  true/false 모두 가능하다고 간주 MUST 한다.
- 따라서 E202는 일부 “실제로는 항상 초기화되는” 프로그램도
  위 보수적 CFG 기준에서 초기화가 증명되지 않으면 오류가 될 수 있다.
  - 이는 표준이 의도한 제약이며, 구현체 간 판정 불일치를 방지하기 위한 것이다.

> Note (Non-Normative):  
> 예를 들어, `if (a==0) x=1; if (a!=0) x=1;` 같은 코드는 실제로 x가 항상 초기화되지만,  
> 상보성(조건 관계) 추론을 요구하지 않으므로 MiniC89에서는 E202가 날 수 있다(보수적 규칙).

---
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
- MiniC89 문법에 존재하지 않는 금지 키워드 기반 구문(예: while/switch/struct/sizeof 등)도 포함한다.

Required Message
- 다음 형식을 포함 MUST 한다.
  - error MC89-E203: invalid operator or disallowed operator

Example
```c
int main() {
    int x;
    x++;         /* MC89-E203 */
    return x;
}
````

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
**Definition (Normative) — Full-expression**
MiniC89에서 “full-expression”은 다음 위치에 나타나는 `<expression>`을 의미 MUST 한다.

1. **Expression statement**: `E;` 에서의 `E`
2. **Return**: `return E;` 에서의 `E`
3. **Initializer**: `int x = E;` 에서의 `E`
   - `int a = E1, b = E2;` 인 경우 `E1`과 `E2`는 각각 별도의 full-expression로 간주 MUST 한다.
4. **if / if-else**: `if (E) ...` 에서의 `E`
5. **for**: `for (init; cond; step)` 에서 `init`, `cond`, `step` 각각(비어 있지 않은 경우)
위 목록에 포함되지 않는 하위식(subexpression)은 full-expression이 아니다.
(예: 함수 호출 인자 `f(a1, a2)`의 각 `ai`는 full-expression이 아님)

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

**Normative Rule — Sequencing Boundaries for E208**

MiniC89에서 MC89-E208 판정을 위해, 다음은 “sequencing 경계(= sequence point 역할)”로 간주 MUST 한다.

A) **full-expression의 끝** (예: `;` 또는 `return E;`의 종료)  
B) 논리 연산자 `&&`, `||`는 **좌측 피연산자의 평가가 완료된 뒤** 우측 피연산자를 평가하며,
   이 시점은 E208 판정에서 sequencing 경계로 간주 MUST 한다.

MiniC89에서 `?:` 및 콤마 연산자(`,` operator)는 금지이므로,
위 A/B가 E208 판정에 필요한 sequencing 경계의 전부이다.

핵심 효과:  
- 대부분의 이항 연산자(`+`, `*`, `<` 등)는 피연산자 평가 순서가 미지정 → **같은 경계 내부**  
- `&&`/`||`는 좌→우 순서가 정의됨 → 좌/우가 **서로 다른 경계(세그먼트)** 로 분리됨

**Normative Rule — E208 is checked “between sequencing boundaries”**

MC89-E208은 “하나의 full-expression 전체”가 아니라,
**full-expression 안에서 “sequencing 경계 사이(between boundaries)”로 나뉘는 각 구간(세그먼트)** 에 대해 적용 MUST 한다.

- **write(v)**: 형태가 정확히 `v = RHS`인 대입식에서 `v`에 대한 저장(쓰기)
  - (주의) `v`가 LHS로 등장하는 것은 “read”가 아니다.
- **read(v)**: 표현식에서 `v`가 값으로 사용되는 모든 경우
  - 예: `v`, `v + 1`, `f(v)`, `v < 3` 등
- **RHS 내부**: 대입식 `v = RHS`에서 `RHS`의 모든 하위식(subexpression)

**Normative Rule — Not Potentially Evaluated Subexpressions**

`A && B`에서, `A`가 CTCE이고 그 값이 `0`으로 평가되면, `B`는 **평가되지 않는다**.  
`A || B`에서, `A`가 CTCE이고 그 값이 `0`이 아니면, `B`는 **평가되지 않는다**.

위 경우 `B`는 “not potentially evaluated”로 간주하며,
구현체는 **MC89-E208 판정에서 `B` 내부의 read/write를 고려 MUST NOT** 한다.

(선택) 구현체는 CTCE 외의 추가 분석(상수 전파 등)으로 더 많은 “not evaluated” 케이스를
인식 MAY 하나, 위 CTCE 기반 최소 규칙은 반드시 지원 MUST 한다.

주의:
- 이 “무시” 정책은 **E208 판정에만** 적용된다.  
  (예: `B` 안의 MC89-E201/203 같은 다른 정적 오류까지 자동으로 면제한다고 규정하지 말 것)

#### Examples
(1) 쓰기 2회
```c
int main() {
    int x;
    x = (x = 1);      /* MC89-E208 */
    return 0;
}
```
(2) 쓰기 + RHS 밖 읽기
```c
int f(int x) { return x; }

int main() {
    int i;
    i = 0;
    return f(i) + (i = 1);   /* MC89-E208 */
}
```
(3) RHS 내부가 아닌 곳에서 읽기/쓰기 혼합
```c
int main() {
    int u;
    int v;
    u = 0;
    v = (u = 1) + u;         /* MC89-E208 (u가 RHS 밖에서 다시 읽힘) */
    return v;
}
```
(4) `&&`/`||` 경계로 인해 허용되는 케이스
```c
int main() {
  int i;
  i = 0;
  (i = 1) && (i = 2);   /* OK: &&는 좌→우 순서 + sequencing 경계 */
  return i;             /* 2 */
}
```
```c
int main() {
  int i;
  i = 0;
  (i = 1) && i;         /* OK: 좌측 write 이후 우측 read는 sequenced */
  return i;             /* 1 */
}
```
(5) CTCE 단락으로 인해 E208 판정에서 제외되는 케이스
```c
int main() {
  int i;
  i = 0;
  0 && (i = (i = 1));   /* RHS는 not potentially evaluated → E208 판정에서 제외 */
  return i;             /* 0 */
}
```


#### MC89-E209 — Duplicate Declaration
**Condition (MUST detect)**
- 어떤 매개변수/지역 변수 선언이 식별자 `<name>`을 도입할 때,
  다음 중 하나라도 만족하면 MC89-E209이다.
  1) 현재 스코프에 `<name>`이 이미 선언되어 있음 (duplicate in same scope)  
  2) 같은 선언 리스트(`<parameter-list>` / `<init-declarator-list>`) 안에서 `<name>`이 2회 이상 등장함

**Required Message**
```text
error MC89-E209: duplicate declaration of identifier '<name>'
```


#### MC89-E210 — Invalid Type Keyword
**Condition (MUST detect)**
- `int`가 아닌 다른 타입 키워드가 등장한 경우
- `char`, `float`, `double`, `short`, `long`, `unsigned`, `signed`, `void`

**Required Message**
```text
error MC89-E210: invalid type keyword (only 'int' is allowed)
```

**Location**
- 문제의 타입 키워드 토큰의 시작 위치 (line:col)

**Example**
```c
int main() {
    char c;          /* ERROR: MC89-E210 */
    return 0;
}
```


#### MC89-E211 — User-defined Types Not Allowed
**Condition (MUST detect)**
- 다음 키워드가 등장한 경우: 
  `struct`, `union`, `enum`, `typedef`

**Required Message**
```text
error MC89-E211: user-defined types are not allowed
```

**Location**
- 문제의 키워드 토큰의 시작 위치 (line:col)

**Example**
```c
struct S { int x; };    /* ERROR: MC89-E211 */
int main() { return 0; }
```

#### MC89-E212 — Pointers and Arrays Not Allowed

**Condition (MUST detect)**
다음 중 하나라도 만족하면 MC89-E212이다.

1) **포인터 선언자**
- 선언문에서 선언자 부분에 `*`가 등장한 경우  
  예: `int *p;`, `int **pp;`, `int *p = 0;`

2) **주소 연산자**
- 표현식에서 단항 연산자 `&`가 등장한 경우  
  예: `&x`

3) **배열 구문**
- 소스 코드에서 `[` 또는 `]`가 등장하여 배열 선언 또는 첨자 표현식을 구성하는 경우  
  예: `int a[10];`, `a[i]`

**Required Message**
```text
error MC89-E212: pointers and arrays are not allowed
```

**Location**
- 금지된 기호의 첫 문자 위치를 사용한다.

**Examples**
```c
int main() {
  int *p;        /* ERROR: MC89-E212 */
  return 0;
}
```
```c
int main() {
  int a[10];     /* ERROR: MC89-E212 */
  return 0;
}
```
#### MC89-E213 — Increment/Decrement Operators Not Allowed

**Condition (MUST detect)**
- 소스 코드에서 다음 연산자 중 하나가 등장한 경우:
  - `++`
  - `--`
- 해당 연산자가 전위(prefix) 또는 후위(postfix) 형태인지와 무관하다.
  - 예: `++x`, `x++`, `--x`, `x--` 모두 포함

**Required Message**
```text
error MC89-E213: increment and decrement operators are not allowed
```

**Location**
- 해당 연산자 토큰의 첫 문자 위치를 사용한다.

**Examples**
```c
int main() {
  int x;
  x = 0;
  x++;        /* ERROR: MC89-E213 */
  return x;
}
```

#### MC89-E214 — sizeof Operator Not Allowed

**Condition (MUST detect)**
- 소스 코드에서 키워드 `sizeof`가 연산자로 사용된 경우.
- 다음 모든 형태를 포함 MUST 한다.
  - `sizeof x`
  - `sizeof(x)`
  - `sizeof(type-name)` (MiniC89에는 type-name 자체가 거의 없지만, 형태상 포함)

**Required Message**
```text
error MC89-E214: sizeof operator is not allowed
```

**Location**
- 해당 `sizeof` 키워드 토큰의 첫 문자 위치를 사용한다.

**Examples**
```c
int main() {
  int x;
  return sizeof(x);   /* ERROR: MC89-E214 */
}
```

#### MC89-E215 — Conditional Operator Not Allowed

**Condition (MUST detect)**
- 소스 코드에서 조건(삼항) 연산자 형태가 등장한 경우:
  - `E1 ? E2 : E3`
- `?` 또는 `:`가 단독으로 등장하여
  조건 연산자 구문을 구성하려는 모든 시도를 포함 MUST 한다.
  
**Required Message**
```text
error MC89-E215: conditional operator '?:' is not allowed
```

**Location**
- 해당 `?` 키워드 토큰의 첫 문자 위치를 사용한다.

**Examples**
```c
int main() {
  int x;
  x = 1;
  return x ? 10 : 20;   /* ERROR: MC89-E215 */
}
```

#### MC89-E216 — Bitwise Operators Not Allowed

**Condition (MUST detect)**
- 소스 코드에서 다음 비트 연산자 중 하나가 등장한 경우:
  - `&`   (bitwise AND)
  - `|`   (bitwise OR)
  - `^`   (bitwise XOR)
  - `~`   (bitwise NOT)
  - `<<`  (left shift)
  - `>>`  (right shift)

다음 모든 형태를 포함 MUST 한다.
- 이항 연산자 형태: `a & b`, `a | b`, `a ^ b`, `a << b`, `a >> b`
- 단항 연산자 형태: `~a`
  
**Required Message**
```text
error MC89-E216: bitwise operators are not allowed
```

**Location**
- 해당 비트 연산자 토큰의 첫 문자 위치를 사용한다.

**Examples**
```c
int main() {
  int a;
  int b;
  a = 3;
  b = 5;
  return a & b;    /* ERROR: MC89-E216 */
}
```

#### MC89-E217 — Comma Operator Not Allowed

**Condition (MUST detect)**
- 소스 코드에서 다음 형태의 콤마 연산자가 등장한 경우:
  - `E1, E2`
- 단, 다음 경우는 제외 MUST 한다.
  - 함수 호출에서 인자 구분자로 사용되는 `,`
    - 예: `f(a, b, c)`
  - 선언문에서 init-declarator-list를 구분하는 `,`
    - 예: `int a, b;`
  
**Required Message**
```text
error MC89-E217: comma operator is not allowed
```

**Location**
- 해당 콤마 연산자 토큰의 첫 문자 위치를 사용한다.

**Examples**
```c
int main() {
  int a;
  int b;
  a = 1;
  b = 2;
  return (a = 3, b);   /* ERROR: MC89-E217 */
}
```

```c
int f(int a, int b) {
  return a + b;        /* OK */
}

int main() {
  int x;
  int y;
  x = 1;
  y = 2;
  return f(x, y);      /* OK: argument separator */
}
```

```c
int main() {
  int a;
  int b;
  int c;
  a = 1;
  b = 2;
  c = 3;
  /* declaration comma */
  int x, y;            /* OK */
  return a;
}
```

---
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
> 구현 단순성을 위해 생략 가능하다.


### MC89-E308 -- while Statement Not Allowed
#### Condition
- 소스 코드에서 `while` 키워드가
  반복문(statement)을 구성하려는 형태로 등장한 경우.
  - 예: `while (E) S`

#### Required Message
```text
error MC89-E308: 'while' statement is not allowed
```

#### Location
- `while` 키워드의 첫 문자 위치를 사용한다.


### MC89-E309 — do-while Statement Not Allowed
#### Condition
- 소스 코드에서 `do S while (E);` 형태의 반복문이 등장한 경우.

#### Required Message
```text
error MC89-E309: 'do-while' statement is not allowed
```

#### Location
- `do` 키워드의 첫 문자 위치를 사용한다.


### MC89-E310 — switch Statement Not Allowed
#### Condition
- 소스 코드에서 `switch (E) S` 형태의 분기문이 등장한 경우.

#### Required Message
```text
error MC89-E310: 'switch' statement is not allowed
```

#### Location
- `switch` 키워드의 첫 문자 위치를 사용한다.


### MC89-E311 — goto Statement Not Allowed
#### Condition
- 소스 코드에서 `goto` 키워드가 점프 문장을 구성하려는 형태로 등장한 경우.

#### Required Message
```text
error MC89-E311: 'goto' statement is not allowed
```

#### Location
- `switch` 키워드의 첫 문자 위치를 사용한다.




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
   - `int <identifier> "(" [<parameter-list>] ")" ";"`
#### Message
```
error MC89-E404: function prototypes are not allowed in MiniC89
```
#### Example
```c
int f(int a);      /* ERROR: MC89-E404 */
int main() { return 0; }
```

### MC89-E405 -- Global Declaration Not Allowed
#### Condition (MUST detect)
- 파일 스코프에 전역 변수/선언이 등장
- 최소한 다음 형태는 E405로 진단 (MUST)
  - `int <identifier> ";"`
  - `int <identifier> "=" <expression> ";"`
  - `int <identifier> { "," <identifier> } ";"`
#### Message
```
error MC89-E405: global declarations are not allowed (only function definitions permitted)
```
#### Example
```c
int g = 1;         /* ERROR: MC89-E405 */
int main() { return 0; }
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
- 함수 호출 형태 `f(a1, ..., an)`이 등장했을 때,
  다음 중 어느 것도 만족하지 않으면 MC89-E407이다.
  (1) 호출 지점보다 앞쪽(소스 코드 상 earlier in the translation unit)에 `f`의 함수 정의가 존재함
  (2) 현재 정의 중인 함수가 `f`이며, 그 본문 내부에서의 재귀 호출임

즉, 정의가 뒤에 등장하는 forward call도 MC89-E407으로 진단 MUST 한다.
#### Message
```
error MC89-E407: call to undefined function '<name>'
```
#### Example
```c
int main() {
    return add(1, 2);   /* MC89-E407 (add defined later) */
}

int add(int a, int b) {
    return a + b;
}
```

### MC89-E408 -- Argument Count Mismatch
#### Condition (MUST detect)
- 호출 인자 개수 ≠ 함수 정의의 매개변수 개수
#### Message
```
error MC89-E408: argument count mismatch in call to '<name>'
```

### MC89-E409 — Call Target Is Not a Function
#### Condition (MUST detect)
- 호출 형태 `C( ... )`가 파싱되었을 때,
  - `C`가 (괄호 제거 후) 단일 식별자 `id`가 아니거나, 또는
  - `id`가 현재 스코프에서 **변수/매개변수로 해석되거나**, 또는
  - `id`가 함수가 아닌 값(예: 정수 리터럴/산술식/함수 호출 결과 등)으로 해석되는 경우

#### 우선순위
- `id(…)`에서 `id`가 현재 스코프의 **변수/매개변수**로 해석되면 → **E409**
- `id`가 변수로도 해석되지 않고 “함수 후보”일 때, 정의가 없으면 → **E407**
- 함수로 해석되지만 인자 개수가 다르면 → **E408**

**Required Message**
```
error MC89-E409: call target is not a function
```
### MC89-E410 — Control Reaches End of Function
#### Condition (MUST detect)
- 반환 타입이 `int`인 어떤 함수 `f`에 대해,
  그 함수 본문이 **정상 완료(normal completion)** 될 수 있는 실행 경로가 존재하는 경우.
  - 즉, `return <expression>;` 없이 함수의 `}`에 도달 가능한 경우.

#### Required Message
```text
error MC89-E410: control may reach end of function without returning a value
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
|비함수 호출| MC89-E409 |


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
```c
int add(int a, int b) { return a + b; }

int main() {
    return add(1, 2);
}
```

```c
int add(int a, int b) { return a + b; }

int main() {
  return (add)(1, 2);   /* OK: 괄호 제거 후 add는 함수 */
}
```

#### Forbidden Examples
(1) 표준 라이브러리 함수 호출
```c
int main() {
    printf(1);      /* ERROR: call to undefined function 'printf' */
    return 0;
}
```

(2) 전처리 지시문 사용
```c
#include <stdio.h>  /* ERROR: preprocessor directives are not allowed */
int main() { return 0; }
```

(3) 교육용 내장 함수 가정
```c
int main() {
    return input(); /* ERROR: call to undefined function 'input' */
}
```

(4) 연쇄 호출
```c
int f() { return 0; }

int main() {
  return f()();   /* ERROR: MC89-E409 (두 번째 호출의 대상은 int) */
}
```

(5) 비함수 값 호출
```c
int main() {
  return (1)(2);  /* ERROR: MC89-E409 */
}
```

(6) 변수 호출
```c
int main() {
  int x;
  x = 0;
  return x(1);    /* ERROR: MC89-E409 */
}
```

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

### Annex D. Diagnostics — Error Code Summary
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
MC89-E105   Line Comment Not Allowed             "//" 토큰 시퀀스가 등장
MC89-E106   Preprocessor Directive Not Allowed   '#' 등장
MC89-E107   String Literal Not Allowed           '"' 등장
MC89-E108   Character Constant Not Allowed       ''' 등장
MC89-E109   Floating Constant Not Allowed        '1.' 등장
MC89-E110   Forbidden Keyword                    MiniC89에서 금지된 키워드 사용

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
MC89-E209   Duplicate Declaration           같은 스코프에 같은 이름이 중복해서 선언됨
MC89-E210   Invalid Type Keyword            `int` 이외의 타입이 사용됨
MC89-E211   User-defined Types Not Allowed  `struct`, `union`, `enum`, `typedef`가 사용됨
MC89-E212   Pointers and Arrays Not Allowed 포인터 또는 배열 사용됨
MC89-E213   Increment/Decrement Operators Not Allowed 증감연산자 사용됨
MC89-E214   sizeof Operator Not Allowed     sizeof 연산자 사용됨
MC89-E215   Conditional Operator Not Allowed     ?: 연산자 사용됨
MC89-E216   Bitwise Operators Not Allowed   비트연산자 사용됨
MC89-E217   Comma Operator Not Allowed      콤마연산자 사용됨


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
MC89-E308   while Statement Not Allowed while문 사용
MC89-E309   do-while Statement Not Allowed  do..while문 사용
MC89-E310   switch Statement Not Allowed    switch문 사용
MC89-E311   goto Statement Not Allowed      goto문 사용


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
MC89-E409   Call to Non-Function           비함수 호출

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
