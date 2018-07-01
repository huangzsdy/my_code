'''Train CIFAR10 with PyTorch.'''
from __future__ import print_function

import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
import torch.backends.cudnn as cudnn

import torchvision
import torchvision.transforms as transforms

import os
import argparse

from models import *
from utils import progress_bar
from torch.autograd import Variable

from myDataset import myImageFolder

from logger import Logger

parser = argparse.ArgumentParser(description='PyTorch CIFAR10 Training')
parser.add_argument('--lr', default=0.1, type=float, help='learning rate')
parser.add_argument('--gpus',default="1",help='gpu device_ids to use')
parser.add_argument('--checkpoint',default=None,help='checkpoint to resume')
parser.add_argument('--checkpoint_path',default=None,help='folder to save checkpoint')
# parser.add_argument('--train_batch_size',default=128,type=int,help='batch_size for training')
# parser.add_argument('--test_batch_size',default=100,type=int,help='batch_size for testing')

args = parser.parse_args()

use_cuda = torch.cuda.is_available()
best_acc = 0  # best test accuracy
start_epoch = 0  # start from epoch 0 or last checkpoint epoch
CIFAR10_FOLDER = '/home/huangzesang/CIFAR10/png/'
classes = ('plane', 'car', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck')

# Data
print('==> Preparing data..')
transform_train = transforms.Compose([
    transforms.RandomCrop(32, padding=4),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(),
    transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010)),
])

transform_test = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2010)),
])

trainset = myImageFolder(root=CIFAR10_FOLDER + 'train',classes=classes,label=CIFAR10_FOLDER + '../train.list',transform=transform_train)
trainloader = torch.utils.data.DataLoader(trainset, batch_size=128, shuffle=True, num_workers=2)

testset = myImageFolder(root=CIFAR10_FOLDER + 'test',classes=classes,label=CIFAR10_FOLDER + '../test.list',transform=transform_test)
testloader = torch.utils.data.DataLoader(testset, batch_size=100, shuffle=False, num_workers=2)

# trainset = myImageFolder(root=CIFAR10_FOLDER + 'train',classes=classes,label=CIFAR10_FOLDER + '../train.list',transform=transform_train)
# trainloader = torch.utils.data.DataLoader(trainset, batch_size=128, shuffle=True, num_workers=2)

# testset = myImageFolder(root=CIFAR10_FOLDER + 'test',classes=classes,label=CIFAR10_FOLDER + '../test.list',transform=transform_test)
# testloader = torch.utils.data.DataLoader(testset, batch_size=100, shuffle=False, num_workers=2)

# Model
if args.checkpoint != None:
    # Load checkpoint.
    print('==> Resuming from checkpoint:{} ..'.format(args.checkpoint))
    assert os.path.isfile(args.checkpoint), 'Error: no checkpoint directory found!'
    checkpoint = torch.load(args.checkpoint)
    net = checkpoint['net']
    best_acc = checkpoint['acc']
    start_epoch = checkpoint['epoch']

else:
    print('==> Building model..')
    # net = VGG('VGG19')
    # net = ResNet18()
    net = PreActResNet18()
    # net = GoogLeNet()
    # net = DenseNet121()
    # net = ResNeXt29_2x64d()
    # net = MobileNet()
    # net = DPN92()
    # net = ShuffleNetG2()
    # net = SENet18()
    # net = LeNet()

if not os.path.isdir(args.checkpoint_path):
    print("create folder to store checkpoint:%s"%args.checkpoint_path)
    os.mkdir(args.checkpoint_path)

gpus = [int(i) for i in args.gpus.split(',')]
if use_cuda:
    net.cuda()
    net = torch.nn.DataParallel(net, device_ids=range(2))
    cudnn.benchmark = True

# Loss and Optimizer
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(net.parameters(), lr=args.lr, momentum=0.9, weight_decay=5e-4)


def train(epoch):
    print('\nEpoch: %d' % epoch)
    net.train()
    train_loss = 0
    correct = 0
    total = 0
    for batch_idx, (inputs, targets) in enumerate(trainloader):
        if use_cuda:
            inputs, targets = inputs.cuda(), targets.view(-1).type(torch.LongTensor).cuda()
        optimizer.zero_grad()
        inputs, targets = Variable(inputs), Variable(targets)
        outputs = net(inputs)
        loss = criterion(outputs, targets)
        loss.backward()
        optimizer.step()

        train_loss += loss.data[0]
        _, predicted = torch.max(outputs.data, 1)
        total += targets.size(0)
        correct += predicted.eq(targets.data).cpu().sum()

        progress_bar(batch_idx, len(trainloader), 'Loss: %.3f | Acc: %.3f%% (%d/%d)'
            % (train_loss/(batch_idx+1), 100.*correct/total, correct, total))

# Testing
def test(epoch):
    global best_acc
    net.eval()
    test_loss = 0
    correct = 0
    total = 0
    for batch_idx, (inputs, targets) in enumerate(testloader):
        if use_cuda:
            inputs, targets = inputs.cuda(), targets.view(-1).type(torch.LongTensor).cuda()
        inputs, targets = Variable(inputs, volatile=True), Variable(targets)
        outputs = net(inputs)
        loss = criterion(outputs, targets)

        test_loss += loss.data[0]
        _, predicted = torch.max(outputs.data, 1)
        total += targets.size(0)
        correct += predicted.eq(targets.data).cpu().sum()

        progress_bar(batch_idx, len(testloader), 'Loss: %.3f | Acc: %.3f%% (%d/%d)'
            % (test_loss/(batch_idx+1), 100.*correct/total, correct, total))

    # Save checkpoint.
    acc = 100.*correct/total
    if acc > best_acc:
        print('Saving..')
        state = {
            'net': net.module if use_cuda else net,
            'acc': acc,
            'epoch': epoch,
        }
        torch.save(state, args.checkpoint_path + '/ckpt.t7_%d'%(epoch))
        best_acc = acc

for epoch in range(start_epoch, start_epoch+200):
    train(epoch)
    test(epoch)
exit()
# def logWithInfo(net,info,step):
#     for tag, value in info.items():
#         logger.scalar_summary(tag, value,step + 1)
#     # (2) Log values and gradients of the parameters (histogram)
#     for tag, value in net.named_parameters():
#         tag = tag.replace('.', '/')
#         logger.histo_summary(tag, (value).data.cpu().numpy(), step + 1)
#         logger.histo_summary(tag+'/grad', (value.grad).data.cpu().numpy(), step + 1)


