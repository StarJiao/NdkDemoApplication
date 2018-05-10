//
// Created by star on 18-3-22.
//

#ifndef MYAPPLICATION_JNI_LOG_H
#define MYAPPLICATION_JNI_LOG_H

#ifdef __cplusplus
extern "C" {
#endif
#include <android/log.h>
// 宏定义类似java 层的定义,不同级别的Log LOGI, LOGD, LOGW, LOGE, LOGF。 对就Java中的 Log.i log.d
#define LOG_TAG    "JNILOG" // 这个是自定义的LOG的标识
//#undef LOG // 取消默认的LOG
//log_info一个单一的char *str LOGI(const char *);
#define LOGI(...)  __android_log_write(ANDROID_LOG_INFO,LOG_TAG, __VA_ARGS__)
//log_debug一个格式化的字符串  LOGD("%s%d", char *, int );
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG, __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG, __VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif //MYAPPLICATION_JNI_LOG_H
