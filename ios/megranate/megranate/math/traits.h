//
//  traits.h
//  megranate
//
//  Created by liu on 2018/7/8.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef traits_h
#define traits_h
namespace megranate {
    template <typename T>
    class Traits;
    
    template<>
    class Traits<float>{
    public:
        typedef float TraitsType;
        static TraitsType const zero(){ return 0.0f;}
        //一般在类内部只能对整形或枚举类型初始化静态成员变量，所以使用静态函数。
    };
    
    template<>
    class Traits<int>{
    public:
        typedef int TraitsType;
        static TraitsType const zero(){ return 0;}
    };
    
    template<>
    class Traits<double>{
    public:
        typedef double TraitsType;
        static TraitsType const zero(){ return 0.0;}
    };
    
//-----------
    template<typename T , unsigned int N>
    class TraitsN{
    public:
        T* _datas;
    };
    
    template<typename T>
    class TraitsN<T, 2>{
    public:
        union{
            struct{T x, y;};
            struct{T r, g;};
            struct{T q, s;};
            T _datas[2];
        };
    };
    
    template<typename T>
    class TraitsN<T, 3>{
    public:
        union{
            struct{T x, y, z;};
            struct{T r, g, b;};
            struct{T q, s, t;};
            T _datas[3];
        };
    };
    
    template<typename T>
    class TraitsN<T, 4>{
    public:
        union{
            struct{T x, y, z, w;};
            struct{T r, g, b, a;};
            struct{T q, s, t, p;};
            T _datas[4];
        };
    };
    
//--------

}

#endif /* traits_h */
