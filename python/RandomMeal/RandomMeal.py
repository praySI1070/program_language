from PyQt5.QtWidgets import QApplication, QDialog, QWidget,QPushButton,QLabel, QMainWindow,QHBoxLayout,QSizePolicy
from PyQt5.QtGui import QPixmap
from PyQt5.uic import loadUi
from PyQt5.QtCore import QUrl
from PyQt5.QtWebEngineWidgets import QWebEngineView
import os
from RandomMealSerach import RandomMealSerach
from datetime import datetime


class WebEngineWindow(QMainWindow):

    def __init__(self, url,close_WebEngineWindow):
        super().__init__()

        self.close_WebEngineWindow = close_WebEngineWindow
        
        # 툴바 만들기
        toolbar = self.addToolBar('메인 툴바')

        # 툴바에 넣을 버튼 두 개 만들기
        button1 = QPushButton('선택')
        button2 = QPushButton('선택 안함')

        button_style = """
            QPushButton {
                height: 60px;     /* 높이를 60px로! */
                font-size: 16px;  /* 글씨 크기를 16px로! */
                background-color: lightblue;
            }
        """

        button1.setStyleSheet(button_style)
        button2.setStyleSheet(button_style)
        button1.clicked.connect(self.yes)
        button2.clicked.connect(self.no)

        # 버튼들을 담을 위젯과 레이아웃 만들기
        button_widget = QWidget()
        button_layout = QHBoxLayout(button_widget)
        button_layout.setContentsMargins(0, 0, 0, 0) # 마진 없애기
        button_layout.setSpacing(50)

        # 버튼들을 레이아웃에 추가
        button_layout.addWidget(button1)
        button_layout.addWidget(button2)

        # 이제 마법의 '쭉쭉 늘어나는 공간'을 추가할 시간!
        # 버튼 위젯 양옆에 QWidget을 넣고 SizePolicy를 Expanding으로 설정하면
        # 이 위젯들이 공간을 최대한 차지하려고 늘어나면서 가운데 위젯(버튼 위젯)을 밀어내요.
        left_spacer = QWidget()
        right_spacer = QWidget()
        left_spacer.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        right_spacer.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        # 툴바에 '쭉쭉 늘어나는 공간'과 버튼 위젯 추가
        toolbar.addWidget(left_spacer)      # 왼쪽 공간
        toolbar.addWidget(button_widget)    # 버튼 위젯 (이게 가운데로 갈 거예요)
        toolbar.addWidget(right_spacer)     # 오른쪽 공간
        
        # QWebEngineView 인스턴스 생성
        self.browser = QWebEngineView()
        self.browser.setUrl(QUrl(url))  # 웹 페이지 URL 설정
        

        # 메인 윈도우의 중앙 위젯에 웹 브라우저 추가
        self.setCentralWidget(self.browser)
        
        # 창 제목 설정
        self.setWindowTitle("Web Browser")
        
        # 창 크기 설정
        self.setGeometry(100, 100, 1200, 800)

        self.show()

    def yes(self):
        self.close_WebEngineWindow(True)
        self.close()

    def no(self):
        self.close_WebEngineWindow(False)
        self.close()

class MyWindow(QDialog):
    now_pressed_option = [0,0,0,0]
    serachList = []
    button_index = 0

    # 40개의 메뉴중에 10개만 뽑기
    url = 'https://www.10000recipe.com/recipe/list.html'

    unSelectStyle = """
            QPushButton {
                background-color: rgba(0,255,255,00);
                border: 2px solid lightgray;
            }
            QPushButton:hover {
                background-color: rgba(211, 211, 211, 0.5);
            }
            QPushButton:pressed {
                background-color: rgb(169, 169, 169,0.5);
            }
        """
    
    selectStyle = """
            QPushButton {
                background-color: rgba(0, 200, 200, 00);
                border: 4px solid black;
            }
    """

    # 방법별 3
    cat1 = ['','6','1','7','36','41','42','8','10','9','38','67','39','37','11']
    # 상황별 1
    cat2 = ['','12','18','13','19','21','15','43','17','45','20','46','44','14','22']
    # 재료별 2
    cat3 = ['','70','71','72','23','28','24','50','33','47','32','25','31','48','27','26','34']
    # 종류별 0
    cat4 = ['','63','56','54','55','60','53','52','61','57','58','65','64','68','66','69','59','62']
    
    def __init__(self):
        super().__init__()
        file_path = os.path.abspath('./RandomMeal.ui')
        loadUi(file_path, self)  # .ui 파일을 직접 불러옴

        # 이미지 불러오기
        new_pixmap = QPixmap('./class_2.png')
        self.image.setPixmap(new_pixmap)

        # 자식 찾기
        order_text_widget = self.findChild(QWidget, "order_text")
        order_button_widget = self.findChild(QWidget, "order_button")
        a_button_widget = self.findChild(QWidget,"a_Widget")
        b_button_widget = self.findChild(QWidget,"b_Widget")
        c_button_widget = self.findChild(QWidget,"c_Widget")
        d_button_widget = self.findChild(QWidget,"d_Widget")

        test = [a_button_widget,b_button_widget,c_button_widget,d_button_widget]

        for i,index in zip(test,range(4)):
            count=0

            for button in i.findChildren(QPushButton):
                button.clicked.connect(self.select)

                if count==0 : 
                    count+=1
                    continue

                button.setStyleSheet(self.unSelectStyle)
        
        # 여러개 for문 돌리기
        for order_text in order_text_widget.findChildren(QLabel):
            order_text.setText('')

        for order_button in order_button_widget.findChildren(QPushButton):
            order_button.setStyleSheet("""
            QPushButton {
                background-color: rgba(0,255,255,00);
                border: 2px solid lightgray;
            }
            QPushButton:hover {
                background-color: rgba(211, 211, 211, 0.5);
            }
            QPushButton:pressed {
                background-color: rgb(169, 169, 169,0.5);
            }
        """)
            order_button.clicked.connect(self.move_Url)

        #버튼 활용
        self.serachbutton.clicked.connect(self.serach)
        self.exit.clicked.connect(self.close)

    # 위쪽 클릭 함수
    def select(self):
        # 클릭된 버튼을 찾고 해당 인덱스 출력
        clicked_button = self.sender()  # 클릭된 버튼 객체
        parent_widget = clicked_button.parent()  # 클릭된 버튼의 부모 위젯
        parent_widget_name = parent_widget.objectName()
        index_now_pressed_option = 8
        if(parent_widget_name == 'a_Widget'):
            index_now_pressed_option = 0
        elif(parent_widget_name == 'b_Widget'):
            index_now_pressed_option = 1
        elif(parent_widget_name == 'c_Widget'):
            index_now_pressed_option =2
        elif(parent_widget_name == 'd_Widget'):
            index_now_pressed_option = 3

        print(f"Clicked parent index: {index_now_pressed_option}")

        index = 0
        for i in parent_widget.findChildren(QPushButton):
            if(i == clicked_button):
                break
            
            index +=1
        
        print(f"Clicked button index: {index}")

        test = self.now_pressed_option[index_now_pressed_option]
        print(test)

        parent_widget.findChildren(QPushButton)[test].setStyleSheet(self.unSelectStyle)
        self.now_pressed_option[index_now_pressed_option] = index
        clicked_button.setStyleSheet(self.selectStyle)

    # 검색 함수
    def serach(self):
        self.url = self.url + "?q=&query=&" + "cat1="+self.cat1[self.now_pressed_option[3]] + "&cat2="+ self.cat2[self.now_pressed_option[1]] + "&cat3="+ self.cat3[self.now_pressed_option[2]] + "&cat4="+self.cat4[self.now_pressed_option[0]] +"&fct=&order=reco&lastcate=cat3&dsearch=&copyshot=&scrap=&degree=&portion=&time=&niresource="
        print(f"url : {self.url}")
        
        self.serachList = RandomMealSerach(self.url)

        for order_text,serach_text in zip(self.findChild(QWidget, "order_text").findChildren(QLabel),self.serachList):
            order_text.setText(serach_text['text'])

    # 버튼 링크로 이동 함수
    def move_Url(self):
        clicked_button = self.sender()  # 클릭된 버튼 객체
        parent_widget = clicked_button.parent()  # 클릭된 버튼의 부모 위젯

        self.button_index = 0
        for i in parent_widget.findChildren(QPushButton):
            if(i == clicked_button):
                break
            
            self.button_index +=1

        url = self.serachList[self.button_index]['url']
        self.browser_window = WebEngineWindow(url,self.close_WebEngineWindow)


    def close_WebEngineWindow(self,answer):
        print(f"answer = {answer}")
        print(self.now_pressed_option)
        if(answer) :
            # 현재 시간 불러오기
            current_time = datetime.now()

            # 원하는 형식으로 포맷
            formatted_time = current_time.strftime("%Y-%m-%d_%H:%M:%S")

            file_name = "eating.txt"

            temp = self.serachList[self.button_index]

            # 파일이 없으면 생성하고, 있으면 열어서 내용 추가
            with open(file_name, "a", encoding="utf-8") as file:
                #시간, 제목, 사이트주소
                file.write(f"선택한 시간 : {formatted_time}\t {temp['text']} \t {temp['url']} \n")  # 여기에 원하는 내용을 작성

    # 종료 함수
    def close(self):
        print("프로그램 종료")
        QApplication.quit()


if __name__ == "__main__":
    app = QApplication([])
    window = MyWindow()
    window.show()
    app.exec_()