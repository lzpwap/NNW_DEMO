#include <nnw.h>
#include <utility>
#include "armadillo"
#include "and_log.hpp"
#include <string>
int NeuralNetwork::predict(const vec& x) const{
    Layer * currentLayer = this->innerLayer;
    vec out = x;
    while (currentLayer != nullptr) {
        out = currentLayer->transform(out);
        currentLayer = currentLayer->nextLayer;
    }
    int result = -1;
    for (int i = 0; i < out.size(); i++) {
        LOGD("%s", std::to_string(out.at(i)).c_str());
        if(out.at(i)>out.at(result)){
            result = i;
        }
    }
    if(out.at(result)<0.3){
        result = -1;
    }
    return result;
}

NeuralNetwork::NeuralNetwork(const char *modelPath) {
    this->modelPath = modelPath;
    this->innerLayer= nullptr;
}

void NeuralNetwork::initModel() {
    FILE* modelFile;
    modelFile = fopen(this->modelPath,"rb");
    LOGD("打开模型文件文件");
    size_t readSize;
    size_t currentReadRow;
    size_t currentReadCol;
    int activationFlag;
    Layer* layerHead = nullptr;
    Layer* currentLayer = nullptr;
    LOGD("模型位置%s",this->modelPath);
    //开辟空间用于读取模型层数
    int* layerCount = (int*)malloc(4);
    readSize = fread(layerCount,4,1,modelFile);
    if(readSize<=0) return;
    LOGD("%d层模型,开始读取",layerCount[0]);
    //开辟空间用于读取三个32位整数的值,分别是矩阵的行和列
    int* readWeightShape = (int*)malloc(4*3);
    if (readWeightShape == nullptr) return;
    for(int i=0;i<layerCount[0];i++){
        if ((readSize = fread(readWeightShape, 4, 3, modelFile)) != 0) {
            if (readSize == 3) {
                currentReadRow = static_cast<size_t>(readWeightShape[0]);
                currentReadCol = static_cast<size_t>(readWeightShape[1]);
                activationFlag = readWeightShape[2];
                size_t fullSize = currentReadRow * currentReadCol;
                //模型权重和偏移量内存分配
                auto* weight = (double*)malloc(8 * fullSize);
                auto* bais = (double*)malloc(8 * currentReadRow);
                if (weight == nullptr || bais== nullptr) {
                    LOGD("权重分配内存失败%d",i);
                    break;
                }
                readSize = fread(weight, 8, fullSize, modelFile);
                if (readSize == fullSize) {
                    auto* newLayer = new Layer();
                    if (currentLayer == nullptr) {
                        layerHead = currentLayer = newLayer;
                    }
                    else {
                        currentLayer->nextLayer = newLayer;
                        newLayer->preLayer = currentLayer;
                        currentLayer = newLayer;
                    }
                    currentLayer->in = currentReadCol;
                    currentLayer->out = currentReadRow;
                    currentLayer->activationFlag = activationFlag;
                    currentLayer->weight = mat(weight,currentReadRow,currentReadCol,false,true);
                    LOGD("开始读取第%d层权重",i+1);
                }else {
                    LOGD("读取权重数量不正确");
                    break;
                }
                readSize = fread(bais,8,currentReadRow,modelFile);
                if(readSize==currentReadRow){
                    currentLayer->bais = vec(bais,currentReadRow,false, true);
                    LOGD("开始读取第%d层偏移",i+1);
                }
            }
        }
    }
    fclose(modelFile);
    this->innerLayer = layerHead;
    LOGD("模型初始化成功");
}
vec sigmoid(const vec& x){
    return (1.0/(1.0+arma::exp(-x)));
}

vec tanh(const vec& x){
    return arma::tanh(x);
}

vec softMax(const vec& x){
    return arma::exp(x)/arma::sum(arma::exp(x));
}

vec linear(vec x){
    return x;
}

vec doActivation(int flag,const vec& x){
    switch (flag) {
        case 1 : return tanh(x);
        case 2 : return sigmoid(x);
        case 3 : return softMax(x);
        default: return linear(x);
    }
}
vec Layer::transform(const vec& x) const {
    vec h = this->weight * x + this->bais;
    return doActivation(this->activationFlag,h);
}