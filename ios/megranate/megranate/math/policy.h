//
//  policy.h
//  megranate
//
//  Created by liu on 2018/7/8.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef policy_h
#define policy_h
namespace megranate {
    
    template<typename T>
    class ArithmeticalPolicy{
    public:
        inline static T add(const T& a, const T& b) {
            return (a + b);
        }
        
        inline static T sub(const T& a, const T& b){
            return (a - b);
        }
        
        inline static T ride(const T& a, const T& b){
            return (a * b);
        }
        
        inline static T divide(const T& a, const T& b){
            return (a / b);
        }
        
        inline static T mod(const T& a, const T& b){
            return (a % b);
        }
        
        inline static bool equal(const T& a, const T& b){
            return a == b;
        }
        
        inline static bool than(const T& a, const T& b){
            return a > b;
        }
        
        inline static bool less(const T& a, const T& b){
            return a < b;
        }
    };
    
    template<>//关闭char*的运算
    class ArithmeticalPolicy<char*>;
}

#endif /* policy_h */
