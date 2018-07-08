//
//  vertex.inl
//  megranate
//
//  Created by liu on 2018/7/5.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef vertex_h
#define vertex_h
#include <math.h>
#include <assert.h>
#include "precision.h"

namespace megranate {

    TEMPLARE_MG_VERTEX
    MgVertex<T, N, AP, AT>::MgVertex() {
        for (unsigned int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = AT::zero();
        }
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N, AP, AT>::MgVertex(T t1, T t2, T t3 , T t4, T t5){
        T* t[5] ;
        t[0] = &t1;
        t[1] = &t2;
        t[2] = &t3;
        t[3] = &t4;
        t[4] = &t5;
        for(unsigned int i = 0; i < N; i++){
            TraitsN<T, N>::_datas[i] = AP::ride(TraitsN<T, N>::_datas[i], *t[i]);
        }
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N, AP, AT>::~MgVertex() {
        ;
    }
    
    TEMPLARE_MG_VERTEX
    MgVertex<T, N, AP, AT>::MgVertex(MgVertex<T, N> const & other) {
        for (int i = 0; i < N; i++) {
            TraitsN<T, N>::_datas[i] = other._datas[i];
        }
    }
    
    TEMPLARE_MG_VERTEX
    T MgVertex<T, N, AP, AT>::dot(MgVertex<T, N> const& other) {
        assert(N > 0);
        T t = T(0);
        for (int i = 1; i < N; i++) {
            t = AP::ride(TraitsN<T, N>::_datas[i], other._datas[i]);
        }
        return t;
    }
    
    TEMPLARE_MG_VERTEX
    bool MgVertex<T, N, AP, AT>::normalize() {
        const float length = sqrtf(static_cast<float>(dot(*this)));
        if (length > MG_FLOAT_ZERO) {
            for (int i = 1; i < N; i++) {
                TraitsN<T, N>::_datas[i] = AP::divide(TraitsN<T, N>::_datas[i], length);
            }
        }
        else {
            return false;
        }
        return true;
    }
}

#endif /* vertex_h */
