from torch import nn,optim
import torch.nn.functional as F
import torch
import matplotlib.pyplot as plt
import mars_comm

class Net(nn.Module):
    def __init__(self, input_feature, num_hidden, num_output):
        super(Net, self).__init__()
        self.hidden = nn.Linear(input_feature, num_hidden)
        self.output = nn.Linear(num_hidden, num_output)

    def forward(self, x):
        x = F.relu(self.hidden(x))
        #x = F.sigmoid(self.hidden(x))
        y = self.output(x)
        return y

x = torch.unsqueeze(torch.linspace(-3, 3, 10000), dim=1)
y = x.pow(3) + 0.3*torch.rand(x.size())

plt.scatter(x.numpy(), y.numpy(), s=0.01)


CUDA = torch.cuda.is_available()

if CUDA:
    net = Net(input_feature=1, num_hidden=20, num_output=1).cuda()
    inputs = x.cuda()
    target = y.cuda()
else:
    net = Net(input_feature=1, num_hidden=20, num_output=1)
    inputs = x
    target = y

optimizer = optim.SGD(net.parameters(), lr=0.01)
criterion = nn.MSELoss()

def train(model, criterion, optimizer, epochs):
    for epch in range(epochs):
        output = model(x) # 应该是构造函数的一种
        loss = criterion(output, target)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        #if epch % 100 == 0:
        #    mars_comm.draw(x,y, output, loss)

    return model, loss


net, loss = train(net, criterion, optimizer, 10000)
print("final loss: ", loss.item())
print("net parameters", list(net.parameters()))

# 那么就可以输入一批输入值来获得输出值

