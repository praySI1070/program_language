import pandas as pd

# 광물 데이터를 불러옵니다.
df = pd.read_csv('./sonar3.csv', header=None)

# 첫 5줄을 봅니다.
df.head()

# 일반 암석(0)과 광석(1)이 몇 개 있는지 확인합니다.
print(df[60].value_counts())

X = df.iloc[:,0:60]
y = df.iloc[:,60]

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# 모델을 설정합니다.
model = Sequential()
model.add(Dense(24,  input_dim=60, activation='relu'))
model.add(Dense(10, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

# 모델을 컴파일합니다.
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

# 모델을 실행합니다.
history=model.fit(X, y, epochs=200, batch_size=10)

