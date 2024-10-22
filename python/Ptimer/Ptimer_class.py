#_로 시작하는 이름을 가진 변수는 외부에서 직접 접근하지 않는 파이썬의 관행

class Ptime:
    def __init__(self,total):
        self._total = total
        self._time = 0
        self._minute = 0
        self._second = 0

        self.update_time()
    
    #속성으로 변환

    @property
    def total(self):
        return self._total
    @property
    def time(self):
        return self._time
    
    @property
    def minute(self):
        return self._minute
    
    @property
    def second(self):
        return self._second
    
    @total.setter
    def total(self,value):
        self._total += value

        self.update_time()

    @time.setter
    def time(self,value):
        self._total += value*60*60

        self.update_time()
        


    @minute.setter
    def minute(self,value):
        self._total += value*60

        self.update_time()
    

    @second.setter
    def second(self,value):
        self._total += value

        self.update_time()
    

    def reset(self):
        self._total = 0
        self.update_time()

    def update_time(self):
        if self._total < 0:
            raise ValueError("시간이 음수일 수는 없습니다.")

        self._time = int(self._total / 3600)
        self._minute = int((self._total / 60)%60)
        self._second = int(self._total % 60)


    #객체 자체를 출력할떄 넘겨주는 형식
    #서로 다른 자료형 간 인터페이스를 제공하기 위한 목적으로 존재
    def __str__(self):
        return f"{self._time}시간 {self._minute}분 {self._second}초"
    
