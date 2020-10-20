import matplotlib.image as mpimg
import numpy as np
from matplotlib import pyplot as plt
import copy

img = mpimg.imread('data\\1600.jpg')
#灰度化
img_array = 0.2989 *img[:, :, 0]+0.5870*img[:, :, 1]+0.1140*img[:, :, 2]
#实现图像矩阵的归一化操作
img_array /= 255
#print(img_array)
row, column = img_array.shape
new_img=img_array.copy()
sobelNum=0
sobelThreshold=0.7
for i in range(1,row-1):
    for j in range(1,column-1):
        sobelNum=abs(img_array[i-1,j+1]+2*img_array[i,j+1]+img_array[i+1,j+1]-img_array[i-1,j-1]-2*img_array[i,j-1]-img_array[i+1,j-1])+\
                 abs(img_array[i-1,j-1]+2*img_array[i-1,j]+img_array[i-1,j+1]-img_array[i+1,j-1]-2*img_array[i+1,j]-img_array[i+1,j+1])
        print(img_array[i-1,j+1],i,j)
        if(sobelNum > sobelThreshold):
            new_img[i,j]=1
        else:
            new_img[i,j]=0
plt.imshow(new_img,cmap='gray')
plt.show()