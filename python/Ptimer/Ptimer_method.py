import tkinter as tk
from Ptimer_class import Ptime as Pt

#변수
chmg = "시작대기중"
#밀리세컨드
settimer = Pt(0)
playtimer = Pt(0)


before_timer_id = None

#타이머 시작 함수
def start(window,label,label2):
    global before_timer_id
    global chmg
    chmg = "타이머 시작"
    label.config(text=f"{chmg}", font=("Arial", 20))

    #전의 타이머예약 삭제
    if before_timer_id is not None:
        window.after_cancel(before_timer_id)

    update(window,label2)

    return


def update(window,label2):
    global before_timer_id
    global settimer
    count = 0
    
    if settimer.total <= 0:
        return

    settimer.total = -1


    label2.config(text = f"남은 시간\n{settimer.time}시간 {settimer.minute}분 {settimer.second}초",font=("Arial", 15))
    before_timer_id = window.after(1000,lambda:update(window,label2))       #1초마다 반복

    return


#타이머 중지함수
def stop(window,label):
    global before_timer_id
    global chmg


    #이미 중지중일 떄 오류
    if before_timer_id is None:
        error("중지중입니다.")
        return
    

    chmg = "타이머 중지"
    label.config(text=f"{chmg}", font=("Arial", 20))
    window.after_cancel(before_timer_id)
    before_timer_id = None

    return


#타이머 초기화 함수
def reset(label2):
    global settimer
    global playtimer

    settimer.reset()
    settimer.total = playtimer.total

    label2.config(text = f"남은 시간\n{settimer.time}시간 {settimer.minute}분 {settimer.second}초",font=("Arial", 15))

    return


#타이머 시간설정 함수
def timeset(window,label2):
    #전용 창 띄우기
    tiset = tk.Toplevel()
    tiset.title("타이머 시간 설정")
    tiset.geometry("300x300")

    # 부모 창의 크기 및 위치 가져오기
    x = window.winfo_x() + (window.winfo_width() // 2) - 150  # 부모 창의 중앙 x좌표
    y = window.winfo_y() + (window.winfo_height() // 2) - 150  # 부모 창의 중앙 y좌표
    tiset.geometry(f"300x300+{x}+{y}")  # 창 크기와 위치 설정

    window.resizable(False, False)

    timer_set_me = tk.Label(tiset,text="타이머 시간 설정",font=("Arial", 15) )
    timer_set_me.grid(row=0,column=2,columnspan=3,pady=10)

    #시간
    set_hour_box = tk.Entry(tiset,width=5)
    set_hour_box.grid(row=1,column=1,padx=5,pady=10)
    #박스에 값 미리넣기, 0은 시작위치
    set_hour_box.insert(0,'0')

    set_hour = tk.Label(tiset,text="시간")
    set_hour.grid(row=1, column=2,padx=5,pady=10)

    #분
    set_minute_box = tk.Entry(tiset,width=5)
    set_minute_box.grid(row=1,column=3,padx=5,pady=10)
    set_minute_box.insert(0,'0')
    set_minute = tk.Label(tiset,text="분")
    set_minute.grid(row=1, column=4,padx=5,pady=10)

    #초
    set_second_box = tk.Entry(tiset,width=5)
    set_second_box.grid(row=1,column=5,padx=5,pady=10)
    set_second_box.insert(0,'0')
    set_second = tk.Label(tiset,text="초")
    set_second.grid(row=1, column=6,padx=5,pady=10)

    #확인 버튼
    set_timer_button = tk.Button(tiset,text="설정 완료",overrelief="solid",width=20,height=1,command=lambda:settimecomplete(int(set_hour_box.get()),int(set_minute_box.get()),int(set_second_box.get()),tiset,label2))
    set_timer_button.grid(row=2,column=2,columnspan=3,pady=10)

    return

def settimecomplete(hour,minute,second,tiset,label2):
    global settimer
    global playtimer

    playtimer.reset()

    
    playtimer.time = hour
    playtimer.minute = minute
    playtimer.second = second
    



    tiset.destroy()
    reset(label2)

    return
    

#에러 함수
def error(message):
    errorset = tk.Toplevel()
    errorset.overrideredirect(True)     #타이틀 창 제거
    errorset.geometry("200x100")
    errorset.resizable(False, False)
    errorset.config(bg='#d5dee8')  # 배경색을 파란색으로 설정


    # 테두리를 위한 Frame 추가
    border_frame = tk.Frame(errorset, bg='blue')
    border_frame.pack(fill=tk.BOTH, expand=True, padx=1, pady=1)


    errormessage = tk.Label(errorset,text=f"{message}")
    errormessage.pack(pady = 10)

    #현재 마우스 위치 가져오기
    x, y = errorset.winfo_pointerxy()


    errorclose = tk.Button(errorset,text="확인", command=errorset.destroy)
    errorclose.pack(pady = 10)

    errorset.geometry(f"+{x-100}+{y-70}")

    return
