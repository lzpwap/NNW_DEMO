//
// Created by lzp_w on 2022/11/17.
//

#ifndef HOTFIXDEMO_BITMAPUTILS_H
#define HOTFIXDEMO_BITMAPUTILS_H

#endif //HOTFIXDEMO_BITMAPUTILS_H
#include<iostream>
#include <nnw.h>
class BitmapUtils{
private:
    NeuralNetwork * innerModel = nullptr;
public:
    int processBitmap(JNIEnv *env,jobject bitmap,jstring modelPath);
    NeuralNetwork * getModel(const char* modelPath);
};
