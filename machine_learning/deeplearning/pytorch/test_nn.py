import torch
from time import perf_counter
from torch import nn, optim as optim
from time import perf_counter
import mars_comm

x =  torch.unsqueeze(torch.linspace(-3,3, 1000), dim=1)
y = x + 1.2*torch.rand(x.size())

class LR(nn.Module):
    def __init__(self):
        super(LR, self).__init__()
        self.linear = nn.Linear(1,1)

    def forward(self, x):
        out = self.linear(x)
        return out

if mars_comm.CUDA:
    LR_model = LR().cuda()
    inputs = x.cuda()
    target = y.cuda()
else:
    LR_model = LR()
    inputs = x
    target = y

criterion = nn.MSELoss()
optimizer = optim.SGD(LR_model.parameters(), lr=1e-2)

def train(model, criterion, optimizer, epochs):
    for epoch in range(epochs):
        output = model(inputs)
        loss = criterion(output, target)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        #if epochs % 1000 == 0:
        #    mars_comm.draw(output, loss)
    return model, loss

start = perf_counter()
w,loss = train(LR_model, criterion, optimizer, 1000)
finish = perf_counter()
time = finish - start
print("计算时间:%s" % time)
print("final loss:", loss.item())
print("weights:", list(LR_model.parameters()))
