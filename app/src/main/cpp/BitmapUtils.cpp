//
// Created by lzp_w on 2022/11/17.
//
#include <android/bitmap.h>
#include <android/log.h>
#include "BitmapUtils.h"
#include <armadillo>
#include "and_log.hpp"

void doOther(NeuralNetwork * model){
    FILE* test;
    test = fopen("/data/data/com.lzzzp.myapplication/cache/test.data","rb");
    auto* testX = (double*)malloc(8*static_cast<size_t>(784));
    if(testX!= nullptr) return;
    size_t readSize = fread(testX, static_cast<size_t>(8), static_cast<size_t>(784), test);
    if(readSize==784){
        arma::vec v(testX,784,false, true);
        LOGD("额外的预测结果%d", model->predict(v));
    }
    fclose(test);
}
int BitmapUtils::processBitmap(JNIEnv *env,jobject bitmap,jstring modelPath){
    AndroidBitmapInfo bitmapInfo;
    if(ANDROID_BITMAP_RESULT_SUCCESS!=AndroidBitmap_getInfo(env,bitmap,&bitmapInfo)){
        return -2;
    }
    void* srcBuf;
    if(ANDROID_BITMAP_RESULT_SUCCESS!=AndroidBitmap_lockPixels(env,bitmap,&srcBuf)){
        return -2;
    }
    size_t w = bitmapInfo.width;
    size_t h = bitmapInfo.height;
    auto* srcPixel = (int32_t *)srcBuf;
    auto* xPixel = (double *)malloc(8*w*h);
    int alpha = 0xFF << 24;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            int color = srcPixel[i*h+j];
            int red = (color & 0x00FF0000)>>16;
            int green = (color & 0x0000FF00)>>8;
            int blue = (color & 0x000000FF);
            //转换为黑白图
            color = 255 - (red+green+blue)/3;
            //处理输入数据,均值归一化
            xPixel[i*h+j] = color * (1.0/255.0);
            color = alpha | (color<<16) | (color <<8) | color;
            srcPixel[i*h+j] = color;
        }
    }
    AndroidBitmap_unlockPixels(env,bitmap);
    const char * modelPathCS = env->GetStringUTFChars(modelPath,JNI_FALSE);
    NeuralNetwork* model = this->getModel(modelPathCS);
    arma::vec v(xPixel, w * h, false, false);
    int result = model->predict(v);
    LOGD("预测结果%s", std::to_string(result).c_str());
    //doOther(model);
    return result;
}

NeuralNetwork * BitmapUtils::getModel(const char* modelPath){
    if(innerModel== nullptr){
        innerModel = new NeuralNetwork(modelPath);
        innerModel->initModel();
    }
    return innerModel;
}


