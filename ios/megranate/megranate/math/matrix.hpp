//
//  matrix.hpp
//  megranate
//
//  Created by liu on 2018/7/5.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef matrix_hpp
#define matrix_hpp
#include "traits.h"
#include "policy.h"

namespace megranate {
    #define TEMPLARE_MG_MATRIX template <typename T, unsigned int M, unsigned int N, typename AP, typename AT>
    
    template <typename T,
    unsigned int M,
    unsigned int N,
    typename AP = ArithmeticalPolicy<T>,
    typename AT = Traits<T> >
    class MgMatrix{
    public:
        /*
         0 1 2 ....N
         1
         2
         :
         M
         */
        ~MgMatrix();
        MgMatrix();
        MgMatrix(MgMatrix<T, M, N> const & other);
        MgMatrix(T t);
        MgMatrix(T t1, T t2, T t3, T t4,
                 T t5 = AT::zero(), T t6 = AT::zero(), T t7 = AT::zero(), T t8 = AT::zero(),
                 T t9 = AT::zero(), T t10 = AT::zero(), T t11 = AT::zero(), T t12 = AT::zero(),
                 T t13 = AT::zero(), T t14 = AT::zero(), T t15 = AT::zero(), T t16 = AT::zero());
    public:
        MgMatrix<T, M, N> transpose() const;
        MgMatrix<T, M, N> inverse() const;
        void sacled(MgVertex<T, N> const &) const;
        void set_rotation(MgVertex<T, N> const &) const;
        void set_translation(MgVertex<T, N> const &) const;
        void identity();
        void set_zero();
        
        
        bool operator== (MgMatrix<T, M, N> const&);
        MgMatrix<T, M, N>& operator= (MgMatrix<T, M, N> const&);
        
        MgMatrix<T, M, N> operator+ (MgMatrix<T, M, N> const&) const;
        MgMatrix<T, M, N> operator- (MgMatrix<T, M, N> const&) const;
        MgMatrix<T, M, N> operator* (MgMatrix<T, M, N> const&) const;
        MgMatrix<T, M, N> operator/ (MgMatrix<T, M, N> const&) const;
        MgMatrix<T, M, N> operator% (MgMatrix<T, M, N> const&) const;
        MgMatrix<T, M, N> operator+ (T const&);
        MgMatrix<T, M, N> operator- (T const&);
        MgMatrix<T, M, N> operator* (T const&);
        MgMatrix<T, M, N> operator/ (T const&);
        MgMatrix<T, M, N> operator% (T const&);
        MgMatrix<T, M, N>& operator+= (MgMatrix<T, M, N> const&);
        MgMatrix<T, M, N>& operator-= (MgMatrix<T, M, N> const&);
        MgMatrix<T, M, N>& operator*= (MgMatrix<T, M, N> const&);
        MgMatrix<T, M, N>& operator/= (MgMatrix<T, M, N> const&);
        MgMatrix<T, M, N>& operator%= (MgMatrix<T, M, N> const&);
        MgMatrix<T, M, N>& operator+= (T const&);
        MgMatrix<T, M, N>& operator-= (T const&);
        MgMatrix<T, M, N>& operator*= (T const&);
        MgMatrix<T, M, N>& operator/= (T const&);
        MgMatrix<T, M, N>& operator%= (T const&);
    public:
        union{
        T _m[M][N];
        T m[M][N];
        };
    };

}

#include "matrix.inl"
#include "matrix_binary.inl"
#include "matrix_specialization.inl"

#endif /* matrix_hpp */
