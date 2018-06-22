from sklearn.metrics import roc_curve
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import cPickle as cp
import sys

def load_result(result_file):
	result = open(result_file)
	label = []
	prob = []
	for line in result:
		line = line.strip().split(' ')
		label.append(int(line[0]))
		prob.append(float(line[1]))
	return label,prob

colors = ['red','blue','green','black','orange','yellow']
num = len(sys.argv) 
results = []
pic_name = sys.argv[1]
if num < 1:
	print "No input!"
	print "usage: python cal_roc_t.py  pic_name result_1 result_2 ..."
	exit()

for i in range(2,num):
	
	result_file = sys.argv[i]
	label,prob = load_result(result_file)
	label = np.array(label)
	prob = np.array(prob)
	print label
	fpr, tpr, thresholds = roc_curve(label, prob, pos_label=1)
	for j in range(len(fpr)):
		print fpr[j], tpr[j], thresholds[j]
	#print thresholds
	#print fpr.shape
# plt.figure()
	plt.plot(fpr, tpr, label="msu", color = colors[i - 2])


plt.plot([0, 1], [1, 0], 'k-')
plt.xlim([0.0, 0.2])
plt.ylim([0.8, 1.0])
plt.xticks(np.arange(0.0, 0.2, 0.01))
plt.yticks(np.arange(0.8, 1.0, 0.01))
plt.xlabel('False Positive Rate')
plt.ylabel('True Positive Rate')
plt.title('ROC')
plt.grid('on')
plt.legend(loc="lower right")
plt.savefig(pic_name)
