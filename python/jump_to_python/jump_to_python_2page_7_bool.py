a = True
b = False
print(a)
print(b)
print(type(a))
print(type(b))
print(1 == 1)
print(2 > 1)
print(2 < 1)

#자료형의 참과 거짓
#문자열,리스트,튜플,딕셔너리 드으이 값이 비어있으면 거짓, 아니면 참
#숫자는 0일 때 거짓, None은 거짓
a = [1,2,3,4]
while a:
    print(a.pop())  #리스트 안에 요소가 있으면 계속 참이므로, 계속 뽑아냄
print(a)
if []:
    print("참")
else:
    print("거짓")
if [1,2,3]:
    print("참")
else:
    print("거짓")

#볼 연산
print(bool('python'))
