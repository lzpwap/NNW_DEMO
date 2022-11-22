//
// Created by lzp_w on 2022/11/19.
//

#ifndef HOTFIXDEMO_AND_LOG_H
#define HOTFIXDEMO_AND_LOG_H

#endif //HOTFIXDEMO_AND_LOG_H

#include <android/log.h>
#define TAG "JNITEST"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)