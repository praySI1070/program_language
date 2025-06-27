import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import numpy as np
import matplotlib.pyplot as plt
import threading

torch.manual_seed(1)

loaded_data = np.loadtxt('./diabetes.csv', delimiter=',')

x_data = loaded_data[:, :-1]
y_data = loaded_data[:, -1:]
x_train = torch.FloatTensor(x_data)
y_train = torch.FloatTensor(y_data)

class BinaryClassifier(nn.Module):
    def __init__(self):
        super().__init__()
        self.linear = nn.Linear(8, 1)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        return self.sigmoid(self.linear(x))
    
model = BinaryClassifier()

# optimizer 설정
optimizer = optim.SGD(model.parameters(), lr=1)

cost_list = []
accuracy_list = []

nb_epochs = 1000
for epoch in range(nb_epochs + 1):

    # H(x) 계산
    hypothesis = model(x_train)

    # cost 계산
    cost = F.binary_cross_entropy(hypothesis, y_train)
    cost_list.append(cost.item())

    # cost로 H(x) 개선
    optimizer.zero_grad()
    cost.backward()
    optimizer.step()

    prediction = hypothesis >= torch.FloatTensor([0.5]) # 예측값이 0.5를 넘으면 True로 간주
    correct_prediction = prediction.float() == y_train # 실제값과 일치하는 경우만 True로 간주
    accuracy = correct_prediction.sum().item() / len(correct_prediction) # 정확도를 계산
    accuracy_list.append(accuracy)

    # 10번마다 로그 출력
    if epoch % 10 == 0:
        print('Epoch {:4d}/{} Cost: {:.6f} Accuracy {:2.2f}%'.format( # 각 에포크마다 정확도를 출력
            epoch, nb_epochs, cost.item(), accuracy * 100,
        ))

for param in model.parameters():
    print(param)

# 인터랙티브 모드 활성화
plt.ion()

def plot_loss():
    plt.figure(figsize=(8, 6))
    plt.title('Loss Trend')
    plt.xlabel('epochs')
    plt.ylabel('LOSS')
    plt.grid()

    plt.plot(cost_list, label='Training Loss')
    plt.legend(loc='best')

    # 그래프를 즉시 표시
    plt.draw()
    plt.pause(0.1)  # 잠시 대기해서 그래프를 업데이트할 시간 확보

def plot_accuracy():
    plt.figure(figsize=(8, 6))
    plt.title('Accuracy Trend')
    plt.xlabel('epochs')
    plt.ylabel('Accuracy')
    plt.grid()

    plt.plot(accuracy_list, label='Training Accuracy')
    plt.legend(loc='best')

    # 그래프를 즉시 표시
    plt.draw()
    plt.pause(0.1)  # 잠시 대기해서 그래프를 업데이트할 시간 확보

# 쓰레드에서 그래프 표시 작업을 수행하되, 실제로 그리는 부분은 메인 스레드에서 수행
def run_plots():
    plot_loss()
    plot_accuracy()

# 메인 스레드에서 실행
run_plots()

# 인터랙티브 모드를 종료하고 그래프를 완전히 보여줌
plt.ioff()
plt.show()
