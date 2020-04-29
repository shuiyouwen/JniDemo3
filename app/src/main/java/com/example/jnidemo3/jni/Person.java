package com.example.jnidemo3.jni;

import android.util.Log;

public class Person {
    public static int age = 18;
    public String name = "小明";

    @Override
    public String toString() {
        return "Person{" +
                "age=" + age +
                ", name='" + name + '\'' +
                '}';
    }

    public String callMethod(String str) {
        if (str != null) {
            Log.d("jni_proctice", "call method with " + str);
        } else {
            Log.d("jni_proctice", "call method with null");
        }
        return "";
    }

    public static String callStaticMethod(String[] strs, int num) {
        if (strs != null) {
            for (String str : strs) {
                Log.d("jni_proctice", "str is:" + str);
            }
        }
        return "";
    }
}
