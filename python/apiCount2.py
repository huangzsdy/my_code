#coding:utf-8
from datetime import datetime
from elasticsearch import Elasticsearch
from pymongo import *
import json,os,xlwt
import commands
from bson.objectid import ObjectId

esUrl = 'http://10.28.205.16:9988'

es = Elasticsearch(esUrl,timeout=120)

mongodbUrl = "mongodb://faceall:DeepLearning@dds-2ze0ece465dbc6841.mongodb.rds.aliyuncs.com:3717,dds-2ze0ece465dbc6842.mongodb.rds.aliyuncs.com:3717/prod-api?replicaSet=mgset-2923433"
index = 'prod-api-*'
threshold1 = datetime(2017,8,1,0,0,0)
threshold2 = datetime(2017,9,1,0,0,0)

# key = 'KveY2D7gV1QjI0Z6f0Ag2br2ngWACppt1xlvAb4X'
# method = '/v2/detection/detect'

def getApiName():
    apiNames = []
    path = '/home/faceall/apiFramework/source/public/v2'
    cmd = 'find ' + path + ' -type f -name "*.js"'
    result = commands.getoutput(cmd).split('\n')
    for name in result:
        if 'api_call_counts' not in name and 'util' not in name and 'http' not in name and '/v2/faceset/add_faces' not in name and '/v2/detection/attributes' not in name:
            apiNames.append(name[name.find('/v2'):].split('.')[0])

    apiNames.append('/v2/faceset/add_face')
    apiNames.append('/v2/detection/attribute')
    return apiNames


def query(key,method):
    data = {
        'query':{
            'bool':{
                "must":[
                    {'match':{'api_key':{'query':key,'operator':'and'}}},{'match':{'api_method':{'query':method,'operator':'and'}}}
                ],
                "filter":[
                    {
                        "range":{
                            "@timestamp":{
                                # "from":"now-7d",
                                # "to":"now"
                                "gt":threshold1,
                                "lte":threshold2
                            }
                        }
                    }
                ]
            }
        }   
    }
    res = es.search(index=index,body=data)
    # print key,method,res['hits']['total']
    return res['hits']['total']

def writeToExcel(records,apiNames):
    wb = xlwt.Workbook()
    ws = wb.add_sheet("api")
    ws.write(0,0,'api_key')
    ws.write(0,1,'name')
    ws.write(0,2,'description')
    ws.write(0,3,'total')
    for i in xrange(len(apiNames)):
        ws.write(0,4 + i,apiNames[i])
    for i in xrange(len(records.keys())):
        key = records.keys()[i]
        res = records[key]
        row = i + 1

        api_key = key.split('_')[0]
        name = key.split('_')[1]
        description = key.split('_')[2]
        ws.write(row,0,api_key)
        ws.write(row,1,name)
        ws.write(row,2,description)
        total = 0
        for k in xrange(len(apiNames)):
            api = apiNames[k]
            if api in res:
                ws.write(row,4 + k,res[api])
                total = total + res[api]
            else:
                ws.write(row,4 + k,0)
        ws.write(row,3,total)
    wb.save('test.xls')

def main():
    allResult = {}
    mongoClient = MongoClient(mongodbUrl)['prod-api']
    cmd = {'_id':0,'key':1,'name':1,'description':1}
    keysCollections = mongoClient.apis.find({},cmd)
    apiMethods = getApiName()
    for one in list(keysCollections):
        print 'api_key:',one['key'],'name:',one['name'],'description:',one['description']
        tmpName = '_'.join([one['key'],one['name'],one['description']])
        allResult[tmpName] = {}
        for method in apiMethods:
            count = query(one['key'],method)
            if count == 0:
                continue 
            allResult[tmpName][method] = count
        if len(allResult[tmpName].keys()) == 0:
            del allResult[tmpName]

    writeToExcel(allResult,apiMethods)

    for key,counts in allResult.items():
        if len(counts.keys()) > 0:
            print key
            for one in counts:
                print one,counts[one]

if __name__ == '__main__':
    main()

