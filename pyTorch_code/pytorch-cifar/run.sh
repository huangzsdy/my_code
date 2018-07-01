set -x
source /home/huangzesang/share/env_my.sh

#CUDA_VISIBLE_DEVICES=1
GPUS=0,1
LR=1
RESUME_POINT=../checkpoints/ckpt.t7_4
CHECKPOINTS_PATH=../checkpoints
# CHECKPOINTS_PATH=/home/huangzesang/share/learning/my_code/pyTorch_code/checkpoints
TRAIN_BATCH_SIZE=128
TEST_BATCH_SIZE=100
LOG_INTERVAL=10

python -u  main3.py\
 --gpus ${GPUS} \
 --lr ${LR} \
 --checkpoint_path ${CHECKPOINTS_PATH}\
 --train_batch_size ${TRAIN_BATCH_SIZE} \
 --test_batch_size ${TEST_BATCH_SIZE} \
 --log_interval ${LOG_INTERVAL}
 # --resume_point $RESUME_POINT\

