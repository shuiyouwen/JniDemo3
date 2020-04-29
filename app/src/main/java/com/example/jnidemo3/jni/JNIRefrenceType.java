package com.example.jnidemo3.jni;

public class JNIRefrenceType {
    static {
        System.loadLibrary("native-lib");
    }

    public native String handleStringArray(String[] array);
}
