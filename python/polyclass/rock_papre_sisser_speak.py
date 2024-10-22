import random
import pyttsx3 as py
engine = py.init()
engine.setproperty('rate',150)

def speak(text):
    engine.say(text)
    engine.runAndWait()

rock = '''
    _______
---'   ____)
      (_____)
      (_____)
      (____)
---.__(___)
'''
paper = '''
    _______
---'   ____)____
          ______)
          _______)
         _______)
---.__________)
'''
scissors = '''
    _______
---'   ____)____
          ______)
       __________)
      (____)
---.__(___)
'''
def me():
    b = input("바위는 0 보는 1 가위는 2중에 하나를 선택하시오.(0/1/2)")
    if(b == '0'):
        print(rock)
        return 0
    elif(b == '1'):
        print(paper)
        return 1
    elif(b == '2'):
        print(scissors)
        return 2
    elif(b == '999'):
        exit()
    else:
        print("다시 선택해주세요.")
        return me()

def game():
    b = me()
    cp = random.randrange(0,3)
    print("cp :" + str(cp))
    if(cp == 0):
        print(rock)
    elif(cp == 1):
        print(paper)
    else:
        print(scissors)
    
    if(int(b) - int (cp) == 0):
        print("무승부")
        speak("무승부")
    elif(int(b) - int(cp) == 1 or int(b) - int(cp) == -2):
        print("승리")
        speak("승리")
    else:
        print("패배")
        speak("패배")
    
    game()

game()
