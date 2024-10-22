#딕셔너리는 key를 통하여 value를 얻는다.
#딕셔너리의 기본 모습
#{Key1: value1, Key2: value2, Key: value3}
dic = {'name': 'pey', 'phone': '010-9999-1234', 'birth': '1118'}
print(dic)

#딕셔너리 쌍 추가, 삭제하기
#쌍 추가하기
a = {1: 'a'}
a[2] = 'b'
print(a)
a['name'] = 'pey'
print(a)

#삭제하기
del a[1]
print(a)    #1번값 삭제

#딕셔너리에서 Key를 사용해 Value 얻기
grade = {'pey': 10, 'julliet': 99}
print(grade['pey'])
print(grade['julliet'])
#딕셔너리 만들 때 주의할 사항
#Key 값이 중복이 안되서 한개를 제외하고는 전부 삭제되므로 Key값은 중복되서는 안 된다.
#Key에 리스트는 사용 불가능 But, 튜플쪽에는 리스트를 사용가능

#딕셔너리 관련 함수
#Key리스트 만들기 - Keys
a = {'name': 'pey', 'phone': '010-9999-1234', 'birth': '1118'}
b = a.keys()    #a의 Key만을 모아 dict_keys 객체를 리턴한다.
print(b)
for k in a.keys():
    print(k)
#리스트 고유의 append, insert, pop, remove, sort함수는 수행 불가

#리스트로 변환
print(list(a.keys()))

#value 리스트 만들기 - values
print(a.values())

#Key, Value 쌍 얻기 - items
print(a.items())

#Key:Value 쌍 모두 지우기 - clear
a.clear()
print(a)

#Key로 value 얻기 - get
a = {'name': 'pey', 'phone': '010-9999-1234', 'birth': '1118'}
print(a.get('name'))
print(a.get('phone'))

#Key가 없을 경우, 미리 정해둔 값을 대신 가져오기
print(a.get('play', 'x'))

#해당 Key가 딕셔너리 안에 있는지 조사하기 - in
print('name' in  a)
print('email' in a)