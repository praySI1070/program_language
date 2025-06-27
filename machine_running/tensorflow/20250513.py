from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

import matplotlib.pyplot as plt
import seaborn as sns

# pandas 라이브러리를 불러옵니다.
import pandas as pd

# 피마 인디언 당뇨병 데이터셋을 불러옵니다.
df = pd.read_csv('./pima-indians-diabetes3.csv')

# print("df.head\n")
# print(df.head(5))
#
# print("df['diabetes'].value_counts()\n")
# print(df['diabetes'].value_counts())
#
# print("df.describe()\n")
# print(df.describe())
#
# print("df.corr()\n")
# print(df.corr())

# 데이터 간의 상관 관계를 그래프로 표현해 봅니다.
colormap = plt.cm.gist_heat   # 그래프의 색상 구성을 정합니다.
plt.figure(figsize=(12,12))   # 그래프의 크기를 정합니다.

# 그래프의 속성을 결정합니다. vmax의 값을 0.5로 지정해 0.5에 가까울수록 밝은색으로 표시되게 합니다.
#sns.heatmap(df.corr(),linewidths=0.1,vmax=0.5, cmap=colormap, linecolor='white', annot=True)


# plasma를 기준으로 각각 정상과 당뇨가 어느 정도 비율로 분포하는지 살펴봅니다.
# plt.hist(x=[df.plasma[df.diabetes==0], df.plasma[df.diabetes==1]], bins=30, histtype='barstacked', label=['normal','diabetes'])
# plt.legend()
# plt.show()

# 세부 정보를 X로 지정합니다.
X = df.iloc[:,0:8]
# 당뇨병 여부를 y로 지정합니다.
y = df.iloc[:,8]

# 모델을 설정합니다.
model = Sequential()
model.add(Dense(20, input_dim=8, activation='relu', name='Dense_1'))
model.add(Dense(12, activation='relu', name='Dense_2'))
model.add(Dense(20, activation='relu', name='Dense_3'))
model.add(Dense(8, activation='relu', name='Dense_4'))
model.add(Dense(1, activation='sigmoid',name='Dense_5'))
model.summary()

# 모델을 컴파일합니다.
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

# 모델을 실행합니다.
history=model.fit(X, y, epochs=300, batch_size=5)
