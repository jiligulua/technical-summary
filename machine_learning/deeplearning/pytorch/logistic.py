import torch
from torch import nn, optim
import matplotlib.pyplot as plt


class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.linear = nn.Linear(2, 2)

    def forward(self, x):
        x = self.linear(x)
        x = torch.sigmoid(x)
        return x

class Logistic:
    def build(self, num_samples, epochs):
        self.data_set(num_samples)
        #self.draw_raw_datas()
        self.format_source()
        self.train(epochs)


    def format_source(self):
        self.CUDA = torch.cuda.is_available()
        if self.CUDA:
            self.net = Net().cuda()
            self.inputs = self.x.cuda()
            self.targets = self.y.targets()
        else:
            self.net = Net()
            self.inputs = self.x
            self.targets = self.y
    

    def data_set(self, num_samples):
        self.num_samples = num_samples*2
        cluster = torch.ones(num_samples,2)
        data0 = torch.normal(4*cluster, 2)
        data1 = torch.normal(-4*cluster, 2)
        label0 = torch.zeros(num_samples)
        label1 = torch.ones(num_samples)
        
        self.x = torch.cat((data0, data1)).type(torch.FloatTensor)
        self.y = torch.cat((label0, label1)).type(torch.LongTensor)
    

    def draw_raw_datas(self):
        plt.scatter(self.x.numpy()[:,0], self.x.numpy()[:,1], c=self.y.numpy(), s=10, lw=0, cmap='rainbow_r')
        plt.show()
    
    
    def draw_result(self, output):
        if self.CUDA:
            output = output.cuda()
        plt.cla()
        output = torch.max((output), 1)[1]
        pred_y = output.data.numpy().squeeze()
        target_y = self.y.numpy()
        plt.scatter(self.x.numpy()[:,0], self.x.numpy()[:,1], c=pred_y, s=10, lw=0,cmap='RdYlGn')
        accuracy = sum(pred_y == target_y) / self.num_samples
        plt.text(1.5,4, 'Accuracy=%s' % (accuracy), fontdict={'size': 20, 'color': 'red'})
        plt.show()
        plt.pause(0.01)


    def train(self, epochs):
        print('train\n') 
        self.select_optim_criterion()
        for epoch in range(epochs):
            output = self.net(self.inputs)
            loss = self.criterion(output, self.targets)
            self.optimizer.zero_grad()
            loss.backward()
            self.optimizer.step()

            if epoch % 40 == 0:
                self.draw_result(output)
        

    def select_optim_criterion(self):
        self.optimizer = optim.SGD(self.net.parameters(), lr=0.02) 
        self.criterion = nn.CrossEntropyLoss()
    
if __name__ == '__main__':
    logis = Logistic()
    print("Test Python")
    logis.build(100, 1000)
