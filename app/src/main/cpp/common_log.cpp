//
// Created by star on 18-5-10.
//

#include "jni_log.h"
#include <sstream>

using namespace std;

static stringstream ss;

template<class T>
void T_log_i(T t) {
    ss << t;
    LOGI(ss.str().c_str());
    ss.str("");
}