# MiniC89 Language Standard
**Draft Version:** v0.5
**Status:** Rewriting

본 문서는 사이버보안학과 신입생 교육을 목적으로 하는  
C89 부분집합 언어 **MiniC89**의 공식 표준을 정의한다.

이 표준은 **학생, TA, 채점기, 컴파일러/VM 구현자** 모두의 공통 기준이다.

---

### 1 Introduction
- 1.1 Purpose
- 1.2 Scope
- 1.3 Relationship to ANSI C89
- 1.4 Conformance
- 1.5 Definition of terms

### 2 Environment
- 2.1 Conceptual models
  - 2.1.1 Translation environment
    - 2.1.1.1 Program structure
    - 2.1.1.2 Translation phases
    - 2.1.1.3 Diagnostics
  - 2.1.2 Execution environments
    - 2.1.2.1 Freestanding environment
    - 2.1.2.2 Program execution
- 2.2 Environmental considerations
  - 2.2.1 Character sets
  - 2.2.2 Signals and interrupts
  - 2.2.3 Environmental limits
    - 2.2.3.1 Translation limits
    - 2.2.3.2 Numerical limits

### 3 Lexical Elements
- 3.1 Keywords
- 3.2 Identifiers
  - 3.2.1 Scopes
  - 3.2.2 Storage durations
  - 3.2.3 Type
- 3.4 Constants
- 3.5 Operators
- 3.6 Punctuators
- 3.7 Comments

### 4 Expressions
- 4.1 Primary expressions
- 4.2 Postfix operator
  - 4.2.1 Function calls 
- 4.3 Unary operators
  - 4.3.1 Unary arithmetic operators  
- 4.4 Multiplicative operators
- 4.5 Additive operators
- 4.6 Relational operators
- 4.7 Equality operators
- 4.8 Logical AND operator
- 4.9 Logical OR operator
- 4.10 Assignment operator
- 4.11 Constant expressions

### 5 Declarations
- 5.1 Declarators
- 5.2 Type name
- 5.3 Initialization

### 6 Statements
- 6.1 Block
- 6.2 Expression statements
- 6.3 The if statement
- 6.4 The for statement
- 6.5 The continue statement
- 6.6 The break statement
- 6.7 The return statement

### 7 External definition
- 7.1 Function Definition

---

## 1. Introduction

### 1.1 Purpose

MiniC89의 목적은 C 언어를 처음 접하는 학습자가 가장 낮은 진입 장벽으로 C의 핵심 개념을 이해할 수 있는 것이다.
MiniC89는 교육 목적의 언어로서 다음 설계 목표를 가진다.
- 초심자를 위한 최소 언어로 필수 개념만 포함
- ANSI C89 문법을 기반으로 하되, 일부 문법/제약은 최신 C 규칙 채택
- 프로그램 동작을 특정 C 구현체나 호스트 환경이 아니라, MiniC89 추상 머신 기준으로 설명 가능하도록 정의
- Undefined Behavior를 반드시 진단 및 검출하도록 정의

### 1.2 Scope

본 표준은 다음 내용을 다룬다.

- MiniC89의 문법
- MiniC89의 정적 의미, 제약, 및 정적 진단 규칙
- MiniC89의 추상 머신 의미 기반 실행 의미
- Undefined Behavior의 정의와 발생시 처리 규칙
- 관찰 가능한 실행 결과
- 정적 오류/UB의 분류 및 진단 코드

본 표준은 다음을 규정하지 않는다.

- 추상 머신 또는 가상 머신의 내부 구현 구조
- 최적화 전략 및 성능 목표
- 구현 언어 및 배포 방식
- 호스트 환경 의존 동작

### 1.3 Relationship to ANSI C89

MiniC89는 ANSI C89의 엄격한 부분집합이며 다음을 만족한다.
- MiniC89 프로그램 소스 코드는 ANSI C89 문법에 대해 유효해야 한다. 
- 단, MiniC89 프로그램의 의미는 특정 C 구현체가 아니라, 본 표준 및 MiniC89 추상 머신에 의해 결정된다.
- ANSI C89에서 unspecified, implementation-defined로 남아 있는 동작은, 교육 목적과 결정론적 실행을 위해 본 표준에서 명시적으로 고정하거나, 그렇지 않은 경우 Undefined Behavior로 분류할 수 있다.

### 1.4 Conformance

- 적합한 프로그램은 본 표준에 명시된 기능만 쓰는 프로그램이다.

- 정의된 실행은 실행중 Undefined Behavior가 발생하지 않은 실행이다.

- 적합한 구현체는 적합한 프로그램을 허용해야 하고, 본 표준에서 금지된 프로그램에 대해 정의된 진단 메시지를 출력해야 한다.

- Undefined Behavior가 발생하면 그 시점 이후는 더 이상 정의된 실행이 아니며, 적합한 구현체는 본 표준에서 규정한 진단 메시지를 출력한 후 프로그램을 종료해야 한다.

- 적합한 구현체는 C89에서의 Unspecified/implementation-defined에 의존하는 프로그램을 진단하여 본 표준에서 정의한 진단 메시지를 출력한다. 

### 1.5 Definition of terms

본 표준에서 사용되는 규범 키워드의 의미는 다음과 같다.

- **Shall**: 반드시 충족되어야 하는 요구사항이다. 위반한 프로그램 또는 구현체는 MiniC89에 부적합하다.

- **Shall not**: 절대적으로 금지되는 요구사항이다. 위반한 프로그램 또는 구현체는 MiniC89에 부적합하다.

또한 다음 용어를 사용한다.

- **Implementation**: 본 표준에 정의된 문법/의미/진단 규칙을 구현하여 MiniC89 프로그램을 번역 및 실행하는 구성 요소의 집합을 말한다. 구현체는 특정 호스트 환경이나 기존 C 컴파일러의 동작에 의존하여서는 안 된다.

- **Undefined behavior**: 오류가 있는 프로그램이나 오류가 있는 데이터나 값이 정해지지 않은 데이터를 써서 발생하는 모든 현상을 의미한다. 

- **Diagnostic**: 본 표준이 요구하는 방식으로 오류 또는 UB를 사용자에게 보고하는 행위를 말한다(진단 메시지 및 진단 코드 포함).

---

## 2 Environment
### 2.1 Conceptual models
#### 2.1.1 Translation environment

MiniC89 프로그램은 소스 코드 형태에서 실행 가능한 형태로 변환되는 번역 과정을 거친다.

##### 2.1.1.1 Program structure

MiniC89 프로그램은 단 하나의 번역 단위로 구성된다.

MiniC89는 전처리기 지시문을 지원하지 않으며, 별도의 헤더 파일 포함이나 외부 라이브러리 링크 과정은 본 표준의 범위 밖이다.

내장 함수 및 표준 라이브러리 함수 사용은 허용되지 않는다.

적합한 프로그램은 적어도 하나의 외부 선언을 포함해야 한다.

##### 2.1.1.2 Translation phases

구현체는 개념적으로 다음 단계를 거쳐 프로그램을 처리해야 한다.

- **어휘 분석**: 소스 파일을 토큰의 스트림으로 분해한다. 주석은 공백 1개로 치환된다.

- **구문 및 의미 분석**: 토큰 스트림을 해석하여 문법적 오류와 정적 의미 오류(허용되지 않은 구문 요소 사용, 타입 불일치 등)를 검사한다.

- **코드 생성**: MiniC89 추상 머신이 실행 가능한 명령어(바이트코드 등)로 변환한다.

##### 2.1.1.3 Diagnostics

구현체는 번역 과정에서 본 표준의 문법 규칙이나 정적 의미 규칙을 위반한 경우, 반드시 하나 이상의 진단 메시지를 출력하고 번역을 중단해야 한다.

진단 메시지는 오류가 발생한 소스 코드의 위치(라인 번호 등)와 원인을 식별할 수 있는 정보를 포함해야 한다.
  
#### 2.1.2 Execution environments

MiniC89 프로그램은 MiniC89 추상 머신 위에서 실행된다.

##### 2.1.2.1 Freestanding environment

MiniC89는 운영체제의 지원 없이 동작하는 독립 환경을 따른다. 

프로그램의 시작점은 소스 파일에서 가장 마지막에 정의되는 함수다. 

##### 2.1.2.2 Program execution

본 표준의 의미론적 설명은 추상 머신의 동작을 정의한다. 최적화 이슈는 이 추상 머신의 동작 정의에 영향을 주지 않는다.

부수 효과
- 변수에 값을 저장하거나, 함수를 호출하는 행위는 실행 환경의 상태를 변화시키는 부수 효과다.
- 수식을 계산하는 것은 부수 효과를 발생시킬 수 있다.

시퀀스 포인트
- 실행 순서상 특정 지점인 시퀀스 포인트에서, 이전에 발생된 모든 부수 효과는 완료되어야 하고, 이후에 발생할 부수 효과는 아직 시작하지 않아야 한다.
- 시퀀스 포인트 관련 규칙은 본 표준의 추상 머신 의미 절에서 규정한다.

평가 및 최적화
- 추상 머신에서 모든 수식은 의미론에 명시된 대로 평가된다.
- 실제 구현체는 수식의 값이 사용되지 않고, 부수 효과가 없다고 판단될 경우, 해당 계산의 일부를 수행하지 않을 수 있다.
- 예외: 단, 계산 과정에서 Undefined Behavior가 발생할 가능성이 있는 경우, 구현체는 이를 임의로 삭제해서는 안되며 반드시 실제 연산을 수행하여 오류를 진단해야 한다.

자동 저장 기간
- 블록에 진입할 때마다, 해당 블록 내에 선언된 자동 저장 기간의 객체 인스턴스가 생성된다.
- 이 객체는 블록의 실행이 끝날 때까지 값을 유지하며, 재귀 호출 등으로 인해 블록이 중단된 상태에서도 값을 보존한다.

적합한 구현체의 최소 요구 사항
- 시퀀스 포인트: 시퀀스 포인트에서 객체의 값은 추상 머신이 정의한 상태와 일치해야 한다.
- 프로그램 종료: 프로그램 종료시 반환되는 값은 추상 머신의 결과와 일치해야 한다.
- UB 진단: 실행 중 발생하는 모든 Undefined Behavior는 즉시 감지되어야 한다. 

예시: 

다음 코드 조각에서,

```c
int a;
int b;
/* ... a와 b에 값이 저장됨 ... */
a = a + b;
```

추상 머신은 `a`와 `b`의 값을 더하여 그 결과를 `a`에 저장한다. 만약 `a + b`의 결과가 16-bit `int` 범위를 벗어난다면, 이는 오버플로우에 해당하는 Undefined Behavior이며 구현체는 이를 반드시 진단하고 실행을 중단해야 한다.

### 2.2 Environmental considerations
#### 2.2.1 Character sets

MiniC89 프로그램은 7-bit ASCII 코드에 기반한 다음과 같은 기본 소스 문자 집합으로 작성되어야 한다. 

1. 영어 대소문자 (52자):
```
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
a b c d e f g h i j k l m n o p q r s t u v w x y z
```

2. 10진 숫자 (10자):
```
0 1 2 3 4 5 6 7 8 9
```

3. 그래픽 문자 (18자):
```
! % & ( ) * + , - / ; < = > { | } _
```

4. 공백 문자 (2자): 스페이스, 탭

5. 줄바꿈 (1자): 소스 파일의 각 줄은 줄 바꿈 표시로 구분된다.

MiniC89는 런터임에 문자나 문자열 데이터를 처리하지 않으므로, 별도의 실행 문자 집합을 정의하지 않는다.

진단 규칙: 주석 내부를 제외하고, 위에서 정의된 소스 문자 집합 이외의 문자가 소스 파일에서 발견될 경우, 구현체는 이를 문법 오류로 진단하고 번역을 중단해야 한다. 

#### 2.2.2 Function execution environment

재귀 호출
- 함수는 자기 자신을 직접 또는 간접적으로 호출(재귀 호출)할 수 있어야 한다.
- 재귀 호출이 발생했을 때, 이전에 실행 중이었고 아직 종료되지 않은 함수 호출에서의 제어 흐름, 반환 값, 자동 저장 기간의 객체는 보존되어야 한다.

저장 공간의 분리
- 자동 저장 기간의 모든 객체는 함수 코드와 분리하여 관리되어야 한다.
- 구현체는 함수가 호출될 때마다 해당 호출만을 위한 고유한 저장 공간을 할당하여, 각 호출 간의 변수 충돌을 방지해야 한다.

#### 2.2.3 Environmental limits

구현체는 프로그램의 번역 및 실행에 있어 다음과 같은 최소한의 한계를 지원해야 한다. 

##### 2.2.3.1 Translation limits

구현체는 다음의 한계를 초과하지 않는 프로그램을 하나 이상 올바르게 번역하고 실행할 수 있어야 한다.

1. 코드 구조의 중첩

- 15 nesting levels: 복합 문, 반복 제어 구조, 선택 제어 구조의 중첩 깊이.

- 32 expressions nested: 괄호()로 묶인 표현식의 중첩 깊이. (예: ((a+(b*c))...))

2. 식별자

- 31 significant initial characters: 식별자(변수명, 함수명)의 유효 길이. 

- 511 external identifiers: 번역 단위에 존재하는 외부 식별자(함수 정의)의 총 개수.

- 127 identifiers with block scope: 하나의 블록 내에 선언된 지역 변수의 개수.

3. 함수

- 31 parameters: 하나의 함수 정의에 포함된 매개변수의 개수.

- 31 arguments: 하나의 함수 호출에 전달되는 인자의 개수.

4. 소스 코드

- 509 characters: 소스 코드 한 줄의 최대 길이.

##### 2.2.3.2 Numerical limits

MiniC89는 언어 사양 자체적으로 다음의 수치 한계를 규정한다.

MiniC89의 유일한 산술 타입인 `int`는 16-bit 2의 보수 표현 방식을 따르며, 그 범위는 다음과 같이 고정된다.

- INT_MIN: -32,768
- INT_MAX: +32,767

연산 결과가 `INT_MIN`과 `INT_MAX` 범위를 벗어나는 경우, 구현체는 이를 Undefined Behavior로 간주하여 반드시 진단 메시지를 출력하고 실행을 중단해야 한다.
    
## 3. Lexical Elements

MiniC89의 소스 코드는 다음 토큰들로 구성된다.

- Keywords
- Identifiers
- Integer constants
- Operators
- Punctuators

토큰을 파싱할때 최대 토큰 길이 법칙을 적용한다.

### 3.1 Keywords

MiniC89 구현체는 ANSI C89에서 정의된 모든 키워드를 우선적으로 토큰화 한다.  

다음은 MiniC89에서 쓰이는 `MiniC89키워드`를 정의한다.

```c
int  
if  
else  
for  
return  
break  
continue  
```

다음 키워드는 C89에 있기 때문에 MiniC89에서 쓰이지는 않지만 보존된 `비MiniC89키워드`를 정의한다. 

```c
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
```

### 3.2 Identifiers

- `이름`은 알파벳 또는 '_'로 시작한다.
- 이후 알파벳, 숫자, '_'의 조합으로 구성된다.
- 키워드와 동일한 이름은 사용할 수 없다.

#### 3.2.1 Scopes

- `이름`이 유효한 범위는 파일 스코프와 블록 스코프가 있다. 
- 파일 스코프는 중괄호 `{ }` 바깥에서 선언된 식별자에 해당한다. 소스 파일 전체에서 접근 가능하다.
- 파일 스코프에서는 함수 정의와 함수 원형 선언만 허용된다. (전역변수는 허용되지 않는다)
- 블록 스코프는 함수 매개변수 또는 중괄호 `{ }` 안에서 선언된 식별자에 해당한다. 해당 중괄호가 끝날 때까지 `}` 접근 가능하다. 
- 블록 스코프에서 변수를 선언하면 자동 저장기간 메모리가 할당된다.
- 같은 블록 스코프에서 동일한 이름을 두번 정의할 수 없다.
- 어떤 스코프에서 스코프 바깥과 동일한 이름을 선언한 경우, 스코프 바깥의 이름은 가려진다. 

#### 3.2.2 Storage durations
- 변수의 저장기간은 자동 저장기간만이 존재한다.
- 자동 저장기간을 가진 변수는 해당 블록에 진입할 때 메모리 공간이 확보되고, 해당 블록이 끝날 때 메모리 공간이 반환된다. 

#### 3.2.3 Type
- `타입`에는 `int`만 존재한다.
- `int`에서 표현 가능한 범위는 2.2.3.2 Numerical limits에 정해져 있다.

### 3.4 Constants
- `상수`는 10진 정수 리터럴만 허용된다.
- 허용되는 정수 리터럴의 범위는 0부터 `int` 타입에서 표현 가능한 최대값 까지다.

### 3.5 Operators
- `연산자`에는 `함수호출연산자`, `산술연산자`, `대입연산자`, `비교연산자`, `논리연산자`가 있다.
- `함수호출연산자`에는 `(`, `)`가 있다.
- `산술연산자`에는 `+`, `-`, `*`, `/`, `%`가 있다.
- `대입연산자`에는 `=`가 있다.
- `비교연산자`에는 `<`, `>`, `<=`, `>=`, `==`, `!=` 가 있다.
- `논리연산자`에는 `!`, `&&`, `||`, 가 있다.

### 3.6 Punctuators
- `구두점`에는 `(`, `)`, `{`, `}`, `,`, `=`, `;`가 있다.

### 3.7 Comments and Whitespace

- `/* ... */` 형식의 주석만 허용된다.
- 주석은 중첩될 수 없다.
- `//` 형식의 주석은 허용되지 않는다.
- 주석은 컴파일시 띄어쓰기 ` ` 하나로 변환된다. 
- 공백 문자는 띄어쓰기 ` `, 줄바꿈 `\n`, 수평탭 `\t`만 허용된다.
- 주석과 공백 문자는 토큰화을 나누는 데만 영향을 준다. 
- 백슬래시 `\`를 통한 줄 합치기는 지원하지 않는다.

## 4. Expressions

- `식`은 연산자와 피연산자를 통해 계산을 하거나, 변수나 함수를 지칭하거나, 프로그램 상태를 변화시키는 것을 한다.
- 시퀀스 포인트 사이에서 변수의 값은 한번만 바뀔 수 있고, 값이 바뀌는 경우에는 새로운 값을 계산하기 위해서만 값을 읽을 수 있다.

### 4.1 Primary expression
- `기본수식`에는 `식별자`, `상수`, `(` `수식` `)`이 있다.
- `식별자`는 변수일 수도 있고, 함수일 수도 있다.
- `식별자`가 변수일 경우, 대입연산자 `=`의 왼쪽에 있지 않으면 저장된 `int` 값으로 변환된다. 
- `상수`의 타입은 항상 `int`다.
- `(` `수식` `)`의 타입과 결과는 괄호 안의 `수식`과 같다. `수식`의 결과가 변수나 함수일 경우 `(` `수식` `)`의 결과도 똑같이 변수나 함수다.

### 4.2 Postfix expression
- `후위식`에는 `기본수식`, `함수호출식`이 있다.

### 4.2.1 Function calls
- `함수호출식`에는 `기본수식` `(` `)`, `기본수식` `(` `인자-식-리스트` `)`가 있다.
-  `(` 왼쪽에 있는 `기본수식`은 결과가 함수여야 한다.
-  호출하려는 함수는 반드시 호출 이전에 선언되어 있어야 한다. 
- `인자-식-리스트`가 없는 경우, 해당 함수는 매개변수를 받지 않아야 한다. 
- `인자-식-리스트`에는 `대입식`과 `인자-식-리스트` `,` `인자-식`이 있다.
- `인자-식-리스트`가 있는 경우, 매개변수와 인자의 개수가 같아야하고, 각 매개변수에 대입연산자(`=`)에 의해 인자의 값이 저장되는 것 처럼 인자의 값이 변환된다.
- 인자 평가 순서는 정해져 있지 않다.
- 호출 결과의 타입은 항상 `int`이며, 결과값은 호출한 함수가 반환(`return`)한 값이다.
- 재귀 호출은 허용된다.

### 4.3 Unary expression
- `단항식`에는 `후위식`, `단항연산자` `후위식`이 있다.
- `단항연산자`에는 `+`, `-`, `!`가 있다.

