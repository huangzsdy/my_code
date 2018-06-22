#coding:utf-8
#统计旋转框的召回和漏检

import os
import cv2
import sys
import numpy as np
from os import path as osp
from functools import cmp_to_key

gtThreshold = 0.5
mrThreshold = 0.3

def IouCalculate(box1,box2):
    class Point(object):
        def __init__(self, x, y):
            self.x = x
            self.y = y

    def cmp(a, b,c):
            if a.x >= 0 and b.x < 0:
                return -1
            if a.x == 0 and b.x == 0:
                # return a.y > b.y
                if a.y > b.y:
                    return -1
                elif a.y < b.y:
                    return 1
                return 0
            det = (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y)
            if det < 0:
                return 1
            if det > 0:
                return -1
            d1 = (a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y)
            d2 = (b.x - c.x) * (b.x - c.x) + (b.y - c.y) * (b.y - c.y)
            # return d1 > d2
            if d1 > d2:
                return -1
            elif d1 < d2:
                return 1
            return 0
    def GetIntersection(box1,box2):
        ## centerx, centery w, h, thetta
        # rect1 = ((1,1),(2,2),0)
        # rect2 = ((1,2),(2,2),0)
        rect1 = cv2.minAreaRect(box1)
        rect2 = cv2.minAreaRect(box2)

        r1 = cv2.rotatedRectangleIntersection(rect1, rect2)

        # has no intersection
        if r1[0] == 0:
            return 0

        x = 0
        y = 0
        p = []

        len_p = r1[1].shape[0]
        for i in range(len_p):
            p.append(Point(r1[1][i][0][0], r1[1][i][0][1]))
            x += r1[1][i][0][0]
            y += r1[1][i][0][1]

        c = Point(x / len_p, y/len_p)

        key = cmp_to_key(lambda x,y: cmp(x, y,c))
        pp = sorted(p, key=key)
        r = np.full((len_p, 2), 0.0, dtype='float32')
        for i in range(len(pp)):
            print(pp[i].x, pp[i].y)
            r[i][0] = pp[i].x
            r[i][1] = pp[i].y
        intersectArea = cv2.contourArea(r)
        return intersectArea

    box1 = np.array(box1)
    box2 = np.array(box2)
    area1 = cv2.contourArea(box1)
    area2 = cv2.contourArea(box2)
    intersectArea = GetIntersection(box1,box2)

    return float(intersectArea)/(area1 + area2 - intersectArea)

def testIouCalculate():
    box1 = np.array([[0,0],[2,0],[2,2],[0,2]])
    box2 = np.array([[0,1],[2,1],[2,3],[0,3]])
    iouScore = IouCalculate(box1,box2)
    print(iouScore)

# 画框
def plotRect(imgName,boxes):
    resultFolder = './'
    imgName = sys.argv[1]
    imgGt = sys.argv[2]

    dstName = osp.join(resultFolder,imgName.split('/')[-1])
    dst = cv2.imread(imgName)
    for box in boxes:
        for i in range(4):
            cv2.line(dst,(box[i][0],box[i][1]),(box[(i+1)%4][0],box[(i+1)%4][1]),255,0)
    cv2.imwrite(dstName,dst)

## get recall and missrate of a image
def perImage(gtFile,predFile):
    with open(gtFile) as fp1:
        data1 = fp1.read().splitlines()
    gtBoxes = []
    for line in data1:
        if len(line.split()) < 4:
            continue
        points = [int(float((i))) for i in line.split()]
        box = []
        for j in range(0,8,2):
            # print(points)
            x,y = points[j],points[j+1]
            box.append([x,y])
        gtBoxes.append(box)

    with open(predFile) as fp2:
        data2 = fp2.read().splitlines()
    preBoxes = []
    for line in data2:
        points = [int(float((i))) for i in line.split()]
        box = []
        for j in range(0,8,2):
            x,y = points[j],points[j+1]
            box.append([x,y])
        preBoxes.append(box)

    tp = 0
    fp = 0
    for gtBox in gtBoxes:
        for preBox in preBoxes:
            iouScore = IouCalculate(gtBox,preBox)
            if iouScore >= gtThreshold:
                tp += 1
            elif iouScore < mrThreshold:
                fp += 1
    return tp/(float)(len(gtBoxes)),fp/(float)(len(preBox))


def main():
    gtFolder = '/home/xiaoyang/label'
    predFolder = '/home/huangzesang/share/projects/bar-qr-code/test/images/QR_RES/prediction'
    mRecall = 0
    mMissRate = 0
    imgNum = len(os.listdir(gtFolder))

    for img in os.listdir(gtFolder):
        predImg = osp.join(predFolder,img.split('.')[0] + '_prediction')
        print(img,predImg)
        print("calculate recall and missRate between {},{}".format(img,predImg))
        recall,missRate = perImage(osp.join(gtFolder,img),predImg)

        mRecall += recall
        mMissRate += missRate
    print("recall:",(float)(mRecall/imgNum),"missrate:",(float)(mMissRate/imgNum))


main()
# testIouCalculate()
