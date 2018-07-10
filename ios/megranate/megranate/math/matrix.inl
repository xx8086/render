//
//  matrix.inl
//  megranate
//
//  Created by liu on 2018/7/5.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef matrix_inl
#define matrix_inl

namespace megranate {
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N, AP, AT>::~MgMatrix() {
        ;
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N, AP, AT>::MgMatrix(){
        for(unsigned int i = 0; i < M; i ++){
            for(unsigned int j = 0; j < N; j ++){
                _m[i][j];
            }
        }
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N, AP, AT>::MgMatrix(MgMatrix<T, M, N> const & other){
        for(unsigned int i = 0; i < M; i ++){
            for(unsigned int j = 0; j < N; j ++){
                _m[i][j] = other._m[i][j];
            }
        }
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N, AP, AT>::MgMatrix(T t){
        for(unsigned int i = 0; i < M; i ++){
            for(unsigned int j = 0; j < N; j ++){
                _m[i][j] = t;
            }
        }
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N, AP, AT>::MgMatrix(
             T t1, T t2, T t3, T t4,
             T t5, T t6, T t7, T t8,
             T t9, T t10, T t11, T t12,
             T t13, T t14, T t15, T t16){
        T* t[16];
        t[0] = &t1; t[1] = &t2; t[2] = &t3; t[3] = &t4;
        t[4] = &t5; t[5] = &t6; t[6] = &t7; t[7] = &t8;
        t[8] = &t9; t[9] = &t10; t[10] = &t11; t[11] = &t12;
        t[12] = &t13; t[13] = &t14; t[14] = &t15; t[15] = &t16;
        for(unsigned int i = 0; i < M; i ++){
            for(unsigned int j = 0; j < N; j ++){
                _m[i][j] = *t[i * M + j];
            }
        }
    }
    
    TEMPLARE_MG_MATRIX
    MgMatrix<T, M, N> MgMatrix<T, M, N, AP, AT>::transpose() const{
        MgMatrix<T, M, N> n;
        for(unsigned int i = 0; i < M; i ++){
            for(unsigned int j = 0; j < N; j ++){
                n[j][i] = _m[i][j];
            }
        }
        return n;
    }
    
    TEMPLARE_MG_MATRIX
    void MgMatrix<T, M, N, AP, AT>::identity(){
        for(unsigned int i = 0; i < M; i ++){
            for(unsigned int j = 0; j < N; j ++){
                if( i == j){
                    _m[i][j] = 1;
                }
                else{
                    _m[i][j];
                }
            }
        }
    }
    
    TEMPLARE_MG_MATRIX
    void MgMatrix<T, M, N, AP, AT>::set_zero(){
        for(unsigned int i = 0; i < M; i ++){
            for(unsigned int j = 0; j < N; j ++){
                _m[i][j];
            }
        }
    }
}

#endif /* matrix_inl */
