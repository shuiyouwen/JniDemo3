package com.example.jnidemo3.jni;

public class JNIStringType {
    static {
        System.loadLibrary("native-lib");
    }

    public native String getStringFromC(String str);

    public native void handleStringByC(String str);
}
