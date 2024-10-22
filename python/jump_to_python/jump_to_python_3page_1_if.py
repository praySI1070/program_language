#조건문 if
money = True
if money:
    print("택시를 타고 가라")
else:
    print("걸어 가라")

#비교 연산자
# x == y    같다
# x != y    같지 않다
# x >= y    x가 y보다 크거나 같다
# x <= y    x가 y보다 작거나 같다
money = 2000
if money >= 3000:
    print("택시를 타고 가라")
else:
    print("걸어가라")

#and / or / not
#in / not in
#x in (리스트 , 튜플, 문자열)
#x not in (리스트, 튜플, 문자열)
print(1 in [1, 2, 3])
print(1 not in [1, 2, 3])
pocket = ['paper', 'money', 'cellphone']
if 'money' in pocket:
    pass
else:
    print("카드를 꺼내라")

#elif
pocket = ['crad', 'cellphone']
if 'money' in pocket:
    print("택시를 타고 가라")
elif 'card':
    print("카드로 택시를 타고 가라")
else:
    print("걸어가라")

#if문 한줄
pocket = ['paper', 'money', 'cellphone']
if 'money' in pocket: pass
else: print("카드를 꺼내라")

#조건부 표현식
#변수 = 조건문이_참인_경우의_값 if 조건문 else 조건문이_거짓인_경우의_값
score = 60
if score >=60:
    message = "Success"
else :
    message = "failure"
print(message)
messaged = "Succes" if score >=60 else "failure"
print(messaged)
