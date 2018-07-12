//
//  object.cpp
//  megranate
//
//  Created by liu on 2018/7/4.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include "object.h"
#include "context.h"

namespace megranate {
    
    TypeInfo::TypeInfo(const mg_char* typeName, const TypeInfo* baseTypeInfo) :
    _type(typeName),
    _type_name(typeName),
    _base_type_info(baseTypeInfo){
    }
    
    TypeInfo::~TypeInfo(){
    }
    
    mg_bool TypeInfo::is_type_of(StringHash type) const{
        const TypeInfo* current = this;
        while (current){
            if (current->get_type() == type) { return true; }
            current = current->get_base_type_info();
        }
        
        return false;
    }
    
    mg_bool TypeInfo::is_type_of(const TypeInfo* typeInfo) const{
        const TypeInfo* current = this;
        while (current){
            if (current == typeInfo) { return true; }
            current = current->get_base_type_info();
        }
        return false;
    }

    Object::Object(Context* context) :
    _context(context){
    }
    
    Object::~Object(){
    }
    
    mg_bool Object::is_instance_of(StringHash type) const{
        return get_type_info()->is_type_of(type);
    }
    
    mg_bool Object::is_instance_of(const TypeInfo* type_info) const{
        return get_type_info()->is_type_of(type_info);
    }
    
    Object* Object::get_sub_system(StringHash type) const{
        return _context->get_sub_system(type);
    }
}
