//
//  matrix.inl
//  megranate
//
//  Created by liu on 2018/7/5.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#pragma once

namespace megranate {
#define EXTENDED_IMPLEMENTATION_MgMatrix
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>::~MgMatrix() {
        ;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>::MgMatrix(){
        for(unsigned int i = 0; i < M;, i ++){
            for(unsigned int j = 0; j < N;, j ++){
                _m[i][j] = AT::zero();
            }
        }
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>::MgMatrix(MgMatrix<T, M, N> const & other){
        for(unsigned int i = 0; i < M;, i ++){
            for(unsigned int j = 0; j < N;, j ++){
                _m[i][j] = other._m[i][j];
            }
        }
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>::MgVertex(T t){
        for(unsigned int i = 0; i < M;, i ++){
            for(unsigned int j = 0; j < N;, j ++){
                _m[i][j] = t;
            }
        }
    }
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N>::MgVertex(T t1, T t2, T t3, T t4,
             T t5 = AT::zero(), T t6 = AT::zero(), T t7 = AT::zero(), T t8 = AT::zero(),
             T t9 = AT::zero(), T t10 = AT::zero(), T t11 = AT::zero(), T t12 = AT::zero(),
             T t13 = AT::zero(), T t14 = AT::zero(), T t15 = AT::zero(), T t16 = AT::zero()){
        T* t[16]
        t[0] = &t1; t[1] = &t2; t[2] = &t3; t[3] = &t4;
        t[4] = &t5; t[5] = &t6; t[6] = &t7; t[7] = &t8;
        t[8] = &t9; t[9] = &t10; t[10] = &t11; t[11] = &t12;
        t[12] = &t13; t[13] = &t14; t[14] = &t15; t[15] = &t16;
        for(unsigned int i = 0; i < M;, i ++){
            for(unsigned int j = 0; j < N;, j ++){
                _m[i][j] = *(t + i * m + j);
            }
        }
    }
    
    template <typename T, unsigned int M, unsigned int N>
    MgMatrix<T, M, N>::MgMatrix() {
        for (unsigned int line = 0; line < _line; line++) {
            for (unsigned int col = 0; col < _col; col++) {
                _datas[line][col] = 0;
            }
        }
    }    
    
}
