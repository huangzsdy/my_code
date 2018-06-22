import os.path as osp
import matplotlib.pyplot as plt
import matplotlib.image  as mpimg
import numpy as np

cls_map = {o.strip().split()[1]:o.strip().split()[-1] for o in open('/home/safe_data_dir/imagenet2017/ILSVRC/devkit/data/map_clsloc.txt')}
image_folder = '/home/safe_data_dir/imagenet2017/ILSVRC/Data/CLS-LOC/val'
images = [osp.join(image_folder,o.strip().split()[0]) for o in open('/home/safe_data_dir/imagenet2017/ILSVRC/ImageSets/CLS-LOC/val.txt')]

plt.rcParams['figure.figsize'] = (10, 10) 
plt.rcParams['image.interpolation'] = 'nearest'
plt.rcParams['image.cmap'] = 'gray'

rect_boxes = [o.strip() for o in open('/home/huangzesang/py-R-FCN-multiGPU/output/rfcn_end2end_ohem/val/evaluation/top1')]
colors = plt.cm.hsv(np.linspace(0,1,1001)).tolist()

def plot_rect(img,coords):
	image = mpimg.imread(img)
	
	plt.cla()
	currentAxis = plt.gca()
	color = colors[int(label)]
	label_name = cls_map[label]
	currentAxis.add_patch(plt.Rectangle(*coords, fill=False, edgecolor=color, linewidth=2))
	currentAxis.text(xmin,ymin,label_name,bbox={'alpha':0.5})
	new_img = 'saved_imgs/' +'new_' +img.split('/')[-1]

	plt.imshow(image)
	plt.savefig(new_img)
	print new_img

for i,line in enumerate(rect_boxes):
	img = images[i] + '.JPEG'
	label = line.split()[0]
	xmin = float(line.split()[1])
	ymin = float(line.split()[2])
	xmax = float(line.split()[3])
	ymax = float(line.split()[4])
	coords = (xmin, ymin), xmax-xmin, ymax-ymin
	plot_rect(img,coords)







