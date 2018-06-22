#coding:utf-8
from pymongo import *
import json,os
from bson.objectid import ObjectId
import requests
import time
import datetime


def requester(method,params):
    params['api_key'] = 'omhb0QSUL6Cj7XtprIO0UGIxy5WUnHgu7j3ABrtY'
    params['api_secret'] = '4aGQhwR6iGbabxhFHBjXKYOfIsFRtcd7OqzeB5RK'
    url = 'http://127.0.0.1:9995/v2/'
    result = requests.post(url + method,params,timeout=3000000000)
    return result.json()
    
    

mongodbUrl = "mongodb://faceall:DeepLearning@dds-2ze0ece465dbc6841.mongodb.rds.aliyuncs.com:3717,dds-2ze0ece465dbc6842.mongodb.rds.aliyuncs.com:3717/wenwangyilian?replicaSet=mgset-2923433"




def check():
  tmp = 0
  folder = '/local/data/apiFramework/forapi/feature/'
  features = set()
  for i in faceset_collections:
      if tmp == 10000:
         pass
      if i['detectionResult'].has_key('feature'):
          feature_path = folder + i['detectionResult']['feature'].split('/')[-1]
          if not feature_path in features:
                 features.add(feature_path)
          else:
             print feature_path,i['id']
             tmp+=1
    
  print 'tmp:',tmp,'count',len(features) 

def get():
  for o in face_collections:
    # print type(o['meta']['createAt'])
    if  o['meta']['createAt'] >= threshold_1 and o['meta']['createAt'] <= threshold_2:
      if  o['detectionResult'].has_key('feature'):
          feature = o['detectionResult']['feature']
          img = o['detectionResult']['detection']['path']
          if not feature.startswith('/local/data/apiFramework/forapi/feature'):
              tmp_feature = '/local/data/apiFramework/forapi/feature/' +feature.split('/')[-1]
              tmp_path = '/local/data/apiFramework/forapi/upload/' + img.split('/')[-1]
              if os.path.exists(tmp_feature):
                # feature_res = requester('detection/feature',{'face_id':feature.split('/')[-1]})
                print feature,img
          else:
            if os.path.exists(feature):
              print feature,img

def update(record):
    if  record['detectionResult'].has_key('feature'):
        feature = record['detectionResult']['feature']
        img = record['detectionResult']['detection']['path']
        if not feature.startswith('/local/data/apiFramework/forapi/feature') :#or  img.startswith('home/faceall'):
            print '========='
            
            tmp_feature = '/local/data/apiFramework/forapi/feature/' +feature.split('/')[-1]
            tmp_path = '/local/data/apiFramework/forapi/upload/' + img.split('/')[-1]
            if  os.path.exists(tmp_path) :
                print feature,img
                record['detectionResult']['detection']['path'] = tmp_path           
                cmd_1 = {'$set':{'detectionResult':record['detectionResult']}}
                client.wenwangyilian.faces.update({'id':record['id']},cmd_1)
                exit()

            if os.path.exists(tmp_feature):
                print feature,img
                record['detectionResult']['feature'] = tmp_feature 
                cmd_2 = {'$set':{'detectionResult':record['detectionResult']}}
                client.wenwangyilian.faces.update({'id':record['id']},cmd_2)

if __name__ == '__main__':
  client = MongoClient(mongodbUrl)
  cmd = {'_api':ObjectId("58af96529074926329cdf0f4")}

  threshold_1 = datetime.datetime(2017,4,18)#时间戳20170418
  threshold_2 = datetime.datetime(2017,4,20)
  face_collections = client.wenwangyilian.faces.find({'_api':ObjectId("58af96529074926329cdf0f4"),'meta.createAt':{'$gte':threshold_1,'$lt':threshold_2}})

  get()
  

