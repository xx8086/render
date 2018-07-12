//
//  timer.hpp
//  megranate
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef timer_hpp
#define timer_hpp

#include <stdio.h>
#include <chrono>
#include "base_type.h"
namespace megranate {
    class Timer
    {
    public:
        Timer();
        ~Timer();
    public:
        mg_float interval_ms();
        mg_void set_count_time(mg_int ms);
        mg_bool count_time();//每隔ms毫秒返回true,在ms时间内返回都是false
        mg_bool count_time_loop();
        
    private:
        mg_int _ms_count = 0;
        std::chrono::system_clock::time_point _aysnc_ms_count;
    };
}

#endif /* timer_hpp */
