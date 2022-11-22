package com.example.nativelib

import android.graphics.Bitmap

class NativeLib {

    /**
     * A native method that is implemented by the 'nativelib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun checkBitmap(bitmap: Bitmap, modelPath:String):Int

    external fun readModel(filePath:String):String

    companion object {
        // Used to load the 'nativelib' library on application startup.
        init {
            System.loadLibrary("nativelib")
        }
    }
}