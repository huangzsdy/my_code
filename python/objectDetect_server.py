#!/usr/bin/env python
# --------------------------------------------------
# @brief: socket, "input_json_path#output_json_path"
# Wirtten by hukun 2015.08.19
# --------------------------------------------------
import numpy as np
import time
import os
import json
import sys
import socket
import logging
import cv2
import caffe

caffe.set_mode_cpu()

MODEL_DEF = "./model/ero/ero_2114_deploy.prototxt"
MODEL_PATH = "./model/ero/ero_2114.caffemodel"
MEAN_FILE = "./model/ero/ero_mean.npy"

PORN_IDXES = [1484, 1984, 2036, 2110]
CARTOON_IDXES = [2112]
ID_CARD_IDXES = [2113]
MASK_IDXES = [643, 1971]

socketPort = int(sys.argv[1])

logger = logging.getLogger('logger')
logger.setLevel(logging.DEBUG)
fh = logging.FileHandler('./log/porn-rec-2114-{}.log'.format(socketPort))
fh.setLevel(logging.INFO)
ch = logging.StreamHandler()
ch.setLevel(logging.INFO)
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
fh.setFormatter(formatter)
ch.setFormatter(formatter)
logger.addHandler(fh)
logger.addHandler(ch)

porn_lines = open("./model/ero/4_classes.txt", 'r').readlines()
porn_chs_description = []
porn_eng_description = []
for line in porn_lines:
  line = line.strip().split('#')
  porn_eng_description.append(line[0])
  porn_chs_description.append(line[1])

obj_lines = open("./model/ero/2114_classes.txt", "r").readlines()
obj_chs_description = []
obj_eng_description = []
for line in obj_lines:
  line = line.strip().split('#')
  obj_eng_description.append(line[0])
  obj_chs_description.append(line[1])

mean = np.load(MEAN_FILE).mean(1).mean(1)
mean = mean[:, np.newaxis, np.newaxis]
net = caffe.Net(MODEL_DEF, MODEL_PATH, caffe.TEST)
RESIZE_SQUARE = 224

def predict(image_list):
  inputs = []
  for image_path in image_list:
    if not os.path.exists(image_path):
      raise Exception("Image path not exist")
      return
    try:
      print image_path
      tmp_input = cv2.imread(image_path)
    except Exception as e:
      raise Exception("Image damaged or illegal format")
      return
    try:
      tmp_input = cv2.resize(tmp_input,(RESIZE_SQUARE, RESIZE_SQUARE)).astype(np.float32)
      tmp_input = tmp_input.transpose((2, 0, 1))
      # tmp_input = tmp_input * 255.
      # tmp_input = tmp_input[(2, 1, 0), :, :]
      tmp_input -= mean
      tmp_input = np.require(tmp_input, dtype=np.float32)
      inputs.append(tmp_input)
    except Exception as e:
      raise Exception("Image damaged or illegal format")
      return
  if len(inputs) > 0:
    inputs = np.require(inputs, dtype=np.float32)
    net.blobs['data'].reshape(inputs.shape[0], inputs.shape[1], inputs.shape[2], inputs.shape[3])
    net.blobs['data'].data[...] = inputs
    net.forward(end="prob")
    scores = net.blobs["prob"].data
    return scores
  else:
    return
# added 2016.03.25, output 4 classes, porn, cartoon, id_card, mask
def porn_construct_json_v4(predictions):
  num = predictions.shape[0]
  ress_json = []
  for i in range(num):
    pre = predictions[i]
    obj_indexes = np.argsort(-pre)[0:50]
    indexes = obj_indexes[0:5]
    res_json = {}
    # obj
    obj_dic = []
    for idx in obj_indexes:
      tmp_dic = {}
      tmp_dic["id"] = str(idx)
      tmp_dic["probability"] = str(float(round(pre[idx], 4)))
      tmp_dic["description"] = obj_chs_description[idx]
      tmp_dic["description_en"] = obj_eng_description[idx]
      obj_dic.append(tmp_dic)
    # porn
    # return porn, suspect, normal
    # porn_top_k = 3
    # porn_index = indexes[0]
    # porn_id = 2
    # for j, idx in enumerate(indexes):
    #   if idx in PORN_IDXES:
    #     if j < porn_top_k:
    #       porn_id = 0
    #       porn_index = idx
    #       break
    #     else:
    #       porn_id = 1
    #       porn_index = idx
    #       break
    # porn_dic["id"] = str(porn_id)
    # porn_dic["description"] = porn_chs_description[3 * 0 + porn_id]
    # porn_dic["description_en"] = porn_eng_description[3 * 0 + porn_id]
    # if porn_id == 0:
    #   # porn
    #   porn_dic["probability"] = float(round(pre[porn_index], 5))
    # elif porn_id == 1:
    #   # suspected porn
    #   porn_dic["probability"] = float(round(pre[porn_index] + 0.5, 5))
    # else:
    #   # not porn, normal
    #   porn_dic["probability"] = float(round(np.sum(pre[indexes]), 5))

    # return porn, suspect, sexy, normal
    porn_dic = {}
    sexy_num = 0
    porn_sig = 0
    porn_index = 0
    for i, idx in enumerate(indexes):
      if i < 3:
        if 'sexy' in obj_eng_description[idx]:
          sexy_num += 1
        if 'porn' in obj_eng_description[idx]:
          porn_sig = 1
          porn_index = idx
      else:
        if 'sexy' in obj_eng_description[idx]:
          sexy_num += 1
        if 'porn' in obj_eng_description[idx]:
          porn_sig = 2
          porn_index = idx
    if porn_sig == 1: #porn
      porn_dic['id'] = str(0)
      porn_dic['probability'] = float(round(pre[porn_index], 5))
      porn_dic['description'] = porn_chs_description[0]
      porn_dic['description_en'] = porn_eng_description[0]
    elif porn_sig == 2: # suspect
      porn_dic['id'] = str(1)
      porn_dic['probability'] = float(round(pre[porn_index] + 0.5, 5))
      porn_dic['description'] = porn_chs_description[1]
      porn_dic['description_en'] = porn_eng_description[1]
    else:
      if sexy_num >= 3: # sexy
        porn_dic['id'] = str(2)
        porn_dic['probability'] = float(round(np.sum(pre[indexes]), 5))
        porn_dic['description'] = porn_chs_description[2]
        porn_dic['description_en'] = porn_eng_description[2]
      else: # normal
        porn_dic['id'] = str(3)
        porn_dic['probability'] = float(round(np.sum(pre[indexes]), 5))
        porn_dic['description'] = porn_chs_description[3]
        porn_dic['description_en'] = porn_eng_description[3]
    # cartoon
    cartoon_dic = {}
    cartoon_score = 0.
    for idx in CARTOON_IDXES:
      cartoon_score += pre[idx]
    if cartoon_score > 0.5:
      cartoon_id = 0
      cartoon_dic["probability"] = float(round(cartoon_score, 5))
    elif cartoon_score > 0.1:
      cartoon_id = 1
      cartoon_dic["probability"] = float(round((cartoon_score-0.1) / 0.4, 5))
    else:
      cartoon_id = 2
      cartoon_dic["probability"] = float(round(1 - cartoon_score, 5))
    cartoon_dic["id"] = str(cartoon_id)
    cartoon_dic["description"] = porn_chs_description[4 + cartoon_id]
    cartoon_dic["description_en"] = porn_eng_description[4 + cartoon_id]
    # id_card
    id_card_dic = {}
    id_card_score = 0.
    for idx in ID_CARD_IDXES:
      id_card_score += pre[idx]
    if id_card_score > 0.5:
      id_card_id = 0
      id_card_dic["probability"] = float(round(id_card_score, 5))
    elif id_card_score > 0.1:
      id_card_id = 1
      id_card_dic["probability"] = float(round((id_card_score-0.1) / 0.4, 5))
    else:
      id_card_id = 2
      id_card_dic["probability"] = float(round(1 - id_card_score, 5))
    id_card_dic["id"] = str(id_card_id)
    id_card_dic["description"] = porn_chs_description[7+ id_card_id]
    id_card_dic["description_en"] = porn_eng_description[7 + id_card_id]
    # mask
    mask_dic = {}
    mask_score = 0.
    for idx in MASK_IDXES:
      mask_score += pre[idx]
    if mask_score > 0.5:
      mask_id = 0
      mask_dic["probability"] = float(round(mask_score, 5))
    elif mask_score > 0.1:
      mask_id = 1
      mask_dic["probability"] = float(round((mask_score-0.1) / 0.4, 5))
    else:
      mask_id = 2
      mask_dic["probability"] = float(round(1 - mask_score, 5))
    mask_dic["id"] = str(mask_id)
    mask_dic["description"] = porn_chs_description[10 + mask_id]
    mask_dic["description_en"] = porn_eng_description[10 + mask_id]
    # construct json
    res_json["object"] = obj_dic
    res_json["porn"] = porn_dic
    res_json["cartoon"] = cartoon_dic
    res_json["id_card"] = id_card_dic
    res_json["mask"] = mask_dic
    ress_json.append(res_json)
  return ress_json

def write_err_info(output_file, err_info):
  info_dic = {}
  info_dic['msg'] = err_info
  info_dic_str = json.dumps(info_dic, separators = (',', ':'))
  f = open(output_file, 'w')
  f.write(info_dic_str)
  f.close()

if __name__=="__main__":
  start_time = time.time()
  end_time = time.time()
  load_model_time = end_time - start_time
  logger.info('Loading model time: ' + str(load_model_time) + 's')

  sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
  sock.bind(('0.0.0.0', socketPort))
  sock.listen(1)
  logger.info("Start listening on " + str(socketPort))
  while True:
    connection, address = sock.accept()
    logger.info("port {} accept ip {}".format(socketPort, str(address)))
    try:
      connection.settimeout(20)
      buf = connection.recv(1024*1024)
      buf_string_arr = buf.split('#')
      if len(buf_string_arr) != 2:
        logger.error("[Wrong Input Syntax]: " + buf)
        connection.send('ERROR : Wrong Input Syntax')
        connection.close()
        continue
      logger.info('Start calculating...')
      input_file_path = buf_string_arr[0]
      output_file_path = buf_string_arr[1]
      input_file = open(input_file_path)
      input_file_arr = json.load(input_file)
      input_file.close()
      result_arr = {}
      if len(input_file_arr) == 0:
        logger.error("[No Input Images]: " + str(input_file_arr))
        write_err_info(output_file_path, "No input images")
        connection.send('ERROR: No Input Images')
        connection.close()
        continue

      start_time = time.time()
      logger.debug("input_file_arr: " + str(input_file_arr))
      try:
        predictions = predict(input_file_arr)
      except Exception as e:
        logger.error(str(e))
        write_err_info(output_file_path, str(e))
        connection.send('ERROR: ' + str(e))
        connection.close()
        continue
      end_time = time.time()
      logger.info("Predictions time: " + str(end_time-start_time) + 's')
      logger.debug("Predictions result: " + str(predictions))

      if predictions.shape[0] != len(input_file_arr):
        write_err_info(output_file_path, "Error happened in predictions")
        connection.send('ERROR: error happened in predictions')
        connection.close()
        logger.error("Error happened in predictions")
        continue

      result_arr = porn_construct_json_v4(predictions)
      output_json_str = json.dumps(result_arr, separators = (',', ':'))
      output_file = open(output_file_path, 'w')
      output_file.write(output_json_str)
      output_file.close()

      connection.send('Success')
      logger.info('Caculation finished')
    except Exception as e:
      write_err_info(output_file_path, str(e))
      try:
        connection.send('ERROR: ' + str(e))
      except:
        pass
      logger.error(str(e))
    finally:
      connection.close()

