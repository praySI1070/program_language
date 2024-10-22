#파이썬은 변수에 저장된 값을 스스로 판단하여 자료형의 타입을 지정하기 떄문에 더 편리하다.

#리스트를 복사하고자 할 때
a = [1,2,3]
b = a       #b는 a의 포인터 변수인 거 같음
print(id(a))
print(id(b))    #동일
a[1] = 4
print(a)
print(b)

#변수 복사하면서 다른 주소를 가르키기
#[:] 사용하기
a = [1,2,3]
b = a[:]
a[1] = 4
print(a)
print(b)
print(id(a))
print(id(b))
#copy 모듈 사용하기
from copy import copy
a = [1,2,3]
b = copy(a)
print(b is a)
#copy 함수 사용
a = [1,2,3]
b = a.copy()
print(b is a)
print("--------")

#변수를 만드는 여러가지 방법
a, b = ('python', 'life')
(a,b) = 'python', 'life'    #a는 문자
[a,b] = ['python', 'life']  #a는 문자
a = b = 'python'

#두 변수의 값 바꾸기
a = 3
b = 5
a, b = b, a
print(a,b)