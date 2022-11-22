package com.lzzzp.myapplication

import android.graphics.Bitmap
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.nativelib.NativeLib
import java.io.File

class NnwDemoActivity : AppCompatActivity() {
    private val tvResult by lazy {
        findViewById<TextView>(R.id.tv_result)
    }
    private val btnPredict by lazy {
        findViewById<Button>(R.id.btn_predict)
    }
    private val btnClear by lazy {
        findViewById<Button>(R.id.btn_clear)
    }
    private val handWriteView by lazy {
        findViewById<HandWriteView>(R.id.hv_write)
    }

    private val nativeLib by lazy {
        NativeLib()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.layout_nnw_demo)
        btnPredict.setOnClickListener {
            doPredict()
        }
        btnClear.setOnClickListener {
            handWriteView.clear()
            tvResult.text = "继续试试"
        }
    }

    private fun doPredict() {
        val drawBitmap = handWriteView.getDrawBitmap()
        if (drawBitmap != null) {
            val newScaleBitmap = Bitmap.createScaledBitmap(drawBitmap, 28, 28, false)
            val absolutePath = cacheDir?.absolutePath
            val path = absolutePath + File.separator + "model.ml"
            if (getModelReady(path)) {
                val checkBitmap = nativeLib.checkBitmap(newScaleBitmap, path)
                if (checkBitmap < 0) {
                    tvResult.text = "没识别出来"
                } else {
                    tvResult.text = "我猜你写的是$checkBitmap"
                }
                handWriteView.drawNewBitmap(newScaleBitmap)
            } else {
                Toast.makeText(this, "模型未找到", Toast.LENGTH_SHORT).show()
            }
        }
    }

    private fun getModelReady(path: String): Boolean {
        try {
            val modelFile = File(path)
            if (!modelFile.exists()) {
                if (modelFile.createNewFile()) {
                    //把assets的模型导入到缓存中.
                    val modelIs = resources?.assets?.open("model.ml") ?: return false
                    val modelOs = modelFile.outputStream() ?: return false
                    val buf = ByteArray(2048)
                    while (modelIs.read(buf) > 0) {
                        modelOs.write(buf)
                    }
                    modelIs.close()
                    modelOs.close()
                    return true
                }
            }
        } catch (e: Throwable) {
            return false
        }
        return true
    }
}