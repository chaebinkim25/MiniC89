# The C89 Draft

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
      - [3.5.4.3 Function declarators (including prototypes)](#3543-function-declarators-including-prototypes)
    - [3.5.5 Type names](#355-type-names)
    - [3.5.6 Type definitions](#356-type-definitions)
    - [3.5.7 Initialization](#357-initialization)
  - [3.6 STATEMENTS](#36-statements)
    - [3.6.1 Labeled statements](#361-labeled-statements)
    - [3.6.2 Compound statement, or block](#362-compound-statement-or-block)
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
      - [3.8.3.2 The # operator](#3832-the--operator)
      - [3.8.3.3 The ## operator](#3833-the--operator)
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
    - [4.1.3 Errors <errno.h>](#413-errors-errnoh)
    - [4.1.4 Limits <float.h> and <limits.h>](#414-limits-floath-and-limitsh)
    - [4.1.5 Common definitions <stddef.h>](#415-common-definitions-stddefh)
    - [4.1.6 Use of library functions](#416-use-of-library-functions)
  - [4.2 DIAGNOSTICS <assert.h>](#42-diagnostics-asserth)
    - [4.2.1 Program diagnostics](#421-program-diagnostics)
      - [4.2.1.1 The assert macro](#4211-the-assert-macro)
  - [4.3 CHARACTER HANDLING <ctype.h>](#43-character-handling-ctypeh)
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
  - [4.4 LOCALIZATION <locale.h>](#44-localization-localeh)
    - [4.4.1 Locale control](#441-locale-control)
      - [4.4.1.1 The setlocale function](#4411-the-setlocale-function)
    - [4.4.2 Numeric formatting convention inquiry](#442-numeric-formatting-convention-inquiry)
      - [4.4.2.1 The localeconv function](#4421-the-localeconv-function)
  - [4.5 MATHEMATICS <math.h>](#45-mathematics-mathh)
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
    - [4.5.6 Nearest integer, absolute value, and remainder functions](#456-nearest-integer-absolute-value-and-remainder-functions)
      - [4.5.6.1 The ceil function](#4561-the-ceil-function)
      - [4.5.6.2 The fabs function](#4562-the-fabs-function)
      - [4.5.6.3 The floor function](#4563-the-floor-function)
      - [4.5.6.4 The fmod function](#4564-the-fmod-function)
  - [4.6 NON-LOCAL JUMPS <setjmp.h>](#46-non-local-jumps-setjmph)
    - [4.6.1 Save calling environment](#461-save-calling-environment)
      - [4.6.1.1 The setjmp macro](#4611-the-setjmp-macro)
    - [4.6.2 Restore calling environment](#462-restore-calling-environment)
      - [4.6.2.1 The longjmp function](#4621-the-longjmp-function)
  - [4.7 SIGNAL HANDLING <signal.h>](#47-signal-handling-signalh)
    - [4.7.1 Specify signal handling](#471-specify-signal-handling)
      - [4.7.1.1 The signal function](#4711-the-signal-function)
    - [4.7.2 Send signal](#472-send-signal)
      - [4.7.2.1 The raise function](#4721-the-raise-function)
  - [4.8 VARIABLE ARGUMENTS <stdarg.h>](#48-variable-arguments-stdargh)
    - [4.8.1 Variable argument list access macros](#481-variable-argument-list-access-macros)
      - [4.8.1.1 The va_start macro](#4811-the-va_start-macro)
      - [4.8.1.2 The va_arg macro](#4812-the-va_arg-macro)
      - [4.8.1.3 The va_end macro](#4813-the-va_end-macro)
  - [4.9 INPUT/OUTPUT <stdio.h>](#49-inputoutput-stdioh)
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
    - [4.9.6 Formatted input/output functions](#496-formatted-inputoutput-functions)
      - [4.9.6.1 The fprintf function](#4961-the-fprintf-function)
      - [4.9.6.2 The fscanf function](#4962-the-fscanf-function)
      - [4.9.6.3 The printf function](#4963-the-printf-function)
      - [4.9.6.4 The scanf function](#4964-the-scanf-function)
      - [4.9.6.5 The sprintf function](#4965-the-sprintf-function)
      - [4.9.6.6 The sscanf function](#4966-the-sscanf-function)
      - [4.9.6.7 The vfprintf function](#4967-the-vfprintf-function)
      - [4.9.6.8 The vprintf function](#4968-the-vprintf-function)
      - [4.9.6.9 The vsprintf function](#4969-the-vsprintf-function)
    - [4.9.7 Character input/output functions](#497-character-inputoutput-functions)
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
    - [4.9.8 Direct input/output functions](#498-direct-inputoutput-functions)
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
  - [4.10 GENERAL UTILITIES <stdlib.h>](#410-general-utilities-stdlibh)
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
  - [4.11 STRING HANDLING <string.h>](#411-string-handling-stringh)
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
  - [4.12 DATE AND TIME <time.h>](#412-date-and-time-timeh)
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
    - [4.13.1 Errors <errno.h>](#4131-errors-errnoh)
    - [4.13.2 Character handling <ctype.h>](#4132-character-handling-ctypeh)
    - [4.13.3 Localization <locale.h>](#4133-localization-localeh)
    - [4.13.4 Mathematics <math.h>](#4134-mathematics-mathh)
    - [4.13.5 Signal handling <signal.h>](#4135-signal-handling-signalh)
    - [4.13.6 Input/output <stdio.h>](#4136-inputoutput-stdioh)
    - [4.13.7 General utilities <stdlib.h>](#4137-general-utilities-stdlibh)
    - [4.13.8 String handling <string.h>](#4138-string-handling-stringh)
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
    - [A.3.1 ERRORS <errno.h>](#a31-errors-errnoh)
    - [A.3.2 COMMON DEFINITIONS <stddef.h>](#a32-common-definitions-stddefh)
    - [A.3.3 DIAGNOSTICS <assert.h>](#a33-diagnostics-asserth)
    - [A.3.4 CHARACTER HANDLING <ctype.h>](#a34-character-handling-ctypeh)
    - [A.3.5 LOCALIZATION <locale.h>](#a35-localization-localeh)
    - [A.3.6 MATHEMATICS <math.h>](#a36-mathematics-mathh)
    - [A.3.7 NON-LOCAL JUMPS <setjmp.h>](#a37-non-local-jumps-setjmph)
    - [A.3.8 SIGNAL HANDLING <signal.h>](#a38-signal-handling-signalh)
    - [A.3.9 VARIABLE ARGUMENTS <stdarg.h>](#a39-variable-arguments-stdargh)
    - [A.3.10 INPUT/OUTPUT <stdio.h>](#a310-inputoutput-stdioh)
    - [A.3.11 GENERAL UTILITIES <stdlib.h>](#a311-general-utilities-stdlibh)
    - [A.3.12 STRING HANDLING <string.h>](#a312-string-handling-stringh)
    - [A.3.13 DATE AND TIME <time.h>](#a313-date-and-time-timeh)
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
      - [A.6.3.8 Structures, unions, enumerations, and bit-fields](#a638-structures-unions-enumerations-and-bit-fields)
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

(This foreword is not a part of American National Standard for Information Systems --- Programming Language C, X3.???-1988.)

American National Standard Programming Language C specifies the syntax and semantics of programs written in the C programming language. It specifies the C program's interactions with the execution environment via input and output data. It also specifies restrictions and limits imposed upon conforming implementations of C language translators.

The standard was developed by the X3J11 Technical Committee on the C Programming Language under project 381-D by American National Standards Committee on Computers and Information Processing (X3). SPARC document number 83-079 describes the purpose of this project to "provide an unambiguous and machine-independent definition of the language C."

The need for a single clearly defined standard had arisen in the C community due to a rapidly expanding use of the C programming language and the variety of differing translator implementations that had been and were being developed. The existence of similar but incompatible implementations was a serious problem for program developers who wished to develop code that would compile and execute as expected in several different environments.

Part of this problem could be traced to the fact that implementors did not have an adequate definition of the C language upon which to base their implementations. The de facto C programming language standard, The C Programming Language by Brian W. Kernighan and Dennis M. Ritchie, is an excellent book; however, it is not precise or complete enough to specify the C language fully. In addition, the language has grown over years of use to incorporate new ideas in programming and to address some of the weaknesses of the original language.

American National Standard Programming Language C addresses the problems of both the program developer and the translator implementor by specifying the C language precisely.

The work of X3J11 began in the summer of 1983, based on the several documents that were made available to the Committee (see [1.5, Base Documents](#15-base-documents)). The Committee divided the effort into three pieces: the environment, the language, and the library. A complete specification in each of these areas is necessary if truly portable programs are to be developed. Each of these areas is addressed in the Standard. The Committee evaluated many proposals for additions, deletions, and changes to the base documents during its deliberations. A concerted effort was made to codify existing practice wherever unambiguous and consistent practice could be identified. However, where no consistent practice could be identified, the Committee worked to establish clear rules that were consistent with the overall flavor of the language.

This document was approved as an American National Standard by the American National Standards Institute (ANSI) on DD MM, 1988. Suggestions for improvement of this Standard are welcome. They should be sent to the American National Standards Institute, 1430 Broadway, New York, NY 10018.

The Standard was processed and approved for submittal to ANSI by the American National Standards Committee on Computers and Information Processing, X3. Committee approval of the Standard does not necessarily imply that all members voted for its approval. At the time that it approved this Standard, the X3 Committee had the following members:

Organization Name of Representative (To be completed on approval of the Standard.)

Technical Committee X3J11 on the C Programming Language had the following members at the time they forwarded this document to X3 for processing as an American National Standard:

|  |  |  |
| :--- | :--- | :--- |
| **Chair** | Jim Brodie | |
| **Vice-Chair** | Thomas Plum | Plum Hall |
| **Secretary** | P. J. Plauger | Whitesmiths, Ltd. |
| **International Rep.** | P. J. Plauger<br>Steve Hersee | Whitesmiths, Ltd.<br>Lattice, Inc. |
| **Vocabulary Rep.** | Andrew Johnson | Prime Computer |
| **Environment Subcom. Chair** | Ralph Ryan<br>Ralph Phraner | Microsoft<br>Phraner Associates |
| **Language Subcom. Chair** | Lawrence Rosler | AT&T |
| **Library Subcom. Chair** | P. J. Plauger | Whitesmiths, Ltd. |
| **Draft Redactor** | David F. Prosser<br>Lawrence Rosler | AT&T<br>AT&T |
| **Rationale Redactor** | Randy Hudson | Intermetrics, Inc. |

In the following list, unmarked names denote principal members and * denotes alternate members.

|  |  |
| :--- | :--- |
| **David F. Prosser** | AT&T |
| **Steven J. Adamski*** | AT&T *(X3H2 SQL liaison)* |
| **Bob Gottlieb** | Alliant Computer Systems |
| **Kevin Brosnan** | Alliant Computer Systems |
| **Neal Weidenhofer** | Amdahl |
| **Philip C. Steel** | American Cimflex |
| **Eric McGlohon*** | American Cimflex |
| **Stephen Kafka** | Analog Devices |
| **Kevin Leary*** | Analog Devices |
| **Gordon Sterling*** | Analog Devices |
| **John Peyton** | Apollo Computer |
| **Elizabeth Crockett** | Apple Computers |
| **Ed Wells** | Arinc |
| **Tom Ketterhagen*** | Arinc |
| **Vaughn Vernon** | Aspen Scientific |
| **Craig Bordelon** | Bell Communications Research |
| **Steve Carter*** | Bell Communications Research |
| **William Puig*** | Bell Communications Research |
| **Bob Jervis** | Borland International |
| **Yom-Tov Meged** | Boston Systems Office |
| **Rose Thomson*** | Boston Systems Office |
| **Maurice Fathi** | COSMIC |
| **John Wu** | Charles River Data Systems |
| **Daniel Mickey** | Chemical Abstracts Service |
| **Thomas Mimlitch*** | Chemical Abstracts Service |
| **Alan Losoff** | Chicago Research & Trading Group |
| **Edward Briggs** | Citibank |
| **Firmo Freire** | Cobra S/A |
| **Jim Patterson** | Cognos |
| **Bruce Tetelman** | Columbia U. Center for Computing |
| **Terry Moore** | CompuDas |
| **Mark Barrenechea** | Computer Associates |
| **George Eberhardt** | Computer Innovations |
| **Dave Neathery*** | Computer Innovations |
| **Joseph Bibbo** | Computrition |
| **Steve Davies** | Concurrent Computer Corporation |
| **Don Fosbury** | Control Data |
| **George VandeBunte*** | Control Data |
| **Lloyd Irons** | Cormorant Communications |
| **Tom MacDonald** | Cray Research |
| **Lynne Johnson*** | Cray Research |
| **Dave Becker*** | Cray Research |
| **Jean Risley** | Custom Development Environments |
| **Rex Jaeschke** | DEC Professional |
| **Mike Terrazas** | DECUS Representative |
| **Michael Meissner** | Data General |
| **Mark Harris*** | Data General |
| **Leonard Ohmes** | Datapoint |
| **James Stanley** | Data Systems Analysts |
| **Samuel J. Kendall** | Delft Consulting |
| **Randy Meyers** | Digital Equipment Corporation |
| **Art Bjork*** | Digital Equipment Corporation |
| **Lu Anne Van de Pas*** | Digital Equipment Corporation |
| **Ben Patel** | EDS |
| **Richard Relph** | EPI |
| **Graham Andrews** | Edinburgh Portable Compilers |
| **Colin McPhail*** | Edinburgh Portable Compilers |
| **J. Stephen Adamczyk** | Edison Design Group |
| **Eric Schwarz*** | Edison Design Group |
| **Dmitry Lenkov** | Everest Solutions |
| **Frank Farance** | Farance Inc. |
| **Peter Hayes*** | Farance Inc. |
| **Florin Jordan** | Floradin |
| **Philip Provin** | General Electric Information Services |
| **Liz Sanville** | Gould CSD |
| **Tina Aleksa*** | Gould CSD |
| **Thomas Kelly** | HCR Corporation |
| **Paul Jackson*** | HCR Corporation |
| **Gary Jeter** | Harris Computer Systems |
| **Sue Meloy** | Hewlett Packard |
| **Larry Rosler*** | Hewlett Packard |
| **Michelle Ruscetta*** | Hewlett Packard |
| **Thomas E. Osten** | Honeywell Information Systems |
| **David Kayden*** | Honeywell Information Systems |
| **Shawn Elliott** | IBM |
| **Larry Breed*** | IBM |
| **Mel Goldberg*** | IBM |
| **Mike Banahan** | Instruction Set |
| **Clark Nelson** | Intel |
| **Dan Lau*** | Intel |
| **John Wolfe** | InterACT |
| **Lillian Toll*** | InterACT |
| **Randy Hudson** | Intermetrics |
| **Keith Winter** | International Computers Ltd. |
| **Honey M. Schrecker*** | International Computers Ltd. |
| **Jim Brodie** | J. Brodie & Associates |
| **Jacklin Kotikian** | Kendall Square Research |
| **W. Peter Hesse** | LSI Logic Europe Ltd. |
| **John Kaminski** | Language Processors Inc. |
| **David Yost** | Laurel Arts |
| **Mike Branstetter** | Lawrence Livermore National Laboratory |
| **Bob Weaver** | Los Alamos National Laboratory |
| **Lidia Eberhart** | Modcomp |
| **Robert Sherry** | Manx Software |
| **Courtney Meissen** | Mark Williams Co. |
| **Patricia Jenkins** | Masscomp |
| **Dave Hinman*** | Masscomp |
| **Michael Kearns** | MetaLink |
| **Tom Pennello** | MetaWare Incorporated |
| **David F. Weil** | Microsoft |
| **Mitch Harder*** | Microsoft |
| **Kim Kempf** | Microware Systems |
| **Shane McCarron** | Minnesota Educational Computing |
| **Bruce Olsen** | Mosaic Technologies |
| **Michael Paton** | Motorola |
| **Rick Schubert** | NCR |
| **Brian Johnson*** | NCR |
| **Joseph Mueller** | National Semiconductor |
| **Derek Godfrey*** | National Semiconductor |
| **Jim Upperman** | National Bureau of Standards |
| **James W. Williams** | Naval Research Laboratory |
| **Lisa Simon** | OCLC |
| **Paul Amaranth** | Oakland University |
| **August R. Hansen** | Omniware |
| **Michael Rolle** | Oracle |
| **Carl Ellis** | Oregon Software |
| **Barry Hedquist** | Perennial |
| **Sassan Hazeghi** | Peritus International |
| **James Holmlund*** | Peritus International |
| **Thomas Plum** | Plum Hall |
| **Christopher Skelly*** | Plum Hall |
| **Andrew Johnson** | Prime Computer |
| **Fran Litterio*** | Prime Computer |
| **Daniel J. Conrad** | Prismatics |
| **David Fritz** | Production Languages |
| **Kenneth Pugh** | Pugh Killeen |
| **Ed Ramsey** | Purdue University |
| **Stephen Roberts*** | Purdue University |
| **Kevin Nolan** | Quantitative Technology Corp. |
| **Robert Mueller*** | Quantitative Technology Corp. |
| **Chris DeVoney** | Que Corporation |
| **Jon Tulk** | Rabbit Software |
| **Terry Colligan** | Rational Systems |
| **Daniel Saks** | Saks & Associates |
| **Nancy Saks*** | Saks & Associates |
| **Oliver Bradley** | SAS Institute |
| **Alan Beale*** | SAS Institute |
| **Larry Jones** | SDRC |
| **Donald Kossman** | SEI Information Technology |
| **Kenneth Harrenstien** | SRI International |
| **Larry Rosenthal** | Sierra Systems |
| **Phil Hempfner** | Southern Bell Telephone |
| **Purshotam Rajani** | Spruce Technology |
| **Savu Savulescu** | Stagg Systems |
| **Peter Darnell** | Stellar Computer |
| **Lee W. Cooprider*** | Stellar Computer |
| **Paul Gilmartin** | Storage Technology Corp. |
| **Steve Muchnick** | Sun Microsystems |
| **Chuck Rasbold** | Supercomputer Systems, Inc. |
| **Kelly O'Hair*** | Supercomputer Systems, Inc. |
| **Henry Richardson** | Tandem |
| **John M. Hausman*** | Tandem |
| **Samuel Harbison** | Tartan Laboratories |
| **Michael S. Ball** | TauMetric |
| **Carl Sutton** | Tektronix |
| **Jim Besemer*** | Tektronix |
| **Reid Tatge** | Texas Instruments |
| **Ed Brower** | Tokheim |
| **Robert Mansfield*** | Tokheim |
| **Monika Khushf** | Tymlabs |
| **Morgan Jones*** | Tymlabs |
| **Don Bixler** | Unisys |
| **Steve Bartels*** | Unisys |
| **Glenda Berkheimer*** | Unisys |
| **Annice Jackson*** | Unisys |
| **Fred Blonder** | University of Maryland |
| **Fred Schwarz** | University of Michigan |
| **R. Jordan Kreindler** | University of Southern California CTC |
| **Mike Carmody** | University of Waterloo |
| **Douglas Gwyn** | US Army BRL *(IEEE P1003 liaison)* |
| **C. Dale Pierce*** | US Army Management Engineering |
| **John C. Black** | VideoFinancial |
| **Joseph Musacchia** | Wang Labs |
| **Fred Rozakis*** | Wang Labs |
| **P. J. Plauger** | Whitesmiths, Ltd. |
| **Kim Leeper** | Wick Hill |
| **Mark Wittenberg** | Zehntel |
| **Jim Balter** | |
| **Robert Bradbury** | |
| **Edward Chin** | |
| **Neil Daniels** | |
| **Stephen Desofi** | |
| **Michael Duffy** | |
| **Phillip Escue** | |
| **Ralph Phraner** | |
| **D. Hugh Redelmeier** | |
| **Arnold Davi Robbins** | |
| **Roger Wilks** | |
| **Michael J. Young** | |

| | | | |
| :--- | :--- | :--- | :--- |
| **Purpose** | [1.1](#11-purpose) | **Scope** | [1.2](#12-scope) |
| **References** | [1.3](#13-references) | **Organization of the document** | [1.4](#14-organization-of-the-document) |
| **Base documents** | [1.5](#15-base-documents) | **Definitions of terms** | [1.6](#16-definitions-of-terms) |
| **Compliance** | [1.7](#17-compliance) | **Translation environment** | [2.](#2-environment) |
| **Execution environment** | [2.](#2-environment) | **Separate compilation** | [2.1.1.1](#2111-program-structure) |
| **Separate translation** | [2.1.1.1](#2111-program-structure) | **Source file** | [2.1.1.1](#2111-program-structure) |
| **Translation unit** | [2.1.1.1](#2111-program-structure) | **Program execution** | [2.1.2.3](#2123-program-execution) |
| **Side effects** | [2.1.2.3](#2123-program-execution) | **Sequence point** | [2.1.2.3](#2123-program-execution) |
| **Character set** | [2.2.1](#221-character-sets) | **Signals** | [2.2.3](#223-signals-and-interrupts) |
| **Interrupts** | [2.2.3](#223-signals-and-interrupts) | **Syntax notation** | [3.](#3-language) |
| **Lexical elements** | [3.1](#31-lexical-elements) | **Comment** | [3.1](#31-lexical-elements) |
| **White space** | [3.1](#31-lexical-elements) | **List of keywords** | [3.1.1](#311-keywords) |
| **Reserved words** | [3.1.1](#311-keywords) | **Underscore character** | [3.1.2](#312-identifiers) |
| **Enumeration constant** | [3.1.2](#312-identifiers) | **Length of names** | [3.1.2](#312-identifiers) |
| **Internal name, length of** | [3.1.2](#312-identifiers) | **External name, length of** | [3.1.2](#312-identifiers) |
| **Function name, length of** | [3.1.2](#312-identifiers) | **Scopes** | [3.1.2.1](#3121-scopes-of-identifiers) |
| **Prototype, function** | [3.1.2.1](#3121-scopes-of-identifiers) | **Function scope** | [3.1.2.1](#3121-scopes-of-identifiers) |
| **File scope** | [3.1.2.1](#3121-scopes-of-identifiers) | **Block scope** | [3.1.2.1](#3121-scopes-of-identifiers) |
| **Block structure** | [3.1.2.1](#3121-scopes-of-identifiers) | **Function prototype scope** | [3.1.2.1](#3121-scopes-of-identifiers) |
| **Linkage** | [3.1.2.2](#3122-linkages-of-identifiers) | **External linkage** | [3.1.2.2](#3122-linkages-of-identifiers) |
| **Internal linkage** | [3.1.2.2](#3122-linkages-of-identifiers) | **No linkage** | [3.1.2.2](#3122-linkages-of-identifiers) |
| **Name spaces** | [3.1.2.3](#3123-name-spaces-of-identifiers) | **Named label** | [3.1.2.3](#3123-name-spaces-of-identifiers) |
| **Structure tag** | [3.1.2.3](#3123-name-spaces-of-identifiers) | **Union tag** | [3.1.2.3](#3123-name-spaces-of-identifiers) |
| **Enumeration tag** | [3.1.2.3](#3123-name-spaces-of-identifiers) | **Structure member name** | [3.1.2.3](#3123-name-spaces-of-identifiers) |
| **Union member name** | [3.1.2.3](#3123-name-spaces-of-identifiers) | **Storage duration** | [3.1.2.4](#3124-storage-durations-of-objects) |
| **Static storage duration** | [3.1.2.4](#3124-storage-durations-of-objects) | **Automatic storage duration** | [3.1.2.4](#3124-storage-durations-of-objects) |
| **Types** | [3.1.2.5](#3125-types) | **Object types** | [3.1.2.5](#3125-types) |
| **Function types** | [3.1.2.5](#3125-types) | **Incomplete types** | [3.1.2.5](#3125-types) |
| **Char type** | [3.1.2.5](#3125-types) | **Signed character** | [3.1.2.5](#3125-types) |
| **Signed char type** | [3.1.2.5](#3125-types) | **Short type** | [3.1.2.5](#3125-types) |
| **Long type** | [3.1.2.5](#3125-types) | **Unsigned type** | [3.1.2.5](#3125-types) |
| **Float type** | [3.1.2.5](#3125-types) | **Double type** | [3.1.2.5](#3125-types) |
| **Long double type** | [3.1.2.5](#3125-types) | **Basic types** | [3.1.2.5](#3125-types) |
| **Character types** | [3.1.2.5](#3125-types) | **Enumerated type** | [3.1.2.5](#3125-types) |
| **Void type** | [3.1.2.5](#3125-types) | **Derived types** | [3.1.2.5](#3125-types) |
| **Integral types** | [3.1.2.5](#3125-types) | **Arithmetic types** | [3.1.2.5](#3125-types) |
| **Scalar types** | [3.1.2.5](#3125-types) | **Aggregate types** | [3.1.2.5](#3125-types) |
| **Constants** | [3.1.3](#313-constants) | **Floating constant** | [3.1.3.1](#3131-floating-constants) |
| **Double constant** | [3.1.3.1](#3131-floating-constants) | **Integer constant** | [3.1.3.2](#3132-integer-constants) |
| **Decimal constant** | [3.1.3.2](#3132-integer-constants) | **Octal constant** | [3.1.3.2](#3132-integer-constants) |
| **Hexadecimal constant** | [3.1.3.2](#3132-integer-constants) | **Unsigned constant** | [3.1.3.2](#3132-integer-constants) |
| **Long constant** | [3.1.3.2](#3132-integer-constants) | **Enumeration constant** | [3.1.3.3](#3133-enumeration-constants) |
| **Character constant** | [3.1.3.4](#3134-character-constants) | **Backslash character** | [3.1.3.4](#3134-character-constants) |
| **Escape character** | [3.1.3.4](#3134-character-constants) | **Escape sequence** | [3.1.3.4](#3134-character-constants) |
| **String literal** | [3.1.4](#314-string-literals) | **Character string** | [3.1.4](#314-string-literals) |
| **Operator** | [3.1.5](#315-operators) | **Evaluation** | [3.1.5](#315-operators) |
| **Operand** | [3.1.5](#315-operators) | **Punctuator** | [3.1.6](#316-punctuators) |
| **Character-integer conversion** | [3.2.1.1](#3211-characters-and-integers) | **Integer-character conversion** | [3.2.1.1](#3211-characters-and-integers) |
| **Integral promotions** | [3.2.1.1](#3211-characters-and-integers) | **Integer-long conversion** | [3.2.1.1](#3211-characters-and-integers) |
| **Signed character** | [3.2.1.1](#3211-characters-and-integers) | **Unsigned-integer conversion** | [3.2.1.2](#3212-signed-and-unsigned-integers) |
| **Integer-unsigned conversion** | [3.2.1.2](#3212-signed-and-unsigned-integers) | **Long-unsigned conversion** | [3.2.1.2](#3212-signed-and-unsigned-integers) |
| **Long-integer conversion** | [3.2.1.2](#3212-signed-and-unsigned-integers) | **Floating-integer conversion** | [3.2.1.3](#3213-floating-and-integral) |
| **Integer-floating conversion** | [3.2.1.3](#3213-floating-and-integral) | **Float-double conversion** | [3.2.1.4](#3214-floating-types) |
| **Double-float conversion** | [3.2.1.4](#3214-floating-types) | **Arithmetic conversions** | [3.2.1.5](#3215-usual-arithmetic-conversions) |
| **Type conversion rules** | [3.2.1.5](#3215-usual-arithmetic-conversions) | **Lvalue** | [3.2.2.1](#3221-lvalues-and-function-designators) |
| **Function designator** | [3.2.2.1](#3221-lvalues-and-function-designators) | **Conversion of array** | [3.2.2.1](#3221-lvalues-and-function-designators) |
| **Conversion of function name** | [3.2.2.1](#3221-lvalues-and-function-designators) | **Void type** | [3.2.2.2](#3222-void) |
| **Pointer-pointer conversion** | [3.2.2.3](#3223-pointers) | **Integer-pointer conversion** | [3.2.2.3](#3223-pointers) |
| **Null pointer** | [3.2.2.3](#3223-pointers) | **Expression** | [3.3](#33-expressions) |
| **Precedence of operators** | [3.3](#33-expressions) | **Associativity of operators** | [3.3](#33-expressions) |
| **Order of evaluation of expressions** | [3.3](#33-expressions) | **Order of evaluation** | [3.3](#33-expressions) |
| **Bitwise operators** | [3.3](#33-expressions) | **Exceptions** | [3.3](#33-expressions) |
| **Primary expression** | [3.3.1](#331-primary-expressions) | **Type of string** | [3.3.1](#331-primary-expressions) |
| **Parenthesized expression** | [3.3.1](#331-primary-expressions) | **Subscript operator** | [3.3.2](#332-postfix-operators) |
| **Function call** | [3.3.2](#332-postfix-operators) | **Structure member operator** | [3.3.2](#332-postfix-operators) |
| **Structure pointer operator** | [3.3.2](#332-postfix-operators) | **++ increment operator** | [3.3.2](#332-postfix-operators) |
| **-- decrement operator** | [3.3.2](#332-postfix-operators) | **Array, explanation of subscripting** | [3.3.2.1](#3321-array-subscripting) |
| **Subscripting, explanation of** | [3.3.2.1](#3321-array-subscripting) | **Multi-dimensional array** | [3.3.2.1](#3321-array-subscripting) |
| **Storage order of array** | [3.3.2.1](#3321-array-subscripting) | **Function call** | [3.3.2.2](#3322-function-calls) |
| **Implicit declaration of function** | [3.3.2.2](#3322-function-calls) | **Function argument** | [3.3.2.2](#3322-function-calls) |
| **Call by value** | [3.3.2.2](#3322-function-calls) | **Recursion** | [3.3.2.2](#3322-function-calls) |
| **Structure reference** | [3.3.2.3](#3323-structure-and-union-members) | **Union reference** | [3.3.2.3](#3323-structure-and-union-members) |
| **Common initial sequence** | [3.3.2.3](#3323-structure-and-union-members) | **Postfix ++ and --** | [3.3.2.4](#3324-postfix-increment-and-decrement-operators) |
| **-- decrement operator** | [3.3.2.4](#3324-postfix-increment-and-decrement-operators) | **Unary expression** | [3.3.3](#333-unary-operators) |
| **++ increment operator** | [3.3.3](#333-unary-operators) | **-- decrement operator** | [3.3.3](#333-unary-operators) |
| **Sizeof operator** | [3.3.3](#333-unary-operators) | **& address operator** | [3.3.3](#333-unary-operators) |
| *** indirection operator** | [3.3.3](#333-unary-operators) | **+ unary plus operator** | [3.3.3](#333-unary-operators) |
| **- unary minus operator** | [3.3.3](#333-unary-operators) | **~ bitwise complement operator** | [3.3.3](#333-unary-operators) |
| **! logical negation operator** | [3.3.3](#333-unary-operators) | **++ increment operator** | [3.3.3.1](#3331-prefix-increment-and-decrement-operators) |
| **Prefix ++ and --** | [3.3.3.1](#3331-prefix-increment-and-decrement-operators) | **-- decrement operator** | [3.3.3.1](#3331-prefix-increment-and-decrement-operators) |
| **+ unary plus operator** | [3.3.3.3](#3333-unary-arithmetic-operators) | **- unary minus operator** | [3.3.3.3](#3333-unary-arithmetic-operators) |
| **~ bitwise complement operator** | [3.3.3.3](#3333-unary-arithmetic-operators) | **! logical negation operator** | [3.3.3.3](#3333-unary-arithmetic-operators) |
| **Byte** | [3.3.3.4](#3334-the-sizeof-operator) | **Storage allocator** | [3.3.3.4](#3334-the-sizeof-operator) |
| **Cast expression** | [3.3.4](#334-cast-operators) | **Cast operator** | [3.3.4](#334-cast-operators) |
| **Explicit conversion operator** | [3.3.4](#334-cast-operators) | **Pointer conversion** | [3.3.4](#334-cast-operators) |
| **Explicit conversion operator** | [3.3.4](#334-cast-operators) | **Pointer-integer conversion** | [3.3.4](#334-cast-operators) |
| **Integer-pointer conversion** | [3.3.4](#334-cast-operators) | **Alignment restriction** | [3.3.4](#334-cast-operators) |
| **Arithmetic operators** | [3.3.5](#335-multiplicative-operators) | **Multiplicative operators** | [3.3.5](#335-multiplicative-operators) |
| *** multiplication operator** | [3.3.5](#335-multiplicative-operators) | **/ division operator** | [3.3.5](#335-multiplicative-operators) |
| **% modulus operator** | [3.3.5](#335-multiplicative-operators) | **Additive operators** | [3.3.6](#336-additive-operators) |
| **+ addition operator** | [3.3.6](#336-additive-operators) | **- subtraction operator** | [3.3.6](#336-additive-operators) |
| **Pointer arithmetic** | [3.3.6](#336-additive-operators) | **Shift operators** | [3.3.7](#337-bitwise-shift-operators) |
| **<< left shift operator** | [3.3.7](#337-bitwise-shift-operators) | **>> right shift operator** | [3.3.7](#337-bitwise-shift-operators) |
| **Relational operators** | [3.3.8](#338-relational-operators) | **< less than operator** | [3.3.8](#338-relational-operators) |
| **> greater than operator** | [3.3.8](#338-relational-operators) | **<= less than or equal to operator** | [3.3.8](#338-relational-operators) |
| **>= greater than or equal to operator** | [3.3.8](#338-relational-operators) | **Pointer comparison** | [3.3.8](#338-relational-operators) |
| **Equality operators** | [3.3.9](#339-equality-operators) | **== equality operator** | [3.3.9](#339-equality-operators) |
| **!= inequality operator** | [3.3.9](#339-equality-operators) | **& bitwise AND operator** | [3.3.10](#3310-bitwise-and-operator) |
| **^ bitwise exclusive OR operator** | [3.3.11](#3311-bitwise-exclusive-or-operator) | **\| bitwise inclusive OR operator** | [3.3.12](#3312-bitwise-inclusive-or-operator) |
| **&& logical AND operator** | [3.3.13](#3313-logical-and-operator) | **\|\| logical OR operator** | [3.3.14](#3314-logical-or-operator) |
| **?: conditional expression** | [3.3.15](#3315-conditional-operator) | **Assignment operators** | [3.3.16](#3316-assignment-operators) |
| **Assignment expression** | [3.3.16](#3316-assignment-operators) | **Simple assignment** | [3.3.16.1](#33161-simple-assignment) |
| **Conversion by assignment** | [3.3.16.1](#33161-simple-assignment) | **Compound assignment** | [3.3.16.2](#33162-compound-assignment) |
| **Comma operator** | [3.3.17](#3317-comma-operator) | **Constant expression** | [3.4](#34-constant-expressions) |
| **Permitted form of initializer** | [3.4](#34-constant-expressions) | **Declarations** | [3.5](#35-declarations) |
| **Storage-class specifier** | [3.5.1](#351-storage-class-specifiers) | **Storage-class declaration** | [3.5.1](#351-storage-class-specifiers) |
| **Typedef declaration** | [3.5.1](#351-storage-class-specifiers) | **Extern storage class** | [3.5.1](#351-storage-class-specifiers) |
| **Static storage class** | [3.5.1](#351-storage-class-specifiers) | **Auto storage class** | [3.5.1](#351-storage-class-specifiers) |
| **Register storage class** | [3.5.1](#351-storage-class-specifiers) | **Type specifier** | [3.5.2](#352-type-specifiers) |
| **Void type** | [3.5.2](#352-type-specifiers) | **Char type** | [3.5.2](#352-type-specifiers) |
| **Short type** | [3.5.2](#352-type-specifiers) | **Int type** | [3.5.2](#352-type-specifiers) |
| **Long type** | [3.5.2](#352-type-specifiers) | **Float type** | [3.5.2](#352-type-specifiers) |
| **Double type** | [3.5.2](#352-type-specifiers) | **Signed type** | [3.5.2](#352-type-specifiers) |
| **Unsigned type** | [3.5.2](#352-type-specifiers) | **Structure declaration** | [3.5.2.1](#3521-structure-and-union-specifiers) |
| **Union declaration** | [3.5.2.1](#3521-structure-and-union-specifiers) | **Bit-field declaration** | [3.5.2.1](#3521-structure-and-union-specifiers) |
| **Bit-field** | [3.5.2.1](#3521-structure-and-union-specifiers) | **Member alignment** | [3.5.2.1](#3521-structure-and-union-specifiers) |
| **Enumeration** | [3.5.2.2](#3522-enumeration-specifiers) | **Enum-specifier** | [3.5.2.2](#3522-enumeration-specifiers) |
| **Enumerator** | [3.5.2.2](#3522-enumeration-specifiers) | **Structure tag** | [3.5.2.3](#3523-tags) |
| **Union tag** | [3.5.2.3](#3523-tags) | **Structure content** | [3.5.2.3](#3523-tags) |
| **Union content** | [3.5.2.3](#3523-tags) | **Enumeration content** | [3.5.2.3](#3523-tags) |
| **Self-referential structure** | [3.5.2.3](#3523-tags) | **Type qualifier** | [3.5.3](#353-type-qualifiers) |
| **Const type qualifier** | [3.5.3](#353-type-qualifiers) | **Volatile type qualifier** | [3.5.3](#353-type-qualifiers) |
| **Declarator** | [3.5.4](#354-declarators) | **Type declaration** | [3.5.4](#354-declarators) |
| **Declaration of pointer** | [3.5.4.1](#3541-pointer-declarators) | **Array declaration** | [3.5.4.2](#3542-array-declarators) |
| **Declaration of function** | [3.5.4.3](#3543-function-declarators-including-prototypes) | **Type names** | [3.5.5](#355-type-names) |
| **Abstract declarator** | [3.5.5](#355-type-names) | **Typedef declaration** | [3.5.6](#356-type-definitions) |
| **Initialization** | [3.5.7](#357-initialization) | **Initialization of statics** | [3.5.7](#357-initialization) |
| **Implicit initialization** | [3.5.7](#357-initialization) | **Default initialization** | [3.5.7](#357-initialization) |
| **Initialization of automatics** | [3.5.7](#357-initialization) | **Aggregate initialization** | [3.5.7](#357-initialization) |
| **Array initialization** | [3.5.7](#357-initialization) | **Structure initialization** | [3.5.7](#357-initialization) |
| **Character array initialization** | [3.5.7](#357-initialization) | **Wchar_t array initialization** | [3.5.7](#357-initialization) |
| **Statements** | [3.6](#36-statements) | **Sequencing of statements** | [3.6](#36-statements) |
| **Full expression** | [3.6](#36-statements) | **Labeled statement** | [3.6.1](#361-labeled-statements) |
| **Named label** | [3.6.1](#361-labeled-statements) | **Case label** | [3.6.1](#361-labeled-statements) |
| **Default label** | [3.6.1](#361-labeled-statements) | **Compound statement** | [3.6.2](#362-compound-statement-or-block) |
| **Block** | [3.6.2](#362-compound-statement-or-block) | **Block structure** | [3.6.2](#362-compound-statement-or-block) |
| **Initialization in blocks** | [3.6.2](#362-compound-statement-or-block) | **Expression statement** | [3.6.3](#363-expression-and-null-statements) |
| **Null statement** | [3.6.3](#363-expression-and-null-statements) | **Empty statement** | [3.6.3](#363-expression-and-null-statements) |
| **If-else statement** | [3.6.4.1](#3641-the-if-statement) | **Switch statement** | [3.6.4.2](#3642-the-switch-statement) |
| **Switch body** | [3.6.4.2](#3642-the-switch-statement) | **Loop body** | [3.6.5](#365-iteration-statements) |
| **While statement** | [3.6.5.1](#3651-the-while-statement) | **Do statement** | [3.6.5.2](#3652-the-do-statement) |
| **For statement** | [3.6.5.3](#3653-the-for-statement) | **Goto statement** | [3.6.6.1](#3661-the-goto-statement) |
| **Continue statement** | [3.6.6.2](#3662-the-continue-statement) | **Break statement** | [3.6.6.3](#3663-the-break-statement) |
| **Return statement** | [3.6.6.4](#3664-the-return-statement) | **Type conversion by return** | [3.6.6.4](#3664-the-return-statement) |
| **Conversion by return** | [3.6.6.4](#3664-the-return-statement) | **External definition** | [3.7](#37-external-definitions) |
| **Function definition** | [3.7.1](#371-function-definitions) | **Parameter** | [3.7.1](#371-function-definitions) |
| **Array argument** | [3.7.1](#371-function-definitions) | **Function name argument** | [3.7.1](#371-function-definitions) |
| **Pointer to function** | [3.7.1](#371-function-definitions) | **Object definitions** | [3.7.2](#372-external-object-definitions) |
| **Scope of externals** | [3.7.2](#372-external-object-definitions) | **Tentative definition** | [3.7.2](#372-external-object-definitions) |
| **Preprocessing directives** | [3.8](#38-preprocessing-directives) | **Macro preprocessor** | [3.8](#38-preprocessing-directives) |
| **Preprocessing directive lines** | [3.8](#38-preprocessing-directives) | **Conditional inclusion** | [3.8.1](#381-conditional-inclusion) |
| **#if** | [3.8.1](#381-conditional-inclusion) | **#elif** | [3.8.1](#381-conditional-inclusion) |
| **#ifdef** | [3.8.1](#381-conditional-inclusion) | **#ifndef** | [3.8.1](#381-conditional-inclusion) |
| **#else** | [3.8.1](#381-conditional-inclusion) | **#endif** | [3.8.1](#381-conditional-inclusion) |
| **#include** | [3.8.2](#382-source-file-inclusion) | **Source file inclusion** | [3.8.2](#382-source-file-inclusion) |
| **Macro replacement** | [3.8.3](#383-macro-replacement) | **Object-like macro** | [3.8.3](#383-macro-replacement) |
| **Function-like macro** | [3.8.3](#383-macro-replacement) | **Macro name** | [3.8.3](#383-macro-replacement) |
| **#define** | [3.8.3](#383-macro-replacement) | **Macro parameters** | [3.8.3](#383-macro-replacement) |
| **Macro invocation** | [3.8.3](#383-macro-replacement) | **Argument substitution** | [3.8.3.1](#3831-argument-substitution) |
| **# operator** | [3.8.3.2](#3832-the--operator) | **## operator** | [3.8.3.3](#3833-the--operator) |
| **Rescanning and replacement** | [3.8.3.4](#3834-rescanning-and-further-replacement) | **Macro definition scope** | [3.8.3.5](#3835-scope-of-macro-definitions) |
| **#undef** | [3.8.3.5](#3835-scope-of-macro-definitions) | **#line** | [3.8.4](#384-line-control) |
| **Error directive** | [3.8.5](#385-error-directive) | **Pragma directive** | [3.8.6](#386-pragma-directive) |
| **Null directive** | [3.8.7](#387-null-directive) | **Introduction** | [4.1](#41-introduction) |
| **String definition** | [4.1.1](#411-definitions-of-terms) | **Letter definition** | [4.1.1](#411-definitions-of-terms) |
| **Decimal-point definition** | [4.1.1](#411-definitions-of-terms) | **Reserved identifier** | [4.1.2](#412-standard-headers) |
| **Printing character** | [4.3](#43-character-handling-ctypeh) | **Control character** | [4.3](#43-character-handling-ctypeh) |
| **Variable arguments** | [4.8](#48-variable-arguments-stdargh) | **Unbuffered stream** | [4.9.3](#493-files) |
| **Fully buffered stream** | [4.9.3](#493-files) | **Line buffered stream** | [4.9.3](#493-files) |
| **Appendices** | [A.](#a-appendices) | **Language syntax summary** | [A.1](#a1-language-syntax-summary) |
| **Sequence points** | [A.2](#a2-sequence-points) | **Library summary** | [A.3](#a3-library-summary) |
| **Implementation limits** | [A.4](#a4-implementation-limits) | **Warnings** | [A.5](#a5-common-warnings) |
| **Portability** | [A.6](#a6-portability-issues) | **Order of evaluation** | [A.6.1](#a61-unspecified-behavior) |
| **Machine dependency** | [A.6.3](#a63-implementation-defined-behavior) | **Restrictions on registers** | [A.6.3.7](#a637-registers) |
| **Function pointer casts** | [A.6.5.7](#a657-function-pointer-casts) | **Bit-field types** | [A.6.5.8](#a658-non-int-bit-field-types) |
| **Fortran keyword** | [A.6.5.9](#a659-the-fortran-keyword) | **Asm keyword** | [A.6.5.10](#a6510-the-asm-keyword) |
| **Multiple external definitions** | [A.6.5.11](#a6511-multiple-external-definitions) | **Empty macro arguments** | [A.6.5.12](#a6512-empty-macro-arguments) |
| **Predefined macro names** | [A.6.5.13](#a6513-predefined-macro-names) | **Signal handler arguments** | [A.6.5.14](#a6514-extra-arguments-for-signal-handlers) |
| **Stream types** | [A.6.5.15](#a6515-additional-stream-types-and-file-opening-modes) | **File-opening modes** | [A.6.5.15](#a6515-additional-stream-types-and-file-opening-modes) |
| **File position indicator** | [A.6.5.16](#a6516-defined-file-position-indicator) | **Foreword** | [A.7](#a7-index) |

## 1. INTRODUCTION

### 1.1 PURPOSE

This Standard specifies the form and establishes the interpretation of programs written in the C programming language. [^1]

### 1.2 SCOPE

This Standard specifies:

* the representation of C programs;

* the syntax and constraints of the C language;

* the semantic rules for interpreting C programs;

* the representation of input data to be processed by C programs;

* the representation of output data produced by C programs;

* the restrictions and limits imposed by a conforming implementation of C.

This Standard does not specify:

* the mechanism by which C programs are transformed for use by a data-processing system;

* the mechanism by which C programs are invoked for use by a data-processing system;

* the mechanism by which input data are transformed for use by a C program;

* the mechanism by which output data are transformed after being produced by a C program;

* the size or complexity of a program and its data that will exceed the capacity of any specific data-processing system or the capacity of a particular processor;

* all minimal requirements of a data-processing system that is capable of supporting a conforming implementation.

### 1.3 REFERENCES

1. "The C Reference Manual" by Dennis M. Ritchie, a version of which was published in The C Programming Language by Brian W. Kernighan and Dennis M. Ritchie, Prentice-Hall, Inc., (1978). Copyright owned by AT&T.

2. 1984 /usr/group Standard by the /usr/group Standards Committee, Santa Clara, California, USA (November, 1984).

3. American National Dictionary for Information Processing Systems, Information Processing Systems Technical Report ANSI X3/TR-1-82 (1982).

4. ISO 646-1983 Invariant Code Set.

5. IEEE Standard for Binary Floating-Point Arithmetic (ANSI/IEEE Std 754-1985).

6. ISO 4217 Codes for the Representation of Currency and Funds.

### 1.4 ORGANIZATION OF THE DOCUMENT

This document is divided into four major sections:

1. this introduction;

2. the characteristics of environments that translate and execute C programs;

3. the language syntax, constraints, and semantics;

4. the library facilities.

Examples are provided to illustrate possible forms of the constructions described. Footnotes are provided to emphasize consequences of the rules described in the section or elsewhere in the Standard. References are used to refer to other related sections. A set of appendices summarizes information contained in the Standard. The abstract, the foreword, the examples, the footnotes, the references, and the appendices are not part of the Standard.

### 1.5 BASE DOCUMENTS

The language section ([3.](#3-language)) is derived from ``The C Reference Manual'' by Dennis M. Ritchie, a version of which was published as Appendix A of The C Programming Language by Brian W. Kernighan and Dennis M. Ritchie, Prentice-Hall, Inc., 1978; copyright owned by AT&T.

The library section ([4.](#4-library)) is based on the 1984 /usr/group Standard by the /usr/group Standards Committee, Santa Clara, California, USA (November 14, 1984).

### 1.6 DEFINITIONS OF TERMS

In this Standard, "shall" is to be interpreted as a requirement on an implementation or on a program; conversely, "shall not" is to be interpreted as a prohibition.

The following terms are used in this document:

* Implementation --- a particular set of software, running in a particular translation environment under particular control options, that performs translation of programs for, and supports execution of functions in, a particular execution environment.

* Bit --- the unit of data storage in the execution environment large enough to hold an object that may have one of two values. It need not be possible to express the address of each individual bit of an object.

* Byte --- the unit of data storage in the execution environment large enough to hold any member of the basic character set of the execution environment. It shall be possible to express the address of each individual byte of an object uniquely. A byte is composed of a contiguous sequence of bits, the number of which is implementation-defined. The least significant bit is called the low-order bit; the most significant bit is called the high-order bit.

* Object --- a region of data storage in the execution environment, the contents of which can represent values. Except for bit-fields, objects are composed of contiguous sequences of one or more bytes, the number, order, and encoding of which are either explicitly specified or implementation-defined.

* Character --- a single byte representing a member of the basic character set of either the source or the execution environment.

* Multibyte character --- a sequence of one or more bytes representing a member of the extended character set of either the source or the execution environment. The extended character set is a superset of the basic character set.

* Alignment --- a requirement that objects of a particular type be located on storage boundaries with addresses that are particular multiples of a byte address.

* Argument --- an expression in the comma-separated list bounded by the parentheses in a function call expression, or a sequence of preprocessing tokens in the comma-separated list bounded by the parentheses in a function-like macro invocation. Also known as "actual argument" or "actual parameter."

* Parameter --- an object declared as part of a function declaration or definition that acquires a value on entry to the function, or an identifier from the comma-separated list bounded by the parentheses immediately following the macro name in a function-like macro definition. Also known as "formal argument" or "formal parameter."

* Unspecified behavior --- behavior, for a correct program construct and correct data, for which the Standard imposes no requirements.

* Undefined behavior --- behavior, upon use of a nonportable or erroneous program construct, of erroneous data, or of indeterminately-valued objects, for which the Standard imposes no requirements. Permissible undefined behavior ranges from ignoring the situation completely with unpredictable results, to behaving during translation or program execution in a documented manner characteristic of the environment (with or without the issuance of a diagnostic message), to terminating a translation or execution (with the issuance of a diagnostic message).

If a "shall" or "shall not" requirement that appears outside of a constraint is violated, the behavior is undefined. Undefined behavior is otherwise indicated in this Standard by the words "undefined behavior" or by the omission of any explicit definition of behavior. There is no difference in emphasis among these three; they all describe "behavior that is undefined."

* Implementation-defined behavior --- behavior, for a correct program construct and correct data, that depends on the characteristics of the implementation and that each implementation shall document.

* Locale-specific behavior --- behavior that depends on local conventions of nationality, culture, and language that each implementation shall document.

* Diagnostic message --- a message belonging to an implementation-defined subset of the implementation's message output.

* Constraints --- syntactic and semantic restrictions by which the exposition of language elements is to be interpreted.

* Implementation limits --- restrictions imposed upon programs by the implementation.

* Forward references --- references to later sections of the Standard that contain additional information relevant to this section.

Other terms are defined at their first appearance, indicated by *italic type*. Terms explicitly defined in this Standard are not to be presumed to refer implicitly to similar terms defined elsewhere.

Terms not defined in this Standard are to be interpreted according to the American National Dictionary for Information Processing Systems, Information Processing Systems Technical Report ANSI X3/TR-1-82 (1982).

**Forward references:** localization ([4.4](#44-localization-localeh)).

"Examples"

An example of unspecified behavior is the order in which the arguments to a function are evaluated.

An example of undefined behavior is the behavior on integer overflow.

An example of implementation-defined behavior is the propagation of the high-order bit when a signed integer is shifted right.

An example of locale-specific behavior is whether the `islower` function returns true for characters other than the 26 lower-case English letters.

**Forward references:** bitwise shift operators ([3.3.7](#337-bitwise-shift-operators)), expressions ([3.3](#33-expressions)), function calls ([3.3.2.2](#3322-function-calls)), the islower function ([4.3.1.6](#4316-the-islower-function)).

### 1.7 COMPLIANCE

A *strictly conforming program* shall use only those features of the language and library specified in this Standard. It shall not produce output dependent on any unspecified, undefined, or implementation-defined behavior, and shall not exceed any minimum implementation limit.

The two forms of conforming implementation are hosted and freestanding. A *conforming hosted implementation* shall accept any strictly conforming program. A *conforming freestanding implementation* shall accept any strictly conforming program in which the use of the features specified in the library section ([4.](#4-library)) is confined to the contents of the standard headers `<float.h>`, `<limits.h>`, `<stdarg.h>`, and `<stddef.h>`. A conforming implementation may have extensions (including additional library functions), provided they do not alter the behavior of any strictly conforming program.

A *conforming program* is one that is acceptable to a conforming implementation. [^2]

An implementation shall be accompanied by a document that defines all implementation-defined characteristics and all extensions.

**Forward references**: limits <float.h> and <limits.h> ([4.1.4](#414-limits-floath-and-limitsh)), variable arguments <stdarg.h> ([4.8](#48-variable-arguments-stdargh)), common definitions <stddef.h> ([4.1.5](#415-common-definitions-stddefh)).

### 1.8 FUTURE DIRECTIONS

With the introduction of new devices and extended character sets, new features may be added to the Standard. Subsections in the language and library sections warn implementors and programmers of usages which, though valid in themselves, may conflict with future additions.

Certain features are *obsolescent*, which means that they may be considered for withdrawal in future revisions of the Standard. They are retained in the Standard because of their widespread use, but their use in new implementations (for implementation features) or new programs (for language or library features) is discouraged.

**Forward references**: future language directions ([3.9.9](#39-future-language-directions)), future library directions ([4.13](#413-future-library-directions)).

### 1.9 ABOUT THIS DRAFT

Symbols in the right margin mark substantive differences between this draft and its predecessor (ANSI X3J11/88-001, January 11, 1988). A plus sign indicates an addition, a minus sign a deletion, and a vertical bar a replacement.

This section and the difference marks themselves will not appear in the published document.

## 2. ENVIRONMENT

An implementation translates C source files and executes C programs in two data-processing-system environments, which will be called the *translation environment* and the *execution environment* in this Standard. Their characteristics define and constrain the results of executing conforming C programs constructed according to the syntactic and semantic rules for conforming implementations.

**Forward references**: In the environment section [2.](#2-environment), only a few of many possible forward references have been noted.

### 2.1 CONCEPTUAL MODELS

#### 2.1.1 Translation environment

##### 2.1.1.1 Program structure

A C program need not all be translated at the same time. The text of the program is kept in units called *source files* in this Standard. A source file together with all the headers and source files included via the preprocessing directive `#include`, less any source lines skipped by any of the conditional inclusion preprocessing directives, is called a *translation unit*. Previously translated translation units may be preserved individually or in libraries. The separate translation units of a program communicate by (for example) calls to functions whose identifiers have external linkage, by manipulation of objects whose identifiers have external linkage, and by manipulation of data files. Translation units may be separately translated and then later linked to produce an *executable program*.

**Forward references**: conditional inclusion ([3.8.1](#381-conditional-inclusion)), linkages of identifiers ([3.1.2.2](#3122-linkages-of-identifiers)), source file inclusion ([3.8.2](#382-source-file-inclusion)).

##### 2.1.1.2 Translation phases

The precedence among the syntax rules of translation is specified by the following phases.[^3]

1. Physical source file characters are mapped to the source character set (introducing new-line characters for end-of-line indicators) if necessary. Trigraph sequences are replaced by corresponding single-character internal representations.

2. Each instance of a new-line character and an immediately preceding backslash character is deleted, splicing physical source lines to form *logical source lines*. A source file that is not empty shall end in a new-line character, which shall not be immediately preceded by a backslash character.

3. The source file is decomposed into preprocessing tokens[^4] and sequences of white-space characters (including comments). A source file shall not end in a partial preprocessing token or comment. Each comment is replaced by one space character. New-line characters are retained. Whether each nonempty sequence of other white-space characters is retained or replaced by one space character is implementation-defined.

4. Preprocessing directives are executed and macro invocations are expanded. A `#include` preprocessing directive causes the named header or source file to be processed from phase 1 through phase 4, recursively.

5. Each escape sequence in character constants and string literals is converted to a member of the execution character set.

6. Adjacent character string literal tokens are concatenated and adjacent wide string literal tokens are concatenated.

7. White-space characters separating tokens are no longer significant. Preprocessing tokens are converted into tokens. The resulting tokens are syntactically and semantically analyzed and translated.

8. All external object and function references are resolved. Library components are linked to satisfy external references to functions and objects not defined in the current translation. All such translator output is collected into a *program image* which contains information needed for execution in its execution environment.

**Forward references**: lexical elements ([3.1](#31-lexical-elements)), preprocessing directives ([3.8](#38-preprocessing-directives)), trigraph sequences ([2.2.1.1](#2211-trigraph-sequences)).

##### 2.1.1.3 Diagnostics

A conforming implementation shall produce at least one diagnostic message (identified in an implementation-defined manner) for every translation unit that contains a violation of any syntax rule or constraint. Diagnostic messages need not be produced in other circumstances.

#### 2.1.2 Execution environments

Two execution environments are defined: *freestanding* and *hosted*. In both cases, *program startup* occurs when a designated C function is called by the execution environment. All objects in static storage shall be initialized (set to their initial values) before program startup. The manner and timing of such initialization are otherwise unspecified. *Program termination* returns control to the execution environment.

**Forward references**: initialization ([3.5.7](#357-initialization)).

##### 2.1.2.1 Freestanding environment

In a freestanding environment (in which C program execution may take place without any benefit of an operating system), the name and type of the function called at program startup are implementation-defined. There are otherwise no reserved external identifiers. Any library facilities available to a freestanding program are implementation-defined.

The effect of program termination in a freestanding environment is implementation-defined.

##### 2.1.2.2 Hosted environment

A hosted environment need not be provided, but shall conform to the following specifications if present.

"Program startup"

The function called at program startup is named `main`. The implementation declares no prototype for this function. It can be defined with no parameters:

```c
int main(void) { /*...*/ }
```

or with two parameters (referred to here as `argc` and `argv`, though any names may be used, as they are local to the function in which they are declared):

```c
int main(int argc, char *argv[]) { /*...*/ }
```

If they are defined, the parameters to the main function shall obey the following constraints:

* The value of `argc` shall be nonnegative.

* `argv[argc]` shall be a null pointer.

* If the value of `argc` is greater than zero, the array members `argv[0]` through `argv[argc-1]` inclusive shall contain pointers to strings, which are given implementation-defined values by the host environment prior to program startup. The intent is to supply to the program information determined prior to program startup from elsewhere in the hosted environment. If the host environment is not capable of supplying strings with letters in both upper-case and lower-case, the implementation shall ensure that the strings are received in lower-case.

* If the value of `argc` is greater than zero, the string pointed to by `argv[0]` represents the program name; `argv[0][0]` shall be the null character if the program name is not available from the host environment. If the value of `argc` is greater than one, the strings pointed to by `argv[1]` through `argv[argc-1]` represent the program parameters.

* The parameters `argc` and `argv` and the strings pointed to by the argv array shall be modifiable by the program, and retain their last-stored values between program startup and program termination.

"Program execution"

In a hosted environment, a program may use all the functions, macros, type definitions, and objects described in the library section (4.).

"Program termination"

A return from the initial call to the `main` function is equivalent to calling the exit function with the value returned by the `main` function as its argument. If the `main` function executes a return that specifies no value, the termination status returned to the host environment is undefined.

**Forward references**: definition of terms ([4.1.1](#411-definitions-of-terms)), the exit function ([4.10.4.3](#41043-the-exit-function)).

##### 2.1.2.3 Program execution

The semantic descriptions in this Standard describe the behavior of an *abstract machine* in which issues of optimization are irrelevant.

Accessing a volatile object, modifying an object, modifying a file, or calling a function that does any of those operations are all *side effects*, which are changes in the state of the execution environment. Evaluation of an expression may produce side effects. At certain specified points in the execution sequence called `sequence points`, all side effects of previous evaluations shall be complete and no side effects of subsequent evaluations shall have taken place.

In the abstract machine, all expressions are evaluated as specified by the semantics. An actual implementation need not evaluate part of an expression if it can deduce that its value is not used and that no needed side effects are produced (including any caused by calling a function or accessing a volatile object).

When the processing of the abstract machine is interrupted by receipt of a signal, only the values of objects as of the previous sequence point may be relied on. Objects that may be modified between the previous sequence point and the next sequence point need not have received their correct values yet.

An instance of each object with automatic storage duration is associated with each entry into a block. Such an object exists and retains its last-stored value during the execution of the block and while the block is suspended (by a call of a function or receipt of a signal).

The least requirements on a conforming implementation are:

* At sequence points, volatile objects are stable in the sense that previous evaluations are complete and subsequent evaluations have not yet occurred.

* At program termination, all data written into files shall be identical to the result that execution of the program according to the abstract semantics would have produced.

* The input and output dynamics of interactive devices shall take place as specified in [4.9.3](#493-files). The intent of these requirements is that unbuffered or line-buffered output appear as soon as possible, to ensure that prompting messages actually appear prior to a program waiting for input.

What constitutes an `interactive device` is implementation-defined.

More stringent correspondences between abstract and actual semantics may be defined by each implementation.

"Examples"

An implementation might define a one-to-one correspondence between abstract and actual semantics: at every sequence point, the values of the actual objects would agree with those specified by the abstract semantics. The keyword volatile would then be redundant.

Alternatively, an implementation might perform various optimizations within each translation unit, such that the actual semantics would agree with the abstract semantics only when making function calls across translation unit boundaries. In such an implementation, at the time of each function entry and function return where the calling function and the called function are in different translation units, the values of all externally linked objects and of all objects accessible via pointers therein would agree with the abstract semantics. Furthermore, at the time of each such function entry the values of the parameters of the called function and of all objects accessible via pointers therein would agree with the abstract semantics. In this type of implementation, objects referred to by interrupt service routines activated by the signal function would require explicit specification of volatile storage, as well as other implementation-defined restrictions.

In executing the fragment

```c
char c1, c2;
/*...*/
c1 = c1 + c2;
```

the "integral promotions" require that the abstract machine promote the value of each variable to `int` size and then add the two `int`s and truncate the sum. Provided the addition of two `char`s can be done without creating an overflow exception, the actual execution need only produce the same result, possibly omitting the promotions.

Similarly, in the fragment

```c
float f1, f2;
double d;
/*...*/
f1 = f2 * d;
```

the multiplication may be executed using single-precision arithmetic if the implementation can ascertain that the result would be the same as if it were executed using double-precision arithmetic (for example, if `d` were replaced by the constant `2.0`, which has type `double`). Alternatively, an operation involving only `int`s or `float`s may be executed using double-precision operations if neither range nor precision is lost thereby.

**Forward references**: compound statement, or block ([3.6.2](#362-compound-statement-or-block)), files ([4.9.3](#493-files)), sequence points ([3.3](#33-expressions), [3.6](#36-statements)), the signal function ([4.7](#47-signal-handling-signalh)), type qualifiers ([3.5.3](#353-type-qualifiers)).

### 2.2 ENVIRONMENTAL CONSIDERATIONS

#### 2.2.1 Character sets

Two sets of characters and their associated collating sequences shall be defined: the set in which source files are written, and the set interpreted in the execution environment. The values of the members of the *execution character set* are implementation-defined; any additional members beyond those required by this section are locale-specific.

In a character constant or string literal, members of the execution character set shall be represented by corresponding members of the *source character set* or by escape sequences consisting of the backslash `\` followed by one or more characters. A byte with all bits set to 0, called the *null character*, shall exist in the basic execution character set; it is used to terminate a character string literal.

Both the basic source and basic execution character sets shall have at least the following members: the 26 upper-case letters of the English alphabet
>
> **A** **B** **C** **D** **E** **F** **G** **H** **I** **J** **K** **L** **M**
>
> **N** **O** **P** **Q** **R** **S** **T** **U** **V** **W** **X** **Y** **Z**
>
the 26 lower-case letters of the English alphabet
>
> **a** **b** **c** **d** **e** **f** **g** **h** **i** **j** **k** **l** **m**
>
> **n** **o** **p** **q** **r** **s** **t** **u** **v** **w** **x** **y** **z**
>
the 10 decimal digits
>
> **0** **1** **2** **3** **4** **5** **6** **7** **8** **9**
>
the following 29 graphic characters
>
>**\!** **\"** **\#** **\%** **\&** **\'** **\(** **\)** **\*** **\+** **\,** **\-** **\.** **\/** **\:**
>
> **\;** **\<** **\=** **\>** **\?** **\[** **\\** **\]** **\^** **\_** **\{** **\|** **\}** **\~**
>
the space character, and control characters representing horizontal tab, vertical tab, and form feed. In both the source and execution basic character sets, the value of each character after `0` in the above list of decimal digits shall be one greater than the value of the previous. In source files, there shall be some way of indicating the end of each line of text; this Standard treats such an end-of-line indicator as if it were a single new-line character. In the execution character set, there shall be control characters representing alert, backspace, carriage return, and new line. If any other characters are encountered in a source file (except in a preprocessing token that is never converted to a token, a character constant, a string literal, or a comment), the behavior is undefined.

**Forward references**: character constants ([3.1.3.4](#3134-character-constants)), preprocessing directives ([3.8](#38-preprocessing-directives)), string literals ([3.1.4](#314-string-literals)), comments ([3.1.9](#319-comments)).

##### 2.2.1.1 Trigraph sequences

All occurrences in a source file of the following sequences of three characters (called *trigraph sequences*[^5]) are replaced with the corresponding single character.

|   |   |
| :--- | :--- |
| `??=` | `#` |
| `??(` | `[` |
| `??/` | `\` |
| `??)` | `]` |
| `??'` | `^` |
| `??<` | `{` |
| `??!` | <code>\|</code> |
| `??>` | `}` |
| `??-` | `~` |

No other trigraph sequences exist. Each `?` that does not begin one of the trigraphs listed above is not changed.

###### Example

The following source line
```c
         printf("Eh???/n");
```

becomes (after replacement of the trigraph sequence `??/`)

```c
         printf("Eh?\n");
```

##### 2.2.1.2 Multibyte characters

The source character set may contain multibyte characters, used to represent members of the extended character set. The execution character set may also contain multibyte characters, which need not have the same encoding as for the source character set. For both character sets, the following shall hold:

* The single-byte characters defined in [2.2.1](#221-character-sets) shall be present.

* The presence, meaning, and representation of any additional members is locale-specific.

* A multibyte character may have a *state-dependent encoding*, wherein each sequence of multibyte characters begins in an initial shift state and enters other implementation-defined *shift states* when specific multibyte characters are encountered in the sequence. While in the *initial shift state*, all single-byte characters retain their usual interpretation and do not alter the shift state. The interpretation for subsequent bytes in the sequence is a function of the current shift state.

* A byte with all bits zero shall be interpreted as a null character independent of shift state.

* A byte with all bits zero shall not occur in the second or subsequent bytes of a multibyte character.

For the source character set, the following shall hold:

* A comment, string literal, character constant, or header name shall begin and end in the initial shift state.

* A comment, string literal, character constant, or header name shall consist of a sequence of valid multibyte characters.

#### 2.2.2 Character display semantics

The *active position* is that location on a display device where the next character output by the fputc function would appear. The intent of writing a printable character (as defined by the `isprint` function) to a display device is to display a graphic representation of that character at the active position and then advance the active position to the next position on the current line. The direction of printing is locale-specific. If the active position is at the final position of a line (if there is one), the behavior is unspecified.

Alphabetic escape sequences representing nongraphic characters in the execution character set are intended to produce actions on display devices as follows: (*alert*) Produces an audible or visible alert. The active position shall not be changed. (*backspace*) Moves the active position to the previous position on the current line. If the active position is at the initial position of a line, the behavior is unspecified. (*form feed*) Moves the active position to the initial position at the start of the next logical page. (*new line*) Moves the active position to the initial position of the next line. (*carriage return*) Moves the active position to the initial position of the current line. (*horizontal tab*) Moves the active position to the next horizontal tabulation position on the current line. If the active position is at or past the last defined horizontal tabulation position, the behavior is unspecified. (*vertical tab*) Moves the active position to the initial position of the next vertical tabulation position. If the active position is at or past the last defined vertical tabulation position, the behavior is unspecified.

Each of these escape sequences shall produce a unique implementation-defined value which can be stored in a single char object. The external representations in a text file need not be identical to the internal representations, and are outside the scope of this Standard.

**Forward references**: the fputc function ([4.9.7.3](#4973-the-fputc-function)), the isprint function ([4.3.1.7](#4317-the-isprint-function)).

#### 2.2.3 Signals and interrupts

Functions shall be implemented such that they may be interrupted at any time by a signal, or may be called by a signal handler, or both, with no alteration to earlier, but still active, invocations' control flow (after the interruption), function return values, or objects with automatic storage duration. All such objects shall be maintained outside the *function image* (the instructions that comprise the executable representation of a function) on a per-invocation basis.

The functions in the standard library are not guaranteed to be reentrant and may modify objects with static storage duration.

#### 2.2.4 Environmental limits

Both the translation and execution environments constrain the implementation of language translators and libraries. The following summarizes the environmental limits on a conforming implementation.

##### 2.2.4.1 Translation limits

The implementation shall be able to translate and execute at least one program that contains at least one instance of every one of the following limits:[^6]

* 15 nesting levels of compound statements, iteration control structures, and selection control structures

* 8 nesting levels of conditional inclusion

* 12 pointer, array, and function declarators (in any combinations) modifying an arithmetic, a structure, a union, or an incomplete type in a declaration

* 31 declarators nested by parentheses within a full declarator

* 32 expressions nested by parentheses within a full expression

* 31 significant initial characters in an internal identifier or a macro name

* 6 significant initial characters in an external identifier

* 511 external identifiers in one translation unit

* 127 identifiers with block scope declared in one block

* 1024 macro identifiers simultaneously defined in one translation unit

* 31 parameters in one function definition

* 31 arguments in one function call

* 31 parameters in one macro definition

* 31 arguments in one macro invocation

* 509 characters in a logical source line

* 509 characters in a character string literal or wide string literal (after concatenation)

* 32767 bytes in an object (in a hosted environment only)

* 8 nesting levels for `#include`'d files

* 257 case labels for a switch statement (excluding those for any nested switch statements)

* 127 members in a single structure or union

* 127 enumeration constants in a single enumeration

* 15 levels of nested structure or union definitions in a single struct-declaration-list
 
##### 2.2.4.2 Numerical limits

A conforming implementation shall document all the limits specified in this section, which shall be specified in the headers `<limits.h>` and `<float.h>`.

"Sizes of integral types `<limits.h>`"

The values given below shall be replaced by constant expressions suitable for use in `#if` preprocessing directives. Their implementation-defined values shall be equal or greater in magnitude (absolute value) to those shown, with the same sign.

* maximum number of bits for smallest object that is not a bit-field (byte) `CHAR_BIT` `8`

* minimum value for an object of type signed char `SCHAR_MIN` `-127`

* maximum value for an object of type signed char `SCHAR_MAX` `+127`

* maximum value for an object of type unsigned char `UCHAR_MAX` `255`

* minimum value for an object of type char `CHAR_MIN` see below

* maximum value for an object of type char `CHAR_MAX` see below

* maximum number of bytes in a multibyte character, for any supported locale `MB_LEN_MAX` `1`

* minimum value for an object of type short int `SHRT_MIN` `-32767`

* maximum value for an object of type short int `SHRT_MAX` `+32767`

* maximum value for an object of type unsigned short int `USHRT_MAX` `65535`

* minimum value for an object of type int `INT_MIN` `-32767`

* maximum value for an object of type int `INT_MAX` `+32767`

* maximum value for an object of type unsigned int `UINT_MAX` `65535`

* minimum value for an object of type long int `LONG_MIN` `-2147483647`

* maximum value for an object of type long int `LONG_MAX` `+2147483647`

* maximum value for an object of type unsigned long int `ULONG_MAX` `4294967295`

If the value of an object of type char sign-extends when used in an expression, the value of `CHAR_MIN` shall be the same as that of `SCHAR_MIN` and the value of `CHAR_MAX` shall be the same as that of `SCHAR_MAX`. If the value of an object of type char does not sign-extend when used in an expression, the value of `CHAR_MIN` shall be 0 and the value of `CHAR_MAX` shall be the same as that of `UCHAR_MAX`. [^7]

"Characteristics of floating types `<float.h>`"

The characteristics of floating types are defined in terms of a model that describes a representation of floating-point numbers and values that provide information about an implementation's floating-point arithmetic. The following parameters are used to define the model for each floating-point type:

A *normalized floating-point number* $x$ ($f_1 > 0$ if $x$ is defined by the following model):[^8] 

```math
x = s \times b^e \times \sum_{k=1}^{p} (f_k \times b^{-k}), \quad e_{min} \le e \le e_{max}
```

Of the values in the `<float.h>` header, `FLT_RADIX` shall be a constant expression suitable for use in `#if` preprocessing directives; all other values need not be constant expressions. All except `FLT_RADIX` and `FLT_ROUNDS` have separate names for all three floating-point types. The floating-point model representation is provided for all values except `FLT_ROUNDS`.

The rounding mode for floating-point addition is characterized by the value of `FLT_ROUNDS`: `-1` indeterminable, `0` toward zero, `1` to nearest, `2` toward positive infinity, `3` toward negative infinity. All other values for `FLT_ROUNDS` characterize implementation-defined rounding behavior.

The values given in the following list shall be replaced by implementation-defined expressions that shall be equal or greater in magnitude (absolute value) to those shown, with the same sign.

* radix of exponent representation, *b*

|   |   |
| :--- | :--- |
| `FLT_RADIX` | `2` |

* number of base-`FLT_RADIX` digits in the floating-point mantissa, *p*

|   |   |
| :--- | :----- |
| `FLT_MANT_DIG` |   |
| `DBL_MANT_DIG` |   |
| `LDBL_MANT_DIG` |   |

* number of decimal digits of precision,
```math
\lfloor (p - 1) \times \log_{10} b \rfloor + 
\begin{cases} 
1 & \text{if } b \text{ is a power of 10} \\ 
0 & \text{otherwise} 
\end{cases}
```

|   |   |
| :--- | :----- |
| `FLT_DIG` | `6` |
| `DBL_DIG` | `10` |
| `LDBL_DIG` |  `10` |

* minimum negative integer such that `FLT_RADIX` raised to that power minus 1 is a normalized floating-point number, *$e_{min}$*

|   |   |
| :--- | :----- |
| `FLT_MIN_EXP` |   |
| `DBL_MIN_EXP` |   |
| `LDBL_MIN_EXP` |   |

* minimum negative integer such that 10 raised to that power is in the range of normalized floating-point numbers,

|   |   |
| :--- | :----- |
| `FLT_MIN_10_EXP` | `-37` |
| `DBL_MIN_10_EXP` | `-37` |
| `LDBL_MIN_10_EXP` | `-37` |

* maximum integer such that `FLT_RADIX` raised to that power minus 1 is a representable finite floating-point number, *$e_{max}$*

|   |   |
| :--- | :----- |
| `FLT_MAX_EXP` |   |
| `DBL_MAX_EXP` |   |
| `LDBL_MAX_EXP` |   |

* maximum integer such that 10 raised to that power is in the range of representable finite floating-point numbers,

|   |   |
| :--- | :----- |
| `FLT_MAX_10_EXP` | `+37` |
| `DBL_MAX_10_EXP` | `+37` |
| `LDBL_MAX_10_EXP` | `+37` |

The values given in the following list shall be replaced by implementation-defined expressions with values that shall be equal to or greater than those shown.

* maximum representable finite floating-point number,

|   |   |
| :--- | :----- |
| `FLT_MAX` | `1E+37` |
| `DBL_MAX` | `1E+37` |
| `LDBL_MAX` | `1E+37` |

The values given in the following list shall be replaced by implementation-defined expressions with values that shall be equal to or smaller than those shown.

* minimum positive floating-point number $x$ such that $1.0 + x$

|   |   |
| :--- | :----- |
| `FLT_EPSILON` | `1E-5` |
| `DBL_EPSILON` | `1E-9` |
| `LDBL_EPSILON` | `1E-9` |

* minimum normalized positive floating-point number, $b^{ e_{min} - 1 }$

|   |   |
| :--- | :----- |
| `FLT_MIN` | `1E-37` |
| `DBL_MIN` | `1E-37` |
| `LDBL_MIN` | `1E-37` |

###### Examples

The following describes an artificial floating-point representation that meets the minimum requirements of the Standard, and the appropriate values in a <float.h> header for type `float`:

```math
x = s \times 16^{e} \times \sum_{k=1}^{6} f_k \times 16^{-k}, \qquad -31 \le e \le +32
```
<br/>

|   |   |
| :--- | :--- |
| `FLT_RADIX` | `16` |
| `FLT_MANT_DIG` | `6` |
| `FLT_EPSILON` | `9.53674316E-07F` |
| `FLT_DIG` | `6` |
| `FLT_MIN_EXP` | `-31` |
| `FLT_MIN` | `2.93873588E-39F` |
| `FLT_MIN_10_EXP` | `-38` |
| `FLT_MAX_EXP` | `+32` |
| `FLT_MAX` | `3.40282347E+38F` |
| `FLT_MAX_10_EXP` | `+38` |

The following describes floating-point representations that also meet the requirements for single-precision and double-precision normalized numbers in the IEEE Standard for Binary Floating-Point Arithmetic (ANSI/IEEE Std 754-1985),[^9] b and the appropriate values in a <float.h> header for types `float` and `double`: 

```math
x_f = s \times 2^{e} \times \sum_{k=1}^{24} f_k \times 2^{-k}, \qquad -125 \le e \le +128
```

```math
x_d = s \times 2^{e} \times \sum_{k=1}^{53} f_k \times 2^{-k}, \qquad -1021 \le e \le +1024
```
<br/>

|   |   |   |   |
| :--- | :--- | :--- | :--- |
| `FLT_RADIX` | `2` |   |   |
| `FLT_MANT_DIG` | `24` | `DBL_MANT_DIG` | `53` |
| `FLT_EPSILON` | `1.19209290E-07F` | `DBL_EPSILON` | `2.2204460492503131E-16` |
| `FLT_DIG` | `6` | `DBL_DIG` | `15` |
| `FLT_MIN_EXP` | `-125` | `DBL_MIN_EXP` | `-1021` |
| `FLT_MIN` | `1.17549435E-38F` | `DBL_MIN` | `2.2250738585072016E-308` |
| `FLT_MIN_10_EXP` | `-37` | `DBL_MIN_10_EXP` | `-307` |
| `FLT_MAX_EXP` | `+128` | `DBL_MAX_EXP` | `+1024` |
| `FLT_MAX` | `3.40282347E+38F` | `DBL_MAX` | `1.7976931348623157E+308` |
| `FLT_MAX_10_EXP` | `+38` | `DBL_MAX_10_EXP` | `+308` |

The values shown above for `FLT_EPSILON` and `DBL_EPSILON` are appropriate for the ANSI/IEEE Std 754-1985 default rounding mode (to nearest). Their values may differ for other rounding modes.

**Forward references**: conditional inclusion ([3.8.1](#381-conditional-inclusion)). conditional inclusion ([3.8.1](#381-conditional-inclusion)).

## 3. LANGUAGE

In the syntax notation used in the language section ([3.](#3-language)), syntactic categories (nonterminals) are indicated by italic type, and literal words and character set members (terminals) by bold type. A colon (:) following a nonterminal introduces its definition. Alternative definitions are listed on separate lines, except when prefaced by the words "one of." An optional symbol is indicated by the so that

> **{** &nbsp; *expression<sub>opt</sub>* &nbsp; **}**

indicates an optional expression enclosed in braces.

### 3.1 LEXICAL ELEMENTS

###### Syntax

*token:*
> 
> [*keyword*](#311-keywords)
> 
> [*identifier*](#312-identifiers)
> 
> [*constant*](#313-constants)
> 
> [*string-literal*](#314-string-literals)
> 
> [*operator*](#315-operators)
> 
> [*punctuator*](#316-punctuators)
> 
*preprocessing-token:*
> 
> [*header-name*](#317-header-names)
> 
> [*identifier*](#312-identifiers)
> 
> [*pp-number*](#318-preprocessing-numbers)
> 
> [*character-constant*](#3134-character-constants)
> 
> [*string-literal*](#314-string-literals)
> 
> [*operator*](#315-operators)
> 
> [*punctuator*](#316-punctuators)
> 
> **<sub>each non-white-space character that cannot be one of the above</sub>**
>

###### Constraints

Each preprocessing token that is converted to a token shall have the lexical form of a keyword, an identifier, a constant, a string literal, an operator, or a punctuator.

###### Semantics

A *token* is the minimal lexical element of the language in translation phases 7 and 8. The categories of tokens are: keywords, identifiers, constants, string literals, operators, and punctuators. A *preprocessing token* is the minimal lexical element of the language in translation phases 3 through 6. The categories of preprocessing token are: header names, identifiers, preprocessing numbers, character constants, string literals, operators, punctuators, and single non-white-space characters that do not lexically match the other preprocessing token categories. If a `'` or a `"` character matches the last category, the behavior is undefined. Comments (described later) and the characters space, horizontal tab, new-line, vertical tab, and form-feed --- collectively called *white space* --- can separate preprocessing tokens. As described in [3.8](#38-preprocessing-directives), in certain circumstances during translation phase 4, white space (or the absence thereof) serves as more than preprocessing token separation. White space may appear within a preprocessing token only as part of a header name or between the quotation characters in a character constant or string literal.

If the input stream has been parsed into preprocessing tokens up to a given character, the next preprocessing token is the longest sequence of characters that could constitute a preprocessing token.

###### Examples

The program fragment `1Ex` is parsed as a preprocessing number token (one that is not a valid floating or integer constant token), even though a parse as the pair of preprocessing tokens `1` and `Ex` might produce a valid expression (for example, if `Ex` were a macro defined as `+1` ). Similarly, the program fragment `1E1` is parsed as a preprocessing number (one that is a valid floating constant token), whether or not `E` is a macro name.

The program fragment `x+++++y` is parsed as `x ++ ++ + y`, which violates a constraint on increment operators, even though the parse `x ++ + ++ y` might yield a correct expression.

**Forward references**: character constants ([3.1.3.4](#3134-character-constants)), comments ([3.1.9](#319-comments)), expressions ([3.3](#33-expressions)), floating constants ([3.1.3.1](#3131-floating-constants)), header names ([3.1.7](#317-header-names)), macro replacement ([3.8.3](#383-macro-replacement)), postfix increment and decrement operators ([3.3.2.4](#3324-postfix-increment-and-decrement-operators)), prefix increment and decrement operators ([3.3.3.1](#3331-prefix-increment-and-decrement-operators)), preprocessing directives ([3.8](#38-preprocessing-directives)), preprocessing numbers ([3.1.8](#318-preprocessing-numbers)), string literals ([3.1.4](#314-string-literals)).

#### 3.1.1 Keywords

###### Syntax

*keyword:* <sub>one of</sub>
> 
> **auto**  **double** **int** **struct**
> 
> **break** **else** **long** **switch**
> 
> **case** **enum** **register** **typedef**
> 
> **char** **extern** **return** **union**
> 
> **const** **float** **short** **unsigned**
> 
> **continue** **for** **signed** **void**
> 
> **default** **goto** **sizeof** **volatile**
> 
> **do** **if** **static** **while**
> 
###### Semantics

The above tokens (entirely in lower-case) are reserved (in translation phases 7 and 8) for use as keywords, and shall not be used otherwise.

#### 3.1.2 Identifiers

###### Syntax

<a name="identifier"></a>
*identifier:*
> 
> [*nondigit*](#nondigit)
> 
> [*identifier*](#identifier) &nbsp; [*nondigit*](#nondigit)
> 
> [*identifier*](#identifier) &nbsp; [*digit*](#digit)
> 
<a name="nondigit"></a>
*nondigit:* <sub>one of</sub>
> 
> **_** **a** **b** **c** **d** **e** **f** **g** **h** **i** **j** **k** **l** **m**
> 
> **n** **o** **p** **q** **r** **s** **t** **u** **v** **w** **x** **y** **z**
> 
> **A** **B** **C** **D** **E** **F** **G** **H** **I** **J** **K** **L** **M**
> 
> **N** **O** **P** **Q** **R** **S** **T** **U** **V** **W** **X** **Y** **Z**
> 
<a name="digit"></a>
*digit:* <sub>one of</sub>
> 
> **0** **1** **2** **3** **4** **5** **6** **7** **8** **9**
> 
###### Description

An identifier is a sequence of nondigit characters (including the underscore `_` and the lower-case and upper-case letters) and digits. The first character shall be a nondigit character.

###### Constraints

In translation phases 7 and 8, an identifier shall not consist of the same sequence of characters as a keyword.

###### Semantics

An identifier denotes an object, a function, or one of the following entities that will be described later: a tag or a member of a structure, union, or enumeration; a typedef name; a label name; a macro name; or a macro parameter. A member of an enumeration is called an *enumeration constant*. Macro names and macro parameters are not considered further here, because prior to the semantic phase of program translation any occurrences of macro names in the source file are replaced by the preprocessing token sequences that constitute their macro definitions.

There is no specific limit on the maximum length of an identifier.

"Implementation limits"

The implementation shall treat at least the first 31 characters of an *internal name* (a macro name or an identifier that does not have external linkage) as significant. Corresponding lower-case and upper-case letters are different. The implementation may further restrict the significance of an *external name* (an identifier that has external linkage) to six characters and may ignore distinctions of alphabetical case for such names.[^10] These limitations on identifiers are all implementation-defined.

Any identifiers that differ in a significant character are different identifiers. If two identifiers differ in a non-significant character, the behavior is undefined.

**Forward references**: linkages of identifiers ([3.1.2.2](#3122-linkages-of-identifiers)), macro replacement ([3.8.3](#383-macro-replacement)).

##### 3.1.2.1 Scopes of identifiers

An identifier is visible (i.e., can be used) only within a region of program text called its *scope*. There are four kinds of scopes: function, file, block, and function prototype. (A *function prototype* is a declaration of a function that declares the types of its parameters.)

A label name is the only kind of identifier that has *function scope*. It can be used (in a `goto` statement) anywhere in the function in which it appears, and is declared implicitly by its syntactic appearance (followed by a `:` and a statement). Label names shall be unique within a function.

Every other identifier has scope determined by the placement of its declaration (in a declarator or type specifier). If the declarator or type specifier that declares the identifier appears outside of any block or list of parameters, the identifier has *file scope*, which terminates at the end of the translation unit. If the declarator or type specifier that declares the identifier appears inside a block or within the list of parameter declarations in a function definition, the identifier has *block scope*, which terminates at the `}` that closes the associated block. If the declarator or type specifier that declares the identifier appears within the list of parameter declarations in a function prototype (not part of a function definition), the identifier has *function prototype scope*, which terminates at the end of the function declarator. If an outer declaration of a lexically identical identifier exists in the same name space, it is hidden until the current scope terminates, after which it again becomes visible.

Structure, union, and enumeration tags have scope that begins just after the appearance of the tag in a type specifier that declares the tag. Each enumeration constant has scope that begins just after the appearance of its defining enumerator in an enumerator list. Any other identifier has scope that begins just after the completion of its declarator.

**Forward references**: compound statement, or block ([3.6.2](#362-compound-statement-or-block)), declarations ([3.5](#35-declarations)), enumeration specifiers ([3.5.2.2](#3522-enumeration-specifiers)), function calls ([3.3.2.2](#3322-function-calls)), function declarators (including prototypes) ([3.5.4.3](#3543-function-declarators-including-prototypes)), function definitions ([3.7.1](#371-function-definitions)), the goto statement ([3.6.6.1](#3661-the-goto-statement)), labeled statements ([3.6.1](#361-labeled-statements)), name spaces of identifiers ([3.1.2.3](#3123-name-spaces-of-identifiers)), scope of macro definitions ([3.8.3.5](#3835-scope-of-macro-definitions)), source file inclusion ([3.8.2](#382-source-file-inclusion)), tags ([3.5.2.3](#3523-tags)), type specifiers ([3.5.2](#352-type-specifiers)).

##### 3.1.2.2 Linkages of identifiers

An identifier declared in different scopes or in the same scope more than once can be made to refer to the same object or function by a process called *linkage*. There are three kinds of linkage: external, internal, and none.

In the set of translation units and libraries that constitutes an entire program, each instance of a particular identifier with *external linkage* denotes the same object or function. Within one translation unit, each instance of an identifier with *internal linkage* denotes the same object or function. Identifiers with *no linkage* denote unique entities.

If the declaration of an identifier for an object or a function has file scope and contains the storage-class specifier `static`, the identifier has internal linkage.

If the declaration of an identifier for an object or a function contains the storage-class specifier `extern`, the identifier has the same linkage as any visible declaration of the identifier with file scope. If there is no visible declaration with file scope, the identifier has external linkage.

If the declaration of an identifier for a function has no storage-class specifier, its linkage is determined exactly as if it were declared with the storage-class specifier `extern`. If the declaration of an identifier for an object has file scope and no storage-class specifier, its linkage is external.

The following identifiers have no linkage: an identifier declared to be anything other than an object or a function; an identifier declared to be a function parameter; an identifier declared to be an object inside a block without the storage-class specifier `extern`.

If, within a translation unit, the same identifier appears with both internal and external linkage, the behavior is undefined.

**Forward references**: compound statement, or block ([3.6.2](#362-compound-statement-or-block)), declarations ([3.5](#35-declarations)), expressions ([3.3](#33-expressions)), external definitions ([3.7](#37-external-definitions)).

##### 3.1.2.3 Name spaces of identifiers

If more than one declaration of a particular identifier is visible at any point in a translation unit, the syntactic context disambiguates uses that refer to different entities. Thus, there are separate *name spaces* for various categories of identifiers, as follows:

* label names (disambiguated by the syntax of the label declaration and use);

* the tags of structures, unions, and enumerations (disambiguated by following any[^11] of the keywords `struct`, `union`, or `enum`);

* the members of structures or unions; each structure or union has a separate name space for its members (disambiguated by the type of the expression used to access the member via the `.` or `->` operator);

* all other identifiers, called *ordinary identifiers* (declared in ordinary declarators or as enumeration constants).

**Forward references**: declarators ([3.5.4](#354-declarators)), enumeration specifiers ([3.5.2.2](#3522-enumeration-specifiers)), labeled statements ([3.6.1](#361-labeled-statements)), structure and union specifiers ([3.5.2.1](#3521-structure-and-union-specifiers)), structure and union members ([3.3.2.3](#3323-structure-and-union-members)), tags ([3.5.2.3](#3523-tags)).

##### 3.1.2.4 Storage durations of objects

An object has a *storage duration* that determines its lifetime. There are two storage durations: static and automatic.

An object declared with external or internal linkage, or with the storage-class specifier `static` has *static storage duration*. For such an object, storage is reserved and its stored value is initialized only once, prior to program startup. The object exists and retains its last-stored value throughout the execution of the entire program.[^12]

An object declared with no linkage and without the storage-class specifier `static` has *automatic storage duration*. Storage is guaranteed to be reserved for a new instance of such an object on each normal entry into the block in which it is declared, or on a jump from outside the block to a label in the block or in an enclosed block. If an initialization is specified for the value stored in the object, it is performed on each normal entry, but not if the block is entered by a jump to a label. Storage for the object is no longer guaranteed to be reserved when execution of the block ends in any way. (Entering an enclosed block suspends but does not end execution of the enclosing block. Calling a function that returns suspends but does not end execution of the block containing the call.) The value of a pointer that referred to an object with automatic storage duration that is no longer guaranteed to be reserved is indeterminate.

**Forward references**: compound statement, or block ([3.6.2](#362-compound-statement-or-block)), function calls ([3.3.2.2](#3322-function-calls)), initialization ([3.5.7](#357-initialization)).

##### 3.1.2.5 Types

The meaning of a value stored in an object or returned by a function is determined by the *type* of the expression used to access it. (An identifier declared to be an object is the simplest such expression; the type is specified in the declaration of the identifier.) Types are partitioned into *object types* (types that describe objects), *function types* (types that describe functions), and *incomplete types* (types that describe objects but lack information needed to determine their sizes).

An object declared as type `char` is large enough to store any member of the basic execution character set. If a member of the required source character set enumerated in [2.2.1](#221-character-sets) is stored in a `char` object, its value is guaranteed to be positive. If other quantities are stored in a `char` object, the behavior is implementation-defined: the values are treated as either signed or nonnegative integers.

There are four signed integer types, designated as `signed char`, `short int`, `int`, and `long int`. (The signed integer and other types may be designated in several additional ways, as described in [3.5.2](#352-type-specifiers))

An object declared as type `signed char` occupies the same amount of storage as a "plain" `char` object. A "plain" `int` object has the natural size suggested by the architecture of the execution environment (large enough to contain any value in the range `INT_MIN` to `INT_MAX` as defined in the header `<limits.h>`). In the list of signed integer types above, the range of values of each type is a subrange of the values of the next type in the list.

For each of the signed integer types, there is a corresponding (but different) unsigned integer type (designated with the keyword `unsigned`) that uses the same amount of storage (including sign information) and has the same alignment requirements. The range of nonnegative values of a signed integer type is a subrange of the corresponding unsigned integer type, and the representation of the same value in each type is the same. A computation involving unsigned operands can never overflow, because a result that cannot be represented by the resulting unsigned integer type is reduced modulo the number that is one greater than the largest value that can be represented by the resulting unsigned integer type.

There are three floating types, designated as `float`, `double`, and `long double`. The set of values of the type `float` is a subset of the set of values of the type `double`; the set of values of the type `double` is a subset of the set of values of the type `long double`.

The type `char`, the signed and unsigned integer types, and the floating types are collectively called the *basic types*. Even if the implementation defines two or more basic types to have the same representation, they are nevertheless different types.

There are three character types, designated as `char`, `signed char`, and `unsigned char`.

An enumeration comprises a set of named integer constant values. Each distinct enumeration constitutes a different *enumerated type*.

The `void` type comprises an empty set of values; it is an incomplete type that cannot be completed.

Any number of *derived types* can be constructed from the basic, enumerated, and incomplete types, as follows:

* An *array type* describes a contiguously allocated set of objects with a particular member object type, called the *element type*. Array types are characterized by their element type and by the number of members of the array. An array type is said to be derived from its element type, and if its element type is T, the array type is sometimes called "array of T." The construction of an array type from an element type is called "array type derivation."

* A *structure type* describes a sequentially allocated set of member objects, each of which has an optionally specified name and possibly distinct type.

* A *union type* describes an overlapping set of member objects, each of which has an optionally specified name and possibly distinct type.

* A *function type* describes a function with specified return type. A function type is characterized by its return type and the number and types of its parameters. A function type is said to be derived from its return type, and if its return type is T, the function type is sometimes called "function returning T." The construction of a function type from a return type is called "function type derivation."

* A *pointer type* may be derived from a function type, an object type, or an incomplete type, called the *referenced type*. A pointer type describes an object whose value provides a reference to an entity of the referenced type. A pointer type derived from the referenced type T is sometimes called "pointer to T." The construction of a pointer type from a referenced type is called "pointer type derivation."

These methods of constructing derived types can be applied recursively.

The type `char`, the signed and unsigned integer types, and the enumerated types are collectively called *integral types*. The representations of integral types shall define values by use of a *pure binary numeration system*. ([^13] American National Dictionary for Information Processing Systems.) The representations of floating types are unspecified.

Integral and floating types are collectively called *arithmetic types*. Arithmetic types and pointer types are collectively called *scalar types*. Array and structure types are collectively called *aggregate types*.[^14]

A pointer to `void` shall have the same representation and alignment requirements as a pointer to a character type. Other pointer types need not have the same representation or alignment requirements.

An array type of unknown size is an incomplete type. It is completed, for an identifier of that type, by specifying the size in a later declaration (with internal or external linkage). A structure or union type of unknown content (as described in [3.5.2.3](#3523-tags)) is an incomplete type. It is completed, for all declarations of that type, by declaring the same structure or union tag with its defining content later in the same scope.

Array, function, and pointer types are collectively called *derived declarator types*. A declarator type derivation from a type T is the construction of a derived declarator type from T by the application of an array, a function, or a pointer type derivation to T.

A type is characterized by its *top type*, which is either the first type named in describing a derived type (as noted above in the construction of derived types), or the type itself if the type consists of no derived types.

A type has *qualified type* if its top type is specified with a type qualifier; otherwise it has *unqualified type*. The type qualifiers `const` and `volatile` respectively designate *const-qualified type* and *volatile-qualified type*.[^15] For each qualified type there is an unqualified type that is specified the same way as the qualified type, but without any type qualifiers in its top type. This type is known as the *unqualified version of the qualified type*. Similarly, there are appropriately *qualified versions of types* (such as a const-qualified version of a type), just as there are appropriately *non-qualified versions of types* (such as a non-const-qualified version of a type).

###### Examples

The type designated as "`float *`" is called "pointer to `float`" and its top type is a pointer type, not a floating type. The const-qualified version of this type is designated as "`float * const`" whereas the type designated as "`const float *`" is not a qualified type --- it is called "pointer to` const float`" and is a pointer to a qualified type.

Finally, the type designated as "`struct tag (*[5])(float)`" is called "array of pointer to function returning `struct` tag." Its top type is array type. The array has length five and the function has a single parameter of type `float`.

**Forward references**: character constants ([3.1.3.4](#3134-character-constants)), declarations ([3.5](#35-declarations)), tags ([3.5.2.3](#3523-tags)), type qualifiers ([3.5.3](#353-type-qualifiers)).

##### 3.1.2.6 Compatible type and composite type

Two types have compatible type if their types are the same. Additional rules for determining whether two types are compatible are described in [3.5.2](#352-type-specifiers) for type specifiers, in [3.5.3](#353-type-qualifiers) for type qualifiers, and in [3.5.4](#354-declarators) for declarators.[^16] Moreover, two structure, union, or enumeration types declared in separate translation units are compatible if they have the same number of members, the same member names, and compatible member types; for two structures, the members shall be in the same order; for two enumerations, the members shall have the same values.

All declarations that refer to the same object or function shall have compatible type; otherwise the behavior is undefined.

A composite type can be constructed from two types that are compatible; it is a type that is compatible with both of the two types and has the following additions:

* If one type is an array of known size, the composite type is an array of that size.

* If only one type is a function type with a parameter type list (a function prototype), the composite type is a function prototype with the parameter type list.

* If both types have parameter type lists, the type of each parameter in the composite parameter type list is the composite type of the corresponding parameters.

These rules apply recursively to the types from which the two types are derived.

For an identifier with external or internal linkage declared in the same scope as another declaration for that identifier, the type of the identifier becomes the composite type.

###### Example

Given the following two file scope declarations:

```c
         int f(int (*)(), double (*)[3]);
         int f(int (*)(char *), double (*)[]);
```

The resulting composite type for the function is:

```c
         int f(int (*)(char *), double (*)[3]);
```

**Forward references**: declarators ([3.5.4](#354-declarators)), enumeration specifiers ([3.5.2.2](#3522-enumeration-specifiers)), structure and union specifiers ([3.5.2.1](#3521-structure-and-union-specifiers)), type definitions ([3.5.6](#356-type-definitions)), type qualifiers ([3.5.3](#353-type-qualifiers)), type specifiers ([3.5.2](#352-type-specifiers)).

#### 3.1.3 Constants

###### Syntax

<a name="constant"></a>
*constant:*
> 
> [*floating-constant*](#floating-constant)
> 
> [*integer-constant*](#integer-constant)
> 
> [*enumeration-constant*](#enumeration-constant)
> 
> [*character-constant*](#character-constant)
> 
###### Constraints

The value of a constant shall be in the range of representable values for its type.

###### Semantics

Each constant has a type, determined by its form and value, as detailed later.

##### 3.1.3.1 Floating constants

###### Syntax

<a name="floating-constant"></a>
*floating-constant:*
> 
> [*fractional-constant*](#fractional-constant) &nbsp; *[exponent-part](#exponent-part)<sub>opt</sub>* &nbsp; *[floating-suffix](#floating-suffix)<sub>opt</sub>*
> 
> [*digit-sequence*](#digit-sequence) &nbsp; [*exponent-part*](#exponent-part) &nbsp; *[floating-suffix](#floating-suffix)<sub>opt</sub>*
> 
<a name="fractional-constant"></a>
*fractional-constant:*
> 
> *[digit-sequence](#digit-sequence)<sub>opt</sub>* &nbsp; **.** &nbsp; [*digit-sequence*](#digit-sequence)
> 
> [*digit-sequence*](#digit-sequence) &nbsp; **.**
> 
<a name="exponent-part"></a>
*exponent-part:*
> 
> **e** &nbsp; *[sign](#sign)<sub>opt</sub>* &nbsp; [*digit-sequence*](#digit-sequence)
> 
> **E** &nbsp; *[sign](#sign)<sub>opt</sub>* &nbsp; [*digit-sequence*](#digit-sequence)
> 
<a name="sign"></a>
*sign:* <sub>one of</sub>
> 
> **+** **-**
> 
<a name="digit-sequence"></a>
*digit-sequence:*
> 
> [*digit*](#digit)
> 
> [*digit-sequence*](#digit-sequence) &nbsp; [*digit*](#digit)
> 
<a name="floating-suffix"></a>
*floating-suffix:* <sub>one of</sub>
> 
> **f** **l** **F** **L**
> 
###### Description

A floating constant has a value part that may be followed by an exponent part and a suffix that specifies its type. The components of the value part may include a digit sequence representing the whole-number part, followed by a period (`.`), followed by a digit sequence representing the fraction part. The components of the exponent part are an `e` or `E` followed by an exponent consisting of an optionally signed digit sequence. Either the whole-number part or the fraction part shall be present; either the period or the exponent part shall be present.

###### Semantics

The value part is interpreted as a decimal rational number; the digit sequence in the exponent part is interpreted as a decimal integer. The exponent indicates the power of 10 by which the value part is to be scaled. If the scaled value is in the range of representable values (for its type) but cannot be represented exactly, the result is either the nearest higher or nearest lower value, chosen in an implementation-defined manner.

An unsuffixed floating constant has type `double`. If suffixed by the letter `f` or `F`, it has type `float`. If suffixed by the letter `l` or `L`, it has type `long double`.

##### 3.1.3.2 Integer constants

###### Syntax

<a name="integer-constant"></a>
*integer-constant:*
> 
> [*decimal-constant*](#decimal-constant) &nbsp; *[integer-suffix](#integer-suffix)<sub>opt</sub>*
> 
> [*octal-constant*](#octal-constant) &nbsp; *[integer-suffix](#integer-suffix)<sub>opt</sub>*
> 
> [*hexadecimal-constant*](#hexadecimal-constant) &nbsp; *[integer-suffix](#integer-suffix)<sub>opt</sub>*
> 
<a name="decimal-constant"></a>
*decimal-constant:*
> 
> [*nonzero-digit*](#nonzero-digit)
> 
> [*decimal-constant*](#decimal-constant) &nbsp; [*digit*](#digit)
> 
<a name="octal-constant"></a>
*octal-constant:*
> 
> **0**
> 
> [*octal-constant*](#octal-constant) &nbsp; [*octal-digit*](#octal-digit)
>  
<a name="hexadecimal-constant"></a>
*hexadecimal-constant:*
> 
> **0x** &nbsp; [*hexadecimal-digit*](#hexadecimal-digit)
> 
> **0X** &nbsp; [*hexadecimal-digit*](#hexadecimal-digit)
> 
> [*hexadecimal-constant*](#hexadecimal-constant) &nbsp; [*hexadecimal-digit*](#hexadecimal-digit)
> 
<a name="nonzero-digit"></a>
*nonzero-digit:* <sub>one of</sub>
> 
> **1** **2** **3** **4** **5** **6** **7** **8** **9** 
> 
<a name="octal-digit"></a>
*octal-digit:* <sub>one of</sub>
> 
> **0** **1** **2** **3** **4** **5** **6** **7**
> 
<a name="hexadecimal-digit"></a>
*hexadecimal-digit:* <sub>one of</sub>
> 
> **0** **1** **2** **3** **4** **5** **6** **7** **8** **9** 
> 
> **a** **b** **c** **d** **e** **f**
> 
> **A** **B** **C** **D** **E** **F**
> 
<a name="integer-suffix"></a>
*integer-suffix:*
> 
> [*unsigned-suffix*](#unsigned-suffix) &nbsp; *[long-suffix](#long-suffix)<sub>opt</sub>*
> 
> [*long-suffix*](#long-suffix) &nbsp; *[unsigned-suffix](#unsigned-suffix)<sub>opt</sub>*
> 
<a name="unsigned-suffix"></a>
*unsigned-suffix:* <sub>one of</sub>
> 
> **u** **U**
> 
<a name="long-suffix"></a>
*long-suffix:* <sub>one of</sub>
> 
> **l** **L**
> 
###### Description

An integer constant begins with a digit, but has no period or exponent part. It may have a prefix that specifies its base and a suffix that specifies its type.

A decimal constant begins with a nonzero digit and consists of a sequence of decimal digits. An octal constant consists of the prefix `0` optionally followed by a sequence of the digits `0` through `7` only. A hexadecimal constant consists of the prefix `0x` or `0X` followed by a sequence of the decimal digits and the letters `a` (or `A`) through `f` (or `F`) with values 10 through 15 respectively.

###### Semantics

The value of a decimal constant is computed base 10; that of an octal constant, base 8; that of a hexadecimal constant, base 16. The lexically first digit is the most significant.

The type of an integer constant is the first of the corresponding list in which its value can be represented. Unsuffixed decimal: `int`, `long int`, `unsigned long int`; unsuffixed octal or hexadecimal: `int`, `unsigned int`, `long int`, `unsigned long int`; suffixed by the letter `u` or `U`: `unsigned int`, `unsigned long int`; suffixed by the letter `l` or `L`: `long int`, `unsigned long int`; suffixed by both the letters `u` or `U` and `l` or `L`: `unsigned long int`.

##### 3.1.3.3 Enumeration constants

###### Syntax

<a name="enumeration-constant"></a>
*enumeration-constant:*
> 
> [*identifier*](#identifier)
> 
###### Semantics

An identifier declared as an enumeration constant has type int.

**Forward references**: enumeration specifiers ([3.5.2.2](#3522-enumeration-specifiers)).

##### 3.1.3.4 Character constants

###### Syntax

<a name="character-constant"></a>
*character-constant:*
> 
> **'** &nbsp; [*c-char-sequence*](#c-char-sequence) &nbsp; **'**
> 
> **L** &nbsp; **'** &nbsp; [*c-char-sequence*](#c-char-sequence) &nbsp; **'**
> 
<a name="c-char-sequence"></a>
*c-char-sequence:*
> 
> [*c-char*](#c-char)
> 
> [*c-char-sequence*](#c-char-sequence) &nbsp; [*c-char*](#c-char)
> 
<a name="c-char"></a>
*c-char:*
> 
> <sub>**any member of the source character set except the single-quote ', backslash \, or new-line character**</sub>
> 
> [*escape-sequence*](#escape-sequence)
> 
<a name="escape-sequence"></a>
*escape-sequence:*
> 
> [*simple-escape-sequence*](#simple-escape-sequence)
> 
> [*octal-escape-sequence*](#octal-escape-sequence)
> 
> [*hexadecimal-escape-sequence*](#hexadecimal-escape-sequence)
> 
<a name="simple-escape-sequence"></a>
*simple-escape-sequence:* <sub>one of</sub>
> 
> **\\'** &nbsp; **\\"** &nbsp; **\\?** &nbsp; **\\\\**
> 
> **\\a** &nbsp; **\\b** &nbsp; **\\f** &nbsp; **\\n** &nbsp; **\\r** &nbsp; **\\t** &nbsp; **\\v**
> 
<a name="octal-escape-sequence"></a>
*octal-escape-sequence*: 
> 
> **\\** &nbsp; [*octal-digit*](#octal-digit)
> 
> **\\** &nbsp; [*octal-digit*](#octal-digit) &nbsp; [*octal-digit*](#octal-digit)
> 
> **\\** &nbsp; [*octal-digit*](#octal-digit) &nbsp; [*octal-digit*](#octal-digit) &nbsp; [*octal-digit*](#octal-digit)
> 
<a name="hexadecimal-escape-sequence"></a>
*hexadecimal-escape-sequence*: 
> 
> **\\x** &nbsp; [*hexadecimal-digit*](#hexadecimal-digit)
> 
> [*hexadecimal-escape-sequence*](#hexadecimal-escape-sequence) &nbsp; [*hexadecimal-digit*](#hexadecimal-digit)
> 
###### Description

An integer character constant is a sequence of one or more multibyte characters enclosed in single-quotes, as in `'x'` or `'ab'`. A wide character constant is the same, except prefixed by the letter `L`. With a few exceptions detailed later, the elements of the sequence are any members of the source character set; they are mapped in an implementation-defined manner to members of the execution character set.

The single-quote `'`, the double-quote `"`, the question-mark `?`, the backslash `\`, and arbitrary integral values, are representable according to the following table of escape sequences:

|   |   |   |
| :--- | :----- | :----- |
| single-quote | \' | `\'` |
| double-quote | \" | `\"` |
| question-mark | \? | `\?` |
| backslash | \\ | `\\` |
| octal integer |   | `\` octal digits |
| hexadecimal integer |   | `\x` hexadecimal digits |

The double-quote `"` and question-mark `?` are representable either by themselves or by the escape sequences `\"` and `\?` respectively, but the single-quote `'` and the backslash `\` shall be represented, respectively, by the escape sequences `\'` and `\\`.

The octal digits that follow the backslash in an octal escape sequence are taken to be part of the construction of a single character for an integer character constant or of a single wide character for a wide character constant. The numerical value of the octal integer so formed specifies the value of the desired character.

The hexadecimal digits that follow the backslash and the letter `x` in a hexadecimal escape sequence are taken to be part of the construction of a single character for an integer character constant or of a single wide character for a wide character constant. The numerical value of the hexadecimal integer so formed specifies the value of the desired character.

Each octal or hexadecimal escape sequence is the longest sequence of characters that can constitute the escape sequence.

In addition, certain nongraphic characters are representable by escape sequences consisting of the backslash `\` followed by a lower-case letter: `\a`, `\b`, `\f`, `\n`, `\r`, `\t`, and `\v`.[^17] If any other escape sequence is encountered, the behavior is undefined.[^18]

###### Constraints

The value of an octal or hexadecimal escape sequence shall be in the range of representable values for the unsigned type corresponding to its type.

###### Semantics

An integer character constant has type `int`. The value of an integer character constant containing a single character that maps into a member of the basic execution character set is the numerical value of the representation of the mapped character interpreted as an integer. The value of an integer character constant containing more than one character, or containing a character or escape sequence not represented in the basic execution character set, is implementation-defined. In particular, in an implementation in which type `char` has the same range of values as `signed char`, the high-order bit position of a single-character integer character constant is treated as a sign bit.

A wide character constant has type `wchar_t`, an integral type defined in the `<stddef.h>` header. The value of a wide character constant containing a single multibyte character that maps into a member of the extended execution character set is the wide character (code) corresponding to that multibyte character, as defined by the `mbtowc` function, with an implementation-defined current locale. The value of a wide character constant containing more than one multibyte character, or containing a multibyte character or escape sequence not represented in the extended execution character set, is implementation-defined.

###### Examples

The construction `'\0'` is commonly used to represent the null character.

Consider implementations that use two's-complement representation for integers and eight bits for objects that have type char. In an implementation in which type `char` has the same range of values as `signed char`, the integer character constant `'\xFF'` has the value if type char has the same range of values as `unsigned char`, the character constant `'\xFF'` has the value

Even if eight bits are used for objects that have type `char`, the construction `'\x123'` specifies an integer character constant containing only one character. (The value of this single-character integer character constant is implementation-defined and violates the above constraint.) To specify an integer character constant containing the two characters whose values are `0x12` and `'3'`, the construction `'\0223'` may be used, since a hexadecimal escape sequence is terminated only by a non-hexadecimal character. (The value of this two-character integer character constant is implementation-defined also.)

Even if 12 or more bits are used for objects that have type `wchar_t`, the construction `L'\1234'` specifies the implementation-defined value that results from the combination of the values `0123` and `'4'`.

**Forward references**: characters and integers ([3.2.1.1](#3211-characters-and-integers)) common definitions <stddef.h> ([4.1.5](#415-common-definitions-stddefh)), the mbtowc function ([4.10.7.2](#41072-the-mbtowc-function)).

#### 3.1.4 String literals

###### Syntax

<a name="string-literal"></a>
*string-literal:*
> 
> **"** &nbsp; *[s-char-sequence](#s-char-sequence)<sub>opt</sub>* &nbsp; **"**
> 
> **L** &nbsp; **"** &nbsp; *[s-char-sequence](#s-char-sequence)<sub>opt</sub>* &nbsp; **"**
> 
<a name="s-char-sequence"></a>
*s-char-sequence:*
> 
> [*s-char*](#s-char)
> 
> [*s-char-sequence*](#s-char-sequence) &nbsp; [*s-char*](#s-char)
> 
<a name="s-char"></a>
*s-char:*
> 
> <sub>**any member of the source character set except the double-quote ", backslash \, or new-line character**</sub>
> 
> [*escape-sequence*](#escape-sequence)
> 
###### Description

A character string literal is a sequence of zero or more multibyte characters enclosed in double-quotes, as in `"xyz"`. A wide string literal is the same, except prefixed by the letter `L`.

The same considerations apply to each element of the sequence in a character string literal or a wide string literal as if it were in an integer character constant or a wide character constant, except that the single-quote `'` is representable either by itself or by the escape sequence `\'`, but the double-quote shall be represented by the escape sequence `\"`.

###### Semantics

A character string literal has static storage duration and type "array of `char`," and is initialized with the given characters. A wide string literal has static storage duration and type "array of `wchar_t`," and is initialized with the wide characters corresponding to the given multibyte characters. Character string literals that are adjacent tokens are concatenated into a single character string literal. A null character is then appended.[^19] Likewise, adjacent wide string literal tokens are concatenated into a single wide string literal to which a code with value zero is then appended. If a character string literal token is adjacent to a wide string literal token, the behavior is undefined.

Identical string literals of either form need not be distinct. If the program attempts to modify a string literal of either form, the behavior is undefined.

###### Example

This pair of adjacent character string literals

```c
         "\x12" "3"
```

produces a single character string literal containing the two characters whose values are `\x12` and `'3'`, because escape sequences are converted into single members of the execution character set just prior to adjacent string literal concatenation.

**Forward references**: common definitions <stddef.h> ([4.1.5](#415-common-definitions-stddefh)).

#### 3.1.5 Operators

###### Syntax

<a name="operator"></a>
*operator:* <sub>one of</sub>
> 
> **\[** &nbsp; **\]** &nbsp; **(** &nbsp; **)** &nbsp; **.** &nbsp; **->**
> 
> **++** &nbsp; **--** &nbsp; **&** &nbsp; **\*** &nbsp; **+** &nbsp; **-** &nbsp; **~** &nbsp; **!** &nbsp; **sizeof**
> 
> **/** &nbsp; **%** &nbsp; **<<** &nbsp; **>>** &nbsp; **<** &nbsp; **>** &nbsp; **<=** &nbsp; **>=** &nbsp; **==** &nbsp; **!=** &nbsp; **^** &nbsp; **|** &nbsp; **&&** &nbsp; **||** &nbsp; **?** &nbsp; **:**
> 
> **=** &nbsp; **\*=** &nbsp; **/=** &nbsp; **%=** &nbsp; **+=** &nbsp; **-=** &nbsp; **<<=** &nbsp; **>>=** &nbsp; **&=** &nbsp; **^=** &nbsp; **|=** &nbsp; **,** &nbsp; **#** &nbsp; **##**
> 
###### Constraints

The operators `[ ]`, `( )`, and `? :` shall occur in pairs, possibly separated by expressions. The operators `#` and `##` shall occur in macro-defining preprocessing directives only.

###### Semantics

An operator specifies an operation to be performed \(an evaluation\) that yields a value, or yields a designator, or produces a side effect, or a combination thereof. An operand is an entity on which an operator acts.

**Forward references**: expressions ([3.3](#33-expressions)), macro replacement ([3.8.3](#383-macro-replacement)).


#### 3.1.6 Punctuators

###### Syntax

<a name="punctuator"></a>
*punctuator:* <sub>one of</sub>

> 
> **\[** &nbsp; **\]** &nbsp; **(** &nbsp; **)** &nbsp; **{** &nbsp; **}** &nbsp; **\*** &nbsp; **,** &nbsp; **:** &nbsp; **=** &nbsp; **;** &nbsp; **...** &nbsp; **#**
>
###### Constraints

The punctuators `[ ]`, `( )`, and `{ }` shall occur in pairs, possibly separated by expressions, declarations, or statements. The punctuator `#` shall occur in preprocessing directives only.

###### Semantics

A punctuator is a symbol that has independent syntactic and semantic significance but does not specify an operation to be performed that yields a value. Depending on context, the same symbol may also represent an operator or part of an operator.

**Forward references**: expressions ([3.3](#33-expressions)), declarations ([3.5](#35-declarations)), preprocessing directives ([3.8](#38-preprocessing-directives)), statements ([3.6](#36-statements)).

#### 3.1.7 Header names

###### Syntax

<a name="header-name"></a>
*header-name:*
> 
> **<** &nbsp; [*h-char-sequence*](#h-char-sequence) &nbsp; **>**
> 
> **"** &nbsp; [*q-char-sequence*](#q-char-sequence) &nbsp; **"**
> 
<a name="h-char-sequence"></a>
*h-char-sequence:*
> 
> [*h-char*](#h-char)
> 
> [*h-char-sequence*](#h-char-sequence) &nbsp; [*h-char*](#h-char)
> 
<a name="h-char"></a>
*h-char:*
>
> <sub>**any member of the source character set except the new-line character and >**</sub>
>
<a name="q-char-sequence"></a>
*q-char-sequence:*
> 
> [*q-char*](#q-char)
> 
> [*q-char-sequence*](#q-char-sequence) &nbsp; [*q-char*](#q-char)
>
<a name="q-char"></a>
*q-char:*
> 
> <sub>**any member of the source character set except the new-line character and "**</sub>
> 
###### Constraints

Header name preprocessing tokens shall only appear within a `#include` preprocessing directive.

###### Semantics

The sequences in both forms of header names are mapped in an implementation-defined manner to headers or external source file names as specified in [3.8.2](#382-source-file-inclusion)

If the characters `'`, `\`, `"`, or `/*` occur in the sequence between the `<` and `>` delimiters, the behavior is undefined. Similarly, if the characters `'`, `\`, or `/*` occur in the sequence between the `"` delimiters, the behavior is undefined.[^20]

###### Example

The following sequence of characters:

```c
         0x3<1/a.h>1e2
         #include <1/a.h>
         #define const.member@$
```

forms the following sequence of preprocessing tokens (with each individual preprocessing token delimited by a { on the left and a } on the right).

```
         {0x3}{<}{1}{/}{a}{.}{h}{>}{1e2}
         {#}{include} {<1/a.h>}
         {#}{define} {const}{.}{member}{@}{$}
```

**Forward references**: source file inclusion ([3.8.2](#382-source-file-inclusion)).

#### 3.1.8 Preprocessing numbers

###### Syntax

<a name="pp-number"></a>
*pp-number:*
> 
> [*digit*](#digit)
> 
> **.** &nbsp; [*digit*](#digit)
> 
> [*pp-number*](#pp-number) &nbsp; [*digit*](#digit)
> 
> [*pp-number*](#pp-number) &nbsp; [*nondigit*](#nondigit)
> 
> [*pp-number*](#pp-number) &nbsp; **e** &nbsp; [*sign*](#sign)
> 
> [*pp-number*](#pp-number) &nbsp; **E** &nbsp; [*sign*](#sign)
> 
> [*pp-number*](#pp-number) &nbsp; **.**
> 
###### Description

A preprocessing number begins with a digit optionally preceded by a period (`.`) and may be followed by letters, underscores, digits, periods, and `e+`, `e-`, `E+`, or `E-` character sequences.

Preprocessing number tokens lexically include all floating and integer constant tokens.

###### Semantics

A preprocessing number does not have type or a value; it acquires both after a successful conversion (as part of translation phase 7) to a floating constant token or an integer constant token.

#### 3.1.9 Comments

Except within a character constant, a string literal, or a comment, the characters `/*` introduce a comment. The contents of a comment are examined only to identify multibyte characters and to find the characters `*/` that terminate it.[^21]

### 3.2 CONVERSIONS

Several operators convert operand values from one type to another automatically. This section specifies the result required from such an implicit conversion, as well as those that result from a cast operation (an explicit conversion). The list in [3.2.1.5](#3215-usual-arithmetic-conversions) summarizes the conversions performed by most ordinary operators; it is supplemented as required by the discussion of each operator in [3.3](#33-expressions)

Conversion of an operand value to a compatible type causes no change.

**Forward references**: cast operators ([3.3.4](#334-cast-operators)).

#### 3.2.1 Arithmetic operands

##### 3.2.1.1 Characters and integers

A `char`, a `short int`, or an `int` bit-field, or their `signed` or `unsigned` varieties, or an object that has enumeration type, may be used in an expression wherever an `int` or `unsigned int` may be used. If an `int` can represent all values of the original type, the value is converted to an `int`; otherwise it is converted to an `unsigned int`. These are called the integral promotions.

The integral promotions preserve value including sign. As discussed earlier, whether a "plain" `char` is treated as `signed` is implementation-defined.

**Forward references**: enumeration specifiers ([3.5.2.2](#3522-enumeration-specifiers)), structure and union specifiers ([3.5.2.1](#3521-structure-and-union-specifiers)).

##### 3.2.1.2 Signed and unsigned integers

When an unsigned integer is converted to another integral type, if the value can be represented by the new type, its value is unchanged.

When a signed integer is converted to an unsigned integer with equal or greater size, if the value of the signed integer is nonnegative, its value is unchanged. Otherwise: if the unsigned integer has greater size, the signed integer is first promoted to the signed integer corresponding to the unsigned integer; the value is converted to `unsigned` by adding to it one greater than the largest number that can be represented in the unsigned integer type.[^22]

When an integer is demoted to an unsigned integer with smaller size, the result is the nonnegative remainder on division by the number one greater than the largest unsigned number that can be represented in the type with smaller size. When an integer is demoted to a signed integer with smaller size, or an unsigned integer is converted to its corresponding signed integer, if the value cannot be represented the result is implementation-defined.

##### 3.2.1.3 Floating and integral

When a value of floating type is converted to integral type, the fractional part is discarded. If the value of the integral part cannot be represented by the integral type, the behavior is undefined.[^23]

When a value of integral type is converted to floating type, if the value being converted is in the range of values that can be represented but cannot be represented exactly, the result is either the nearest higher or nearest lower value, chosen in an implementation-defined manner.

##### 3.2.1.4 Floating types

When a `float` is promoted to `double` or `long double`, or a `double` is promoted to `long double`, its value is unchanged.

When a `double` is demoted to `float` or a `long double` to `double` or `float`, if the value being converted is outside the range of values that can be represented, the behavior is undefined. If the value being converted is in the range of values that can be represented but cannot be represented exactly, the result is either the nearest higher or nearest lower value, chosen in an implementation-defined manner.

##### 3.2.1.5 Usual arithmetic conversions

Many binary operators that expect operands of arithmetic type cause conversions and yield result types in a similar way. The purpose is to yield a common type, which is also the type of the result. This pattern is called the usual arithmetic conversions: First, if either operand has type `long double`, the other operand is converted to `long double`. Otherwise, if either operand has type `double`, the other operand is converted to `double`. Otherwise, if either operand has type `float`, the other operand is converted to `float`. Otherwise, the integral promotions are performed on both operands. Then the following rules are applied: If either operand has type `unsigned long int`, the other operand is converted to `unsigned long int`. Otherwise, if one operand has type `long int` and the other has type `unsigned int`, if a `long int` can represent all values of an `unsigned int`, the operand of type `unsigned int` is converted to `long int`; if a `long int` cannot represent all the values of an `unsigned int`, both operands are converted to `unsigned long int`. Otherwise, if either operand has type `long int`, the other operand is converted to `long int`. Otherwise, if either operand has type `unsigned int`, the other operand is converted to `unsigned int`. Otherwise, both operands have type `int`.

The values of operands and of the results of expressions may be represented in greater precision and range than that required by the type; the types are not changed thereby.

#### 3.2.2 Other operands

##### 3.2.2.1 Lvalues and function designators

An lvalue is an expression (with an object type or an incomplete type other than `void`) that designates an object.[^24] When an object is said to have a particular type, the type is specified by the lvalue used to designate the object. A modifiable lvalue is an lvalue that does not have array type, does not have an incomplete type, does not have a `const`-qualified type, and if it is a structure or union, does not have any member (including, recursively, any member of all contained structures or unions) with a `const`-qualified type.

Except when it is the operand of the `sizeof` operator, the unary `&` operator, the `++` operator, the `--` operator, or the left operand of the `.` operator or an assignment operator, an lvalue that does not have array type is converted to the value stored in the designated object (and is no longer an lvalue). If the lvalue has qualified type, the value has the unqualified version of the type of the lvalue; otherwise the value has the type of the lvalue. If the lvalue has an incomplete type and does not have array type, the behavior is undefined.

Except when it is the operand of the `sizeof` operator or the unary `&` operator, or is a character string literal used to initialize an array of character type, or is a wide string literal used to initialize an array with element type compatible with `wchar_t`, an lvalue that has type "array of type" is converted to an expression that has type "pointer to type" that points to the initial member of the array object and is not an lvalue.

A function designator is an expression that has function type. Except when it is the operand of the `sizeof` operator[^25] or the unary `&` operator, a function designator with type "function returning type" is converted to an expression that has type "pointer to function returning type."

**Forward references**: address and indirection operators ([3.3.3.2](#3332-address-and-indirection-operators)), assignment operators ([3.3.16](#3316-assignment-operators)), common definitions <stddef.h> ([4.1.5](#415-common-definitions-stddefh)), initialization ([3.5.7](#357-initialization)), postfix increment and decrement operators ([3.3.2.4](#3324-postfix-increment-and-decrement-operators)), prefix increment and decrement operators ([3.3.3.1](#3331-prefix-increment-and-decrement-operators)), the sizeof operator ([3.3.3.4](#3334-the-sizeof-operator)), structure and union members ([3.3.2.3](#3323-structure-and-union-members)).

##### 3.2.2.2 void

The (nonexistent) value of a `void` expression (an expression that has type `void`) shall not be used in any way, and implicit or explicit conversions (except to `void`) shall not be applied to such an expression. If an expression of any other type occurs in a context where a `void` expression is required, its value or designator is discarded. (A `void` expression is evaluated for its side effects.)

##### 3.2.2.3 Pointers

A pointer to `void` may be converted to or from a pointer to any incomplete or object type. A pointer to any incomplete or object type may be converted to a pointer to `void` and back again; the result shall compare equal to the original pointer.

A pointer to a non-q-qualified type may be converted to a pointer to the q-qualified version of the type; the values stored in the original and converted pointers shall compare equal.

An integral constant expression with the value `0`, or such an expression cast to type `void *`, is called a null pointer constant. If a null pointer constant is assigned to or compared for equality to a pointer, the constant is converted to a pointer of that type. Such a pointer, called a null pointer, is guaranteed to compare unequal to a pointer to any object or function.

Two null pointers, converted through possibly different sequences of casts to pointer types, shall compare equal.

**Forward references**: cast operators ([3.3.4](#334-cast-operators)), equality operators ([3.3.9](#339-equality-operators)), simple assignment ([3.3.16.1](#33161-simple-assignment)).

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

[^1]: This Standard is designed to promote the portability of C programs among a variety of data-processing systems. It is intended for use by implementors and knowledgeable programmers, and is not a tutorial. It is accompanied by a Rationale document that explains many of the decisions of the Technical Committee that produced it.

[^2]: Strictly conforming programs are intended to be maximally portable among conforming implementations. Conforming programs may depend upon nonportable features of a conforming implementation.

[^3]: Implementations must behave as if these separate phases occur, even though many are typically folded together in practice.

[^4]: As described in 3.1, the process of dividing a source file's characters into preprocessing tokens is context-dependent. For example, see the handling of `<` within a `#include` preprocessing directive.

[^5]: The trigraph sequences enable the input of characters that are not defined in the "ISO 646-1983" Invariant Code Set, which is a subset of the seven-bit ASCII code set.

[^6]: Implementations should avoid imposing fixed translation limits whenever possible.

[^7]: See [3.1.2.5](#3125-types)

[^8]: This model precludes floating-point representations other than sign-magnitude.

[^9]: The floating-point model in that standard sums powers of from zero, so the values of the exponent limits are one less than shown here.

[^10]: See "future language directions" ([3.9.1](#391-external-names)).

[^11]: There is only one name space for tags even though three are possible.

[^12]: In the case of a volatile object, the last store may not be explicit in the program.

[^13]: A positional representation for integers that uses the binary digits 0 and 1, in which the values represented by successive bits are additive, begin with 1, and are multiplied by successive integral powers of 2, except perhaps the bit with the highest position.

[^14]: Note that aggregate type does not include union type because an object with union type can only contain one member at a time.

[^15]: There are three distinct combinations of qualified types.

[^16]: Two types need not be identical to be compatible.

[^17]: The semantics of these characters were discussed in [2.2.2](#222-character-display-semantics)

[^18]: See ``future language directions'' ([3.9.2](#392-character-escape-sequences)).

[^19]: A character string literal need not be a string (see [4.1.1](#411-definitions-of-terms)), because a null character may be embedded in it by a \0 escape sequence.

[^20]: Thus, sequences of characters that resemble escape sequences cause undefined behavior.

[^21]: Thus comments do not nest.

[^22]: In a two's-complement representation, there is no actual change in the bit pattern except filling the high-order bits with copies of the sign bit if the unsigned integer has greater size.

[^23]: The remaindering operation done when a value of integral type is converted to `unsigned` type need not be done when a value of floating type is converted to `unsigned` type. Thus the range of portable values is [0, U type _MAX +1).

[^24]: The name "lvalue" comes originally from the assignment expression `E1 = E2`, in which the left operand `E1` must be a (modifiable) lvalue. It is perhaps better considered as representing an object "locator value." What is sometimes called "rvalue" is in this Standard described as the "value of an expression." An obvious example of an lvalue is an identifier of an object. As a further example, if `E` is a unary expression that is a pointer to an object, `*E` is an lvalue that designates the object to which `E` points.

[^25]: Because this conversion does not occur, the operand of the `sizeof` operator remains a function designator and violates the constraint in [3.3.3.4](#3334-the-sizeof-operator)
