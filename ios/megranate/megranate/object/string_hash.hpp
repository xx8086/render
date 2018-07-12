//
//  string_hash.hpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef string_hash_hpp
#define string_hash_hpp
#include "base_type.h"
#include <string>

namespace megranate {
    class StringHash
    {
    public:
        StringHash() :
        _hash_value(0){
        }
        
        StringHash(const StringHash& rhs) :
        _hash_value(rhs._hash_value){
        }
        
        explicit StringHash(mg_int value) :
        _hash_value(value){
        }
        
        StringHash(const mg_char* str);
        StringHash(const std::string& str);
        
        StringHash& operator =(const StringHash& rhs){
            _hash_value = rhs._hash_value;
            return *this;
        }
        
        StringHash operator +(const StringHash& rhs) const{
            StringHash ret;
            ret._hash_value = _hash_value + rhs._hash_value;
            return ret;
        }
        
        StringHash& operator +=(const StringHash& rhs){
            _hash_value += rhs._hash_value;
            return *this;
        }
        
        mg_bool operator ==(const StringHash& rhs) const { return _hash_value == rhs._hash_value; }
        mg_bool operator !=(const StringHash& rhs) const { return _hash_value != rhs._hash_value; }
        mg_bool operator <(const StringHash& rhs) const { return _hash_value < rhs._hash_value; }
        mg_bool operator >(const StringHash& rhs) const { return _hash_value > rhs._hash_value; }
        
        operator mg_bool() const { return _hash_value != 0; }
        mg_unsigned value() const { return _hash_value; }
        
        std::string to_std_string() const;
        mg_unsigned hash_value() const { return _hash_value; }
        
    public:
        static mg_unsigned sdb_hash(mg_unsigned hash, mg_uchar c);
        static mg_unsigned calculate(const char* str);
        static const StringHash ZERO;
        
    private:
        mg_unsigned _hash_value;
    };
}
#endif /* string_hash_hpp */
