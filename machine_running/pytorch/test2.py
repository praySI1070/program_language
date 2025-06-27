

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

from sklearn.datasets import load_breast_cancer
cancer = load_breast_cancer()
df = pd.DataFrame(cancer.data,columns=cancer.feature_names)

df['class'] = cancer.target
# sns.pairplot(df[['class'] + list(df.columns[:10])])
# plt.show()

cols = [,'class']

data = torch.from_numpy(df[cols].values).float()

x = data[:, :-1]
y = data[:,-1:]

epochs = 200000
lr = 1e-2
print_interval = 10000

model = LogisticModel(input_dim = x.size(-1), output_dim= y.size(-1))
criterion = nn.BCELoss()
optimizer = optim.SGD(model.parameters(), lr=lr)

for i in range(epochs):
    pred = model(x)
    loss = criterion(pred, y)

    optimizer.zero.grad()