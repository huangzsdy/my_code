#coding:utf-8

from methods.utils.requester import request
import os,time,requests,threading
from multiprocessing.dummy import Pool as ThreadPool
url = 'http://127.0.0.1:10001/v2/'
imgs = [ 'images/'+i for  i in os.listdir('images')]
faceids = ['FMz7ftrCuIlJDyQEo253YsNYxhxwdAesz710IuvC']

def send(img):
        st = time.time()
        files = { 'img_file':open(img,'rb')}
        det_res = request('post',url + 'detection/detect',{},files)
        faces = det_res['faces']
        faceids ,fea_res = [],[]
        for j in xrange(len(faces[:1])):
            faceids.append(faces[j]['id'])
            fea_res.append(request('get',url + 'recognition/compare_face_faceset',params={'face_id':faces[j]['id'],'faceset_id':'YI0p6fLFI3UzT1eXZ0E0NiV7cDsKLrcYfMf4i3B9'})['final_time'])
        print time.time() - st,det_res['final_time'],fea_res
        return fea_res

def detect(img):
    st = time.time()
    files = {'img_file':open(img,'r')}
    det_res = request('post',url + 'detection/detect',{},files)
    print 'detect time: ',time.time() - st
    return det_res

def feature(faceid):
    st = time.time()
    params = {'face_id':faceid}
    fea_res = request('get', url + 'detection/feature',params)
    print 'feauture time:',time.time() - st
    return fea_res

def compare(faceid):
    st = time.time()
    compare_res = request('get',url + 'recognition/compare_face_faceset',params={'face_id':faceid,'faceset_id':'YI0p6fLFI3UzT1eXZ0E0NiV7cDsKLrcYfMf4i3B9'})
    print '1:N  time:',time.time() - st
    return compare_res

def pool_map(method,arr):
    length = len(arr)
    pool = ThreadPool(1)
    results = pool.map(method,arr)
    pool.close()
    pool.join()
    return results

if __name__ == '__main__':
  for k in xrange(2000):
#      results = pool_map(send,[imgs[0] for _ in range(100)])
#      results_1 = pool_map(detect,[imgs[0] for i in xrange(100)])
#      print results_1
#      results_2 = pool_map(feature,[faceids[0] for i in xrange(500)])
#      print results_2
#      results_3 = pool_map(compare,[faceids[0] for i in xrange(500)])
#      print results_3
      threads = []
      for i in xrange(500):
        threads.append(threading.Thread(target = detect,args = (imgs[0],))
        threads.append(threading.Thread(target = feature,args = (faceids[0],))
        threads.append(threading.Thread(target = compare,args = (faceids[0],))
      for j in threads:
          j.start()
      for p in threads:
          p.join()

