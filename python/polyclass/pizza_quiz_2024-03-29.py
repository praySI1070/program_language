prize = 0
while(1):
    size = input("원하시는 피자 사이즈는?(S,M,L)")
    if size == 'S':
        prize += 15000
        break
    elif size == 'M':
        prize += 20000
        break
    elif size == 'L':
        prize += 30000
        break
    else:
        print("다시 골라주세요.")

while(1):
    papo = input("페퍼로니를 추가하시겠습니까?(O,X)")
    if papo == 'O':
        prize += 2000
        break
    elif papo == 'X':
        break
    else:
        print('다시 골라주세요.')

while(1):
    cheeze = input("치즈를 추가하시겠습니까?(O,X)")
    if cheeze == 'O':
        prize += 3000
        break
    elif cheeze == 'X':
        break
    else:
        print('다시 골라주세요.')

print('지불하실 금액은 %d입니다.' % prize)
