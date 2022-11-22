import struct
import numpy as np
#加载训练数据
trainSetInputPath = ".\\train-images-idx3-ubyte\\train-images.idx3-ubyte"
trainSetLabelPath = ".\\train-labels-idx1-ubyte\\train-labels.idx1-ubyte"
testSetInputPath = ".\\t10k-images-idx3-ubyte\\t10k-images.idx3-ubyte"
testSetLabelPath = ".\\t10k-labels-idx1-ubyte\\t10k-labels.idx1-ubyte"
def decodeImages(path):
    bin_data = open(path,'rb').read()
    offset = 0
    fmt_header = '>iiii'
    magic_number,num_images,num_rows,num_cols= struct.unpack_from(fmt_header,bin_data,offset)
    offset += struct.calcsize(fmt_header)
    print('魔数:%d,图片数量:%d,图片大小:%d*%d'%(magic_number,num_images,num_rows,num_cols))
    image_size = num_rows*num_cols
    fmt_image = '>'+str(image_size)+'B'
    images = np.empty((num_images,num_rows,num_cols))
    
    for i in range(num_images):
        arr = np.array(struct.unpack_from(fmt_image,bin_data,offset))
        images[i] = arr.reshape((num_rows,num_cols))
        offset+=struct.calcsize(fmt_image)
    print(images.size)
    # plt.imshow(images[100])
    return images
        
def decodeLabels(path):
    bin_data = open(path,'rb').read()
    offset = 0
    fmt_header = '>ii'
    magic_number,num_images = struct.unpack_from(fmt_header,bin_data,offset)
    offset+=struct.calcsize(fmt_header)
    print('魔数:%d,测试集数量:%d'%(magic_number,num_images))
    tests = np.empty(num_images)
    fmt_test = '>'+str(num_images)+'B'
    tests = np.array(struct.unpack_from(fmt_test,bin_data,offset))
    return tests

def decodeTrainSet():
    images = decodeImages(trainSetInputPath)
    tests = decodeLabels(trainSetLabelPath)
    return (images,tests)
def decodeTestSet():
    images = decodeImages(testSetInputPath)
    tests = decodeLabels(testSetLabelPath)
    return (images,tests)
def decodeAllData1():
    trainImages,trainLabels = decodeTrainSet()
    X = []
    for i in range(0,len(trainImages)):
        X.append(trainImages[i].reshape(28*28,1)* (1/255))
    Y = []
    for i in range(0,len(trainLabels)):
        T = np.zeros((10,1))
        T[trainLabels[i]] = 1 
        Y.append(T)
    testImages,testLabels = decodeTestSet()
    T_X = []
    for i in range(0,len(testImages)):
        T_X.append(testImages[i].reshape(28*28,1)* (1/255))
    return (X,Y,T_X,testLabels)

def decodeAllData2():
    trainImages,trainLabels = decodeTrainSet()
    X = []
    for i in range(0,len(trainImages)):
        X.append(trainImages[i].reshape(1,784)[0]* (1.0/255))
    Y = []
    for i in range(0,len(trainLabels)):
        T = np.zeros((1,10))
        T[0,trainLabels[i]] = 1 
        Y.append(T[0])
    testImages,testLabels = decodeTestSet()
    T_X = []
    for i in range(0,len(testImages)):
        T_X.append(testImages[i].reshape(784,1)* (1/255))
    return (X,Y,T_X,testLabels)
# X,Y,T_X,T_Y = decodeAllData1()
# print(np.size(X[1]))
# print(np.size(Y[1]))