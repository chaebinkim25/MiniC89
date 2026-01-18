# C89 초안

- [1. 서론](#1-서론)
  - [1.1 목적](#11-목적)
  - [1.2 적용 범위](#12-적용-범위)
  - [1.3 참조](#13-참조)
  - [1.4 문서 구성](#14-문서-구성)
  - [1.5 기본 문서](#15-기본-문서)
  - [1.6 용어 정의](#16-용어-정의)
  - [1.7 적합성(준수)](#17-적합성(준수))
  - [1.8 향후 방향](#18-향후-방향)
  - [1.9 이 초안에 대하여](#19-이-초안에-대하여)
- [2. 환경](#2-환경)
  - [2.1 개념적 모델](#21-개념적-모델)
    - [2.1.1 번역 환경](#211-번역-환경)
      - [2.1.1.1 프로그램 구조](#2111-프로그램-구조)
      - [2.1.1.2 번역 단계](#2112-번역-단계)
      - [2.1.1.3 진단](#2113-진단)
    - [2.1.2 실행 환경](#212-실행-환경)
      - [2.1.2.1 프리스탠딩(freestanding) 환경](#2121-프리스탠딩(freestanding)-환경)
      - [2.1.2.2 호스티드(hosted) 환경](#2122-호스티드(hosted)-환경)
      - [2.1.2.3 프로그램 실행](#2123-프로그램-실행)
  - [2.2 환경적 고려사항](#22-환경적-고려사항)
    - [2.2.1 문자 집합](#221-문자-집합)
      - [2.2.1.1 트라이그래프(trigraph) 시퀀스](#2211-트라이그래프(trigraph)-시퀀스)
      - [2.2.1.2 다중 바이트 문자](#2212-다중-바이트-문자)
    - [2.2.2 문자 표시 의미](#222-문자-표시-의미)
    - [2.2.3 신호와 인터럽트](#223-신호와-인터럽트)
    - [2.2.4 환경 한계](#224-환경-한계)
      - [2.2.4.1 번역 한계](#2241-번역-한계)
      - [2.2.4.2 수치 한계](#2242-수치-한계)
- [3. 언어](#3-언어)
  - [3.1 어휘 요소](#31-어휘-요소)
    - [3.1.1 키워드](#311-키워드)
    - [3.1.2 식별자](#312-식별자)
      - [3.1.2.1 식별자의 범위](#3121-식별자의-범위)
      - [3.1.2.2 식별자의 연결(linkage)](#3122-식별자의-연결(linkage))
      - [3.1.2.3 식별자의 이름 공간(name space)](#3123-식별자의-이름-공간(name-space))
      - [3.1.2.4 객체의 저장 기간(storage duration)](#3124-객체의-저장-기간(storage-duration))
      - [3.1.2.5 형(type)](#3125-형(type))
      - [3.1.2.6 호환 가능한 형과 합성 형(composite type)](#3126-호환-가능한-형과-합성-형(composite-type))
    - [3.1.3 상수](#313-상수)
      - [3.1.3.1 부동소수점 상수](#3131-부동소수점-상수)
      - [3.1.3.2 정수 상수](#3132-정수-상수)
      - [3.1.3.3 열거 상수](#3133-열거-상수)
      - [3.1.3.4 문자 상수](#3134-문자-상수)
    - [3.1.4 문자열 리터럴](#314-문자열-리터럴)
    - [3.1.5 연산자](#315-연산자)
    - [3.1.6 구두점(punctuators)](#316-구두점(punctuators))
    - [3.1.7 헤더 이름](#317-헤더-이름)
    - [3.1.8 전처리 숫자(preprocessing numbers)](#318-전처리-숫자(preprocessing-numbers))
    - [3.1.9 주석](#319-주석)
  - [3.2 변환](#32-변환)
    - [3.2.1 산술 피연산자](#321-산술-피연산자)
      - [3.2.1.1 문자와 정수](#3211-문자와-정수)
      - [3.2.1.2 부호 있는 정수와 부호 없는 정수](#3212-부호-있는-정수와-부호-없는-정수)
      - [3.2.1.3 부동소수점과 정수형](#3213-부동소수점과-정수형)
      - [3.2.1.4 부동소수점 형](#3214-부동소수점-형)
      - [3.2.1.5 통상적인 산술 변환](#3215-통상적인-산술-변환)
    - [3.2.2 그 밖의 피연산자](#322-그-밖의-피연산자)
      - [3.2.2.1 좌값(lvalue)과 함수 지정자(function designators)](#3221-좌값(lvalue)과-함수-지정자(function-designators))
      - [3.2.2.2 void](#3222-void)
      - [3.2.2.3 포인터](#3223-포인터)
  - [3.3 식(expressions)](#33-식(expressions))
    - [3.3.1 기본 식(primary expressions)](#331-기본-식(primary-expressions))
    - [3.3.2 후위 연산자(postfix operators)](#332-후위-연산자(postfix-operators))
      - [3.3.2.1 배열 첨자 지정(array subscripting)](#3321-배열-첨자-지정(array-subscripting))
      - [3.3.2.2 함수 호출](#3322-함수-호출)
      - [3.3.2.3 구조체 및 공용체 멤버](#3323-구조체-및-공용체-멤버)
      - [3.3.2.4 후위 증가 및 감소 연산자](#3324-후위-증가-및-감소-연산자)
    - [3.3.3 단항 연산자(unary operators)](#333-단항-연산자(unary-operators))
      - [3.3.3.1 전위 증가 및 감소 연산자](#3331-전위-증가-및-감소-연산자)
      - [3.3.3.2 주소 및 간접 참조 연산자](#3332-주소-및-간접-참조-연산자)
      - [3.3.3.3 단항 산술 연산자](#3333-단항-산술-연산자)
      - [3.3.3.4 sizeof 연산자](#3334-sizeof-연산자)
    - [3.3.4 형변환(cast) 연산자](#334-형변환(cast)-연산자)
    - [3.3.5 승법(multiplicative) 연산자](#335-승법(multiplicative)-연산자)
    - [3.3.6 가법(additive) 연산자](#336-가법(additive)-연산자)
    - [3.3.7 비트 시프트(shift) 연산자](#337-비트-시프트(shift)-연산자)
    - [3.3.8 관계(relational) 연산자](#338-관계(relational)-연산자)
    - [3.3.9 등가(equality) 연산자](#339-등가(equality)-연산자)
    - [3.3.10 비트 AND 연산자](#3310-비트-and-연산자)
    - [3.3.11 비트 배타적 OR(exclusive OR) 연산자](#3311-비트-배타적-or(exclusive-or)-연산자)
    - [3.3.12 비트 포함 OR(inclusive OR) 연산자](#3312-비트-포함-or(inclusive-or)-연산자)
    - [3.3.13 논리 AND 연산자](#3313-논리-and-연산자)
    - [3.3.14 논리 OR 연산자](#3314-논리-or-연산자)
    - [3.3.15 조건(conditional) 연산자](#3315-조건(conditional)-연산자)
    - [3.3.16 대입(assignment) 연산자](#3316-대입(assignment)-연산자)
      - [3.3.16.1 단순 대입](#33161-단순-대입)
      - [3.3.16.2 복합 대입](#33162-복합-대입)
    - [3.3.17 쉼표(comma) 연산자](#3317-쉼표(comma)-연산자)
  - [3.4 상수식(constant expressions)](#34-상수식(constant-expressions))
  - [3.5 선언(declarations)](#35-선언(declarations))
    - [3.5.1 저장 클래스(storage-class) 지정자](#351-저장-클래스(storage-class)-지정자)
    - [3.5.2 형(type) 지정자](#352-형(type)-지정자)
      - [3.5.2.1 구조체 및 공용체 지정자](#3521-구조체-및-공용체-지정자)
      - [3.5.2.2 열거(enumeration) 지정자](#3522-열거(enumeration)-지정자)
      - [3.5.2.3 태그(tags)](#3523-태그(tags))
    - [3.5.3 형 한정자(type qualifiers)](#353-형-한정자(type-qualifiers))
    - [3.5.4 선언자(declarators)](#354-선언자(declarators))
      - [3.5.4.1 포인터 선언자](#3541-포인터-선언자)
      - [3.5.4.2 배열 선언자](#3542-배열-선언자)
      - [3.5.4.3 함수 선언자(프로토타입 포함)](#3543-함수-선언자(프로토타입-포함))
    - [3.5.5 형 이름(type names)](#355-형-이름(type-names))
    - [3.5.6 형 정의(type definitions)](#356-형-정의(type-definitions))
    - [3.5.7 초기화(initialization)](#357-초기화(initialization))
  - [3.6 문(statements)](#36-문(statements))
    - [3.6.1 레이블 문(labeled statements)](#361-레이블-문(labeled-statements))
    - [3.6.2 복합문(compound statement), 또는 블록(block)](#362-복합문(compound-statement),-또는-블록(block))
    - [3.6.3 식문(expression statements)과 널(null) 문](#363-식문(expression-statements)과-널(null)-문)
    - [3.6.4 선택 문(selection statements)](#364-선택-문(selection-statements))
      - [3.6.4.1 if 문](#3641-if-문)
      - [3.6.4.2 switch 문](#3642-switch-문)
    - [3.6.5 반복 문(iteration statements)](#365-반복-문(iteration-statements))
      - [3.6.5.1 while 문](#3651-while-문)
      - [3.6.5.2 do 문](#3652-do-문)
      - [3.6.5.3 for 문](#3653-for-문)
    - [3.6.6 점프 문(jump statements)](#366-점프-문(jump-statements))
      - [3.6.6.1 goto 문](#3661-goto-문)
      - [3.6.6.2 continue 문](#3662-continue-문)
      - [3.6.6.3 break 문](#3663-break-문)
      - [3.6.6.4 return 문](#3664-return-문)
  - [3.7 외부 정의(external definitions)](#37-외부-정의(external-definitions))
    - [3.7.1 함수 정의(function definitions)](#371-함수-정의(function-definitions))
    - [3.7.2 외부 객체 정의(external object definitions)](#372-외부-객체-정의(external-object-definitions))
  - [3.8 전처리 지시문(preprocessing directives)](#38-전처리-지시문(preprocessing-directives))
    - [3.8.1 조건부 포함(conditional inclusion)](#381-조건부-포함(conditional-inclusion))
    - [3.8.2 소스 파일 포함(source file inclusion)](#382-소스-파일-포함(source-file-inclusion))
    - [3.8.3 매크로 치환(macro replacement)](#383-매크로-치환(macro-replacement))
      - [3.8.3.1 인자 치환(argument substitution)](#3831-인자-치환(argument-substitution))
      - [3.8.3.2 # 연산자](#3832-#-연산자)
      - [3.8.3.3 ## 연산자](#3833-##-연산자)
      - [3.8.3.4 재스캔(rescanning) 및 추가 치환](#3834-재스캔(rescanning)-및-추가-치환)
      - [3.8.3.5 매크로 정의의 범위(scope)](#3835-매크로-정의의-범위(scope))
    - [3.8.4 행(line) 제어](#384-행(line)-제어)
    - [3.8.5 오류(error) 지시문](#385-오류(error)-지시문)
    - [3.8.6 pragma 지시문](#386-pragma-지시문)
    - [3.8.7 널(null) 지시문](#387-널(null)-지시문)
    - [3.8.8 미리 정의된 매크로 이름(predefined macro names)](#388-미리-정의된-매크로-이름(predefined-macro-names))
  - [3.9 향후 언어 방향(future language directions)](#39-향후-언어-방향(future-language-directions))
    - [3.9.1 외부 이름(external names)](#391-외부-이름(external-names))
    - [3.9.2 문자 이스케이프 시퀀스(character escape sequences)](#392-문자-이스케이프-시퀀스(character-escape-sequences))
    - [3.9.3 저장 클래스 지정자(storage-class specifiers)](#393-저장-클래스-지정자(storage-class-specifiers))
    - [3.9.4 함수 선언자(function declarators)](#394-함수-선언자(function-declarators))
    - [3.9.5 함수 정의(function definitions)](#395-함수-정의(function-definitions))
- [4. 라이브러리](#4-라이브러리)
  - [4.1 개요](#41-개요)
    - [4.1.1 용어 정의](#411-용어-정의)
    - [4.1.2 표준 헤더](#412-표준-헤더)
    - [4.1.3 오류 <errno.h>](#413-오류-<errnoh>)
    - [4.1.4 한계 <float.h> 및 <limits.h>](#414-한계-<floath>-및-<limitsh>)
    - [4.1.5 공통 정의 <stddef.h>](#415-공통-정의-<stddefh>)
    - [4.1.6 라이브러리 함수 사용](#416-라이브러리-함수-사용)
  - [4.2 진단 <assert.h>](#42-진단-<asserth>)
    - [4.2.1 프로그램 진단](#421-프로그램-진단)
      - [4.2.1.1 assert 매크로](#4211-assert-매크로)
  - [4.3 문자 처리 <ctype.h>](#43-문자-처리-<ctypeh>)
    - [4.3.1 문자 검사 함수](#431-문자-검사-함수)
      - [4.3.1.1 isalnum 함수](#4311-isalnum-함수)
      - [4.3.1.2 isalpha 함수](#4312-isalpha-함수)
      - [4.3.1.3 iscntrl 함수](#4313-iscntrl-함수)
      - [4.3.1.4 isdigit 함수](#4314-isdigit-함수)
      - [4.3.1.5 isgraph 함수](#4315-isgraph-함수)
      - [4.3.1.6 islower 함수](#4316-islower-함수)
      - [4.3.1.7 isprint 함수](#4317-isprint-함수)
      - [4.3.1.8 ispunct 함수](#4318-ispunct-함수)
      - [4.3.1.9 isspace 함수](#4319-isspace-함수)
      - [4.3.1.10 isupper 함수](#43110-isupper-함수)
      - [4.3.1.11 isxdigit 함수](#43111-isxdigit-함수)
    - [4.3.2 문자 대소문자 매핑 함수](#432-문자-대소문자-매핑-함수)
      - [4.3.2.1 tolower 함수](#4321-tolower-함수)
      - [4.3.2.2 toupper 함수](#4322-toupper-함수)
  - [4.4 지역화 <locale.h>](#44-지역화-<localeh>)
    - [4.4.1 로캘(locale) 제어](#441-로캘(locale)-제어)
      - [4.4.1.1 setlocale 함수](#4411-setlocale-함수)
    - [4.4.2 숫자 서식 관례 조회](#442-숫자-서식-관례-조회)
      - [4.4.2.1 localeconv 함수](#4421-localeconv-함수)
  - [4.5 수학 <math.h>](#45-수학-<mathh>)
    - [4.5.1 오류 조건 처리](#451-오류-조건-처리)
    - [4.5.2 삼각 함수](#452-삼각-함수)
      - [4.5.2.1 acos 함수](#4521-acos-함수)
      - [4.5.2.2 asin 함수](#4522-asin-함수)
      - [4.5.2.3 atan 함수](#4523-atan-함수)
      - [4.5.2.4 atan2 함수](#4524-atan2-함수)
      - [4.5.2.5 cos 함수](#4525-cos-함수)
      - [4.5.2.6 sin 함수](#4526-sin-함수)
      - [4.5.2.7 tan 함수](#4527-tan-함수)
    - [4.5.3 쌍곡 함수](#453-쌍곡-함수)
      - [4.5.3.1 cosh 함수](#4531-cosh-함수)
      - [4.5.3.2 sinh 함수](#4532-sinh-함수)
      - [4.5.3.3 tanh 함수](#4533-tanh-함수)
    - [4.5.4 지수 및 로그 함수](#454-지수-및-로그-함수)
      - [4.5.4.1 exp 함수](#4541-exp-함수)
      - [4.5.4.2 frexp 함수](#4542-frexp-함수)
      - [4.5.4.3 ldexp 함수](#4543-ldexp-함수)
      - [4.5.4.4 log 함수](#4544-log-함수)
      - [4.5.4.5 log10 함수](#4545-log10-함수)
      - [4.5.4.6 modf 함수](#4546-modf-함수)
    - [4.5.5 거듭제곱 함수](#455-거듭제곱-함수)
      - [4.5.5.1 pow 함수](#4551-pow-함수)
      - [4.5.5.2 sqrt 함수](#4552-sqrt-함수)
    - [4.5.6 가장 가까운 정수, 절댓값, 나머지 함수](#456-가장-가까운-정수,-절댓값,-나머지-함수)
      - [4.5.6.1 ceil 함수](#4561-ceil-함수)
      - [4.5.6.2 fabs 함수](#4562-fabs-함수)
      - [4.5.6.3 floor 함수](#4563-floor-함수)
      - [4.5.6.4 fmod 함수](#4564-fmod-함수)
  - [4.6 비지역 점프(non-local jumps) <setjmp.h>](#46-비지역-점프(non-local-jumps)-<setjmph>)
    - [4.6.1 호출 환경 저장](#461-호출-환경-저장)
      - [4.6.1.1 setjmp 매크로](#4611-setjmp-매크로)
    - [4.6.2 호출 환경 복원](#462-호출-환경-복원)
      - [4.6.2.1 longjmp 함수](#4621-longjmp-함수)
  - [4.7 신호 처리 <signal.h>](#47-신호-처리-<signalh>)
    - [4.7.1 신호 처리 지정](#471-신호-처리-지정)
      - [4.7.1.1 signal 함수](#4711-signal-함수)
    - [4.7.2 신호 전송](#472-신호-전송)
      - [4.7.2.1 raise 함수](#4721-raise-함수)
  - [4.8 가변 인자(variable arguments) <stdarg.h>](#48-가변-인자(variable-arguments)-<stdargh>)
    - [4.8.1 가변 인자 리스트 접근 매크로](#481-가변-인자-리스트-접근-매크로)
      - [4.8.1.1 va_start 매크로](#4811-va_start-매크로)
      - [4.8.1.2 va_arg 매크로](#4812-va_arg-매크로)
      - [4.8.1.3 va_end 매크로](#4813-va_end-매크로)
  - [4.9 입출력 <stdio.h>](#49-입출력-<stdioh>)
    - [4.9.1 개요](#491-개요)
    - [4.9.2 스트림(streams)](#492-스트림(streams))
    - [4.9.3 파일(files)](#493-파일(files))
    - [4.9.4 파일에 대한 연산(operations on files)](#494-파일에-대한-연산(operations-on-files))
      - [4.9.4.1 remove 함수](#4941-remove-함수)
      - [4.9.4.2 rename 함수](#4942-rename-함수)
      - [4.9.4.3 tmpfile 함수](#4943-tmpfile-함수)
      - [4.9.4.4 tmpnam 함수](#4944-tmpnam-함수)
    - [4.9.5 파일 접근 함수](#495-파일-접근-함수)
      - [4.9.5.1 fclose 함수](#4951-fclose-함수)
      - [4.9.5.2 fflush 함수](#4952-fflush-함수)
      - [4.9.5.3 fopen 함수](#4953-fopen-함수)
      - [4.9.5.4 freopen 함수](#4954-freopen-함수)
      - [4.9.5.5 setbuf 함수](#4955-setbuf-함수)
      - [4.9.5.6 setvbuf 함수](#4956-setvbuf-함수)
    - [4.9.6 형식 지정 입출력 함수](#496-형식-지정-입출력-함수)
      - [4.9.6.1 fprintf 함수](#4961-fprintf-함수)
      - [4.9.6.2 fscanf 함수](#4962-fscanf-함수)
      - [4.9.6.3 printf 함수](#4963-printf-함수)
      - [4.9.6.4 scanf 함수](#4964-scanf-함수)
      - [4.9.6.5 sprintf 함수](#4965-sprintf-함수)
      - [4.9.6.6 sscanf 함수](#4966-sscanf-함수)
      - [4.9.6.7 vfprintf 함수](#4967-vfprintf-함수)
      - [4.9.6.8 vprintf 함수](#4968-vprintf-함수)
      - [4.9.6.9 vsprintf 함수](#4969-vsprintf-함수)
    - [4.9.7 문자 입출력 함수](#497-문자-입출력-함수)
      - [4.9.7.1 fgetc 함수](#4971-fgetc-함수)
      - [4.9.7.2 fgets 함수](#4972-fgets-함수)
      - [4.9.7.3 fputc 함수](#4973-fputc-함수)
      - [4.9.7.4 fputs 함수](#4974-fputs-함수)
      - [4.9.7.5 getc 함수](#4975-getc-함수)
      - [4.9.7.6 getchar 함수](#4976-getchar-함수)
      - [4.9.7.7 gets 함수](#4977-gets-함수)
      - [4.9.7.8 putc 함수](#4978-putc-함수)
      - [4.9.7.9 putchar 함수](#4979-putchar-함수)
      - [4.9.7.10 puts 함수](#49710-puts-함수)
      - [4.9.7.11 ungetc 함수](#49711-ungetc-함수)
    - [4.9.8 직접 입출력 함수](#498-직접-입출력-함수)
      - [4.9.8.1 fread 함수](#4981-fread-함수)
      - [4.9.8.2 fwrite 함수](#4982-fwrite-함수)
    - [4.9.9 파일 위치 지정 함수](#499-파일-위치-지정-함수)
      - [4.9.9.1 fgetpos 함수](#4991-fgetpos-함수)
      - [4.9.9.2 fseek 함수](#4992-fseek-함수)
      - [4.9.9.3 fsetpos 함수](#4993-fsetpos-함수)
      - [4.9.9.4 ftell 함수](#4994-ftell-함수)
      - [4.9.9.5 rewind 함수](#4995-rewind-함수)
    - [4.9.10 오류 처리 함수](#4910-오류-처리-함수)
      - [4.9.10.1 clearerr 함수](#49101-clearerr-함수)
      - [4.9.10.2 feof 함수](#49102-feof-함수)
      - [4.9.10.3 ferror 함수](#49103-ferror-함수)
      - [4.9.10.4 perror 함수](#49104-perror-함수)
  - [4.10 일반 유틸리티 <stdlib.h>](#410-일반-유틸리티-<stdlibh>)
    - [4.10.1 문자열 변환 함수](#4101-문자열-변환-함수)
      - [4.10.1.1 atof 함수](#41011-atof-함수)
      - [4.10.1.2 atoi 함수](#41012-atoi-함수)
      - [4.10.1.3 atol 함수](#41013-atol-함수)
      - [4.10.1.4 strtod 함수](#41014-strtod-함수)
      - [4.10.1.5 strtol 함수](#41015-strtol-함수)
      - [4.10.1.6 strtoul 함수](#41016-strtoul-함수)
    - [4.10.2 의사 난수 수열 생성 함수](#4102-의사-난수-수열-생성-함수)
      - [4.10.2.1 rand 함수](#41021-rand-함수)
      - [4.10.2.2 srand 함수](#41022-srand-함수)
    - [4.10.3 메모리 관리 함수](#4103-메모리-관리-함수)
      - [4.10.3.1 calloc 함수](#41031-calloc-함수)
      - [4.10.3.2 free 함수](#41032-free-함수)
      - [4.10.3.3 malloc 함수](#41033-malloc-함수)
      - [4.10.3.4 realloc 함수](#41034-realloc-함수)
    - [4.10.4 환경과의 통신](#4104-환경과의-통신)
      - [4.10.4.1 abort 함수](#41041-abort-함수)
      - [4.10.4.2 atexit 함수](#41042-atexit-함수)
      - [4.10.4.3 exit 함수](#41043-exit-함수)
      - [4.10.4.4 getenv 함수](#41044-getenv-함수)
      - [4.10.4.5 system 함수](#41045-system-함수)
    - [4.10.5 검색 및 정렬 유틸리티](#4105-검색-및-정렬-유틸리티)
      - [4.10.5.1 bsearch 함수](#41051-bsearch-함수)
      - [4.10.5.2 qsort 함수](#41052-qsort-함수)
    - [4.10.6 정수 산술 함수](#4106-정수-산술-함수)
      - [4.10.6.1 abs 함수](#41061-abs-함수)
      - [4.10.6.2 div 함수](#41062-div-함수)
      - [4.10.6.3 labs 함수](#41063-labs-함수)
      - [4.10.6.4 ldiv 함수](#41064-ldiv-함수)
    - [4.10.7 다중 바이트 문자 함수](#4107-다중-바이트-문자-함수)
      - [4.10.7.1 mblen 함수](#41071-mblen-함수)
      - [4.10.7.2 mbtowc 함수](#41072-mbtowc-함수)
      - [4.10.7.3 wctomb 함수](#41073-wctomb-함수)
    - [4.10.8 다중 바이트 문자열 함수](#4108-다중-바이트-문자열-함수)
      - [4.10.8.1 mbstowcs 함수](#41081-mbstowcs-함수)
      - [4.10.8.2 wcstombs 함수](#41082-wcstombs-함수)
  - [4.11 문자열 처리 <string.h>](#411-문자열-처리-<stringh>)
    - [4.11.1 문자열 함수 규약](#4111-문자열-함수-규약)
    - [4.11.2 복사 함수](#4112-복사-함수)
      - [4.11.2.1 memcpy 함수](#41121-memcpy-함수)
      - [4.11.2.2 memmove 함수](#41122-memmove-함수)
      - [4.11.2.3 strcpy 함수](#41123-strcpy-함수)
      - [4.11.2.4 strncpy 함수](#41124-strncpy-함수)
    - [4.11.3 연결(이어붙이기) 함수](#4113-연결(이어붙이기)-함수)
      - [4.11.3.1 strcat 함수](#41131-strcat-함수)
      - [4.11.3.2 strncat 함수](#41132-strncat-함수)
    - [4.11.4 비교 함수](#4114-비교-함수)
      - [4.11.4.1 memcmp 함수](#41141-memcmp-함수)
      - [4.11.4.2 strcmp 함수](#41142-strcmp-함수)
      - [4.11.4.3 strcoll 함수](#41143-strcoll-함수)
      - [4.11.4.4 strncmp 함수](#41144-strncmp-함수)
      - [4.11.4.5 strxfrm 함수](#41145-strxfrm-함수)
    - [4.11.5 검색 함수](#4115-검색-함수)
      - [4.11.5.1 memchr 함수](#41151-memchr-함수)
      - [4.11.5.2 strchr 함수](#41152-strchr-함수)
      - [4.11.5.3 strcspn 함수](#41153-strcspn-함수)
      - [4.11.5.4 strpbrk 함수](#41154-strpbrk-함수)
      - [4.11.5.5 strrchr 함수](#41155-strrchr-함수)
      - [4.11.5.6 strspn 함수](#41156-strspn-함수)
      - [4.11.5.7 strstr 함수](#41157-strstr-함수)
      - [4.11.5.8 strtok 함수](#41158-strtok-함수)
    - [4.11.6 기타 함수](#4116-기타-함수)
      - [4.11.6.1 memset 함수](#41161-memset-함수)
      - [4.11.6.2 strerror 함수](#41162-strerror-함수)
      - [4.11.6.3 strlen 함수](#41163-strlen-함수)
  - [4.12 날짜와 시간 <time.h>](#412-날짜와-시간-<timeh>)
    - [4.12.1 시간의 구성 요소](#4121-시간의-구성-요소)
    - [4.12.2 시간 조작 함수](#4122-시간-조작-함수)
      - [4.12.2.1 clock 함수](#41221-clock-함수)
      - [4.12.2.2 difftime 함수](#41222-difftime-함수)
      - [4.12.2.3 mktime 함수](#41223-mktime-함수)
      - [4.12.2.4 time 함수](#41224-time-함수)
    - [4.12.3 시간 변환 함수](#4123-시간-변환-함수)
      - [4.12.3.1 asctime 함수](#41231-asctime-함수)
      - [4.12.3.2 ctime 함수](#41232-ctime-함수)
      - [4.12.3.3 gmtime 함수](#41233-gmtime-함수)
      - [4.12.3.4 localtime 함수](#41234-localtime-함수)
      - [4.12.3.5 strftime 함수](#41235-strftime-함수)
  - [4.13 향후 라이브러리 방향(future library directions)](#413-향후-라이브러리-방향(future-library-directions))
    - [4.13.1 오류 <errno.h>](#4131-오류-<errnoh>)
    - [4.13.2 문자 처리 <ctype.h>](#4132-문자-처리-<ctypeh>)
    - [4.13.3 지역화 <locale.h>](#4133-지역화-<localeh>)
    - [4.13.4 수학 <math.h>](#4134-수학-<mathh>)
    - [4.13.5 신호 처리 <signal.h>](#4135-신호-처리-<signalh>)
    - [4.13.6 입출력 <stdio.h>](#4136-입출력-<stdioh>)
    - [4.13.7 일반 유틸리티 <stdlib.h>](#4137-일반-유틸리티-<stdlibh>)
    - [4.13.8 문자열 처리 <string.h>](#4138-문자열-처리-<stringh>)
- [A. 부록](#a-부록)
  - [A.1 언어 구문 요약](#a1-언어-구문-요약)
    - [A.1.1 어휘 문법(lexical grammar)](#a11-어휘-문법(lexical-grammar))
      - [A.1.1.1 토큰(tokens)](#a111-토큰(tokens))
      - [A.1.1.2 키워드(keywords)](#a112-키워드(keywords))
      - [A.1.1.3 식별자(identifiers)](#a113-식별자(identifiers))
      - [A.1.1.4 상수(constants)](#a114-상수(constants))
      - [A.1.1.5 문자열 리터럴(string literals)](#a115-문자열-리터럴(string-literals))
      - [A.1.1.6 연산자(operators)](#a116-연산자(operators))
      - [A.1.1.7 구두점(punctuators)](#a117-구두점(punctuators))
      - [A.1.1.8 헤더 이름(header names)](#a118-헤더-이름(header-names))
      - [A.1.1.9 전처리 숫자(preprocessing numbers)](#a119-전처리-숫자(preprocessing-numbers))
    - [A.1.2 구문 구조 문법(phrase structure grammar)](#a12-구문-구조-문법(phrase-structure-grammar))
      - [A.1.2.1 식(expressions)](#a121-식(expressions))
      - [A.1.2.2 선언(declarations)](#a122-선언(declarations))
      - [A.1.2.3 문(statements)](#a123-문(statements))
      - [A.1.2.4 외부 정의(external definitions)](#a124-외부-정의(external-definitions))
    - [A.1.3 전처리 지시문(preprocessing directives)](#a13-전처리-지시문(preprocessing-directives))
  - [A.2 순서점(sequence points)](#a2-순서점(sequence-points))
  - [A.3 라이브러리 요약](#a3-라이브러리-요약)
    - [A.3.1 오류 <errno.h>](#a31-오류-<errnoh>)
    - [A.3.2 공통 정의 <stddef.h>](#a32-공통-정의-<stddefh>)
    - [A.3.3 진단 <assert.h>](#a33-진단-<asserth>)
    - [A.3.4 문자 처리 <ctype.h>](#a34-문자-처리-<ctypeh>)
    - [A.3.5 지역화 <locale.h>](#a35-지역화-<localeh>)
    - [A.3.6 수학 <math.h>](#a36-수학-<mathh>)
    - [A.3.7 비지역 점프 <setjmp.h>](#a37-비지역-점프-<setjmph>)
    - [A.3.8 신호 처리 <signal.h>](#a38-신호-처리-<signalh>)
    - [A.3.9 가변 인자 <stdarg.h>](#a39-가변-인자-<stdargh>)
    - [A.3.10 입출력 <stdio.h>](#a310-입출력-<stdioh>)
    - [A.3.11 일반 유틸리티 <stdlib.h>](#a311-일반-유틸리티-<stdlibh>)
    - [A.3.12 문자열 처리 <string.h>](#a312-문자열-처리-<stringh>)
    - [A.3.13 날짜와 시간 <time.h>](#a313-날짜와-시간-<timeh>)
  - [A.4 구현 한계(implementation limits)](#a4-구현-한계(implementation-limits))
  - [A.5 공통 경고(common warnings)](#a5-공통-경고(common-warnings))
  - [A.6 이식성 문제(portability issues)](#a6-이식성-문제(portability-issues))
    - [A.6.1 미지정 동작(unspecified behavior)](#a61-미지정-동작(unspecified-behavior))
    - [A.6.2 정의되지 않은 동작(undefined behavior)](#a62-정의되지-않은-동작(undefined-behavior))
    - [A.6.3 구현 정의 동작(implementation-defined behavior)](#a63-구현-정의-동작(implementation-defined-behavior))
      - [A.6.3.1 환경(environment)](#a631-환경(environment))
      - [A.6.3.2 식별자(identifiers)](#a632-식별자(identifiers))
      - [A.6.3.3 문자(characters)](#a633-문자(characters))
      - [A.6.3.4 정수(integers)](#a634-정수(integers))
      - [A.6.3.5 부동소수점(floating point)](#a635-부동소수점(floating-point))
      - [A.6.3.6 배열과 포인터(arrays and pointers)](#a636-배열과-포인터(arrays-and-pointers))
      - [A.6.3.7 레지스터(registers)](#a637-레지스터(registers))
      - [A.6.3.8 구조체, 공용체, 열거형, 비트 필드(structures, unions, enumerations, and bit-fields)](#a638-구조체,-공용체,-열거형,-비트-필드(structures,-unions,-enumerations,-and-bit-fields))
      - [A.6.3.9 한정자(qualifiers)](#a639-한정자(qualifiers))
      - [A.6.3.10 선언자(declarators)](#a6310-선언자(declarators))
      - [A.6.3.11 문(statements)](#a6311-문(statements))
      - [A.6.3.12 전처리 지시문(preprocessing directives)](#a6312-전처리-지시문(preprocessing-directives))
      - [A.6.3.13 라이브러리 함수(library functions)](#a6313-라이브러리-함수(library-functions))
    - [A.6.4 로캘 특유 동작(locale-specific behavior)](#a64-로캘-특유-동작(locale-specific-behavior))
    - [A.6.5 일반적인 확장(common extensions)](#a65-일반적인-확장(common-extensions))
      - [A.6.5.1 환경 인자(environment arguments)](#a651-환경-인자(environment-arguments))
      - [A.6.5.2 특수 식별자(specialized identifiers)](#a652-특수-식별자(specialized-identifiers))
      - [A.6.5.3 식별자의 길이와 대/소문자(lengths and cases of identifiers)](#a653-식별자의-길이와-대/소문자(lengths-and-cases-of-identifiers))
      - [A.6.5.4 식별자의 범위(scopes of identifiers)](#a654-식별자의-범위(scopes-of-identifiers))
      - [A.6.5.5 쓰기 가능한 문자열 리터럴(writable string literals)](#a655-쓰기-가능한-문자열-리터럴(writable-string-literals))
      - [A.6.5.6 기타 산술 형(other arithmetic types)](#a656-기타-산술-형(other-arithmetic-types))
      - [A.6.5.7 함수 포인터 형변환(function pointer casts)](#a657-함수-포인터-형변환(function-pointer-casts))
      - [A.6.5.8 int가 아닌 비트 필드 형(non-int bit-field types)](#a658-int가-아닌-비트-필드-형(non-int-bit-field-types))
      - [A.6.5.9 fortran 키워드](#a659-fortran-키워드)
      - [A.6.5.10 asm 키워드](#a6510-asm-키워드)
      - [A.6.5.11 다중 외부 정의(multiple external definitions)](#a6511-다중-외부-정의(multiple-external-definitions))
      - [A.6.5.12 빈 매크로 인자(empty macro arguments)](#a6512-빈-매크로-인자(empty-macro-arguments))
      - [A.6.5.13 미리 정의된 매크로 이름(predefined macro names)](#a6513-미리-정의된-매크로-이름(predefined-macro-names))
      - [A.6.5.14 신호 처리기에 대한 추가 인자(extra arguments for signal handlers)](#a6514-신호-처리기에-대한-추가-인자(extra-arguments-for-signal-handlers))
      - [A.6.5.15 추가 스트림 유형 및 파일 열기 모드(additional stream types and file-opening modes)](#a6515-추가-스트림-유형-및-파일-열기-모드(additional-stream-types-and-file-opening-modes))
      - [A.6.5.16 정의된 파일 위치 지시자(defined file position indicator)](#a6516-정의된-파일-위치-지시자(defined-file-position-indicator))
  - [A.7 색인(index)](#a7-색인(index))

## 1. 서론

### 1.1 목적

### 1.2 적용 범위

### 1.3 참조

### 1.4 문서 구성

### 1.5 기본 문서

### 1.6 용어 정의

### 1.7 적합성(준수)

### 1.8 향후 방향

### 1.9 이 초안에 대하여

## 2. 환경

### 2.1 개념적 모델

#### 2.1.1 번역 환경

##### 2.1.1.1 프로그램 구조

##### 2.1.1.2 번역 단계

##### 2.1.1.3 진단

#### 2.1.2 실행 환경

##### 2.1.2.1 프리스탠딩(freestanding) 환경

##### 2.1.2.2 호스티드(hosted) 환경

##### 2.1.2.3 프로그램 실행

### 2.2 환경적 고려사항

#### 2.2.1 문자 집합

##### 2.2.1.1 트라이그래프(trigraph) 시퀀스

##### 2.2.1.2 다중 바이트 문자

#### 2.2.2 문자 표시 의미

#### 2.2.3 신호와 인터럽트

#### 2.2.4 환경 한계

##### 2.2.4.1 번역 한계

##### 2.2.4.2 수치 한계

## 3. 언어

### 3.1 어휘 요소

#### 3.1.1 키워드

#### 3.1.2 식별자

##### 3.1.2.1 식별자의 범위

##### 3.1.2.2 식별자의 연결(linkage)

##### 3.1.2.3 식별자의 이름 공간(name space)

##### 3.1.2.4 객체의 저장 기간(storage duration)

##### 3.1.2.5 형(type)

##### 3.1.2.6 호환 가능한 형과 합성 형(composite type)

#### 3.1.3 상수

##### 3.1.3.1 부동소수점 상수

##### 3.1.3.2 정수 상수

##### 3.1.3.3 열거 상수

##### 3.1.3.4 문자 상수

#### 3.1.4 문자열 리터럴

#### 3.1.5 연산자

#### 3.1.6 구두점(punctuators)

#### 3.1.7 헤더 이름

#### 3.1.8 전처리 숫자(preprocessing numbers)

#### 3.1.9 주석

### 3.2 변환

#### 3.2.1 산술 피연산자

##### 3.2.1.1 문자와 정수

##### 3.2.1.2 부호 있는 정수와 부호 없는 정수

##### 3.2.1.3 부동소수점과 정수형

##### 3.2.1.4 부동소수점 형

##### 3.2.1.5 통상적인 산술 변환

#### 3.2.2 그 밖의 피연산자

##### 3.2.2.1 좌값(lvalue)과 함수 지정자(function designators)

##### 3.2.2.2 void

##### 3.2.2.3 포인터

### 3.3 식(expressions)

#### 3.3.1 기본 식(primary expressions)

#### 3.3.2 후위 연산자(postfix operators)

##### 3.3.2.1 배열 첨자 지정(array subscripting)

##### 3.3.2.2 함수 호출

##### 3.3.2.3 구조체 및 공용체 멤버

##### 3.3.2.4 후위 증가 및 감소 연산자

#### 3.3.3 단항 연산자(unary operators)

##### 3.3.3.1 전위 증가 및 감소 연산자

##### 3.3.3.2 주소 및 간접 참조 연산자

##### 3.3.3.3 단항 산술 연산자

##### 3.3.3.4 sizeof 연산자

#### 3.3.4 형변환(cast) 연산자

#### 3.3.5 승법(multiplicative) 연산자

#### 3.3.6 가법(additive) 연산자

#### 3.3.7 비트 시프트(shift) 연산자

#### 3.3.8 관계(relational) 연산자

#### 3.3.9 등가(equality) 연산자

#### 3.3.10 비트 AND 연산자

#### 3.3.11 비트 배타적 OR(exclusive OR) 연산자

#### 3.3.12 비트 포함 OR(inclusive OR) 연산자

#### 3.3.13 논리 AND 연산자

#### 3.3.14 논리 OR 연산자

#### 3.3.15 조건(conditional) 연산자

#### 3.3.16 대입(assignment) 연산자

##### 3.3.16.1 단순 대입

##### 3.3.16.2 복합 대입

#### 3.3.17 쉼표(comma) 연산자

### 3.4 상수식(constant expressions)

### 3.5 선언(declarations)

#### 3.5.1 저장 클래스(storage-class) 지정자

#### 3.5.2 형(type) 지정자

##### 3.5.2.1 구조체 및 공용체 지정자

##### 3.5.2.2 열거(enumeration) 지정자

##### 3.5.2.3 태그(tags)

#### 3.5.3 형 한정자(type qualifiers)

#### 3.5.4 선언자(declarators)

##### 3.5.4.1 포인터 선언자

##### 3.5.4.2 배열 선언자

##### 3.5.4.3 함수 선언자(프로토타입 포함)

#### 3.5.5 형 이름(type names)

#### 3.5.6 형 정의(type definitions)

#### 3.5.7 초기화(initialization)

### 3.6 문(statements)

#### 3.6.1 레이블 문(labeled statements)

#### 3.6.2 복합문(compound statement), 또는 블록(block)

#### 3.6.3 식문(expression statements)과 널(null) 문

#### 3.6.4 선택 문(selection statements)

##### 3.6.4.1 if 문

##### 3.6.4.2 switch 문

#### 3.6.5 반복 문(iteration statements)

##### 3.6.5.1 while 문

##### 3.6.5.2 do 문

##### 3.6.5.3 for 문

#### 3.6.6 점프 문(jump statements)

##### 3.6.6.1 goto 문

##### 3.6.6.2 continue 문

##### 3.6.6.3 break 문

##### 3.6.6.4 return 문

### 3.7 외부 정의(external definitions)

#### 3.7.1 함수 정의(function definitions)

#### 3.7.2 외부 객체 정의(external object definitions)

### 3.8 전처리 지시문(preprocessing directives)

#### 3.8.1 조건부 포함(conditional inclusion)

#### 3.8.2 소스 파일 포함(source file inclusion)

#### 3.8.3 매크로 치환(macro replacement)

##### 3.8.3.1 인자 치환(argument substitution)

##### 3.8.3.2 # 연산자

##### 3.8.3.3 ## 연산자

##### 3.8.3.4 재스캔(rescanning) 및 추가 치환

##### 3.8.3.5 매크로 정의의 범위(scope)

#### 3.8.4 행(line) 제어

#### 3.8.5 오류(error) 지시문

#### 3.8.6 pragma 지시문

#### 3.8.7 널(null) 지시문

#### 3.8.8 미리 정의된 매크로 이름(predefined macro names)

### 3.9 향후 언어 방향(future language directions)

#### 3.9.1 외부 이름(external names)

#### 3.9.2 문자 이스케이프 시퀀스(character escape sequences)

#### 3.9.3 저장 클래스 지정자(storage-class specifiers)

#### 3.9.4 함수 선언자(function declarators)

#### 3.9.5 함수 정의(function definitions)

## 4. 라이브러리

### 4.1 개요

#### 4.1.1 용어 정의

#### 4.1.2 표준 헤더

#### 4.1.3 오류 <errno.h>

#### 4.1.4 한계 <float.h> 및 <limits.h>

#### 4.1.5 공통 정의 <stddef.h>

#### 4.1.6 라이브러리 함수 사용

### 4.2 진단 <assert.h>

#### 4.2.1 프로그램 진단

##### 4.2.1.1 assert 매크로

### 4.3 문자 처리 <ctype.h>

#### 4.3.1 문자 검사 함수

##### 4.3.1.1 isalnum 함수

##### 4.3.1.2 isalpha 함수

##### 4.3.1.3 iscntrl 함수

##### 4.3.1.4 isdigit 함수

##### 4.3.1.5 isgraph 함수

##### 4.3.1.6 islower 함수

##### 4.3.1.7 isprint 함수

##### 4.3.1.8 ispunct 함수

##### 4.3.1.9 isspace 함수

##### 4.3.1.10 isupper 함수

##### 4.3.1.11 isxdigit 함수

#### 4.3.2 문자 대소문자 매핑 함수

##### 4.3.2.1 tolower 함수

##### 4.3.2.2 toupper 함수

### 4.4 지역화 <locale.h>

#### 4.4.1 로캘(locale) 제어

##### 4.4.1.1 setlocale 함수

#### 4.4.2 숫자 서식 관례 조회

##### 4.4.2.1 localeconv 함수

### 4.5 수학 <math.h>

#### 4.5.1 오류 조건 처리

#### 4.5.2 삼각 함수

##### 4.5.2.1 acos 함수

##### 4.5.2.2 asin 함수

##### 4.5.2.3 atan 함수

##### 4.5.2.4 atan2 함수

##### 4.5.2.5 cos 함수

##### 4.5.2.6 sin 함수

##### 4.5.2.7 tan 함수

#### 4.5.3 쌍곡 함수

##### 4.5.3.1 cosh 함수

##### 4.5.3.2 sinh 함수

##### 4.5.3.3 tanh 함수

#### 4.5.4 지수 및 로그 함수

##### 4.5.4.1 exp 함수

##### 4.5.4.2 frexp 함수

##### 4.5.4.3 ldexp 함수

##### 4.5.4.4 log 함수

##### 4.5.4.5 log10 함수

##### 4.5.4.6 modf 함수

#### 4.5.5 거듭제곱 함수

##### 4.5.5.1 pow 함수

##### 4.5.5.2 sqrt 함수

#### 4.5.6 가장 가까운 정수, 절댓값, 나머지 함수

##### 4.5.6.1 ceil 함수

##### 4.5.6.2 fabs 함수

##### 4.5.6.3 floor 함수

##### 4.5.6.4 fmod 함수

### 4.6 비지역 점프(non-local jumps) <setjmp.h>

#### 4.6.1 호출 환경 저장

##### 4.6.1.1 setjmp 매크로

#### 4.6.2 호출 환경 복원

##### 4.6.2.1 longjmp 함수

### 4.7 신호 처리 <signal.h>

#### 4.7.1 신호 처리 지정

##### 4.7.1.1 signal 함수

#### 4.7.2 신호 전송

##### 4.7.2.1 raise 함수

### 4.8 가변 인자(variable arguments) <stdarg.h>

#### 4.8.1 가변 인자 리스트 접근 매크로

##### 4.8.1.1 va_start 매크로

##### 4.8.1.2 va_arg 매크로

##### 4.8.1.3 va_end 매크로

### 4.9 입출력 <stdio.h>

#### 4.9.1 개요

#### 4.9.2 스트림(streams)

#### 4.9.3 파일(files)

#### 4.9.4 파일에 대한 연산(operations on files)

##### 4.9.4.1 remove 함수

##### 4.9.4.2 rename 함수

##### 4.9.4.3 tmpfile 함수

##### 4.9.4.4 tmpnam 함수

#### 4.9.5 파일 접근 함수

##### 4.9.5.1 fclose 함수

##### 4.9.5.2 fflush 함수

##### 4.9.5.3 fopen 함수

##### 4.9.5.4 freopen 함수

##### 4.9.5.5 setbuf 함수

##### 4.9.5.6 setvbuf 함수

#### 4.9.6 형식 지정 입출력 함수

##### 4.9.6.1 fprintf 함수

##### 4.9.6.2 fscanf 함수

##### 4.9.6.3 printf 함수

##### 4.9.6.4 scanf 함수

##### 4.9.6.5 sprintf 함수

##### 4.9.6.6 sscanf 함수

##### 4.9.6.7 vfprintf 함수

##### 4.9.6.8 vprintf 함수

##### 4.9.6.9 vsprintf 함수

#### 4.9.7 문자 입출력 함수

##### 4.9.7.1 fgetc 함수

##### 4.9.7.2 fgets 함수

##### 4.9.7.3 fputc 함수

##### 4.9.7.4 fputs 함수

##### 4.9.7.5 getc 함수

##### 4.9.7.6 getchar 함수

##### 4.9.7.7 gets 함수

##### 4.9.7.8 putc 함수

##### 4.9.7.9 putchar 함수

##### 4.9.7.10 puts 함수

##### 4.9.7.11 ungetc 함수

#### 4.9.8 직접 입출력 함수

##### 4.9.8.1 fread 함수

##### 4.9.8.2 fwrite 함수

#### 4.9.9 파일 위치 지정 함수

##### 4.9.9.1 fgetpos 함수

##### 4.9.9.2 fseek 함수

##### 4.9.9.3 fsetpos 함수

##### 4.9.9.4 ftell 함수

##### 4.9.9.5 rewind 함수

#### 4.9.10 오류 처리 함수

##### 4.9.10.1 clearerr 함수

##### 4.9.10.2 feof 함수

##### 4.9.10.3 ferror 함수

##### 4.9.10.4 perror 함수

### 4.10 일반 유틸리티 <stdlib.h>

#### 4.10.1 문자열 변환 함수

##### 4.10.1.1 atof 함수

##### 4.10.1.2 atoi 함수

##### 4.10.1.3 atol 함수

##### 4.10.1.4 strtod 함수

##### 4.10.1.5 strtol 함수

##### 4.10.1.6 strtoul 함수

#### 4.10.2 의사 난수 수열 생성 함수

##### 4.10.2.1 rand 함수

##### 4.10.2.2 srand 함수

#### 4.10.3 메모리 관리 함수

##### 4.10.3.1 calloc 함수

##### 4.10.3.2 free 함수

##### 4.10.3.3 malloc 함수

##### 4.10.3.4 realloc 함수

#### 4.10.4 환경과의 통신

##### 4.10.4.1 abort 함수

##### 4.10.4.2 atexit 함수

##### 4.10.4.3 exit 함수

##### 4.10.4.4 getenv 함수

##### 4.10.4.5 system 함수

#### 4.10.5 검색 및 정렬 유틸리티

##### 4.10.5.1 bsearch 함수

##### 4.10.5.2 qsort 함수

#### 4.10.6 정수 산술 함수

##### 4.10.6.1 abs 함수

##### 4.10.6.2 div 함수

##### 4.10.6.3 labs 함수

##### 4.10.6.4 ldiv 함수

#### 4.10.7 다중 바이트 문자 함수

##### 4.10.7.1 mblen 함수

##### 4.10.7.2 mbtowc 함수

##### 4.10.7.3 wctomb 함수

#### 4.10.8 다중 바이트 문자열 함수

##### 4.10.8.1 mbstowcs 함수

##### 4.10.8.2 wcstombs 함수

### 4.11 문자열 처리 <string.h>

#### 4.11.1 문자열 함수 규약

#### 4.11.2 복사 함수

##### 4.11.2.1 memcpy 함수

##### 4.11.2.2 memmove 함수

##### 4.11.2.3 strcpy 함수

##### 4.11.2.4 strncpy 함수

#### 4.11.3 연결(이어붙이기) 함수

##### 4.11.3.1 strcat 함수

##### 4.11.3.2 strncat 함수

#### 4.11.4 비교 함수

##### 4.11.4.1 memcmp 함수

##### 4.11.4.2 strcmp 함수

##### 4.11.4.3 strcoll 함수

##### 4.11.4.4 strncmp 함수

##### 4.11.4.5 strxfrm 함수

#### 4.11.5 검색 함수

##### 4.11.5.1 memchr 함수

##### 4.11.5.2 strchr 함수

##### 4.11.5.3 strcspn 함수

##### 4.11.5.4 strpbrk 함수

##### 4.11.5.5 strrchr 함수

##### 4.11.5.6 strspn 함수

##### 4.11.5.7 strstr 함수

##### 4.11.5.8 strtok 함수

#### 4.11.6 기타 함수

##### 4.11.6.1 memset 함수

##### 4.11.6.2 strerror 함수

##### 4.11.6.3 strlen 함수

### 4.12 날짜와 시간 <time.h>

#### 4.12.1 시간의 구성 요소

#### 4.12.2 시간 조작 함수

##### 4.12.2.1 clock 함수

##### 4.12.2.2 difftime 함수

##### 4.12.2.3 mktime 함수

##### 4.12.2.4 time 함수

#### 4.12.3 시간 변환 함수

##### 4.12.3.1 asctime 함수

##### 4.12.3.2 ctime 함수

##### 4.12.3.3 gmtime 함수

##### 4.12.3.4 localtime 함수

##### 4.12.3.5 strftime 함수

### 4.13 향후 라이브러리 방향(future library directions)

#### 4.13.1 오류 <errno.h>

#### 4.13.2 문자 처리 <ctype.h>

#### 4.13.3 지역화 <locale.h>

#### 4.13.4 수학 <math.h>

#### 4.13.5 신호 처리 <signal.h>

#### 4.13.6 입출력 <stdio.h>

#### 4.13.7 일반 유틸리티 <stdlib.h>

#### 4.13.8 문자열 처리 <string.h>

## A. 부록

### A.1 언어 구문 요약

#### A.1.1 어휘 문법(lexical grammar)

##### A.1.1.1 토큰(tokens)

##### A.1.1.2 키워드(keywords)

##### A.1.1.3 식별자(identifiers)

##### A.1.1.4 상수(constants)

##### A.1.1.5 문자열 리터럴(string literals)

##### A.1.1.6 연산자(operators)

##### A.1.1.7 구두점(punctuators)

##### A.1.1.8 헤더 이름(header names)

##### A.1.1.9 전처리 숫자(preprocessing numbers)

#### A.1.2 구문 구조 문법(phrase structure grammar)

##### A.1.2.1 식(expressions)

##### A.1.2.2 선언(declarations)

##### A.1.2.3 문(statements)

##### A.1.2.4 외부 정의(external definitions)

#### A.1.3 전처리 지시문(preprocessing directives)

### A.2 순서점(sequence points)

### A.3 라이브러리 요약

#### A.3.1 오류 <errno.h>

#### A.3.2 공통 정의 <stddef.h>

#### A.3.3 진단 <assert.h>

#### A.3.4 문자 처리 <ctype.h>

#### A.3.5 지역화 <locale.h>

#### A.3.6 수학 <math.h>

#### A.3.7 비지역 점프 <setjmp.h>

#### A.3.8 신호 처리 <signal.h>

#### A.3.9 가변 인자 <stdarg.h>

#### A.3.10 입출력 <stdio.h>

#### A.3.11 일반 유틸리티 <stdlib.h>

#### A.3.12 문자열 처리 <string.h>

#### A.3.13 날짜와 시간 <time.h>

### A.4 구현 한계(implementation limits)

### A.5 공통 경고(common warnings)

### A.6 이식성 문제(portability issues)

#### A.6.1 미지정 동작(unspecified behavior)

#### A.6.2 정의되지 않은 동작(undefined behavior)

#### A.6.3 구현 정의 동작(implementation-defined behavior)

##### A.6.3.1 환경(environment)

##### A.6.3.2 식별자(identifiers)

##### A.6.3.3 문자(characters)

##### A.6.3.4 정수(integers)

##### A.6.3.5 부동소수점(floating point)

##### A.6.3.6 배열과 포인터(arrays and pointers)

##### A.6.3.7 레지스터(registers)

##### A.6.3.8 구조체, 공용체, 열거형, 비트 필드(structures, unions, enumerations, and bit-fields)

##### A.6.3.9 한정자(qualifiers)

##### A.6.3.10 선언자(declarators)

##### A.6.3.11 문(statements)

##### A.6.3.12 전처리 지시문(preprocessing directives)

##### A.6.3.13 라이브러리 함수(library functions)

#### A.6.4 로캘 특유 동작(locale-specific behavior)

#### A.6.5 일반적인 확장(common extensions)

##### A.6.5.1 환경 인자(environment arguments)

##### A.6.5.2 특수 식별자(specialized identifiers)

##### A.6.5.3 식별자의 길이와 대/소문자(lengths and cases of identifiers)

##### A.6.5.4 식별자의 범위(scopes of identifiers)

##### A.6.5.5 쓰기 가능한 문자열 리터럴(writable string literals)

##### A.6.5.6 기타 산술 형(other arithmetic types)

##### A.6.5.7 함수 포인터 형변환(function pointer casts)

##### A.6.5.8 int가 아닌 비트 필드 형(non-int bit-field types)

##### A.6.5.9 fortran 키워드

##### A.6.5.10 asm 키워드

##### A.6.5.11 다중 외부 정의(multiple external definitions)

##### A.6.5.12 빈 매크로 인자(empty macro arguments)

##### A.6.5.13 미리 정의된 매크로 이름(predefined macro names)

##### A.6.5.14 신호 처리기에 대한 추가 인자(extra arguments for signal handlers)

##### A.6.5.15 추가 스트림 유형 및 파일 열기 모드(additional stream types and file-opening modes)

##### A.6.5.16 정의된 파일 위치 지시자(defined file position indicator)

### A.7 색인(index)
