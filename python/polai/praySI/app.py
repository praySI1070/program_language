# pip install flask
from flask import Flask, render_template, request, redirect, url_for, session, flash, jsonify
from mysql_connecter import *
from qrcode_maker import newqr, unique_qr_name
from datetime import datetime

app = Flask(__name__)
app.secret_key = '비밀스러운키'
# mysql_connecter.connect_db()

@app.route("/")
def home():
    return render_template('index.html', nowlogin = nowlogin())
def nowlogin():
    return 'user_in_login' in session


@app.route('/facility-info')    # 체육 시설 정보
def facility_info():
    return render_template('facility-info.html', facilities = get_facilities())


@app.route('/facility/<facility_id>')   # 체육 시설 디테일한 정보
def facility_detail(facility_id):
    return render_template('facility-detail.html', facility = get_facility_by_id(facility_id), facilities = get_facilities())


@app.route('/rental-info')  # 대관 정보
def rental_info():
    return render_template('rental-info.html', rental_info = get_rental_info())

@app.route('/get_data')
def get_data():
    facility_code = request.args.get('facilitycode')[1:]
    print(f"코드:"+facility_code)
    data = map_info(facility_code)  # 전달할 데이터 예시

    dict_data = {}
    for item in data:
        dict_data[item[0]] = {
            'code' : item[0],
            'facilities' : item[1],
            'address': item[2],
            'phone': item[3],
            'operation_hours': item[4],
            'latitude': item[5],
            'longitude': item[6]
        }

    return jsonify(dict_data)

@app.route('/facility-ticket')
def ticket_issue():
    return render_template('facility-ticket.html', facilities = get_weekday())


# @app.route('/facility-ticket/<facility_id>')   # 입장권 발급 찐 중요한곳
# def facility_ticket_detail(facility_id):   # 돌려쓰기 잠깐 한것
#     return render_template('facility-ticket-detail.html', 
#                            facility = get_facility_by_id(facility_id), facilities = get_facilities(), name = session['user_in_login'])
@app.route('/facility-ticket/<facility_id>')
def facility_ticket_detail(facility_id):
    if 'user_in_login' in session and session['user_in_login']:
        return render_template('facility-ticket-detail.html', facility = get_weekday_by_id(facility_id)[0],
                               facility_team_reserve = get_team_reserve_data(facility_id),
                               facility_is_team = get_weekday_by_id(facility_id)[0][2],
                               count_use = count_now_use(facility_id))  # 현재 사용 인원 조회
                            #    facility_times = get_facility_times(facility_id)[0],
                            #    facility_fares = get_facility_times(facility_id)[1],
                            #    i = get_facility_times(facility_id)[2])
    else:
        flash('현재 로그인 되어있지 않습니다.')
        return redirect(url_for('login'))

@app.route('/generate-qr/<facility_id>', methods=['POST'])
def generate_qr(facility_id):
    # print(f"테스트 시간 {request.form['playtime']}")    # 디버깅용
    facility_name = get_facility_by_id_to_name(facility_id)
    qr_name = unique_qr_name()
    buyer = session['user_in_login']
    fares = (request.form['fares'])
    user_code = get_mypage_info(buyer)[0][0]  # 유저 고유 코드 검색
    # print(f"테스트 가격 {fares}")    # 디버깅용
    if request.form['playtime'].isdigit() == False:
        date = request.form['date']
        playtime = request.form['playtime']

        
        # 시간 문자열을 파싱
        start_time_str, end_time_str = playtime.split(' ~ ')
        buy_to = datetime.strptime(f"{date} {start_time_str}:00", '%Y-%m-%d %H:%M:%S')  # 문자열을 시간 객체로 변환
        buy_end = datetime.strptime(f"{date} {end_time_str}:00", '%Y-%m-%d %H:%M:%S')

        playtime = int((buy_end - buy_to).total_seconds() / 3600)   # playtime 컬럼에 넣을 값 계산
        if buy_to > datetime.now():
            # 예약 가능 여부 확인
            if can_team_reserve(facility_name, buy_to, buy_end):
                print(f"예약 시간 계산 : {playtime}")
                pass
            else:
                flash('해당 시간은 이미 예약된 시간입니다.')
                print('해당 시간은 이미 예약된 시간입니다.')
                return redirect(url_for('facility_ticket_detail', facility_id=facility_id, fail_already_reserve=True))
        else:
                flash('해당 시간은 예약이 불가능합니다.')
                print('해당 시간은 예약이 불가능합니다.')
                return redirect(url_for('facility_ticket_detail', facility_id=facility_id, fail_past_reserve=True))
    else:
        playtime = request.form['playtime']
        buy_to = datetime.today().strftime("%Y-%m-%d %H:%M:%S")      # buy_date + timedelta(days=1)  # 예시: QR 코드 유효 기간 시작일
        buy_end = datetime.today().strftime("%Y-%m-%d %H:%M:%S")     # buy_to + timedelta(days=30)  # 예시: QR 코드 유효 기간 종료일

    if check_credit(fares, buyer)[0] == False:  # 가격 확인
        flash('크레딧이 부족합니다.')
        return redirect(url_for('facility_ticket_detail', facility_id=facility_id))
    update_credit(fares, buyer)
    newqr(qr_name, facility_id)
    save_qr_data(qr_name, facility_name, buyer, playtime, buy_to, buy_end, user_code, fares)
    flash('QR 코드가 성공적으로 발급되었습니다.')
    return redirect(url_for('mypage'))

@app.route('/notices')
def notices_detail():
    notices = get_notices_info('facility')
    #로그인 중인 유저 아이디
    user_id = None
    if 'user_in_login' in session:
        user_id = session['user_in_login']
    admin = get_admin(user_id)

    #체육관 이름 불러오기
    facilities_info =[]
    for i in get_facilities():
        facilities_info.append(i[1])

     # 페이지네이션을 위한 변수
    page = request.args.get('page', 1, type=int)
    per_page = 8
    start = (page - 1) * per_page
    end = start + per_page
    paginated_notices = notices[start:end]

    total_pages = len(notices) // per_page + (1 if len(notices) % per_page > 0 else 0)

    return render_template('notices-detail.html',notices=paginated_notices, admin=admin, facilities_info=facilities_info, page=page, total_pages=total_pages)

@app.route('/notices-detail-delete')
def notices_detail_delete():
    notices = get_notices_info('facility')

    #로그인 중인 유저 아이디
    user_id = None
    if 'user_in_login' in session:
        user_id = session['user_in_login']
    admin = get_admin(user_id)

    #체육관 이름 불러오기
    facilities_info =[]
    for i in get_facilities():
        facilities_info.append(i[1])

     # 페이지네이션을 위한 변수
    page = request.args.get('page', 1, type=int)
    per_page = 8
    start = (page - 1) * per_page
    end = start + per_page
    paginated_notices = notices[start:end]

    total_pages = len(notices) // per_page + (1 if len(notices) % per_page > 0 else 0)
    
    return render_template('notices-detail-delete.html',notices=paginated_notices, admin=admin, facilities_info=facilities_info, page=page, total_pages=total_pages)

@app.route('/delete_notices', methods=["POST"])
def delete_notices():
    data = request.get_json()
    print(data)
    delete_notices_SQL(data)
    return jsonify({"message": "Notice delete successfully."})

@app.route("/save_notice", methods=["POST"])
def save_notice():
    data = request.get_json() # POST 요청으로부터 JSON 데이터 받기
    # 받은 데이터 처리
    save_notices(data)
    

    return jsonify({"message": "Notice saved successfully."})

@app.route("/update_notice", methods=["POST"])
def update_notice():
    data = request.get_json()
    print(data)
    update_notices(data)
    return jsonify({"message": "Notice update successfully."})

# @app.route('/login')
# def login():
#     return "로그인 페이지"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        input_username = request.form['username']
        input_password = request.form['password']
    
        is_authenticated, message = login_info(input_username, input_password)

        if is_authenticated:
            session['user_in_login'] = input_username
            return redirect(url_for('home'))
        else:
            return render_template('login.html', error=message)
    return render_template('login.html', error=None)

@app.route('/logout',methods=['GET'])
def logout():
    session.pop('user_in_login',None)
    return redirect('/')

@app.route('/mypage')
def mypage():
    if 'user_in_login' in session and session['user_in_login']:
        return render_template('mypage.html',
                                mypage_info = get_mypage_info(session['user_in_login'])[0]) # session에 내 아이디로 저장된 튜플의 0번만 사용 = 내것만 사용
    else:
        flash('현재 로그인 되어있지 않습니다.')
        return redirect(url_for('home'))        # 원래 쓰려고 만든건데 안쓸덧
    
@app.route('/qr-info')
def qrinfo():
    qr_info_tuple = load_qr_info()
    qr_info = [item[0] for item in qr_info_tuple]   # 튜플형태의 구조를 1차원 리스트로 변경
    qrall = all_qrdata(session['user_in_login'])
    qr_images = [item[0] for item in load_qr_images(session['user_in_login'])]      # load_qr_images로 select 한 qr고유코드와 체육관 이름들 저장
    facility_name = [item[1] for item in load_qr_images(session['user_in_login'])]
    return render_template('qr-info.html',
                           qr_images = qr_images,          # qr 이미지 저장
                           facility_name = facility_name,  # 체육관 이름 저장
                           qr_info = qr_info,   # qr 비교해서 팀인지, 아닌지 확인용
                           qrall = qrall)


@app.route('/delete-account')   # 계정 삭제 / 회원 탈퇴
def delete_account():
    account_info = get_mypage_info(session['user_in_login'])[0]
    print(f"아이디 삭제 예시 : {account_info}")
    return render_template('delete-account.html', account_id = account_info[1])

@app.route('/confirm-delete', methods=['POST']) # 탈퇴 진행
def confirm_delete():
    user_id = request.form['user_id']
    password = request.form['password']
    print(f"아이디 삭제 테스트 비번 : {password}")
    if delete_account_confirm(user_id, password) is True:
        return redirect(url_for('login'))
    else:
        return redirect(url_for('delete_account'))

@app.route('/payment-info') # 결제
def payment_info():
    user_code = get_mypage_info(session['user_in_login'])[0][0]
    pay_sum, payment_detail = payment_all(user_code)
    # ┏페이지 관련┓
    page = request.args.get('page', 1, type=int)
    per_page = 25
    start = (page - 1) * per_page
    end = start + per_page
    total_count = len(payment_detail)
    payments_to_display = payment_detail[start:end]
    return render_template('payment-info.html', pay_sum = pay_sum, payment_detail=payments_to_display, total_count=total_count, page=page, per_page=per_page)


@app.route('/signup', methods=['GET', 'POST'])
def signup():
    
    if request.method == 'POST':
        input_id = request.form['id']
        input_password = request.form['password']
        input_name = request.form['name']
        input_phone = request.form['phone']
        input_birthday = request.form['birthday']

        is_authenticated, message = signup_info(input_id,input_password,input_name,input_phone,input_birthday)

        if is_authenticated:

            return render_template('signup.html', success=True)
        else:
            return render_template('signup.html', error = message,failed=True)
    return render_template('signup.html', error=None)

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=8080, debug=True)
