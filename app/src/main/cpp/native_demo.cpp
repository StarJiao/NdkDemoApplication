#include <jni.h>
#include <sstream>
#include <string>
#include "jni_log.h"
#include "common_log.cpp"

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_ndk_demo_myapplication_NativeBridge_stringFromJNI(JNIEnv *env, jobject instance) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jint JNICALL
Java_com_ndk_demo_myapplication_NativeBridge_nativeAdd(JNIEnv *env, jobject instance, jint a,
                                                       jint b) {
    return a + b;
}

JNIEXPORT void JNICALL
Java_com_ndk_demo_myapplication_NativeBridge_nativeLog(JNIEnv *env, jobject instance,
                                                       jstring content_) {
    const char *content = env->GetStringUTFChars(content_, 0);
    LOGI(content);
    env->ReleaseStringUTFChars(content_, content);
    //删除本地引用
    env->DeleteLocalRef(content_);
}

JNIEXPORT void JNICALL
Java_com_ndk_demo_myapplication_NativeBridge_setArray(JNIEnv *env, jobject type, jfloatArray bytes_,
                                                      jint len) {
    jfloat *floatArray = env->GetFloatArrayElements(bytes_, JNI_FALSE);

    for (int i = 0; i < len; i++) {
        LOGD("%f", floatArray[i]);
    }

    //释放数组的对象和数据来源
    env->ReleaseFloatArrayElements(bytes_, floatArray, JNI_FALSE);
    //删除本地引用
    env->DeleteLocalRef(bytes_);
}

JNIEXPORT void JNICALL
Java_com_ndk_demo_myapplication_NativeBridge_setObject(JNIEnv *env, jobject type, jobject bean) {
    jclass beanClass = env->GetObjectClass(bean);

    //直接访问类的属性，获取属性值
    jfieldID stringDataID = env->GetFieldID(beanClass, "string", "Ljava/lang/String;");
    jstring nativeString = (jstring) env->GetObjectField(bean, stringDataID);
    const char *stringContent = env->GetStringUTFChars(nativeString, JNI_FALSE);
    T_log_i(stringContent);

    jfieldID intDataID = env->GetFieldID(beanClass, "integer", "I");
    jint nativeIntData = env->GetIntField(bean, intDataID);
    T_log_i(nativeIntData);

    //通过类的成员方法，调用，获取返回值
    jmethodID getStringMethod = env->GetMethodID(beanClass, "getString", "()Ljava/lang/String;");
    jstring str = (jstring) env->CallObjectMethod(bean, getStringMethod);
    const char *stringData = env->GetStringUTFChars(str, JNI_FALSE);
    T_log_i(stringData);

    jmethodID getIntegerMethod = env->GetMethodID(beanClass, "getInteger", "()I");
    jint integerData = env->CallIntMethod(bean, getIntegerMethod);
    T_log_i(integerData);

    jmethodID isBoolMethod = env->GetMethodID(beanClass, "isBool", "()Z");
    jboolean booleanData = env->CallBooleanMethod(bean, isBoolMethod);
    T_log_i(booleanData);

    jmethodID getFloMethod = env->GetMethodID(beanClass, "getFloat", "()F");
    jfloat floatData = env->CallFloatMethod(bean, getFloMethod);
    T_log_i(floatData);

    jmethodID getDouMethod = env->GetMethodID(beanClass, "getDouble", "()D");
    jdouble doubleData = env->CallDoubleMethod(bean, getDouMethod);
    T_log_i(doubleData);

    jmethodID getChMethod = env->GetMethodID(beanClass, "getChar", "()C");
    jchar charData = env->CallCharMethod(bean, getChMethod);
    T_log_i(charData);

    jmethodID getShMethod = env->GetMethodID(beanClass, "getShort", "()S");
    jshort shortData = env->CallShortMethod(bean, getShMethod);
    T_log_i(shortData);

    jmethodID getByMethod = env->GetMethodID(beanClass, "getByte", "()B");
    jbyte byteData = env->CallByteMethod(bean, getByMethod);
    T_log_i(byteData);
}

JNIEXPORT void JNICALL
Java_com_ndk_demo_myapplication_NativeBridge_classOrInstance(JNIEnv *env, jobject instance) {
    //jni方法的第二个参数，如果是jclass（即对应的java方法是static时），当前的ndk插件不支持直接链接，
    // 导致java代码那边编译器报红，虽然不影响编译器，但是还是不爽，所以统一使用jobject接收实参
    //1、如果classOrInstance在java中是静态方法，这里java传过来的应该是jclass，强转
    //jclass javaClass = (jclass) instance;
    //2、如果classOrInstance在java中是成员方法，这里java传过来的应该是jobject，使用jni获取类的类型
    //jclass javaClass = (jclass) env->GetObjectClass(instance);
    //3、或者直接使用签名find到这个类，这种方式同时也适用于要操作使用的类不是当前的java类
    jclass javaClass = (jclass) env->FindClass("com/ndk/demo/myapplication/NativeBridge");

    jmethodID javaClassMethod = env->GetStaticMethodID(javaClass, "javaClassAdd", "(II)I");
    jmethodID javaObjectMethod = env->GetMethodID(javaClass, "javaMemberAdd", "(II)I");
    jobject javaObject = env->AllocObject(javaClass);
    //调用java里面的静态方法
    jint result1 = env->CallStaticIntMethod(javaClass, javaClassMethod, 3, 4);
    //调用java里面的成员方法
    jint result2 = env->CallIntMethod(javaObject, javaObjectMethod, 5, 3);
    T_log_i(result1);
    T_log_i(result2);

    env->DeleteLocalRef(javaObject);
    env->DeleteLocalRef(javaClass);

    //env->DeleteLocalRef(instance);
}

#ifdef __cplusplus
}
#endif