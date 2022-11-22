#include <jni.h>
#include <string>
#include "BitmapUtils.h"
using namespace std;

extern "C" JNIEXPORT jstring JNICALL Java_com_example_nativelib_NativeLib_stringFromJNI(JNIEnv* env,jobject /* this */) {
    string hello = "hello world";
    return env->NewStringUTF(hello.c_str());
}

BitmapUtils * utils = nullptr;
extern "C" JNIEXPORT jint JNICALL Java_com_example_nativelib_NativeLib_checkBitmap(JNIEnv *env, jobject /* this */, jobject bitmap, jstring modelPath) {
    if(utils == nullptr){
        utils = new BitmapUtils();
    }
    int intResult = utils->processBitmap(env,bitmap,modelPath);
    return intResult;
}

extern "C" JNIEXPORT jstring JNICALL Java_com_example_nativelib_NativeLib_readModel(JNIEnv *env, jobject /* this */, jstring file_path) {
    return env->NewStringUTF("hello world");
}