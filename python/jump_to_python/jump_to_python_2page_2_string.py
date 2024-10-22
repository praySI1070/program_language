# 파이썬에서 문자열 만들기
# "HEllo world"
# 'Python is fun'
# """Life is too short, you need python"""
# '''Life is too short, you need python'''
a = """Hello world"""
print(a)

#문자열에 작은따옴표 포함하기
food = "Python's favorite food is perl"
#작은 따옴표가 안에 들어가면 큰 따옴표 사용
#food = 'Python's favorite food is perl'
print(food)

#역슬레시 사용
food = 'Python\'s faverite food is perl'
print(food)

#여러 줄인 문자열을 변수에 
#개행 사용
multiline = "Life is too short\nYou need python"
print(multiline)

#연속된 따옴표 3개 사용
multiline = '''
Life is too short
You need python
'''
print(multiline)

#문자열 연산
#문자열 더해서 연결
head = "Python"
tail = " is fun!"
print(head + tail)

#문자열 곱하기
a = "Python"
print(a*2)

#응용 -> multistring.py cmd에서 실행
#문자열 길이
a = "test"
print(len(a))

#문자열 인덱싱과 슬라이싱
#인덱싱
a = "Life is too short, You need Python"
print(a[3])
print(a[-2])

#문자열 슬라이싱
print(a[0:4]) # 0 <= a < 4

#슬라이싱으로 문자열 나누기
a = "20240306Sunny"
date = a[:8]
weather = a[8:]
print(date,weather)

#Pithon -> Python으로 변환
a = "Pithon"
print(a[:1] + "y" + a[2:]) #문자열은 수정 불가하므로 이렇게 변경

#문자열 포매팅
print("I eat %d apples." % 3)
print("I eat %s apples." % 'five')
print("I ate %d apples. so I was sick for %s days." % (3,'five'))

# %o 8진수
# %x 16진수
# %% 문자 % 자체
#포맷 코드와 숫자 함꼐 사용하기

#정렬과 공백
print("%10s" % "Hi") #10칸 공백 중 뒤쪽부터 글자 채우기 12345678HI
print("%-10sJANE" % "HI")  # HI12345678JANE

#소수점 표현하기
print("%0.4f" % 3.12345678) #소수점 4번쨰 자리까지 표현 - 5번쨰 자리에서 반올림

#format 함수를 사용한 포매팅
print("I eat {0} apples".format(3))
print("I eat {0} apples".format("five"))

#2개 이상의 값 넣기
#인덱스는 0부터 순서대로
number = 10
day = "three"
print("I ate {0} apples. so I was sick for {1} days. {2}".format(number,day,"finish"))

#이름으로 넣기
print("I ate {number} apples. so I was sick for {day} days.".format(number=10,day=3))

#정렬
print("{0:<10}".format("hi")) #왼쪽정렬
print("{0:>10}".format("hi")) #오른쪽정렬
print("{0:^10}".format("hi")) #중앙정렬

#공백 채우기
print("{0:=^10}".format("hi")) #정렬 문자 앞에 글자를 채워넣으면 그 글자로 공백을 매꿈
print("{0:s<10}".format("hi"))

#소수점 표현하기
y = 0.123456789
print("{0:0.5f}".format(y))
print("{0:10.6f}".format(y)) #총 10자리에서 6자리표현

#{문자} 표현하기
print("{{and}}".format())

#f문자열 포매팅{3.6버전 이상부터 사용가능}
name = '홍길동'
age = 30
print(f"나의 이름은 {name}입니다. 나이는 {age}입니다.")
print("나의 이름은 {0}입니다. 나이는 {1}입니다.".format(name,age))

#표현식이란 중괄호 안의 변수를 계산식과 함께 사용하는 것
print(f"my age is {age + 1} next year.")

#딕셔너리(key와 value를 한쌍으로 가지는 자료형)는 
#f 문자열 포매팅에서 다음과 같이 사용가능
d = {'name' : '홍길동', 'age' : 30}
print(f'나의 이름은 {d["name"]}입니다. 나이는 {d["age"]}입니다.')

#위의 문장에서 '와"는 다르게 사용되야 오류가 뜨지 않는다.
#공백채우기
print(f"{'hi':>10}")
print(f"{'hi':*^10}")

#소수점
print(f"{y:0.4f}")
print(f"{y:10.5f}")
print(f"{{and}}")

#문자열 관련 함수들
#문자 개수 세기 - count
a = "hobby"
print(a.count('b')) #a에서 b가 몇개인지 세기

#위치 알려주기 1 - find
a = "Python is best choice"
print(a.find('b')) #대문자 구분함 없으면 -1반환

#위치 알려주기 2 - index
a = "Life is too short"
print(a.index('t')) #없는 문자를 넣으면 오류
#find 와 index의 차이점은 find는 문자열만 사용가능하고,
#index는 문자열 / 리스트 / 튜플은 사용가능하지만, 딕셔너리에선 사용불가

#시작 위치와 끝 위치
a = "oxoxoxoxoxox"
print(a.index('o', 1, 3)) #1~3번째에서 문자 'o'가 위치한 자리
#문자열 삽입 - join
print(",".join('abcd')) # abcd사이에 ',' 삽입
#소문자를 대문자로 바꾸기 - upper
a = "hi"
print(a.upper())
b = a.upper()
#대문자를 소문자로 바꾸기 - lower
print(b.lower())
#공백 지우기
a = f"{'hello':^10}"
print(a.lstrip()) #왼쪽
print(a.rstrip()) #오른쪽
print(a.strip()) #양쪽
#문자열 바꾸기 - replace
a = "Life is too short"
print(a.replace("Life", "Your leg"))
#문자열 나누기 - split
a = "Life is too short"
print(a.split()) #(space) / (Tab) / (Enter)을 기준으로 문자열을 나눠줌
b = "a:b:c:d"
print(b.split(':')) # (:)를 기준으로 문자열을 나눠줌
