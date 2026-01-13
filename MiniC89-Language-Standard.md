# MiniC89 Language Standard
**Draft Version:** v0.2  
**Status:** Stable Skeleton (Structure Frozen)

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


## 4. Syntax (Grammar)

### 4.1 Grammar Notation
- 문법은 EBNF로 기술된다.
- EBNF에 없는 문법은 존재하지 않는다.

### 4.2 Program Grammar (Translation Unit) -- Normative
> 이 절은 MiniC89 프로그램의 **최상위 문법 구조**를 정의한다.
>
> 이 절의 EBNF는 **번역 단위(translation unit)의 유일한 규범적 정의**이다.

### 4.2.1 EBNF Definition (Normative)
```ebnf
/* ------------------------------------------------------------
 * Program structure (MiniC89)
 * ------------------------------------------------------------ */

<program>                 ::= { <function-definition> } ;
```

### 4.2.2 Normative Rules
- 파일 스코프 (file scope)에서는 **오직 함수 정의만 허용 MUST**한다.
- 전역 변수, 전역 선언, 함수 프로토타입은 **문법적으로 존재하지 않으며 MUST NOT 허용**한다.
- 프로그램은 **정확히 하나의 엔트리 함수 `int main()`을 MUST 포함**해야 한다.
  - `main`은 매개변수를 가질 수 없다.

### 4.2.3 Allowed Examples
```c
int main() {
  return 0;
}
```

### 4.2.4 Forbidden Examples (MUST be Compile-time Error)
#### (1) No main
```c
int f() { return 1; }  /* ERROR: no main */
```
#### (2) Prototype / global variable
```c
inf f(int a);      /* ERROR: prototypes are not allowed */
int main() { return 0; }
```
```c
int g;             /* ERROR: global variables are not allowed */
int main() { return 0; }
```

### 4.2.5 Notes (Non-Normative)
- MiniC89는 **ISO C89의 "translation unit" 개념을 단순화**한 모델을 사용한다.
- 헤더 파일, 전처리, 분할 컴파일 개념은 존재하지 않는다.
- 이로 인해 모든 이름 해석은 **단일 파일, 단일 번역 단위**에서 이루어진다.

### 4.3 Forbidden Syntax

다음 문법 요소는 의도적으로 제거되었다.

- 전역 변수
- 함수 프로토타입
- 포인터
- 배열
- sizeof
- 증감 연산자
- 조건 연산자
- 비트 연산자

---

## 5. Types

### 5.1 Integer Type
- MiniC89에는 int 타입만 존재한다.
- 정수 오버플로는 Undefined Behavior이다.

---
### 5.2 Undefined Behavior

다음은 Undefined Behavior이다.

- 정수 오버플로
- 0으로 나누기
- 미초기화 변수 읽기
- lifetime 종료 객체 접근
- 평가 순서 의존 side-effect

---
## 6. Declarations

### 6.1 Declaration Rules

- 블록 내부에서 선언은 문장보다 앞에 위치 MUST 한다.
- 선언 뒤에 선언은 허용된다.
- 문장 뒤에 선언은 허용되지 않는다.
  
---
### 6.2 Examples
허용:

    {
        int x;
        int y;
        x = 1;
        y = 2;
    }

금지:

    {
        int x;
        x = 1;
        int y;
    }
---

## 7. Expressions

### 7.1 Expression Grammar (Normative)
- 허용되는 식:
  - 산술
  - 비교
  - 논리
  - 대입
  - 함수 호출

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

### 7.2 Operator Hierarchy (Normative)
#### Normative Rules
- 구현체는 7.1의 계층 구조에 따라 **연산자 우선순위**를 **MUST** 해석한다.
- 결합 규칙은 다음과 같이 **MUST** 적용한다.
  - `=`: **right-associative**
  - 그 외 이항 연산자(`|| && == != < <= > >= + - * / %`): **left-associative**
  - 단항 연산자(`+ - !`): **right-associative**

#### Precedence Table (Highest → Loweset)
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

### 7.3 Evaluation Order (Normative, for Determinism)
- MiniC89는 ISO C89와 동일하게, 대부분의 연산자에서 **피연산자의 평가 순서를 지정하지 않는다**.
- 이항 연산자 `A op B`에서 `A`와 `B`의 평가 순서는 **미지정(unspecified)** 이며, 구현체는 특정 순서를 **가정해서는 안된다**.
- 함수 호출 `f(a1, a2, ..., an)`에서
  - 함수 식별자 `f`의 확인과
  - 각 인자 표현식 `ai`의 평가 순서는 **지정되지 않는다**.
- 다음 연산자는 예외적으로 **단락 평가(short-circuit evalutaion)** 을 **MUST** 따른다.
  - `A && B`: `A`가 0이면 `B`는 평가되지 않는다.
  - `A || B`: `A`가 0이 아니면 `B`는 평가되지 않는다.
- 평가 순서에 의존하는 MiniC89 프로그램은 **비이식적(non-portable)** 이며, 구현체는 이를 **컴파일 타임 진단(오류 또는 경고)** 할 수 있다.

### 7.4 Allowed Examples
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

#### 7.5 Forbidden / Problematic Examples
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

### 7.6 Notes (Non-Normative)
- `<argument-list>`에서의 `,`는 **함수 인자 구분자**이며, **콤마 연산자**가 아니다.
- 오버플로, 0으로 나누기, 미초기화 읽기는 Types/UB 절의 규칙을 따른다.
- MiniC89 구현체(컴파일러/VM)은 **교육적 시각화**를 위해 내부적으로 특정 평가 순서(예: left-to-right)를 사용할 수 있다.
- 이러한 내부 실행 순서는 **언어 의미를 규정하지 않으며**, 다른 구현체에서도 동일하게 동작할 것이라는 보장은 없다.
- 본 절의 목적은 "결정적 시각화"와 "C89 의미론 보존"을 **명확히 분리**하는 데 있다.

## 8. Statements

### 8.1 Statement Grammar (Normative)

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

<block-item-seq>       ::= { <declaration> } { <statement> } ;

/* Declarations are defined in Chapter 6, referenced here */
<declaration>          ::= <int-declaration> ;
<int-declaration>      ::= "int" <init-declarator-list> ";" ;

<init-declarator-list> ::= <init-declarator>
                           { "," <init-declarator> } ;

<init-declarator>      ::= <identifier>
                         | <identifier> "=" <assignment-expression> ;

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

### 8.2 Normative Rules
- 블록 내부에서 선언은 **0개 이상 연속으로만** 나타날 수 있으며, **어떤 문장 뒤에도 선언이 올 수 없다 (MUST NOT)**.
- `if`/`else`는 문법에 따라 **가장 가까운 `if`와 결합**한다.
- `for`의 `(init; cond; step)` 각 항은 비어 있을 수 있다.
- `break`/`continue`는 반복문 내부에서만 유효해야 하며, 반복문 밖에서 사용시 구현체는 **컴파일 오류**를 **MUST** 발생시킨다. (문법에 없는 정적 의미 규칙이기 때문에, Diagnostics에서 필수 오류로 연결)

---

### 8.3 Allowed Examples
#### Compound + declarations-at-top
```c
int main() {
  int a;
  int b = 2;
  a = 1;
  return a + b;
}
```
---

#### if / else (dangling-else)
```c
int main() {
  int x;
  x = 0;
  if (x)
    if (1) x = 1;
    else x = 2;  /* else는 안쪽 if에 붙음 */
  return x;
```

---

#### for with empty parts
```c
int main() {
  int i;
  i = 0;
  for (; i < 3; i = i + 1);
  return i;
}
```

---
#### break / continue
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

### 8.4 Forbidden Examples (MUST be Compile-time Error)

#### Declaration after statement (C89 rule violation)
```c
int main() {
  int x;
  x = 1;
  int y;  /* ERROR: declaration after statement */
  y = 2;
  return x + y;
}
```

#### C99-style for declaration
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

#### break / continue outside loop
```c
int main() {
  break;    /* ERROR */
  return 0;
}
```

### 8.5 Notes (Non-NOrmative)
- `;` 단독은 `empty statement`로 허용된다.
- `for(;;)`는 무한 루프를 의미한다(단, 실행 모델/UB 규칙은 별도 절을 따른다).

## 9. Functions

### 9.1 Function & Program Grammar (Normative)

#### EBNF Definition (Normative)
```ebnf

/* Only function definitions are allowed at file scope */
<function-definition>     ::= "int" <identifier> "(" [ <parameter-list> ] ")"
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

### 9.2 Normative Rules

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

### 9.3 Allowed Examples
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

### 9.4 Forbidden Examples (MUST be Compile-time Error)
#### (3) Non-int parameter type
```c
int f(char x) { return 0; }  /* ERROR: only int allowed */
int main() { return 0; }
```
#### (4) Duplicate function definition
```c
int f() { return 1; }
int f() { return 2; }     /* ERROR: duplicate */
int main() { return 0; }  
```

#### (5) Call to undefined function / arity mismatch
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

### MC89-E306 -- Unreachable Statement
Condition (SHOULD detect)
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
> 이 오류는 **SHOULD** 수준이다.
>
> 구현 단순성을 위해 생략 가능.

### 11.x.3 Mapping from Grammar to Diagnostics (Normative)
|Grammar Rule|Error Code|
|`<block-item-seq>` 위반 | MC89-E301 |
|`<for-init>`에 declaration | MC89-E302 |
|`break` 의미 규칙 위반 | MC89-E303 |
|`continue` 의미 규칙 위반 | MC89-E304 |
|`return` 위치 오류 | MC89-E305 |
|`return` 표현식 누락 | MC89-E306 |

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
error MC89-E406: incalid parameter declaration (only 'int <identifier>' allowed)
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

### 12.1 Built-in Functions
<!-- input / output 등 -->

---

## 13. Annex

### Annex A. Standard Examples
### Annex B. Forbidden / Invalid Programs
### Annex C. Removed Undefined Behaviors

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

