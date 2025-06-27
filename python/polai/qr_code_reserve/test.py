from datetime import datetime

print(datetime.today().microsecond)
print(f"{datetime.today().month:02}")

test = f"{datetime.today().year%100}{datetime.today().month:02}{datetime.today().day:02}{datetime.today().microsecond}"
print(test)
print(datetime.today().strftime("%Y-%m-%d %H:%M:%S"))


def get_facilities(table_type):   # 체육 시설 정보
    facilities = table_type
    return facilities

print(get_facilities('시설정보'))




time_str = "06:00 ~ 08:00"

# 공백을 기준으로 문자열을 나누고, 앞부분을 선택
start = time_str.split(' ')
first = int(start[0].split(':')[0])
second = int(start[2].split(':')[0])
print(first)
print(f"테스트 sec - fir {second - first}")

buy_to = datetime.strptime('2024-06-11 09:00:00', '%Y-%m-%d %H:%M:%S')
buy_end = datetime.strptime('2024-06-11 13:00:00', '%Y-%m-%d %H:%M:%S')

# 시간 차이 계산
time_difference = int((buy_end - buy_to).total_seconds() / 3600)
print(time_difference)


# buy_to 변수 설정
buy_to = datetime.strptime('2024-06-09 06:00:00', '%Y-%m-%d %H:%M:%S')

# 현재 시간 구하기
current_time = datetime.now()
print(buy_to, current_time)
# buy_to가 현재 시간보다 빠른지 여부를 확인하여 출력
if buy_to > current_time == False:
    print(0)
else:
    print(1)
