#include <jni.h>
#include <string>
#include <People.h>
#include <android/log.h>
#include <pthread.h>

#define TAG "jni_proctice"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__)

using namespace std;
JNIEnv *env;
JavaVM *vm_;
jobject threadObject;
jclass threadClazz;
jmethodID threadMethod;


extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jnidemo3_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    People people;
    string hello = "Hello from C++";
    return env->NewStringUTF(people.getString().c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_jnidemo3_jni_JNIBasicType_callNativeInt(
        JNIEnv *env,
        jobject instance,
        jint num) {
    LOGD("java int value is %d", num);
    return num * 2;
}

extern "C" JNIEXPORT jbyte JNICALL
Java_com_example_jnidemo3_jni_JNIBasicType_callNativeByte(
        JNIEnv *env,
        jobject instance,
        jbyte byte) {
    LOGD("java byte value is %c", byte);
    return byte;
}

extern "C" JNIEXPORT jchar JNICALL
Java_com_example_jnidemo3_jni_JNIBasicType_callNativeChar(
        JNIEnv *env,
        jobject instance,
        jchar c) {
    LOGD("java char value is %c", c);
    return c;
}

extern "C" JNIEXPORT jshort JNICALL
Java_com_example_jnidemo3_jni_JNIBasicType_callNativeShort(
        JNIEnv *env,
        jobject instance,
        jshort sh) {
    LOGD("java short value is %c", sh);
    return sh;
}

extern "C" JNIEXPORT jlong JNICALL
Java_com_example_jnidemo3_jni_JNIBasicType_callNativeLong(
        JNIEnv *env,
        jobject instance,
        jlong l) {
    LOGD("java long value is %d", l);
    return l;
}

extern "C" JNIEXPORT jfloat JNICALL
Java_com_example_jnidemo3_jni_JNIBasicType_callNativeFloat(
        JNIEnv *env,
        jobject instance,
        jfloat f) {
    LOGD("java short value is %f", f);
    return f;
}

extern "C" JNIEXPORT jdouble JNICALL
Java_com_example_jnidemo3_jni_JNIBasicType_callNativeDouble(
        JNIEnv *env,
        jobject instance,
        jdouble f) {
    LOGD("java double value is %f", f);
    return f;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_jnidemo3_jni_JNIBasicType_callNativeBoolean(
        JNIEnv *env,
        jobject instance,
        jboolean f) {
    LOGD("java boolean value is %p", f);
    return f;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jnidemo3_jni_JNIStringType_getStringFromC(JNIEnv *env, jobject instance,
                                                           jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);
    LOGD("from java string:%s", str);
    env->ReleaseStringUTFChars(str_, str);
    return env->NewStringUTF("from c string hello！");
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_jnidemo3_jni_JNIStringType_handleStringByC(JNIEnv *env, jobject instance,
                                                            jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);
    jsize i = env->GetStringLength(str_);
    char buf[128];
    env->GetStringUTFRegion(str_, 0, i - 1, buf);
    LOGD("字符串长度为%d", i);
    LOGD("字符串%s", buf);
    env->ReleaseStringUTFChars(str_, str);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jnidemo3_jni_JNIRefrenceType_handleStringArray(JNIEnv *env, jobject instance,
                                                                jobjectArray objArray) {
    jobject firstObj = env->GetObjectArrayElement(objArray, 0);
    jstring firstStr_ = static_cast<jstring>(firstObj);
    const char *firstStr = env->GetStringUTFChars(firstStr_, 0);
    LOGD("数组长度是：%d", env->GetArrayLength(objArray));
    LOGD("第一个元素是：%s", firstStr);
    env->ReleaseStringUTFChars(firstStr_, firstStr);
    return env->NewStringUTF(firstStr);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_jnidemo3_jni_JNIAccessField_accessFile(JNIEnv *env, jobject instance,
                                                        jobject obj) {
    jclass clazz = env->GetObjectClass(obj);
    jfieldID pId = env->GetFieldID(clazz, "name", "Ljava/lang/String;");
    jstring oldStr_ = static_cast<jstring>(env->GetObjectField(obj, pId));
    const char *oldStr = env->GetStringUTFChars(oldStr_, 0);
    env->ReleaseStringUTFChars(oldStr_, oldStr);
    LOGD("原来的name是：%s", oldStr);
    const char *prefix = "新的值：";
//    char *res = prefix << oldStr;
    env->SetObjectField(obj, pId, env->NewStringUTF(prefix));

    jfieldID ageFiledId = env->GetStaticFieldID(clazz, "age", "I");
    jint age = env->GetStaticIntField(clazz, ageFiledId);
    LOGD("原来的age是：%d", age);
    age *= 2;
    env->SetStaticIntField(clazz, ageFiledId, age * 2);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidemo3_jni_JNIAccessMethod_accessMethod(JNIEnv *env, jobject thiz,
                                                           jobject person) {
    jclass pJclass = env->GetObjectClass(person);
    jmethodID mId = env->GetMethodID(pJclass, "callMethod",
                                     "(Ljava/lang/String;)Ljava/lang/String;");
//    jclass strClass = env->FindClass("java/lang/String");
//    env->GetObjectField()
    env->CallObjectMethod(person, mId, env->NewStringUTF("哈哈哈哈"));
    jstring jstr = NULL;
    env->CallObjectMethod(person, mId, jstr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidemo3_jni_JNIAccessMethod_accessStaticMethod(JNIEnv *env, jobject thiz,
                                                                 jobject person) {
    jclass pJclass = env->GetObjectClass(person);
    jmethodID mId = env->GetStaticMethodID(pJclass, "callStaticMethod",
                                           "([Ljava/lang/String;I)Ljava/lang/String;");
    jclass strClass = env->FindClass("java/lang/String");
    jint length = 20;
    jobjectArray array = env->NewObjectArray(length, strClass, NULL);
    jstring strItem;
    for (int i = 0; i < length; ++i) {
        strItem = env->NewStringUTF("string in native");
        env->SetObjectArrayElement(array, i, strItem);
    }
    env->CallStaticObjectMethod(pJclass, mId, array, length);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidemo3_jni_JNIInvokeMethod_nativeCallback(JNIEnv *env, jobject thiz,
                                                             jobject callback) {
    jobject threadObject = env->NewGlobalRef(
            callback);
    jclass pJclass = env->GetObjectClass(callback);
    jmethodID mId = env->GetMethodID(pJclass, "callback", "()V");
    env->CallVoidMethod(callback, mId);
}

void *threadCallback(void *) {
    JNIEnv *env = nullptr;
    if (vm_->AttachCurrentThread(&env, nullptr) == 0) {
        env->CallVoidMethod(threadObject, threadMethod);
        vm_->DetachCurrentThread();
    }
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnidemo3_jni_JNIInvokeMethod_nativeThreadCallback(JNIEnv *env, jobject thiz,
                                                                   jobject callback) {
    threadObject = env->NewGlobalRef(callback);
    threadClazz = env->GetObjectClass(callback);
    threadMethod = env->GetMethodID(threadClazz, "threadCallback", "()V");
    pthread_t handle;
    pthread_create(&handle, nullptr, threadCallback, nullptr);
}

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *unused) {
    LOGD("JNI_OnLoad...");
    vm_ = vm;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    return JNI_VERSION_1_6;
}
