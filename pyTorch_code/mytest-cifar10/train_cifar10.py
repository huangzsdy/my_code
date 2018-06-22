#coding:utf-8
import torch
import torchvision
import torchvision.transforms as transforms

from torch.autograd import Variable
import torch.nn as nn
import torch.nn.functional as F

from myDataset import myImageFolder
import torch.optim as optim
import numpy as np
import os
# os.environ["CUDA_VISIBLE_DEVICES"] = "1"
torch.cuda.set_device(1)

# CIFAR10_FOLDER = '/home/safe_data_dir/CIFAR_image/CIFAR10/png/'
CIFAR10_FOLDER = '/home/huangzesang/CIFAR10/png/'
train_batch_size = 50
test_batch_size = 10

classes = ('plane', 'car', 'bird', 'cat',
           'deer', 'dog', 'frog', 'horse', 'ship', 'truck')

# transform = transforms.Compose(
# 	[transforms.ToTensor(),transforms.Normalize((0.5,0.5,0.5),(0.5,0.5,0.5))])
transform = transforms.Compose([
    transforms.RandomCrop(32, padding=4),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(),
    transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010)),
])

# trainset = torchvision.datasets.CIFAR10(root=CIFAR10_FOLDER,train=True,
# 										download=True,transform=transform)
trainset = myImageFolder(root=CIFAR10_FOLDER + 'train',classes=classes,label=CIFAR10_FOLDER + '../train.list',transform=transform)
trainloader = torch.utils.data.DataLoader(trainset,batch_size=train_batch_size,
										shuffle=True,num_workers=10)

# testset = torchvision.datasets.CIFAR10(root=CIFAR10_FOLDER,train=False,
										# download=True,transform=transform)
testset = myImageFolder(root=CIFAR10_FOLDER + 'test',classes=classes,label=CIFAR10_FOLDER + '../test.list',transform=transform)
testloader = torch.utils.data.DataLoader(testset,batch_size=test_batch_size,
										shuffle=False,num_workers=10)



class Net(nn.Module):
	def __init__(self):
		super(Net,self).__init__()
		self.conv1 = nn.Conv2d(3,6,5)
		self.pool = nn.MaxPool2d(2,2)
		self.conv2 = nn.Conv2d(6,16,5)
		self.fc1 = nn.Linear(16*5*5,120)
		self.fc2 = nn.Linear(120,84)
		self.fc3 = nn.Linear(84,10)

	def forward(self,x):
		x = self.pool(F.relu(self.conv1(x)))
		x = self.pool(F.relu(self.conv2(x)))
		x = x.view(-1,16*5*5)
		x = F.relu(self.fc1(x))
		x = F.relu(self.fc2(x))
		x = self.fc3(x)
		
		return x



net = Net().cuda()
optimizer = optim.SGD(net.parameters(),lr=0.001,momentum=0.9)

def train(epoch):
	for k in xrange(epoch):
		running_loss = 0.0
		for i,data in enumerate(trainloader,0):
			inputs,labels = data
			#CrossEntropyLoss	的接口需要是long类型，不能是float
			labels = labels.view(-1).type(torch.LongTensor)

			inputs,labels = Variable(inputs.cuda()),Variable(labels.cuda())

			# zero the parameter gradients
			optimizer.zero_grad()
			# forward + backward + optimize
			outputs = net(inputs)

			criterion = nn.CrossEntropyLoss()
			loss = criterion(outputs,labels)
			# loss_function = nn.NLLLoss()
			# loss = loss_function(outputs,labels)
			loss.backward()
			optimizer.step()
			print '1'

			running_loss += loss.data[0]
			if i % 2 == 1:
				print '[%d,%5d loss: %.3f'%(epoch + 1,i + 1,running_loss/2000)
				running_loss = 0.0

train(1)
print 'Finished Training' 