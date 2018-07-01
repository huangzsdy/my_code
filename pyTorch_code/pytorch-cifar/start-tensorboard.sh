set -x
source ~/share/env_my.sh
#python -u  ~/share/my_env/anaconda2/lib/python2.7/site-packages/tensorflow/tensorboard/tensorboard.py \
nohup tensorboard \
      --logdir=../logs\
      --host=0.0.0.0 >/dev/null &
