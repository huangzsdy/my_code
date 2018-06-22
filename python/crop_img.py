#coding:utf-8
import cv2

img = cv2.imread('ILSVRC2012_test_00054645.JPEG')
print img.shape
h=102.529
w=102.529
x=243.112
y=68.882

lines = [line for line in open('ILSVRC2012_val_00012500.txt')]
x_0 = x
y_0 = y
x_1 = x + w
y_1 = y + h

crop_img = img[y_0:y_1,x_0:x_1]
print crop_img.shape
#crop_img = img[0:200,0:400]
cv2.imwrite('crop_img.jpg',crop_img)

