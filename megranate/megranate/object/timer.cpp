//
//  timer.cpp
//  megranate
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "timer.hpp"

namespace megranate {
    Timer::Timer() {
        _aysnc_ms_count = std::chrono::system_clock::now();
    }
    
    Timer::~Timer(){
        ;
    }
    
    float Timer::interval_ms(){
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - _aysnc_ms_count);
        return static_cast<mg_float>(duration.count()) ;
    }
    
    void Timer::set_count_time(mg_int ms) {
        _ms_count = ms;
        _aysnc_ms_count = std::chrono::system_clock::now();
    }
    
    bool Timer::count_time() {
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - _aysnc_ms_count);
        if (duration.count() >= _ms_count) {
            //_aysnc_ms_count = std::chrono::system_clock::now();
            return true;
        }
        return false;
    }
    
    bool Timer::count_time_loop() {
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - _aysnc_ms_count);
        if (duration.count() >= _ms_count) {
            _aysnc_ms_count = std::chrono::system_clock::now();
            return true;
        }
        return false;
    }
}

