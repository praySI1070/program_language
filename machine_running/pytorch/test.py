#선형회귀

import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
torch.manual_seed(1)

data_url = "http://lib.stat.cmu.edu/datasets/boston"
raw_df = pd.read_csv(data_url, sep="\s+", skiprows=22, header=None)
data = np.hstack([raw_df.values[::2, :], raw_df.values[1::2, :3]])
#target = raw_df.values[1::2, 2]

column_names = ['CRIM','ZN','INDUS','CHAS','NOX','RM','AGE','DIS','RAD','RAX','PTRATIO','B','LSTAT', 'TARGET']

df = pd.DataFrame(data, columns=column_names)

print(df)

#   2   3   5   6   8   11   13
cols = ['TARGET', 'ZN', 'INDUS', 'NOX','RM','DIS','PTRATIO','LSTAT']



data = torch.from_numpy(df[cols].values).float()
x = data[:, 1:]
y = data[:, :1]

epochs = 4000
lr = 1e-3
print_interval = 100

model = nn.Linear(x.size(-1), y.size(-1))
optimizer = optim.SGD(model.parameters(), lr = lr)
for i in range(epochs):
    y_pred = model(x)
    loss = F.mse_loss(y, y_pred)

    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    if (i + 1) % print_interval == 0:
        print("Epoch %d: Loss=%4e" %(i+1, loss))