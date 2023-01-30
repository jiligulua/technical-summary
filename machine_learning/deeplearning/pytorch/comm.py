import matplotlib.pyplot as plt
import torch

CUDA = torch.cuda.is_available()
def draw(output, loss):
    if CUDA:
        output = output.cpu()
    plt.cla()
    plt.scatter(x.numpy(), y.numpy())
    plt.plot(x.numpy(), output.data.numpy(), 'r-', lw=5)
    plt.text(0.5, 0, 'Loss=%s' % (loss.item()), fontdict={'size': 20, 'color': 'red'})
    plt.pause(0.005)
