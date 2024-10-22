#------------------------------------------------------------
#ImportError: cannot import name 'start' from partially initialized module 'Ptimer_method' (most likely due to a circular import) (d:\AS_2405110208_praySI\Timer\Ptimer_method.py)
#임폴트 오류 // 순환 호출

# A클래스에서 B클래스를 호출한다면 A클래스의 내용이 변경되더라도 B클래스를 수정할 필요는 없다. 
# 그러나 A클래스에서 B클래스를 호출하면서 B클래스에서 A클래스를 호출한다면 두 클래스가 서로 의존관계이므로 A클래스의 내용이 변경될 때 B클래스의 내용도 수정되어야 한다. 
# 요구사항 변경으로 인한 소스코드 변경은 필연적으로 발생하고, 그때 변경을 최소화 하기 위해 순환호출을 금지한다.

#수정 전 자료
# import tkinter as tk
# import Ptimer_class as Ptc
# from Ptimer_method import start,stop,reset,timeset
#---------
# import tkinter as tk
# from Ptimer import label,label2,window
#------------------------------------------------------------

import tkinter as tk
import Ptimer_class as Ptc
from Ptimer_method import start,stop,reset,timeset







#윈도우 창 크기 설정
window=tk.Tk()
window.title("Timer")
window.geometry("500x350")
window.resizable(False, False)




#텍스트 표시
label=tk.Label(window, text = "시작 대기중", font=("Arial", 20))
label.pack()

label2 = tk.Label(window, text = f"남은 시간\n0",height=5,font=("Arial", 15))
label2.pack()

#시작 버튼
button = tk.Button(window,text="타이머 시작", overrelief="solid", width=20,height=1,command=lambda:start(window,label,label2))          #람다함수로 매개변수 던지기
button.pack(pady=5)

#중지 버튼
button2 = tk.Button(window, text="타이머 중지",overrelief="solid", width=20,height=1,command=lambda:stop(window,label))
button2.pack(pady=5)

#초기화 버튼
button3 = tk.Button(window,text="타이머 초기화",overrelief="solid", width=20,height=1,command=lambda:reset(label2))
button3.pack(pady=5)

#타이머 시간 설정 버튼
button4 = tk.Button(window,text="타이머 시간 설정",overrelief="solid", width=20,height=1,command=lambda:timeset(window,label2))
button4.pack(pady=5)



window.mainloop()