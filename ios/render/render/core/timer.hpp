//
//  timer.hpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef timer_hpp
#define timer_hpp

#include <stdio.h>
#include <chrono>

class Timer
{
public:
    Timer();
    ~Timer();
public:
    float interval_ms();
    void set_count_time(int ms);
    bool count_time();//每隔ms毫秒返回true,在ms时间内返回都是false
    bool count_time_loop();

private:
    int _ms_count = 0;
    std::chrono::system_clock::time_point _aysnc_ms_count;
};


#endif /* timer_hpp */
