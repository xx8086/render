//
//  single.h
//  megranate
//
//  Created by liu on 2018/7/13.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef single_h
#define single_h

#include <stdio.h>
#include<stdlib.h>
#include "context.h"

namespace megranate {
    template <class T>
    class Singleton
    {
    public:
        inline static T* get_instance(){
            if (_s_instance_prt == nullptr){
                Context* c = new Context;
                _s_instance_prt = new T(c);
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
}

#endif /* single_h */
