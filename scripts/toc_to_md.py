import re

def generate_slug(text):
    """
    텍스트를 GitHub 스타일의 앵커 링크(slug)로 변환합니다.
    예: "1.1 PURPOSE" -> "11-purpose"
    (사용자 예시에 맞춰 점(.)을 제거하고 소문자로 변환 후 공백을 하이픈으로 변경)
    """
    # 1. 소문자 변환
    slug = text.lower()
    # 2. 특수문자 제거 (점 등), 공백은 유지
    slug = slug.replace('.', '')
    # 3. 공백을 하이픈으로 변경
    slug = slug.replace(' ', '-')
    return slug

def parse_level(line):
    """
    줄의 시작 부분(예: 1., 1.1)을 보고 들여쓰기 레벨을 계산합니다.
    """
    # 공백 기준으로 첫 번째 단어(숫자 부분) 추출
    number_part = line.split(' ')[0]
    # 마지막 점 제거 (1. -> 1)
    clean_num = number_part.rstrip('.')
    # 점(.)의 개수로 깊이 판단 (1 -> 1단계, 1.1 -> 2단계)
    return len(clean_num.split('.'))

def convert_to_markdown(input_text):
    lines = input_text.strip().split('\n')
    
    toc_output = []   # 목차 저장용
    body_output = []  # 본문 저장용
    
    for line in lines:
        line = line.strip()
        if not line:
            continue
            
        # 레벨 계산 (1단계, 2단계...)
        level = parse_level(line)
        
        # --- 목차(TOC) 생성 ---
        # 앵커 링크 생성
        anchor = generate_slug(line)
        # 들여쓰기: (레벨 - 1) * 2칸 공백
        indent = '  ' * (level - 1)
        toc_line = f"{indent}- [{line}](#{anchor})"
        toc_output.append(toc_line)
        
        # --- 본문(Header) 생성 ---
        # 요청하신 예시에 따라 1단계는 ##, 2단계는 ###로 시작하도록 설정 (level + 1)
        header_hashes = '#' * (level + 1)
        body_line = f"{header_hashes} {line}\n" # 가독성을 위해 줄바꿈 추가
        body_output.append(body_line)
    
    # 결과 합치기
    return "\n".join(toc_output) + "\n\n" + "\n".join(body_output)

# --- 실행 부분 ---

# 입력 텍스트
input_data = """
1. 서론
1.1 목적
1.2 적용 범위
1.3 참조
1.4 문서 구성
1.5 기본 문서
1.6 용어 정의
1.7 적합성(준수)
1.8 향후 방향
1.9 이 초안에 대하여
"""

# 변환 실행
result = convert_to_markdown(input_data)

# 결과 출력
print(result)

# (선택사항) 파일로 저장하려면 아래 주석을 해제하세요.
# with open("output.md", "w", encoding="utf-8") as f:
#     f.write(result)
