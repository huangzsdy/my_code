#coding:utf-8
import os
import sys
import numpy as np
import logging
logging.getLogger().setLevel(logging.DEBUG)

mxnet_path = '/home/huangzesang/share/mxnet'
sys.path.insert(0,mxnet_path +  '/python')

import mxnet as mx

def get_symbol():
	x = mx.sym.Variable('data')
	y = mx.symbol.Variable('lin_reg_label')
	fully_connected_layer = mx.sym.FullyConnected(data=x,name='fc1',num_hidden=1)
	lro = mx.sym.LinearRegressionOutput(data=fully_connected_layer,label=y,name='lro')

	return lro

train_data = np.random.uniform(0,1,[100,2])
train_label = np.array([train_data[i][0] + 2 * train_data[i][1]  for i in xrange(100)])
batch_size = 1

eval_data = np.array([[7,2],[6,10],[12,2]])
eval_label = np.array([11,26,16])

train_iter = mx.io.NDArrayIter(train_data,train_label,batch_size,shuffle=True,label_name='lin_reg_label')
eval_iter = mx.io.NDArrayIter(eval_data,eval_label,batch_size,shuffle=False)



model = mx.mod.Module(symbol = get_symbol(),data_names=['data'],label_names=['lin_reg_label'])
model.fit(train_iter,eval_iter,
	optimizer_params={'learning_rate':0.0005,'momentum':0.9},
	num_epoch=50,
	eval_metric='mse',
	batch_end_callback=mx.callback.Speedometer(batch_size,10)) # logs per 10 batch_size

predictions = model.predict(eval_iter).asnumpy()
print 'predictions:',predictions.tolist()

