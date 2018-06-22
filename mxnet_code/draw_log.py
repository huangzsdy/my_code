#coding:utf8

import sys
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as pl
import math

log_file = open(sys.argv[1])
batch_size = 500
# batch_size = 705414 / batch_size
epoch_size = 758367 / batch_size

if 'xiong' in sys.argv[1] and 'multi' not in sys.argv[1]:
    xiongmetric = True
else:
    xiongmetric = False

train_epochs = []
train_errs = []
train_top5_epochs = []
train_top5_errs = []
val_epochs = [0]
val_errs = [0.]
val_top5_epochs = [0.]
val_top5_errs = [0.]
lasterr = 0.
for l in log_file:
    if 'Train-accuracy' in l or 'Validation' in l or 'Train-top_k_accuracy' in l or 'Train-multi-accuracy_1' in l:
        sp = l.strip().split()
        epoch = int(sp[3][sp[3].find('[') + 1 : sp[3].find(']')])
        if 'Train-accuracy' in l or 'Train-multi-accuracy_1' in l:
            try:
                batch = int(sp[5][sp[5].find('[') + 1 : sp[5].find(']')])
            except:
                continue
            train_epochs.append(epoch + batch / float(epoch_size))
            thiserr = float(sp[-1].split('=')[-1])
            if xiongmetric:
                correcterr = thiserr if batch == 50 else (thiserr * batch - lasterr * (batch - 50)) / 50
            else:
                correcterr = thiserr
            train_errs.append(correcterr)
            lasterr = thiserr
        elif 'Train-top_k_accuracy' in l:
            batch = int(sp[5][sp[5].find('[') + 1 : sp[5].find(']')])
            train_top5_epochs.append(epoch + batch / float(epoch_size))
            train_top5_errs.append(float(sp[-1].split('=')[-1]))
        elif 'Validation-accuracy' in l:
            batch = (epoch + 1)
            val_epochs.append(batch)
            val_errs.append(float(l.strip().split('=')[-1]))
        elif 'Validation-top_k_accuracy' in l:
            batch = (epoch + 1)
            val_top5_epochs.append(batch)
            val_top5_errs.append(float(l.strip().split('=')[-1]))

# epochs = epochs[::step]
# train_errs = train_errs[::step]
# val_errs = val_errs[::step]
pl.plot(train_epochs, train_errs, 'g')
pl.plot(train_top5_epochs, train_top5_errs, 'b')
pl.plot(val_epochs, val_errs, 'r')
pl.plot(val_top5_epochs, val_top5_errs, 'black')
# pl.ylim(0.5, 0.7)
pl.savefig('err.jpg')
