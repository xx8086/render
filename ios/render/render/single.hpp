//
//  single.hpp
//  render
//
//  Created by liu on 2018/6/26.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef single_hpp
#define single_hpp

#include <stdio.h>
#include<stdlib.h>

template <class T>
class Singleton
{
public:
    inline static T* get_instance(){
        if (_s_instance_prt == nullptr){
            _s_instance_prt = new T;
            //atexit(destroy_instance);
        }
        
        return _s_instance_prt;
    }
    
    inline static void destroy_instance(){
        if (_s_instance_prt != nullptr){
            delete _s_instance_prt;
            _s_instance_prt = nullptr;
        }
        _s_instance_prt = nullptr;
    }
    
protected:
    Singleton() {}
    Singleton(const Singleton& sing) {}
    Singleton& operator=(const Singleton&) {}
    
    virtual ~Singleton(){
    }
private:
    static T* _s_instance_prt;
};

template <class T>
T* Singleton<T>::_s_instance_prt = nullptr;

#endif /* single_hpp */
