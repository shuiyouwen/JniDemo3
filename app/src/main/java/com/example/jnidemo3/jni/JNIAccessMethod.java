package com.example.jnidemo3.jni;

public class JNIAccessMethod {
    static {
        System.loadLibrary("native-lib");
    }

    public native void accessMethod(Person person);

    public native void accessStaticMethod(Person person);
}
