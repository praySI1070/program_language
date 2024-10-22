#리스트
odd = [1,3,5,7,9] #리스트명 = [요소1, 요소2, 요소3]
a = list() #비어있는 리스트
#리스트의 인덱싱
a = [1,2,3]
print(a)
print(a[0])
print(a[0] + a[2])
print(a[-1])
a = [1, 2, 3, ['a', 'b', 'c']]
print(a[0])
print(a[-1])
print(a[-1][1]) # a리스트 안에 있는 리스트 중에 b
#삼중 리스트
a = [1, 2, ['a', 'b', ['Life', 'is']]]
print(a[-1][-1][0])
#리스트의 슬라이싱
a = [1, 2, 3, 4, 5]
print(a[0:2])
a = "12345"
print(a[0:2])
#리스트 더하기
a = [1,2,3]
b = [4,5,6]
print(a+b)
#리스트 반복하기
a = [1,2,3]
print(a*3)
#리스트 길이 구하기
print(len(a))
#리스트 수정과 삭제
a = [1,2,3]
print(a)
a[2] = 4
print(a)
del a[1]  #삭제  #del 객채로 사용
print(a)
#여러개 삭제
a = [1, 2, 3, 4, 5]
del a[:2]
print(a)
#리스트 관련 함수
#리스트에 요소 추가하기 - append
a.append(1)
print(a)
a.append([6,7])
print(a)
#리스트의 정렬 - sort - 정렬을 해서 원래 함수에 반환
a = [1, 4, 3, 2]
a.sort()
print(a)
a = ['b', 'a', 'c']
a.sort()
print(a)
#리스트 뒤집기 - reverse
a.reverse()
print(a)
#인덱스 반환 - index
a = [1, 2, 3]
print(a.index(3)) #2번 위치
print(a.index(1)) #0번 위치
#리스트에 요소 삽입 - insert
a.insert(0,4) #a 0번 자리에 4를 삽입
print(a)
a.insert(3, 5)
print(a)
#리스트 요소 제거 - remove
#remove(x)는 리스트에서 첫번째로 나오는 x를 삭제하는 함수
a = [1,2,3,1,2,3]
a.remove(3)
print(a)
#리스트 요소 끄집어 내기 - pop
#pop는 리스트의 맨 마지막을 반환하고 그 요소는 삭제한다.
a = [1,2,3]
print(a.pop())
print(a)
a = [1,2,3]
print(a.pop(1)) # 1번 자리를 반환하고 삭제
print(a)
#리스트에 포함된 요소 x의 개수 세기 - count
a = [1,2,3,1]
print(a.count(1))
#리스트의 확장 - extend
a = [1,2,3]
a.extend([4,5])
print(a)
b = [6,7]
a.extend(b)
print(a)
a += [8,9]  #==a.extend([8,9])
print(a)