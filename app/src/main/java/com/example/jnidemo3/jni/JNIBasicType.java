package com.example.jnidemo3.jni;

public class JNIBasicType {
    static {
        System.loadLibrary("native-lib");
    }

    public native int callNativeInt(int n);

    public native byte callNativeByte(byte b);

    public native char callNativeChar(char b);

    public native short callNativeShort(short b);

    public native long callNativeLong(long b);

    public native float callNativeFloat(float b);

    public native double callNativeDouble(double b);

    public native boolean callNativeBoolean(boolean b);

}
