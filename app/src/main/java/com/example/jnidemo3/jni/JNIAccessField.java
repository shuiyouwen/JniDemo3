package com.example.jnidemo3.jni;

public class JNIAccessField {
    static {
        System.loadLibrary("native-lib");
    }

    public native void accessFile(Person person);
}
