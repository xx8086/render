//
//  vertex.hpp
//  megranate
//
//  Created by liu on 2018/7/5.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef vertex_hpp
#define vertex_hpp
#include "traits.h"
#include "policy.h"

namespace megranate {    
#define TEMPLARE_MG_VERTEX template <typename T, unsigned int N, typename AP, typename AT>
    
    template <typename T,
    unsigned int N,
    typename AP = ArithmeticalPolicy<T>,
    typename AT = Traits<T> >
    class MgVertex :  public TraitsN<T, N>{
    public:
        ~MgVertex();
        MgVertex();
        MgVertex(MgVertex<T, N> const& other);
        
        MgVertex(T t1, T t2 = AT::zero(), T t3 = AT::zero(), T t4 = AT::zero(), T t5 = AT::zero());
    public:
        T dot(MgVertex<T, N> const& other);
        bool normalize();
        
        MgVertex<T, N>& operator= (MgVertex<T, N> const&);
        bool operator== (MgVertex<T, N> const&);
        
        MgVertex<T, N> operator+ (MgVertex<T, N> const&);
        MgVertex<T, N> operator- (MgVertex<T, N> const&);
        MgVertex<T, N> operator* (MgVertex<T, N> const&);
        MgVertex<T, N> operator/ (MgVertex<T, N> const&);
        MgVertex<T, N> operator% (MgVertex<T, N> const&);
        MgVertex<T, N> operator+ (T const&);
        MgVertex<T, N> operator- (T const&);
        MgVertex<T, N> operator* (T const&);
        MgVertex<T, N> operator/ (T const&);
        MgVertex<T, N> operator% (T const&);
        MgVertex<T, N>& operator+= (MgVertex<T, N> const&);
        MgVertex<T, N>& operator-= (MgVertex<T, N> const&);
        MgVertex<T, N>& operator*= (MgVertex<T, N> const&);
        MgVertex<T, N>& operator/= (MgVertex<T, N> const&);
        MgVertex<T, N>& operator%= (MgVertex<T, N> const&);
        MgVertex<T, N>& operator+= (T const&);
        MgVertex<T, N>& operator-= (T const&);
        MgVertex<T, N>& operator*= (T const&);
        MgVertex<T, N>& operator/= (T const&);
        MgVertex<T, N>& operator%= (T const&);
        
    };
    
#include "vertex.inl"
#include "vertex_binary.inl"
}

#endif /* vertex_hpp */
