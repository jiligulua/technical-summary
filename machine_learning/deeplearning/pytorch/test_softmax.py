from torch import nn, optim
import torch
import torch.nn.functional as F
import matplotlib.pyplot as plt

class Net(nn.Module):
    def __init__(self, input_features, num_hidden, outputs):
        super(Net, self).__init__()
        self.hidden = nn.Linear(input_features, num_hidden)
        self.output = nn.Linear(num_hidden, outputs)

    def forward(self, x):
        x = F.relu(self.hidden(x))
        x = self.output(x)
        x = F.softmax(x)
        return x


def get_model_inputs_target(input_features, num_hidden, outputs, x, y):
    CUDA = torch.cuda.is_available()
    if CUDA:
        net = Net(input_features, num_hidden, outputs).cuda()
        inputs = x.cuda()
        target = y.cuda()
    else:
        net = Net(input_features, num_hidden, outputs)
        inputs = x                                                                                
        target = y
    return net, inputs, target


def get_optimizer_criterion(model):
    optimizer = optim.SGD(model.parameters(), lr=0.02)
    criterion = nn.CrossEntropyLoss()
    return optimizer, criterion


def draw(output, inputs, targets):
    plt.cla()
    output = torch.max(output, 1)[1]
    pred_y = output.data.numpy().squeeze()
    target_y = targets.numpy()
    plt.scatter(inputs.numpy()[:,0], inputs.numpy()[:,1], c=pred_y, s=10,lw=1, cmap='RdYlGn')
    accuracy = sum(pred_y == target_y) / len(inputs.numpy())
    plt.text(1.5, -4, 'Accuracy=%s' % (accuracy), fontdict={'size':20, 'color':'red'})
    plt.pause(0.1)

def train(input_features, num_hidden, output, x, y,epochs):
    model, inputs, target = get_model_inputs_target(input_features, num_hidden, output, x, y)
    optimizer, criterion = get_optimizer_criterion(model)

    for epoch in range(epochs):
        output = model(x)
        loss = criterion(output, target)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if epoch % 40 == 0:
            draw(output, inputs, target)


if __name__ == '__main__':
    cluster = torch.ones(500, 2)
    data0 = torch.normal(4*cluster, 2)
    data1 = torch.normal(-4*cluster, 1)
    data2 = torch.normal(-8*cluster, 1)
    label0 = torch.zeros(500)
    label1 = torch.ones(500)
    label2 = label1*2

    x = torch.cat((data0, data1, data2)).type(torch.FloatTensor)
    y = torch.cat((label0, label2, label2)).type(torch.LongTensor)
    
    train(2, 20, 3, x, y, 10000)
