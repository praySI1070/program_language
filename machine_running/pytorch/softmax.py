import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import numpy as np
import matplotlib.pyplot as plt

torch.manual_seed(1)

# 데이터 로딩 및 전처리
loaded_data = np.loadtxt('./data04zoo.csv', delimiter=',')
x_train = loaded_data[:, 1:-1]  # 1번째 열부터 마지막 전까지가 특징
y_train = loaded_data[:, -1].astype(int)  # 마지막 열이 라벨 (0부터 시작하는 정수형 라벨)

# Tensor로 변환
x_train = torch.FloatTensor(x_train)  # 특징들 (16개의 특성)
y_train = torch.LongTensor(y_train)  # 정수형 라벨 (0부터 6까지)


class SoftmaxClassifierModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.linear = nn.Linear(15, 7) # Output이 3!

    def forward(self, x):
        return self.linear(x)

model = SoftmaxClassifierModel()

# optimizer 설정
optimizer = optim.SGD(model.parameters(), lr=0.1)

nb_epochs = 1000
for epoch in range(nb_epochs + 1):

    # H(x) 계산
    prediction = model(x_train)

    # cost 계산
    cost = F.cross_entropy(prediction, y_train)

    #정확도 계산
    _, prediction_cl = torch.max(prediction,1)
    correct_prediction = (prediction_cl == y_train).sum().item()
    accuracy = correct_prediction / len(y_train) * 100

    # cost로 H(x) 개선
    optimizer.zero_grad()
    cost.backward()
    optimizer.step()

    # 20번마다 로그 출력
    if epoch % 100 == 0:
        print('Epoch {:4d}/{} Cost: {:.6f} Acc : {:.2f}'.format(
            epoch, nb_epochs, cost.item(), accuracy
        ))

# 임의의 입력 값에 대한 예측
with torch.no_grad():
    # 예측하고 싶은 임의의 입력
    new_input = torch.FloatTensor(loaded_data[2, 1:-1])  
    new_input = new_input.unsqueeze(0)  # 배치 차원 추가하여 (1, 15)로 변환
    # 모델 예측: 선형 연산 후 소프트맥스 적용
    prediction = model(new_input)  # 모델을 사용하여 예측값 계산
    
    # 소프트맥스 함수로 확률로 변환
    prediction_probs = F.softmax(prediction, dim=1)  # 각 클래스에 대한 확률
    
    # 예측된 확률 출력
    predicted_class = torch.argmax(prediction_probs, dim=1)  # 가장 높은 확률을 가진 클래스
    print(f"Predicted probabilities for input {new_input.squeeze().tolist()}: {prediction_probs}")
    print(f"Predicted class: {predicted_class.item()}")