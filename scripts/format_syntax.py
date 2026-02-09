import re

text = r"""
postfix-expression:

primary-expression

postfix-expression [ expression ]

postfix-expression ( argument-expression-listopt )

postfix-expression . identifier

postfix-expression -> identifier

postfix-expression ++

postfix-expression --

argument-expression-list:

assignment-expression

argument-expression-list , assignment-expression
"""

# 1. 키워드 및 연산자 정의
keywords = [
    "auto", "double", "int", "struct", "break", "else", "long", "switch",
    "case", "enum", "register", "typedef", "char", "extern", "return", "union",
    "const", "float", "short", "unsigned", "continue", "for", "signed", "void",
    "default", "goto", "sizeof", "volatile", "do", "if", "static", "while"
]

operators_and_punctuators = [
    "...", "<<=", ">>=", "##", "->", "++", "--", "<<", ">>", "<=", ">=", 
    "==", "!=", "&&", "||", "*=", "/=", "%=", "+=", "-=", "&=", "^=", "|=",
    "[", "]", "(", ")", "{", "}", ".", "&", "*", "+", "-", "~", "!", "/", 
    "%", "<", ">", "^", "|", "?", ":", "=", ",", "#", ";"
]

# 2. 정규표현식 조립
# KW: 키워드, OP: 연산자, ID: 일반 단어(하이픈 포함)
kw_regex = r'(?P<KW>\b(?:' + '|'.join(map(re.escape, keywords)) + r')\b)'
# 연산자는 긴 것부터 매칭되도록 정렬
operators_and_punctuators.sort(key=len, reverse=True)
op_regex = r'(?P<OP>' + '|'.join(map(re.escape, operators_and_punctuators)) + r')'
# ID: 일반 단어 (하이픈 포함)
id_regex = r'(?P<ID>\w+(?:-\w+)*)'

master_pattern = re.compile(f'{kw_regex}|{op_regex}|{id_regex}')

# 라벨 패턴: "단어:" 형태
label_pattern = re.compile(r'^([\w-]+):$')

def process_text_final(text):
    result_lines = []
    
    for line in text.split('\n'):
        content = line.strip() 
        
        # 1. 빈 줄 처리
        if not content:
            result_lines.append("> ")
            continue

        # 2. 라벨 처리 (단어: 형태) -> 앵커 태그 생성, > 없음
        label_match = label_pattern.match(content)
        if label_match:
            word = label_match.group(1)
            result_lines.append(f'<a name="{word}"></a>\n*{word}:*')
            continue

        # 3. 일반 코드 줄 처리
        def replace_func(m):
            kind = m.lastgroup
            value = m.group()
            
            if kind == 'KW':  # 키워드
                return f"**{value}**"
                
            elif kind == 'OP':  # 연산자
                # [수정됨] [, ], * 문자는 앞에 역슬래시(\) 추가
                escaped_value = value.replace('*', '\\*').replace('[', '\\[').replace(']', '\\]')
                return f"**{escaped_value}**"
                
            elif kind == 'ID':  # 일반 단어
                if value.endswith("opt") and len(value) > 3:
                    base_word = value[:-3]
                    return f"*[{base_word}]({base_word})<sub>opt</sub>*"
                else:
                    return f"*[{value}]({value})*"
            return value

        processed_line = master_pattern.sub(replace_func, content)
        
        # 공백을 &nbsp;로 변환
        final_line = processed_line.replace(" ", " &nbsp; ")
        
        # 앞에 > 붙이기
        result_lines.append(f"> {final_line}")

    return "\n".join(result_lines)

# 실행
result = process_text_final(text)
print(result)
