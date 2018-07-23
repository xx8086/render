//
//  string_hash.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "string_hash.hpp"

namespace megranate {
    static const mg_int CONVERSION_BUFFER_LENGTH = 128;
    static const mg_int MATRIX_CONVERSION_BUFFER_LENGTH = 256;
    const StringHash StringHash::ZERO;
    
    StringHash::StringHash(const char* str) :
    _hash_value(calculate(str)){
    }
    
    StringHash::StringHash(const std::string& str) :
    _hash_value(calculate(str.c_str())){
    }
    
    mg_unsigned StringHash::sdb_hash(mg_unsigned hash, mg_uchar c) {
        return c + (hash << 6) + (hash << 16) - hash;
    }
    
    mg_unsigned StringHash::calculate(const mg_char* str){
        mg_unsigned hash = 0;
        if (!str){
            return hash;
        }
        
        while (*str){
            mg_char c = *str;
            hash = sdb_hash(hash, (mg_uchar)tolower(c));
            ++str;
        }
        
        return hash;
    }
    
    std::string StringHash::to_std_string() const{
        mg_char temp_buffer[CONVERSION_BUFFER_LENGTH];
        sprintf(temp_buffer, "%08X", _hash_value);
        return std::string(temp_buffer);
    }

}
