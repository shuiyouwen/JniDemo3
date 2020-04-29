package com.example.jnidemo3.jni;

public class JNIInvokeMethod {
    static {
        System.loadLibrary("native-lib");
    }

    public native void nativeCallback(ICallback callback);

    public native void nativeThreadCallback(IThreadCallback callback);
}
