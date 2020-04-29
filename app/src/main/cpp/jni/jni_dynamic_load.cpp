//
// Created by admin on 2020-04-27.
//

#include <jni.h>
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

jint get_random_num(JNIEnv *env) {
    return rand();
}

jstring get_native_string(JNIEnv *env) {
    return env->NewStringUTF("jni动态加载的字符串，嘿嘿嘿");
}

/**
 * 需要注册的函数列表，放在JNINativeMethod类型的数组中，以后如果需要增加函数，只需在这里添加就行了
 * 参数：
 * 1、java代码中用native关键字声明的函数名字符串
 * 2、签名（传进来参数类型和返回值类型的说明）
 * 3、C/C++中对应函数的函数名（地址）
 */
static JNINativeMethod getMethods[] = {
        {"getRandomNum",    "()I",                  (void *) get_random_num},
        {"getNativeString", "()Ljava/lang/String;", (void *) get_native_string}
};

/**
 * 此函数通过调用JNI中 RegisterNatives 方法来注册我们的函数
 * @param env
 * @param className
 * @param methods
 * @param nMethods
 * @return
 */
static int registerNativeMethods(JNIEnv *env, const char *className, const JNINativeMethod *methods,
                                 jint nMethods) {
    jclass clazz;
    //找到声明native方法的类
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, methods, nMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static int registerNatives(JNIEnv *env) {
    const char *className = "com/example/jnidemo3/load/JNIDynamicLoad";
    return registerNativeMethods(env, className, getMethods,
                                 sizeof(getMethods) / sizeof(getMethods[0]));
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    //判断虚拟机状态是否有问题
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    assert(env != NULL);
    if (!registerNatives(env)) {
        return -1;
    }
    return JNI_VERSION_1_6;
}