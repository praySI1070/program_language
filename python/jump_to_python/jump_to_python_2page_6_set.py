#집합(set)은 집합에 관련된 것을 쉽게 처리하기 위해 만든 자료형이다.
s1 = set([1,2,3])
print(s1)
s2 = set("Hello")
print(s2)
s3 = set()  #비어있는거
print(s3)

#집합 자료형의 특징
#중복 허용x
#순서가 없음(Unordered)
#set 자료형을 인덱싱으로 접근하려면 리스트나 튜플로 변환후에 해야 함
l1 = list(s1)
print(l1)
print(l1[0])
t1 = tuple(s1)
print(t1)
print(t1[0])

#교집합, 합집합, 차집합 구하기
s1 = set([1, 2, 3, 4, 5, 6])
s2 = set([4, 5, 6, 7, 8, 9])
#교집
print(s1&s2)
print(s1.intersection(s2))
#합집
print(s1|s2)
print(s1.union(s2))
#차집
print(s1 - s2)
print(s1.difference(s2))

#집합 자료형 관련 함수
#값 1개 추가하기 - add
s1 = set([1,2,3])   #소괄호 주의
s1.add(4)   #?왜안됨 - 집합 설정이 안 되어 있었음
print(s1)
s1 = set([1,2,3])
s1.update([4,5,6])
print(s1)
s1.remove(3)
print(s1)