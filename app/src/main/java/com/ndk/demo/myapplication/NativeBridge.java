package com.ndk.demo.myapplication;

import android.util.Log;

/**
 * Created by star on 18-3-22.
 */

public class NativeBridge {
    static {
        System.loadLibrary("native_demo");
    }

    public static native String stringFromJNI();

    //jni层加法并返回结果
    public static native int nativeAdd(int a, int b);

    //在jni层打印log
    public static native void nativeLog(String content);

    //传递数组
    public static native void setArray(float[] bytes, int len);

    public static native void setObject(BeanDemo bean);

    public native void classOrInstance();

    //给jni调用的类函数
    public static int javaClassAdd(int a, int b) {
        Log.i("jni_test", "java_log:a+b=" + (a + b));
        return a + b;
    }

    //给jni调用的成员函数
    public int javaMemberAdd(int a, int b) {
        return a + b;
    }
}
