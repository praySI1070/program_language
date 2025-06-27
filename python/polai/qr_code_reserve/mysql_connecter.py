import pymysql
from flask import session, flash

def connect_db():
    mysql_info = {
        'host':'127.0.0.1',
        'port':3306,
        'user':'root',
        'password':'1234',
        'database':'Pol_Ai'
    }
    conn = None
    try :
        conn = pymysql.connect(**mysql_info)    # 연결자 설정 (conn = 연결자)
        print("connection ok")
        pass
    except Exception as e:
        print('error', e)
        pass

    return conn

# def connect_db():
#     mysql_info = {
#         'host':'127.0.0.1',
#         'port':3336,
#         'user':'root',
#         'password':'root',
#         'database':'polai'
#     }
#     conn = None
#     try :
#         conn = pymysql.connect(**mysql_info)    # 연결자 설정 (conn = 연결자)
#         print("connection ok")
#         pass
#     except Exception as e:
#         print('error', e)
#         pass

#     return conn








def login_info(username, password):     # 메인에서 로그인
    """ app.py에서 받아온 id, pw로 sql 조회 로그인 """
    conn = connect_db()
    if conn is None:
        print("error")
        return False, "DB에 연결할 수 없습니다"
    
    SQL = f"SELECT PASSWORD FROM 사용자관리 WHERE ID = '{username}'"

    cursor = conn.cursor()
    cursor.execute(SQL)
    row = cursor.fetchone()
    
    if row != None:
        if row[0] == password:
            session['user_in_login'] = username
            print(session)  # 테스트
            return True, "로그인에 성공했습니다"
        else:
            return False, "ID 혹은 PW가 잘못되었습니다"
    else:
        return False, "ID 혹은 PW가 잘못되었습니다"
    
def get_mypage_info(userid):   # 마이페이지
    conn = connect_db()
    try :
        cursor = conn.cursor()
        SQL = f"SELECT * FROM 사용자관리 where ID = '{userid}'"
        cursor.execute(SQL)
        mypage_info = cursor.fetchall()
    except Exception as e:
        print('error get mypage info : ', e)
        mypage_info = []
        pass
    return mypage_info

def delete_account_confirm(userid, password):
    conn = connect_db()
    try:
        cursor = conn.cursor()
        # print(f"테스트 아이디 삭제 커서 : {cursor.execute("select count(*) is true from 사용자관리 where ID = %s and PASSWORD = %s", (userid, password))}")
        cursor.execute("select count(*) is true from 사용자관리 where ID = %s and PASSWORD = %s", (userid, password))
        account_in_db = cursor.fetchone()[0]
        if account_in_db == 1:
            cursor.execute("DELETE FROM 사용자관리 WHERE ID = %s", (userid,))
            conn.commit()
            flash('탈퇴가 완료되었습니다.')
            session.pop('user_in_login',None)
            return True
        else:
            flash('비밀번호 입력이 잘못되었습니다')
            return False
    except Exception as e:
        flash('예기치 못한 오류가 발생했습니다.')
        print("error delete_account confirm : ", e)
        pass

def get_facilities():   # 체육 시설 정보
    conn = connect_db()
    try :
        cursor = conn.cursor()
        SQL = "SELECT * FROM 시설정보 order by code asc"
        cursor.execute(SQL)
        facilities = cursor.fetchall()
    except Exception as e:
        print('error get_facilities : ', e)
        facilities = []
        pass
    return facilities

def get_weekday():   # 평일 예약 정보
    conn = connect_db()
    try :
        cursor = conn.cursor()
        SQL = "SELECT distinct(시설정보.code), 평일예약.facilities from 평일예약,시설정보 WHERE 평일예약.facilities = 시설정보.facilities order by code"
        cursor.execute(SQL)
        weekday = cursor.fetchall()
    except Exception as e:
        print('error', e)
        weekday = []
        pass
    return weekday


def get_facility_by_id(facility_id):
    conn = connect_db()
    try:
        cursor = conn.cursor()
        SQL = "SELECT * FROM 시설정보 WHERE code = %s"
        cursor.execute(SQL, (facility_id,))
        facility = cursor.fetchone()
    except Exception as e:
        print('error', e)
        facility = None
    return facility

def get_weekday_by_id(facility_id):   # 평일 예약 정보 id 검색
    conn = connect_db()
    try :
        cursor = conn.cursor()
        SQL = "SELECT distinct(시설정보.code), 평일예약.facilities, 평일예약.team, 평일예약.additional from 평일예약,시설정보 WHERE 평일예약.facilities = 시설정보.facilities and code = %s order by code"
        cursor.execute(SQL, (facility_id))
        weekday_id = cursor.fetchall()
    except Exception as e:
        print('error', e)
        weekday_id = []
        pass
    return weekday_id

def get_facility_times(facility_id):    # 평일 예약 시간 나열
    conn = connect_db()
    try:
        with conn.cursor() as cursor:
            SQL = "select 평일예약.open, 평일예약.close, 평일예약.fare from 평일예약 join 시설정보 on 평일예약.facilities = 시설정보.facilities where 시설정보.code = %s"
            cursor.execute(SQL, (facility_id,))
            ficility_times = cursor.fetchall()
            times = [ficility_times[0] for ficility_times in ficility_times] + ' ~ ' +  [ficility_times[1] for ficility_times in ficility_times]
            fares = [ficility_times[2] for ficility_times in ficility_times]
            for_i = [(ficility_times[0], ficility_times[1]) for ficility_times in ficility_times]
    except Exception as e:
        print('error', e)
        ficility_times = []
        pass
    return times, fares, for_i



def get_facility_by_id_to_name(facility_id):    # code 로 이름 불러오는거 (굳이 있어야 하나? 싶긴함)
    conn = connect_db()
    try:
        cursor = conn.cursor()
        SQL = "SELECT facilities FROM 시설정보 WHERE code = %s"
        cursor.execute(SQL, (facility_id,))
        facility = cursor.fetchone()
        print(facility)
    except Exception as e:
        print('error', e)
        facility = None
    return facility

def get_rental_info():   # 대관 시설 목록
    conn = connect_db()
    try :
        cursor = conn.cursor()
        SQL = "SELECT distinct(play) FROM play where play is not NULL order by play"
        cursor.execute(SQL)
        rental_info = cursor.fetchall()
    except Exception as e:
        print('error', e)
        rental_info = []
        pass
    return rental_info


def signup_info(id,password,name,phone,birthday):
    phone = phone[:3] + '-' + phone[3:7] + '-' + phone[7:]
    if len(phone) != 13:
        return False, "휴대폰 번호가 이상합니다."
    if int(birthday[4:6]) > 12 or int(birthday[4:6]) < 1:
        return False, "올바른 생일을 입력해 주세요."
    birthday = birthday[:4] + '-' + birthday[4:6] + '-' + birthday[6:]
    conn = connect_db()
    try:
        cursor = conn.cursor()
        SQL = "SELECT ID,phone FROM 사용자관리"
        cursor.execute(SQL)
        row = cursor.fetchall()
        for i in row:
            if i[0] == id:
                return False, "중복된 ID입니다."
        for i in row:
            if i[1] == phone:
                return False, "중복된 휴대폰 번호입니다."
        SQL = f"INSERT INTO 사용자관리 (COUNT_USERS,ID, PASSWORD, NAME, PHONE, birthday) VALUES (0, %s, %s, %s, %s ,%s)"
        cursor.execute(SQL, (id,password,name,phone,birthday))
        conn.commit()
    finally:
        conn.close()
    return True, "회원가입이 완료되었습니다."

def map_info(facility_code):
    conn = connect_db()
    try :
        cursor = conn.cursor()
        SQL = f"SELECT code,facilities,Address,phone,휴관요일,위도,경도 FROM playcheck WHERE play like '%{facility_code}%';"
        cursor.execute(SQL)
        map_info = cursor.fetchall()
    except Exception as e:
        print('error', e)
        map_info = []
        pass
    finally:
        conn.close()
    return map_info


def save_qr_data(qr_name, facility_name, buyer, playtime, buy_to, buy_end, user_code, fare):
    conn = connect_db()
    try:
        with conn.cursor() as cursor:
            SQL = """
                INSERT INTO qrdata (qr_name, facility_name, buyer, playtime, buy_to, buy_end, user_code, fare)
                VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
            """
            cursor.execute(SQL, (qr_name, facility_name, buyer, playtime, buy_to, buy_end, user_code, fare))
            conn.commit()
    except Exception as e:
        print('error save_qr_data : ', e)
        pass

def load_qr_images(user_id):
    conn = connect_db()
    try:
        with conn.cursor() as cursor:
            SQL = "SELECT qr_name, facility_name FROM qrdata join 사용자관리 WHERE buyer = %s and user_code = 사용자관리.COUNT_USERS and (`use` = 0 or qrdata.buy_end > now())"
            cursor.execute(SQL, (user_id,))
            qr_images = cursor.fetchall()
    except Exception as e:
        print('error load_qr_images : ', e)
        qr_images = []
    return qr_images

def load_qr_info():
    conn = connect_db()
    try:
        with conn.cursor() as cursor:
            SQL = "select distinct qrdata.facility_name from qrdata join 평일예약 where qrdata.facility_name = 평일예약.facilities and 평일예약.Team = 1"
            cursor.execute(SQL)
            qrname = cursor.fetchall()
    except Exception as e:
        print('error load_qr_info : ', e)
        qrname = []
    return qrname

def all_qrdata(buyer):
    conn = connect_db()
    try:
        with conn.cursor() as cursor:
            SQL = "SELECT * FROM qrdata where buyer = %s"
            cursor.execute(SQL, buyer)
            qrdata_all = cursor.fetchall()
    except Exception as e:
        print('error all_qrdata : ', e)
        qrdata_all = []
    return qrdata_all

def payment_all(user_code): # 결제관련
    conn = connect_db()
    try:
        with conn.cursor() as cursor:
            SQL = "select * from qrdata where user_code = %s order by buy_date desc"
            cursor.execute(SQL, user_code)
            payment = cursor.fetchall()
            pay_sum = sum(item[10] for item in payment)
    except Exception as e:
        print('error payment_all : ', e)
        payment = []
    return pay_sum, payment

# def payment_detail(user_code):
#     conn = connect_db()
#     try:
#         with conn.cursor() as cursor:
#             SQL = "SELECT * FROM qrdata where user_code = %s"
#             cursor.execute(SQL, user_code)
#             payment = cursor.fetchall()
#     except Exception as e:
#         print('error payment_all : ', e)
#         payment = []
#     return payment

# def qr_query():
#     conn = connect_db()
#     try:
#         with conn.cursor() as cursor:
#             SQL = 'SELECT q.code, q.qr_name, q.buyer, q.playtime, q.buy_date, q.buy_to, q.buy_end, q.facility_name, q.use, q.user_code FROM qrdata q JOIN 평일예약 r ON q.facility_name = r.facilities WHERE r.Team = 1'
#             cursor.execute(SQL)
#             qrdata = cursor.fetchall()
#     except Exception as e:
#         print('error qr_query : ', e)
#         qrdata = []
#     return qrdata

def check_credit(fares, buyer):     # 가격 확인
    conn = connect_db()
    try:
        with conn.cursor() as cursor:
            SQL = "select if(credit - %s  < 0, 0, 1) from 사용자관리 where ID = %s"
            cursor.execute(SQL, (fares,buyer))
            check_credit = cursor.fetchone()
    except Exception as e:
        print('error', e)
        check_credit = []
    return check_credit

def update_credit(fares, buyer):
    conn = connect_db()
    try:
        with conn.cursor() as cursor:
            SQL = "update 사용자관리 set credit = credit - %s where ID = %s"
            cursor.execute(SQL, (fares,buyer))
            conn.commit()
    except Exception as e:
        print('error check_credit: ', e)

def can_team_reserve(facility_name, start_time, end_time):
    conn = connect_db()
    try:
        with conn.cursor() as cursor:
            SQL = "SELECT COUNT(*) FROM qrdata WHERE facility_name = %s AND (buy_to = %s AND buy_end = %s)"
            print(cursor.execute(SQL, (facility_name, start_time, end_time)))
            cursor.execute(SQL, (facility_name, start_time, end_time))
            result = cursor.fetchone()
            return result[0] == 0
    except Exception as e:
        print('error team reserve :', e)

def get_team_reserve_data(facility_id):
    conn = connect_db()
    try:
        with conn.cursor() as cursor:
            SQL = "select 평일예약.* from 평일예약 join 시설정보 on 평일예약.facilities = 시설정보.facilities where 시설정보.code = %s"
            print(cursor.execute(SQL, (facility_id)))
            cursor.execute(SQL, (facility_id))
            facility_data = cursor.fetchone()
            if facility_data:
                return {
                    "name": facility_data[0],
                    "openTime": facility_data[1],
                    "closeTime": facility_data[2],
                    "farePerSlot": facility_data[3],
                    "perTime": facility_data[4],
                    "additional" : facility_data[5],
                    "team": facility_data[6]
                }
            else:
                return None
    except Exception as e:
        print('error team reserve data : ', e)