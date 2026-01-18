- [1. INTRODUCTION](#1-introduction)
  - [1.1 PURPOSE](#11-purpose)
  - [1.2 SCOPE](#12-scope)
  - [1.3 REFERENCES](#13-references)
  - [1.4 ORGANIZATION OF THE DOCUMENT](#14-organization-of-the-document)
  - [1.5 BASE DOCUMENTS](#15-base-documents)
  - [1.6 DEFINITIONS OF TERMS](#16-definitions-of-terms)
  - [1.7 COMPLIANCE](#17-compliance)
  - [1.8 FUTURE DIRECTIONS](#18-future-directions)
  - [1.9 ABOUT THIS DRAFT](#19-about-this-draft)
- [2. ENVIRONMENT](#2-environment)
  - [2.1 CONCEPTUAL MODELS](#21-conceptual-models)
    - [2.1.1 Translation environment](#211-translation-environment)
      - [2.1.1.1 Program structure](#2111-program-structure)
      - [2.1.1.2 Translation phases](#2112-translation-phases)
      - [2.1.1.3 Diagnostics](#2113-diagnostics)
    - [2.1.2 Execution environments](#212-execution-environments)
      - [2.1.2.1 Freestanding environment](#2121-freestanding-environment)
      - [2.1.2.2 Hosted environment](#2122-hosted-environment)
      - [2.1.2.3 Program execution](#2123-program-execution)
  - [2.2 ENVIRONMENTAL CONSIDERATIONS](#22-environmental-considerations)
    - [2.2.1 Character sets](#221-character-sets)
      - [2.2.1.1 Trigraph sequences](#2211-trigraph-sequences)
      - [2.2.1.2 Multibyte characters](#2212-multibyte-characters)
    - [2.2.2 Character display semantics](#222-character-display-semantics)
    - [2.2.3 Signals and interrupts](#223-signals-and-interrupts)
    - [2.2.4 Environmental limits](#224-environmental-limits)
      - [2.2.4.1 Translation limits](#2241-translation-limits)
      - [2.2.4.2 Numerical limits](#2242-numerical-limits)
- [3. LANGUAGE](#3-language)
  - [3.1 LEXICAL ELEMENTS](#31-lexical-elements)
    - [3.1.1 Keywords](#311-keywords)
    - [3.1.2 Identifiers](#312-identifiers)
      - [3.1.2.1 Scopes of identifiers](#3121-scopes-of-identifiers)
      - [3.1.2.2 Linkages of identifiers](#3122-linkages-of-identifiers)
      - [3.1.2.3 Name spaces of identifiers](#3123-name-spaces-of-identifiers)
      - [3.1.2.4 Storage durations of objects](#3124-storage-durations-of-objects)
      - [3.1.2.5 Types](#3125-types)
      - [3.1.2.6 Compatible type and composite type](#3126-compatible-type-and-composite-type)
    - [3.1.3 Constants](#313-constants)
      - [3.1.3.1 Floating constants](#3131-floating-constants)
      - [3.1.3.2 Integer constants](#3132-integer-constants)
      - [3.1.3.3 Enumeration constants](#3133-enumeration-constants)
      - [3.1.3.4 Character constants](#3134-character-constants)
    - [3.1.4 String literals](#314-string-literals)
    - [3.1.5 Operators](#315-operators)
    - [3.1.6 Punctuators](#316-punctuators)
    - [3.1.7 Header names](#317-header-names)
    - [3.1.8 Preprocessing numbers](#318-preprocessing-numbers)
    - [3.1.9 Comments](#319-comments)
  - [3.2 CONVERSIONS](#32-conversions)
    - [3.2.1 Arithmetic operands](#321-arithmetic-operands)
      - [3.2.1.1 Characters and integers](#3211-characters-and-integers)
      - [3.2.1.2 Signed and unsigned integers](#3212-signed-and-unsigned-integers)
      - [3.2.1.3 Floating and integral](#3213-floating-and-integral)
      - [3.2.1.4 Floating types](#3214-floating-types)
      - [3.2.1.5 Usual arithmetic conversions](#3215-usual-arithmetic-conversions)
    - [3.2.2 Other operands](#322-other-operands)
      - [3.2.2.1 Lvalues and function designators](#3221-lvalues-and-function-designators)
      - [3.2.2.2 void](#3222-void)
      - [3.2.2.3 Pointers](#3223-pointers)
  - [3.3 EXPRESSIONS](#33-expressions)
    - [3.3.1 Primary expressions](#331-primary-expressions)
    - [3.3.2 Postfix operators](#332-postfix-operators)
      - [3.3.2.1 Array subscripting](#3321-array-subscripting)
      - [3.3.2.2 Function calls](#3322-function-calls)
      - [3.3.2.3 Structure and union members](#3323-structure-and-union-members)
      - [3.3.2.4 Postfix increment and decrement operators](#3324-postfix-increment-and-decrement-operators)
    - [3.3.3 Unary operators](#333-unary-operators)
      - [3.3.3.1 Prefix increment and decrement operators](#3331-prefix-increment-and-decrement-operators)
      - [3.3.3.2 Address and indirection operators](#3332-address-and-indirection-operators)
      - [3.3.3.3 Unary arithmetic operators](#3333-unary-arithmetic-operators)
      - [3.3.3.4 The sizeof operator](#3334-the-sizeof-operator)
    - [3.3.4 Cast operators](#334-cast-operators)
    - [3.3.5 Multiplicative operators](#335-multiplicative-operators)
    - [3.3.6 Additive operators](#336-additive-operators)
    - [3.3.7 Bitwise shift operators](#337-bitwise-shift-operators)
    - [3.3.8 Relational operators](#338-relational-operators)
    - [3.3.9 Equality operators](#339-equality-operators)
    - [3.3.10 Bitwise AND operator](#3310-bitwise-and-operator)
    - [3.3.11 Bitwise exclusive OR operator](#3311-bitwise-exclusive-or-operator)
    - [3.3.12 Bitwise inclusive OR operator](#3312-bitwise-inclusive-or-operator)
    - [3.3.13 Logical AND operator](#3313-logical-and-operator)
    - [3.3.14 Logical OR operator](#3314-logical-or-operator)
    - [3.3.15 Conditional operator](#3315-conditional-operator)
    - [3.3.16 Assignment operators](#3316-assignment-operators)
      - [3.3.16.1 Simple assignment](#33161-simple-assignment)
      - [3.3.16.2 Compound assignment](#33162-compound-assignment)
    - [3.3.17 Comma operator](#3317-comma-operator)
  - [3.4 CONSTANT EXPRESSIONS](#34-constant-expressions)
  - [3.5 DECLARATIONS](#35-declarations)
    - [3.5.1 Storage-class specifiers](#351-storage-class-specifiers)
    - [3.5.2 Type specifiers](#352-type-specifiers)
      - [3.5.2.1 Structure and union specifiers](#3521-structure-and-union-specifiers)
      - [3.5.2.2 Enumeration specifiers](#3522-enumeration-specifiers)
      - [3.5.2.3 Tags](#3523-tags)
    - [3.5.3 Type qualifiers](#353-type-qualifiers)
    - [3.5.4 Declarators](#354-declarators)
      - [3.5.4.1 Pointer declarators](#3541-pointer-declarators)
      - [3.5.4.2 Array declarators](#3542-array-declarators)
      - [3.5.4.3 Function declarators (including prototypes)](#3543-function-declarators-(including-prototypes))
    - [3.5.5 Type names](#355-type-names)
    - [3.5.6 Type definitions](#356-type-definitions)
    - [3.5.7 Initialization](#357-initialization)
  - [3.6 STATEMENTS](#36-statements)
    - [3.6.1 Labeled statements](#361-labeled-statements)
    - [3.6.2 Compound statement, or block](#362-compound-statement,-or-block)
    - [3.6.3 Expression and null statements](#363-expression-and-null-statements)
    - [3.6.4 Selection statements](#364-selection-statements)
      - [3.6.4.1 The if statement](#3641-the-if-statement)
      - [3.6.4.2 The switch statement](#3642-the-switch-statement)
    - [3.6.5 Iteration statements](#365-iteration-statements)
      - [3.6.5.1 The while statement](#3651-the-while-statement)
      - [3.6.5.2 The do statement](#3652-the-do-statement)
      - [3.6.5.3 The for statement](#3653-the-for-statement)
    - [3.6.6 Jump statements](#366-jump-statements)
      - [3.6.6.1 The goto statement](#3661-the-goto-statement)
      - [3.6.6.2 The continue statement](#3662-the-continue-statement)
      - [3.6.6.3 The break statement](#3663-the-break-statement)
      - [3.6.6.4 The return statement](#3664-the-return-statement)
  - [3.7 EXTERNAL DEFINITIONS](#37-external-definitions)
    - [3.7.1 Function definitions](#371-function-definitions)
    - [3.7.2 External object definitions](#372-external-object-definitions)
  - [3.8 PREPROCESSING DIRECTIVES](#38-preprocessing-directives)
    - [3.8.1 Conditional inclusion](#381-conditional-inclusion)
    - [3.8.2 Source file inclusion](#382-source-file-inclusion)
    - [3.8.3 Macro replacement](#383-macro-replacement)
      - [3.8.3.1 Argument substitution](#3831-argument-substitution)
      - [3.8.3.2 The # operator](#3832-the-#-operator)
      - [3.8.3.3 The ## operator](#3833-the-##-operator)
      - [3.8.3.4 Rescanning and further replacement](#3834-rescanning-and-further-replacement)
      - [3.8.3.5 Scope of macro definitions](#3835-scope-of-macro-definitions)
    - [3.8.4 Line control](#384-line-control)
    - [3.8.5 Error directive](#385-error-directive)
    - [3.8.6 Pragma directive](#386-pragma-directive)
    - [3.8.7 Null directive](#387-null-directive)
    - [3.8.8 Predefined macro names](#388-predefined-macro-names)
  - [3.9 FUTURE LANGUAGE DIRECTIONS](#39-future-language-directions)
    - [3.9.1 External names](#391-external-names)
    - [3.9.2 Character escape sequences](#392-character-escape-sequences)
    - [3.9.3 Storage-class specifiers](#393-storage-class-specifiers)
    - [3.9.4 Function declarators](#394-function-declarators)
    - [3.9.5 Function definitions](#395-function-definitions)
- [4. LIBRARY](#4-library)
  - [4.1 INTRODUCTION](#41-introduction)
    - [4.1.1 Definitions of terms](#411-definitions-of-terms)
    - [4.1.2 Standard headers](#412-standard-headers)
    - [4.1.3 Errors <errno.h>](#413-errors-<errnoh>)
    - [4.1.4 Limits <float.h> and <limits.h>](#414-limits-<floath>-and-<limitsh>)
    - [4.1.5 Common definitions <stddef.h>](#415-common-definitions-<stddefh>)
    - [4.1.6 Use of library functions](#416-use-of-library-functions)
  - [4.2 DIAGNOSTICS <assert.h>](#42-diagnostics-<asserth>)
    - [4.2.1 Program diagnostics](#421-program-diagnostics)
      - [4.2.1.1 The assert macro](#4211-the-assert-macro)
  - [4.3 CHARACTER HANDLING <ctype.h>](#43-character-handling-<ctypeh>)
    - [4.3.1 Character testing functions](#431-character-testing-functions)
      - [4.3.1.1 The isalnum function](#4311-the-isalnum-function)
      - [4.3.1.2 The isalpha function](#4312-the-isalpha-function)
      - [4.3.1.3 The iscntrl function](#4313-the-iscntrl-function)
      - [4.3.1.4 The isdigit function](#4314-the-isdigit-function)
      - [4.3.1.5 The isgraph function](#4315-the-isgraph-function)
      - [4.3.1.6 The islower function](#4316-the-islower-function)
      - [4.3.1.7 The isprint function](#4317-the-isprint-function)
      - [4.3.1.8 The ispunct function](#4318-the-ispunct-function)
      - [4.3.1.9 The isspace function](#4319-the-isspace-function)
      - [4.3.1.10 The isupper function](#43110-the-isupper-function)
      - [4.3.1.11 The isxdigit function](#43111-the-isxdigit-function)
    - [4.3.2 Character case mapping functions](#432-character-case-mapping-functions)
      - [4.3.2.1 The tolower function](#4321-the-tolower-function)
      - [4.3.2.2 The toupper function](#4322-the-toupper-function)
  - [4.4 LOCALIZATION <locale.h>](#44-localization-<localeh>)
    - [4.4.1 Locale control](#441-locale-control)
      - [4.4.1.1 The setlocale function](#4411-the-setlocale-function)
    - [4.4.2 Numeric formatting convention inquiry](#442-numeric-formatting-convention-inquiry)
      - [4.4.2.1 The localeconv function](#4421-the-localeconv-function)
  - [4.5 MATHEMATICS <math.h>](#45-mathematics-<mathh>)
    - [4.5.1 Treatment of error conditions](#451-treatment-of-error-conditions)
    - [4.5.2 Trigonometric functions](#452-trigonometric-functions)
      - [4.5.2.1 The acos function](#4521-the-acos-function)
      - [4.5.2.2 The asin function](#4522-the-asin-function)
      - [4.5.2.3 The atan function](#4523-the-atan-function)
      - [4.5.2.4 The atan2 function](#4524-the-atan2-function)
      - [4.5.2.5 The cos function](#4525-the-cos-function)
      - [4.5.2.6 The sin function](#4526-the-sin-function)
      - [4.5.2.7 The tan function](#4527-the-tan-function)
    - [4.5.3 Hyperbolic functions](#453-hyperbolic-functions)
      - [4.5.3.1 The cosh function](#4531-the-cosh-function)
      - [4.5.3.2 The sinh function](#4532-the-sinh-function)
      - [4.5.3.3 The tanh function](#4533-the-tanh-function)
    - [4.5.4 Exponential and logarithmic functions](#454-exponential-and-logarithmic-functions)
      - [4.5.4.1 The exp function](#4541-the-exp-function)
      - [4.5.4.2 The frexp function](#4542-the-frexp-function)
      - [4.5.4.3 The ldexp function](#4543-the-ldexp-function)
      - [4.5.4.4 The log function](#4544-the-log-function)
      - [4.5.4.5 The log10 function](#4545-the-log10-function)
      - [4.5.4.6 The modf function](#4546-the-modf-function)
    - [4.5.5 Power functions](#455-power-functions)
      - [4.5.5.1 The pow function](#4551-the-pow-function)
      - [4.5.5.2 The sqrt function](#4552-the-sqrt-function)
    - [4.5.6 Nearest integer, absolute value, and remainder functions](#456-nearest-integer,-absolute-value,-and-remainder-functions)
      - [4.5.6.1 The ceil function](#4561-the-ceil-function)
      - [4.5.6.2 The fabs function](#4562-the-fabs-function)
      - [4.5.6.3 The floor function](#4563-the-floor-function)
      - [4.5.6.4 The fmod function](#4564-the-fmod-function)
  - [4.6 NON-LOCAL JUMPS <setjmp.h>](#46-non-local-jumps-<setjmph>)
    - [4.6.1 Save calling environment](#461-save-calling-environment)
      - [4.6.1.1 The setjmp macro](#4611-the-setjmp-macro)
    - [4.6.2 Restore calling environment](#462-restore-calling-environment)
      - [4.6.2.1 The longjmp function](#4621-the-longjmp-function)
  - [4.7 SIGNAL HANDLING <signal.h>](#47-signal-handling-<signalh>)
    - [4.7.1 Specify signal handling](#471-specify-signal-handling)
      - [4.7.1.1 The signal function](#4711-the-signal-function)
    - [4.7.2 Send signal](#472-send-signal)
      - [4.7.2.1 The raise function](#4721-the-raise-function)
  - [4.8 VARIABLE ARGUMENTS <stdarg.h>](#48-variable-arguments-<stdargh>)
    - [4.8.1 Variable argument list access macros](#481-variable-argument-list-access-macros)
      - [4.8.1.1 The va_start macro](#4811-the-va_start-macro)
      - [4.8.1.2 The va_arg macro](#4812-the-va_arg-macro)
      - [4.8.1.3 The va_end macro](#4813-the-va_end-macro)
  - [4.9 INPUT/OUTPUT <stdio.h>](#49-input/output-<stdioh>)
    - [4.9.1 Introduction](#491-introduction)
    - [4.9.2 Streams](#492-streams)
    - [4.9.3 Files](#493-files)
    - [4.9.4 Operations on files](#494-operations-on-files)
      - [4.9.4.1 The remove function](#4941-the-remove-function)
      - [4.9.4.2 The rename function](#4942-the-rename-function)
      - [4.9.4.3 The tmpfile function](#4943-the-tmpfile-function)
      - [4.9.4.4 The tmpnam function](#4944-the-tmpnam-function)
    - [4.9.5 File access functions](#495-file-access-functions)
      - [4.9.5.1 The fclose function](#4951-the-fclose-function)
      - [4.9.5.2 The fflush function](#4952-the-fflush-function)
      - [4.9.5.3 The fopen function](#4953-the-fopen-function)
      - [4.9.5.4 The freopen function](#4954-the-freopen-function)
      - [4.9.5.5 The setbuf function](#4955-the-setbuf-function)
      - [4.9.5.6 The setvbuf function](#4956-the-setvbuf-function)
    - [4.9.6 Formatted input/output functions](#496-formatted-input/output-functions)
      - [4.9.6.1 The fprintf function](#4961-the-fprintf-function)
      - [4.9.6.2 The fscanf function](#4962-the-fscanf-function)
      - [4.9.6.3 The printf function](#4963-the-printf-function)
      - [4.9.6.4 The scanf function](#4964-the-scanf-function)
      - [4.9.6.5 The sprintf function](#4965-the-sprintf-function)
      - [4.9.6.6 The sscanf function](#4966-the-sscanf-function)
      - [4.9.6.7 The vfprintf function](#4967-the-vfprintf-function)
      - [4.9.6.8 The vprintf function](#4968-the-vprintf-function)
      - [4.9.6.9 The vsprintf function](#4969-the-vsprintf-function)
    - [4.9.7 Character input/output functions](#497-character-input/output-functions)
      - [4.9.7.1 The fgetc function](#4971-the-fgetc-function)
      - [4.9.7.2 The fgets function](#4972-the-fgets-function)
      - [4.9.7.3 The fputc function](#4973-the-fputc-function)
      - [4.9.7.4 The fputs function](#4974-the-fputs-function)
      - [4.9.7.5 The getc function](#4975-the-getc-function)
      - [4.9.7.6 The getchar function](#4976-the-getchar-function)
      - [4.9.7.7 The gets function](#4977-the-gets-function)
      - [4.9.7.8 The putc function](#4978-the-putc-function)
      - [4.9.7.9 The putchar function](#4979-the-putchar-function)
      - [4.9.7.10 The puts function](#49710-the-puts-function)
      - [4.9.7.11 The ungetc function](#49711-the-ungetc-function)
    - [4.9.8 Direct input/output functions](#498-direct-input/output-functions)
      - [4.9.8.1 The fread function](#4981-the-fread-function)
      - [4.9.8.2 The fwrite function](#4982-the-fwrite-function)
    - [4.9.9 File positioning functions](#499-file-positioning-functions)
      - [4.9.9.1 The fgetpos function](#4991-the-fgetpos-function)
      - [4.9.9.2 The fseek function](#4992-the-fseek-function)
      - [4.9.9.3 The fsetpos function](#4993-the-fsetpos-function)
      - [4.9.9.4 The ftell function](#4994-the-ftell-function)
      - [4.9.9.5 The rewind function](#4995-the-rewind-function)
    - [4.9.10 Error-handling functions](#4910-error-handling-functions)
      - [4.9.10.1 The clearerr function](#49101-the-clearerr-function)
      - [4.9.10.2 The feof function](#49102-the-feof-function)
      - [4.9.10.3 The ferror function](#49103-the-ferror-function)
      - [4.9.10.4 The perror function](#49104-the-perror-function)
  - [4.10 GENERAL UTILITIES <stdlib.h>](#410-general-utilities-<stdlibh>)
    - [4.10.1 String conversion functions](#4101-string-conversion-functions)
      - [4.10.1.1 The atof function](#41011-the-atof-function)
      - [4.10.1.2 The atoi function](#41012-the-atoi-function)
      - [4.10.1.3 The atol function](#41013-the-atol-function)
      - [4.10.1.4 The strtod function](#41014-the-strtod-function)
      - [4.10.1.5 The strtol function](#41015-the-strtol-function)
      - [4.10.1.6 The strtoul function](#41016-the-strtoul-function)
    - [4.10.2 Pseudo-random sequence generation functions](#4102-pseudo-random-sequence-generation-functions)
      - [4.10.2.1 The rand function](#41021-the-rand-function)
      - [4.10.2.2 The srand function](#41022-the-srand-function)
    - [4.10.3 Memory management functions](#4103-memory-management-functions)
      - [4.10.3.1 The calloc function](#41031-the-calloc-function)
      - [4.10.3.2 The free function](#41032-the-free-function)
      - [4.10.3.3 The malloc function](#41033-the-malloc-function)
      - [4.10.3.4 The realloc function](#41034-the-realloc-function)
    - [4.10.4 Communication with the environment](#4104-communication-with-the-environment)
      - [4.10.4.1 The abort function](#41041-the-abort-function)
      - [4.10.4.2 The atexit function](#41042-the-atexit-function)
      - [4.10.4.3 The exit function](#41043-the-exit-function)
      - [4.10.4.4 The getenv function](#41044-the-getenv-function)
      - [4.10.4.5 The system function](#41045-the-system-function)
    - [4.10.5 Searching and sorting utilities](#4105-searching-and-sorting-utilities)
      - [4.10.5.1 The bsearch function](#41051-the-bsearch-function)
      - [4.10.5.2 The qsort function](#41052-the-qsort-function)
    - [4.10.6 Integer arithmetic functions](#4106-integer-arithmetic-functions)
      - [4.10.6.1 The abs function](#41061-the-abs-function)
      - [4.10.6.2 The div function](#41062-the-div-function)
      - [4.10.6.3 The labs function](#41063-the-labs-function)
      - [4.10.6.4 The ldiv function](#41064-the-ldiv-function)
    - [4.10.7 Multibyte character functions](#4107-multibyte-character-functions)
      - [4.10.7.1 The mblen function](#41071-the-mblen-function)
      - [4.10.7.2 The mbtowc function](#41072-the-mbtowc-function)
      - [4.10.7.3 The wctomb function](#41073-the-wctomb-function)
    - [4.10.8 Multibyte string functions](#4108-multibyte-string-functions)
      - [4.10.8.1 The mbstowcs function](#41081-the-mbstowcs-function)
      - [4.10.8.2 The wcstombs function](#41082-the-wcstombs-function)
  - [4.11 STRING HANDLING <string.h>](#411-string-handling-<stringh>)
    - [4.11.1 String function conventions](#4111-string-function-conventions)
    - [4.11.2 Copying functions](#4112-copying-functions)
      - [4.11.2.1 The memcpy function](#41121-the-memcpy-function)
      - [4.11.2.2 The memmove function](#41122-the-memmove-function)
      - [4.11.2.3 The strcpy function](#41123-the-strcpy-function)
      - [4.11.2.4 The strncpy function](#41124-the-strncpy-function)
    - [4.11.3 Concatenation functions](#4113-concatenation-functions)
      - [4.11.3.1 The strcat function](#41131-the-strcat-function)
      - [4.11.3.2 The strncat function](#41132-the-strncat-function)
    - [4.11.4 Comparison functions](#4114-comparison-functions)
      - [4.11.4.1 The memcmp function](#41141-the-memcmp-function)
      - [4.11.4.2 The strcmp function](#41142-the-strcmp-function)
      - [4.11.4.3 The strcoll function](#41143-the-strcoll-function)
      - [4.11.4.4 The strncmp function](#41144-the-strncmp-function)
      - [4.11.4.5 The strxfrm function](#41145-the-strxfrm-function)
    - [4.11.5 Search functions](#4115-search-functions)
      - [4.11.5.1 The memchr function](#41151-the-memchr-function)
      - [4.11.5.2 The strchr function](#41152-the-strchr-function)
      - [4.11.5.3 The strcspn function](#41153-the-strcspn-function)
      - [4.11.5.4 The strpbrk function](#41154-the-strpbrk-function)
      - [4.11.5.5 The strrchr function](#41155-the-strrchr-function)
      - [4.11.5.6 The strspn function](#41156-the-strspn-function)
      - [4.11.5.7 The strstr function](#41157-the-strstr-function)
      - [4.11.5.8 The strtok function](#41158-the-strtok-function)
    - [4.11.6 Miscellaneous functions](#4116-miscellaneous-functions)
      - [4.11.6.1 The memset function](#41161-the-memset-function)
      - [4.11.6.2 The strerror function](#41162-the-strerror-function)
      - [4.11.6.3 The strlen function](#41163-the-strlen-function)
  - [4.12 DATE AND TIME <time.h>](#412-date-and-time-<timeh>)
    - [4.12.1 Components of time](#4121-components-of-time)
    - [4.12.2 Time manipulation functions](#4122-time-manipulation-functions)
      - [4.12.2.1 The clock function](#41221-the-clock-function)
      - [4.12.2.2 The difftime function](#41222-the-difftime-function)
      - [4.12.2.3 The mktime function](#41223-the-mktime-function)
      - [4.12.2.4 The time function](#41224-the-time-function)
    - [4.12.3 Time conversion functions](#4123-time-conversion-functions)
      - [4.12.3.1 The asctime function](#41231-the-asctime-function)
      - [4.12.3.2 The ctime function](#41232-the-ctime-function)
      - [4.12.3.3 The gmtime function](#41233-the-gmtime-function)
      - [4.12.3.4 The localtime function](#41234-the-localtime-function)
      - [4.12.3.5 The strftime function](#41235-the-strftime-function)
  - [4.13 FUTURE LIBRARY DIRECTIONS](#413-future-library-directions)
    - [4.13.1 Errors <errno.h>](#4131-errors-<errnoh>)
    - [4.13.2 Character handling <ctype.h>](#4132-character-handling-<ctypeh>)
    - [4.13.3 Localization <locale.h>](#4133-localization-<localeh>)
    - [4.13.4 Mathematics <math.h>](#4134-mathematics-<mathh>)
    - [4.13.5 Signal handling <signal.h>](#4135-signal-handling-<signalh>)
    - [4.13.6 Input/output <stdio.h>](#4136-input/output-<stdioh>)
    - [4.13.7 General utilities <stdlib.h>](#4137-general-utilities-<stdlibh>)
    - [4.13.8 String handling <string.h>](#4138-string-handling-<stringh>)
- [A. APPENDICES](#a-appendices)
  - [A.1 LANGUAGE SYNTAX SUMMARY](#a1-language-syntax-summary)
    - [A.1.1 Lexical grammar](#a11-lexical-grammar)
      - [A.1.1.1 Tokens](#a111-tokens)
      - [A.1.1.2 Keywords](#a112-keywords)
      - [A.1.1.3 Identifiers](#a113-identifiers)
      - [A.1.1.4 Constants](#a114-constants)
      - [A.1.1.5 String literals](#a115-string-literals)
      - [A.1.1.6 Operators](#a116-operators)
      - [A.1.1.7 Punctuators](#a117-punctuators)
      - [A.1.1.8 Header names](#a118-header-names)
      - [A.1.1.9 Preprocessing numbers](#a119-preprocessing-numbers)
    - [A.1.2 Phrase structure grammar](#a12-phrase-structure-grammar)
      - [A.1.2.1 Expressions](#a121-expressions)
      - [A.1.2.2 Declarations](#a122-declarations)
      - [A.1.2.3 Statements](#a123-statements)
      - [A.1.2.4 External definitions](#a124-external-definitions)
    - [A.1.3 Preprocessing directives](#a13-preprocessing-directives)
  - [A.2 SEQUENCE POINTS](#a2-sequence-points)
  - [A.3 LIBRARY SUMMARY](#a3-library-summary)
    - [A.3.1 ERRORS <errno.h>](#a31-errors-<errnoh>)
    - [A.3.2 COMMON DEFINITIONS <stddef.h>](#a32-common-definitions-<stddefh>)
    - [A.3.3 DIAGNOSTICS <assert.h>](#a33-diagnostics-<asserth>)
    - [A.3.4 CHARACTER HANDLING <ctype.h>](#a34-character-handling-<ctypeh>)
    - [A.3.5 LOCALIZATION <locale.h>](#a35-localization-<localeh>)
    - [A.3.6 MATHEMATICS <math.h>](#a36-mathematics-<mathh>)
    - [A.3.7 NON-LOCAL JUMPS <setjmp.h>](#a37-non-local-jumps-<setjmph>)
    - [A.3.8 SIGNAL HANDLING <signal.h>](#a38-signal-handling-<signalh>)
    - [A.3.9 VARIABLE ARGUMENTS <stdarg.h>](#a39-variable-arguments-<stdargh>)
    - [A.3.10 INPUT/OUTPUT <stdio.h>](#a310-input/output-<stdioh>)
    - [A.3.11 GENERAL UTILITIES <stdlib.h>](#a311-general-utilities-<stdlibh>)
    - [A.3.12 STRING HANDLING <string.h>](#a312-string-handling-<stringh>)
    - [A.3.13 DATE AND TIME <time.h>](#a313-date-and-time-<timeh>)
  - [A.4 IMPLEMENTATION LIMITS](#a4-implementation-limits)
  - [A.5 COMMON WARNINGS](#a5-common-warnings)
  - [A.6 PORTABILITY ISSUES](#a6-portability-issues)
    - [A.6.1 Unspecified behavior](#a61-unspecified-behavior)
    - [A.6.2 Undefined behavior](#a62-undefined-behavior)
    - [A.6.3 Implementation-defined behavior](#a63-implementation-defined-behavior)
      - [A.6.3.1 Environment](#a631-environment)
      - [A.6.3.2 Identifiers](#a632-identifiers)
      - [A.6.3.3 Characters](#a633-characters)
      - [A.6.3.4 Integers](#a634-integers)
      - [A.6.3.5 Floating point](#a635-floating-point)
      - [A.6.3.6 Arrays and pointers](#a636-arrays-and-pointers)
      - [A.6.3.7 Registers](#a637-registers)
      - [A.6.3.8 Structures, unions, enumerations, and bit-fields](#a638-structures,-unions,-enumerations,-and-bit-fields)
      - [A.6.3.9 Qualifiers](#a639-qualifiers)
      - [A.6.3.10 Declarators](#a6310-declarators)
      - [A.6.3.11 Statements](#a6311-statements)
      - [A.6.3.12 Preprocessing directives](#a6312-preprocessing-directives)
      - [A.6.3.13 Library functions](#a6313-library-functions)
    - [A.6.4 Locale-specific Behavior](#a64-locale-specific-behavior)
    - [A.6.5 Common extensions](#a65-common-extensions)
      - [A.6.5.1 Environment arguments](#a651-environment-arguments)
      - [A.6.5.2 Specialized identifiers](#a652-specialized-identifiers)
      - [A.6.5.3 Lengths and cases of identifiers](#a653-lengths-and-cases-of-identifiers)
      - [A.6.5.4 Scopes of identifiers](#a654-scopes-of-identifiers)
      - [A.6.5.5 Writable string literals](#a655-writable-string-literals)
      - [A.6.5.6 Other arithmetic types](#a656-other-arithmetic-types)
      - [A.6.5.7 Function pointer casts](#a657-function-pointer-casts)
      - [A.6.5.8 Non-int bit-field types](#a658-non-int-bit-field-types)
      - [A.6.5.9 The fortran keyword](#a659-the-fortran-keyword)
      - [A.6.5.10 The asm keyword](#a6510-the-asm-keyword)
      - [A.6.5.11 Multiple external definitions](#a6511-multiple-external-definitions)
      - [A.6.5.12 Empty macro arguments](#a6512-empty-macro-arguments)
      - [A.6.5.13 Predefined macro names](#a6513-predefined-macro-names)
      - [A.6.5.14 Extra arguments for signal handlers](#a6514-extra-arguments-for-signal-handlers)
      - [A.6.5.15 Additional stream types and file-opening modes](#a6515-additional-stream-types-and-file-opening-modes)
      - [A.6.5.16 Defined file position indicator](#a6516-defined-file-position-indicator)
  - [A.7 INDEX](#a7-index)

## 1. INTRODUCTION

### 1.1 PURPOSE

### 1.2 SCOPE

### 1.3 REFERENCES

### 1.4 ORGANIZATION OF THE DOCUMENT

### 1.5 BASE DOCUMENTS

### 1.6 DEFINITIONS OF TERMS

### 1.7 COMPLIANCE

### 1.8 FUTURE DIRECTIONS

### 1.9 ABOUT THIS DRAFT

## 2. ENVIRONMENT

### 2.1 CONCEPTUAL MODELS

#### 2.1.1 Translation environment

##### 2.1.1.1 Program structure

##### 2.1.1.2 Translation phases

##### 2.1.1.3 Diagnostics

#### 2.1.2 Execution environments

##### 2.1.2.1 Freestanding environment

##### 2.1.2.2 Hosted environment

##### 2.1.2.3 Program execution

### 2.2 ENVIRONMENTAL CONSIDERATIONS

#### 2.2.1 Character sets

##### 2.2.1.1 Trigraph sequences

##### 2.2.1.2 Multibyte characters

#### 2.2.2 Character display semantics

#### 2.2.3 Signals and interrupts

#### 2.2.4 Environmental limits

##### 2.2.4.1 Translation limits

##### 2.2.4.2 Numerical limits

## 3. LANGUAGE

### 3.1 LEXICAL ELEMENTS

#### 3.1.1 Keywords

#### 3.1.2 Identifiers

##### 3.1.2.1 Scopes of identifiers

##### 3.1.2.2 Linkages of identifiers

##### 3.1.2.3 Name spaces of identifiers

##### 3.1.2.4 Storage durations of objects

##### 3.1.2.5 Types

##### 3.1.2.6 Compatible type and composite type

#### 3.1.3 Constants

##### 3.1.3.1 Floating constants

##### 3.1.3.2 Integer constants

##### 3.1.3.3 Enumeration constants

##### 3.1.3.4 Character constants

#### 3.1.4 String literals

#### 3.1.5 Operators

#### 3.1.6 Punctuators

#### 3.1.7 Header names

#### 3.1.8 Preprocessing numbers

#### 3.1.9 Comments

### 3.2 CONVERSIONS

#### 3.2.1 Arithmetic operands

##### 3.2.1.1 Characters and integers

##### 3.2.1.2 Signed and unsigned integers

##### 3.2.1.3 Floating and integral

##### 3.2.1.4 Floating types

##### 3.2.1.5 Usual arithmetic conversions

#### 3.2.2 Other operands

##### 3.2.2.1 Lvalues and function designators

##### 3.2.2.2 void

##### 3.2.2.3 Pointers

### 3.3 EXPRESSIONS

#### 3.3.1 Primary expressions

#### 3.3.2 Postfix operators

##### 3.3.2.1 Array subscripting

##### 3.3.2.2 Function calls

##### 3.3.2.3 Structure and union members

##### 3.3.2.4 Postfix increment and decrement operators

#### 3.3.3 Unary operators

##### 3.3.3.1 Prefix increment and decrement operators

##### 3.3.3.2 Address and indirection operators

##### 3.3.3.3 Unary arithmetic operators

##### 3.3.3.4 The sizeof operator

#### 3.3.4 Cast operators

#### 3.3.5 Multiplicative operators

#### 3.3.6 Additive operators

#### 3.3.7 Bitwise shift operators

#### 3.3.8 Relational operators

#### 3.3.9 Equality operators

#### 3.3.10 Bitwise AND operator

#### 3.3.11 Bitwise exclusive OR operator

#### 3.3.12 Bitwise inclusive OR operator

#### 3.3.13 Logical AND operator

#### 3.3.14 Logical OR operator

#### 3.3.15 Conditional operator

#### 3.3.16 Assignment operators

##### 3.3.16.1 Simple assignment

##### 3.3.16.2 Compound assignment

#### 3.3.17 Comma operator

### 3.4 CONSTANT EXPRESSIONS

### 3.5 DECLARATIONS

#### 3.5.1 Storage-class specifiers

#### 3.5.2 Type specifiers

##### 3.5.2.1 Structure and union specifiers

##### 3.5.2.2 Enumeration specifiers

##### 3.5.2.3 Tags

#### 3.5.3 Type qualifiers

#### 3.5.4 Declarators

##### 3.5.4.1 Pointer declarators

##### 3.5.4.2 Array declarators

##### 3.5.4.3 Function declarators (including prototypes)

#### 3.5.5 Type names

#### 3.5.6 Type definitions

#### 3.5.7 Initialization

### 3.6 STATEMENTS

#### 3.6.1 Labeled statements

#### 3.6.2 Compound statement, or block

#### 3.6.3 Expression and null statements

#### 3.6.4 Selection statements

##### 3.6.4.1 The if statement

##### 3.6.4.2 The switch statement

#### 3.6.5 Iteration statements

##### 3.6.5.1 The while statement

##### 3.6.5.2 The do statement

##### 3.6.5.3 The for statement

#### 3.6.6 Jump statements

##### 3.6.6.1 The goto statement

##### 3.6.6.2 The continue statement

##### 3.6.6.3 The break statement

##### 3.6.6.4 The return statement

### 3.7 EXTERNAL DEFINITIONS

#### 3.7.1 Function definitions

#### 3.7.2 External object definitions

### 3.8 PREPROCESSING DIRECTIVES

#### 3.8.1 Conditional inclusion

#### 3.8.2 Source file inclusion

#### 3.8.3 Macro replacement

##### 3.8.3.1 Argument substitution

##### 3.8.3.2 The # operator

##### 3.8.3.3 The ## operator

##### 3.8.3.4 Rescanning and further replacement

##### 3.8.3.5 Scope of macro definitions

#### 3.8.4 Line control

#### 3.8.5 Error directive

#### 3.8.6 Pragma directive

#### 3.8.7 Null directive

#### 3.8.8 Predefined macro names

### 3.9 FUTURE LANGUAGE DIRECTIONS

#### 3.9.1 External names

#### 3.9.2 Character escape sequences

#### 3.9.3 Storage-class specifiers

#### 3.9.4 Function declarators

#### 3.9.5 Function definitions

## 4. LIBRARY

### 4.1 INTRODUCTION

#### 4.1.1 Definitions of terms

#### 4.1.2 Standard headers

#### 4.1.3 Errors <errno.h>

#### 4.1.4 Limits <float.h> and <limits.h>

#### 4.1.5 Common definitions <stddef.h>

#### 4.1.6 Use of library functions

### 4.2 DIAGNOSTICS <assert.h>

#### 4.2.1 Program diagnostics

##### 4.2.1.1 The assert macro

### 4.3 CHARACTER HANDLING <ctype.h>

#### 4.3.1 Character testing functions

##### 4.3.1.1 The isalnum function

##### 4.3.1.2 The isalpha function

##### 4.3.1.3 The iscntrl function

##### 4.3.1.4 The isdigit function

##### 4.3.1.5 The isgraph function

##### 4.3.1.6 The islower function

##### 4.3.1.7 The isprint function

##### 4.3.1.8 The ispunct function

##### 4.3.1.9 The isspace function

##### 4.3.1.10 The isupper function

##### 4.3.1.11 The isxdigit function

#### 4.3.2 Character case mapping functions

##### 4.3.2.1 The tolower function

##### 4.3.2.2 The toupper function

### 4.4 LOCALIZATION <locale.h>

#### 4.4.1 Locale control

##### 4.4.1.1 The setlocale function

#### 4.4.2 Numeric formatting convention inquiry

##### 4.4.2.1 The localeconv function

### 4.5 MATHEMATICS <math.h>

#### 4.5.1 Treatment of error conditions

#### 4.5.2 Trigonometric functions

##### 4.5.2.1 The acos function

##### 4.5.2.2 The asin function

##### 4.5.2.3 The atan function

##### 4.5.2.4 The atan2 function

##### 4.5.2.5 The cos function

##### 4.5.2.6 The sin function

##### 4.5.2.7 The tan function

#### 4.5.3 Hyperbolic functions

##### 4.5.3.1 The cosh function

##### 4.5.3.2 The sinh function

##### 4.5.3.3 The tanh function

#### 4.5.4 Exponential and logarithmic functions

##### 4.5.4.1 The exp function

##### 4.5.4.2 The frexp function

##### 4.5.4.3 The ldexp function

##### 4.5.4.4 The log function

##### 4.5.4.5 The log10 function

##### 4.5.4.6 The modf function

#### 4.5.5 Power functions

##### 4.5.5.1 The pow function

##### 4.5.5.2 The sqrt function

#### 4.5.6 Nearest integer, absolute value, and remainder functions

##### 4.5.6.1 The ceil function

##### 4.5.6.2 The fabs function

##### 4.5.6.3 The floor function

##### 4.5.6.4 The fmod function

### 4.6 NON-LOCAL JUMPS <setjmp.h>

#### 4.6.1 Save calling environment

##### 4.6.1.1 The setjmp macro

#### 4.6.2 Restore calling environment

##### 4.6.2.1 The longjmp function

### 4.7 SIGNAL HANDLING <signal.h>

#### 4.7.1 Specify signal handling

##### 4.7.1.1 The signal function

#### 4.7.2 Send signal

##### 4.7.2.1 The raise function

### 4.8 VARIABLE ARGUMENTS <stdarg.h>

#### 4.8.1 Variable argument list access macros

##### 4.8.1.1 The va_start macro

##### 4.8.1.2 The va_arg macro

##### 4.8.1.3 The va_end macro

### 4.9 INPUT/OUTPUT <stdio.h>

#### 4.9.1 Introduction

#### 4.9.2 Streams

#### 4.9.3 Files

#### 4.9.4 Operations on files

##### 4.9.4.1 The remove function

##### 4.9.4.2 The rename function

##### 4.9.4.3 The tmpfile function

##### 4.9.4.4 The tmpnam function

#### 4.9.5 File access functions

##### 4.9.5.1 The fclose function

##### 4.9.5.2 The fflush function

##### 4.9.5.3 The fopen function

##### 4.9.5.4 The freopen function

##### 4.9.5.5 The setbuf function

##### 4.9.5.6 The setvbuf function

#### 4.9.6 Formatted input/output functions

##### 4.9.6.1 The fprintf function

##### 4.9.6.2 The fscanf function

##### 4.9.6.3 The printf function

##### 4.9.6.4 The scanf function

##### 4.9.6.5 The sprintf function

##### 4.9.6.6 The sscanf function

##### 4.9.6.7 The vfprintf function

##### 4.9.6.8 The vprintf function

##### 4.9.6.9 The vsprintf function

#### 4.9.7 Character input/output functions

##### 4.9.7.1 The fgetc function

##### 4.9.7.2 The fgets function

##### 4.9.7.3 The fputc function

##### 4.9.7.4 The fputs function

##### 4.9.7.5 The getc function

##### 4.9.7.6 The getchar function

##### 4.9.7.7 The gets function

##### 4.9.7.8 The putc function

##### 4.9.7.9 The putchar function

##### 4.9.7.10 The puts function

##### 4.9.7.11 The ungetc function

#### 4.9.8 Direct input/output functions

##### 4.9.8.1 The fread function

##### 4.9.8.2 The fwrite function

#### 4.9.9 File positioning functions

##### 4.9.9.1 The fgetpos function

##### 4.9.9.2 The fseek function

##### 4.9.9.3 The fsetpos function

##### 4.9.9.4 The ftell function

##### 4.9.9.5 The rewind function

#### 4.9.10 Error-handling functions

##### 4.9.10.1 The clearerr function

##### 4.9.10.2 The feof function

##### 4.9.10.3 The ferror function

##### 4.9.10.4 The perror function

### 4.10 GENERAL UTILITIES <stdlib.h>

#### 4.10.1 String conversion functions

##### 4.10.1.1 The atof function

##### 4.10.1.2 The atoi function

##### 4.10.1.3 The atol function

##### 4.10.1.4 The strtod function

##### 4.10.1.5 The strtol function

##### 4.10.1.6 The strtoul function

#### 4.10.2 Pseudo-random sequence generation functions

##### 4.10.2.1 The rand function

##### 4.10.2.2 The srand function

#### 4.10.3 Memory management functions

##### 4.10.3.1 The calloc function

##### 4.10.3.2 The free function

##### 4.10.3.3 The malloc function

##### 4.10.3.4 The realloc function

#### 4.10.4 Communication with the environment

##### 4.10.4.1 The abort function

##### 4.10.4.2 The atexit function

##### 4.10.4.3 The exit function

##### 4.10.4.4 The getenv function

##### 4.10.4.5 The system function

#### 4.10.5 Searching and sorting utilities

##### 4.10.5.1 The bsearch function

##### 4.10.5.2 The qsort function

#### 4.10.6 Integer arithmetic functions

##### 4.10.6.1 The abs function

##### 4.10.6.2 The div function

##### 4.10.6.3 The labs function

##### 4.10.6.4 The ldiv function

#### 4.10.7 Multibyte character functions

##### 4.10.7.1 The mblen function

##### 4.10.7.2 The mbtowc function

##### 4.10.7.3 The wctomb function

#### 4.10.8 Multibyte string functions

##### 4.10.8.1 The mbstowcs function

##### 4.10.8.2 The wcstombs function

### 4.11 STRING HANDLING <string.h>

#### 4.11.1 String function conventions

#### 4.11.2 Copying functions

##### 4.11.2.1 The memcpy function

##### 4.11.2.2 The memmove function

##### 4.11.2.3 The strcpy function

##### 4.11.2.4 The strncpy function

#### 4.11.3 Concatenation functions

##### 4.11.3.1 The strcat function

##### 4.11.3.2 The strncat function

#### 4.11.4 Comparison functions

##### 4.11.4.1 The memcmp function

##### 4.11.4.2 The strcmp function

##### 4.11.4.3 The strcoll function

##### 4.11.4.4 The strncmp function

##### 4.11.4.5 The strxfrm function

#### 4.11.5 Search functions

##### 4.11.5.1 The memchr function

##### 4.11.5.2 The strchr function

##### 4.11.5.3 The strcspn function

##### 4.11.5.4 The strpbrk function

##### 4.11.5.5 The strrchr function

##### 4.11.5.6 The strspn function

##### 4.11.5.7 The strstr function

##### 4.11.5.8 The strtok function

#### 4.11.6 Miscellaneous functions

##### 4.11.6.1 The memset function

##### 4.11.6.2 The strerror function

##### 4.11.6.3 The strlen function

### 4.12 DATE AND TIME <time.h>

#### 4.12.1 Components of time

#### 4.12.2 Time manipulation functions

##### 4.12.2.1 The clock function

##### 4.12.2.2 The difftime function

##### 4.12.2.3 The mktime function

##### 4.12.2.4 The time function

#### 4.12.3 Time conversion functions

##### 4.12.3.1 The asctime function

##### 4.12.3.2 The ctime function

##### 4.12.3.3 The gmtime function

##### 4.12.3.4 The localtime function

##### 4.12.3.5 The strftime function

### 4.13 FUTURE LIBRARY DIRECTIONS

#### 4.13.1 Errors <errno.h>

#### 4.13.2 Character handling <ctype.h>

#### 4.13.3 Localization <locale.h>

#### 4.13.4 Mathematics <math.h>

#### 4.13.5 Signal handling <signal.h>

#### 4.13.6 Input/output <stdio.h>

#### 4.13.7 General utilities <stdlib.h>

#### 4.13.8 String handling <string.h>

## A. APPENDICES

### A.1 LANGUAGE SYNTAX SUMMARY

#### A.1.1 Lexical grammar

##### A.1.1.1 Tokens

##### A.1.1.2 Keywords

##### A.1.1.3 Identifiers

##### A.1.1.4 Constants

##### A.1.1.5 String literals

##### A.1.1.6 Operators

##### A.1.1.7 Punctuators

##### A.1.1.8 Header names

##### A.1.1.9 Preprocessing numbers

#### A.1.2 Phrase structure grammar

##### A.1.2.1 Expressions

##### A.1.2.2 Declarations

##### A.1.2.3 Statements

##### A.1.2.4 External definitions

#### A.1.3 Preprocessing directives

### A.2 SEQUENCE POINTS

### A.3 LIBRARY SUMMARY

#### A.3.1 ERRORS <errno.h>

#### A.3.2 COMMON DEFINITIONS <stddef.h>

#### A.3.3 DIAGNOSTICS <assert.h>

#### A.3.4 CHARACTER HANDLING <ctype.h>

#### A.3.5 LOCALIZATION <locale.h>

#### A.3.6 MATHEMATICS <math.h>

#### A.3.7 NON-LOCAL JUMPS <setjmp.h>

#### A.3.8 SIGNAL HANDLING <signal.h>

#### A.3.9 VARIABLE ARGUMENTS <stdarg.h>

#### A.3.10 INPUT/OUTPUT <stdio.h>

#### A.3.11 GENERAL UTILITIES <stdlib.h>

#### A.3.12 STRING HANDLING <string.h>

#### A.3.13 DATE AND TIME <time.h>

### A.4 IMPLEMENTATION LIMITS

### A.5 COMMON WARNINGS

### A.6 PORTABILITY ISSUES

#### A.6.1 Unspecified behavior

#### A.6.2 Undefined behavior

#### A.6.3 Implementation-defined behavior

##### A.6.3.1 Environment

##### A.6.3.2 Identifiers

##### A.6.3.3 Characters

##### A.6.3.4 Integers

##### A.6.3.5 Floating point

##### A.6.3.6 Arrays and pointers

##### A.6.3.7 Registers

##### A.6.3.8 Structures, unions, enumerations, and bit-fields

##### A.6.3.9 Qualifiers

##### A.6.3.10 Declarators

##### A.6.3.11 Statements

##### A.6.3.12 Preprocessing directives

##### A.6.3.13 Library functions

#### A.6.4 Locale-specific Behavior

#### A.6.5 Common extensions

##### A.6.5.1 Environment arguments

##### A.6.5.2 Specialized identifiers

##### A.6.5.3 Lengths and cases of identifiers

##### A.6.5.4 Scopes of identifiers

##### A.6.5.5 Writable string literals

##### A.6.5.6 Other arithmetic types

##### A.6.5.7 Function pointer casts

##### A.6.5.8 Non-int bit-field types

##### A.6.5.9 The fortran keyword

##### A.6.5.10 The asm keyword

##### A.6.5.11 Multiple external definitions

##### A.6.5.12 Empty macro arguments

##### A.6.5.13 Predefined macro names

##### A.6.5.14 Extra arguments for signal handlers

##### A.6.5.15 Additional stream types and file-opening modes

##### A.6.5.16 Defined file position indicator

### A.7 INDEX
