from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
import numpy as np

Data_set = np.loadtxt("./ThoraricSurgery3.csv", delimiter=",")
X = Data_set[:,0:16]
y = Data_set[:,16]

model = Sequential()
model.add(Dense(30, input_dim=16,activation='relu'))
model.add(Dense(1,activation='sigmoid'))

model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])  # 딥러닝 모델을 실행합니다.
history=model.fit(X, y, epochs=5, batch_size=16)