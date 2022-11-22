package com.lzzzp.myapplication

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.*
import android.util.AttributeSet
import android.view.MotionEvent
import android.view.View
import androidx.core.graphics.setBlendMode


/**
 * Created by lizhipei on 2022/11/17.
 * description：
 * history：
 */
class HandWriteView : View {
    constructor(context: Context) : super(context)
    constructor(context: Context?, attrs: AttributeSet?) : super(context, attrs)
    constructor(context: Context?, attrs: AttributeSet?, defStyleAttr: Int) : super(
        context,
        attrs,
        defStyleAttr
    )
    constructor(
        context: Context?,
        attrs: AttributeSet?,
        defStyleAttr: Int,
        defStyleRes: Int
    ) : super(context, attrs, defStyleAttr, defStyleRes)

    private val paint = Paint()
    private var drawBitmap: Bitmap? = null
    private var mCanvas: Canvas? = null
    private val path = Path()

    init {
        paint.color = Color.BLACK
        paint.strokeWidth = 28f
        paint.style = Paint.Style.FILL
        paint.strokeJoin = Paint.Join.ROUND
        paint.strokeCap = Paint.Cap.ROUND
        val bmf = BlurMaskFilter(30f, BlurMaskFilter.Blur.SOLID)
        paint.maskFilter = bmf
    }

    override fun onMeasure(widthMeasureSpec: Int, heightMeasureSpec: Int) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec)
        if (drawBitmap == null) {
            mCanvas = Canvas(
                Bitmap.createBitmap(measuredWidth, measuredHeight, Bitmap.Config.ARGB_8888).apply {
                    drawBitmap = this
                })
            mCanvas?.drawColor(Color.WHITE)
        }
    }

    private var preX = 0.0f
    private var preY = 0.0f
    @SuppressLint("ClickableViewAccessibility")
    override fun onTouchEvent(event: MotionEvent?): Boolean {
        when (event?.action) {
            MotionEvent.ACTION_DOWN -> {
                preX = event.x ?: 0.0f
                preY = event.y ?: 0.0f
            }
            MotionEvent.ACTION_MOVE -> {
                val newX = event.x ?: 0.0f
                val newY = event.y ?: 0.0f
                mCanvas?.drawLine(preX, preY, newX, newY, paint)
                preX = newX
                preY = newY
                invalidate()
            }
            MotionEvent.ACTION_UP->{
                val newX = event.x ?: 0.0f
                val newY = event.y ?: 0.0f
                mCanvas?.drawLine(preX, preY, newX, newY, paint)
                preX = newX
                preY = newY
                invalidate()
            }
        }
        return true
    }

    override fun onDraw(canvas: Canvas?) {
        drawBitmap?.let { bitmap ->
            canvas?.drawBitmap(bitmap, 0f, 0f, null)
        }
    }

    fun clear() {
        path.reset()
        mCanvas?.drawColor(Color.WHITE)
        mCanvas?.drawPath(path, paint)
        invalidate()
    }

    fun getDrawBitmap(): Bitmap? {
        return drawBitmap
    }

    fun drawNewBitmap(bitmap: Bitmap) {
        val newScaleBitmap = Bitmap.createScaledBitmap(bitmap, measuredWidth, measuredWidth, false)
        mCanvas?.drawBitmap(newScaleBitmap, 0f, 0f, null)
        invalidate()
    }
}