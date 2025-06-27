import qrcode
import os
from datetime import datetime
from flask import render_template,url_for

def newqr(qr_name, facility_id):
    qr_data = qr_name

    # QR 코드 생성
    qr = qrcode.QRCode(version=1, error_correction=qrcode.constants.ERROR_CORRECT_L, box_size=10, border=4)
    qr.add_data(qr_data)
    qr.make(fit=True)

    img = qr.make_image(fill='black', back_color='white')

    # QR 코드를 파일로 저장
    img_path = os.path.join('static/images', f'{qr_name}.png')
    img.save(img_path)

    qr_code_url = url_for('static', filename=f'images/{qr_name}.png')
    return render_template('facility-ticket-detail.html', facility=[None, facility_id], qr_code_url=qr_code_url)


def unique_qr_name():
    while True:
        qr_name = int(f"{datetime.today().year%100}{datetime.today().month:02}{datetime.today().day:02}{datetime.today().microsecond:06}")
        # qr_name에 연도 / 월 / 일 / 마이크로초 6개 합쳐서 저장 -> 24 01 01 987654 식으로
        file_path = os.path.join('static/images', f'{qr_name}.png')
        if not os.path.exists(file_path):
            return qr_name

################################################


# create table qrdata (
# 	code int primary key auto_increment,
#     qr_name int unique key not null,
#     buyer varchar(45) not null,
#     buy_date date not null,
#     buy_to date not null,
#     buy_end date not null
# );