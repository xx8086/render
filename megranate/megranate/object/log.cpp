//
//  log.cpp
//  megranate
//
//  Created by liu on 2018/7/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "log.hpp"
#include <stdio.h>
#include <stdarg.h>

namespace megranate {
    void log_printf (const char *formatStr, ... ){
        va_list params;
        char buf[BUFSIZ];
        
        va_start ( params, formatStr );
        vsprintf ( buf, formatStr, params );
        
#ifdef ANDROID
        __android_log_print ( ANDROID_LOG_INFO, "esUtil" , "%s", buf );
#else
        printf ( "%s", buf );
#endif
        
        va_end ( params );
    }
}
