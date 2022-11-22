# NNW_DEMO
一个识别手写数字的神经网络模型,以及安卓端部署


#训练模型脚本
脚本在/train_demo/nn_2.ipynb
model.ml为生成的模型
四个文件夹是对应的训练数据和测试数据

#模型文件部署
模型文件放在/src/assets目录
运行时复制到cache目录中

#native层神经网络模型
文件夹在/src/main/cpp目录
/src/main/cpp/armadillo-lib/armadillo_bits目录下是第三方的线性代数库
神经网络模型定义在nnw.h和nnw.cpp中
应用层桥接在nativelib.cpp
